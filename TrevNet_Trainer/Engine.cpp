//--------------------------------------------------
// Implementation code for the Engine
//
// @author: Wild Boar
//
// @date: 2023-02-20
//--------------------------------------------------

#include "Engine.h"
using namespace NVL_App;

//--------------------------------------------------
// Constructor and Terminator
//--------------------------------------------------

/**
 * Main Constructor
 * @param logger The logger that we are using for the system
 * @param parameters The input parameters
 */
Engine::Engine(NVLib::Logger* logger, NVLib::Parameters* parameters) 
{
    // Core Initialization
    _logger = logger; _parameters = parameters;

     // Initialize the size
    _sessionId = -1;

    // Load up code_dash here
    _logger->Log(1, "Connecting to the server machine");
    auto server = ArgUtils::GetString(_parameters, "server");
    auto port = ArgUtils::GetString(_parameters, "port");
    auto uri = ArgUtils::GetString(_parameters, "uri");
    _codeDash = new NVL_AI::CodeDash(server, uri, port);
    auto connection = _codeDash->Ping(); 
    if (connection == string()) throw runtime_error("Connection with server failed");
    _logger->Log(1, "Server connection established");

    _logger->Log(1, "Creating the network");
    auto structure = ArgUtils::GetString(_parameters, "network");
    _network = NVL_AI::NetworkFactory::Create(structure);
    _logger->Log(1, "Network is created");
    _logger->Log(1, "Number of network layers: %i", _network->GetLayers().size());
}

/**
 * Main Terminator 
 */
Engine::~Engine() 
{
    // Close the session (if it has not been closed already)
    if (_sessionId != -1) _codeDash->EndSession(_sessionId);

    // Free Loaded Entities
    if (_problem != nullptr) delete _problem;
    if (_network != nullptr) delete _network;

    // Free parameters and code dash
    delete _parameters;  delete _codeDash;
}

//--------------------------------------------------
// Execution Entry Point
//--------------------------------------------------

/**
 * Entry point function
 */
void Engine::Run()
{
    _logger->Log(1, "Loading problem");
    auto problemCode = ArgUtils::GetString(_parameters, "problem_code"); auto problemFile = ArgUtils::GetString(_parameters, "problem_file");
    _problem = new NVL_AI::ProblemLoader(problemCode, problemFile); _problem->Load(_codeDash);
    _logger->Log(1, "Problem Loaded: %s", _problem->GetDescription().c_str());
    _logger->Log(1, "Number of test records: %i", _problem->GetData().rows);

    _logger->Log(1, "Creating a problem evaluator");
    auto isValueOutput = ArgUtils::GetBoolean(_parameters, "value_output");
    auto outputCount = ArgUtils::GetInteger(_parameters, "output_pins");
    auto outputSizes = vector<int>(); ArgUtils::GetVector(_parameters, "output_sizes", outputSizes);
    auto evaluator = NVL_AI::Evaluator(_problem->GetData(), outputCount, isValueOutput, outputSizes);
    _logger->Log(1, "Evaluator created - confirming row count: %i", evaluator.GetRowCount());

    _logger->Log(1, "Registering a session with CodeDash");
    auto algorithmCode = ArgUtils::GetString(_parameters, "algorithm_code");
    auto machine = ArgUtils::GetString(_parameters, "machine");
    _sessionId = _codeDash->CreateSession(algorithmCode, problemCode, machine);
    _logger->Log(1, "Session Created: %i", _sessionId);    

    _logger->Log(1, "Assembling a trainer");
    auto trainer = NVL_AI::Trainer(_sessionId, _logger, _network, &evaluator, _codeDash);
    _logger->Log(1, "Trainer successfully created");

    _logger->Log(1, "Launching training process");
    _codeDash->StartSession(_sessionId);
    auto iterations = ArgUtils::GetInteger(_parameters, "iterations");
    auto learnRate = ArgUtils::GetDouble(_parameters, "learn_rate");
    auto scoreThresh = ArgUtils::GetDouble(_parameters, "score_thresh");
    auto success = trainer.Train(iterations, scoreThresh, learnRate);
    _codeDash->EndSession(_sessionId);

    if (success) _logger->Log(1, "Training completed with a successful convergence");
    else _logger->Log(1, "Training complete without finding an optimal solution");


}
