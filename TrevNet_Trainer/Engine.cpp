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
    _machineName = ArgUtils::GetString(_parameters, "machine");
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
}
