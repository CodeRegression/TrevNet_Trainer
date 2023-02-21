//--------------------------------------------------
// Implementation of class Trainer
//
// @author: Wild Boar
//
// @date: 2023-02-21
//--------------------------------------------------

#include "Trainer.h"
using namespace NVL_AI;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param sessionId The curent Session Identifier
 * @param logger The logger to show the the process
 * @param network The network that we are training
 * @param evaluator The evaluator that we are dealing with
 * @param codeDash A link to the current code dashboard
 */
Trainer::Trainer(int sessionId, NVLib::Logger * logger, Network * network, Evaluator * evaluator, CodeDash * codeDash) :
	_sessionId(sessionId), _logger(logger), _network(network), _evaluator(evaluator), _codeDash(codeDash)
{
	// Extra implementation can go here
}

//--------------------------------------------------
// Training
//--------------------------------------------------

/**
 * @brief Add the training logic to the system
 * @param Iterations The number of iterations to train at
 * @param threshold The threshold to to determine when the answer is close enough
 * @param learnRate The expected learn rate
 * @return bool Returns a bool
 */
bool Trainer::Train(int Iterations, double threshold, double learnRate)
{
	for (auto epoch = 0; epoch < Iterations; epoch++) 
	{
		SendMessage(NVLib::Formatter() << "Processing Epoch: " << epoch);
		auto total = 0.0;

		for (auto row = 0; row < _evaluator->GetRowCount(); row++) 
		{
			auto inputs = vector<double>(); _evaluator->GetInputs(row, inputs);
			auto outputs = vector<double>(); _evaluator->GetOutputs(row, outputs);
			_network->Update(inputs, outputs, learnRate);
			auto actuals = vector<double>(); _network->Evaluate(inputs, actuals);
			auto error = _evaluator->GetError(outputs, actuals);
			total += error;  
		}

		total /= _evaluator->GetRowCount();
		auto modelString = stringstream(); _network->GetModelString(modelString);
		PostUpdate(epoch, modelString.str(), total);

		if (total < threshold) return true;
	}

	return false;
}

//--------------------------------------------------
// Helper Logic
//--------------------------------------------------

/**
 * @brief Functionality to send messages here
 * @param message The message that we are sending
 */
void Trainer::SendMessage(const string& message) 
{
	if (_codeDash != nullptr) _codeDash->SetMessage(_sessionId, message);
	if (_logger != nullptr) _logger->Log(1, message.c_str());
}

/**
 * @brief Add the logic to pose the update
 * @param epoch The current epoch number
 * @param modelString The model string that we are building
 * @param error The error that we are updating
 */
void Trainer::PostUpdate(int epoch, const string& modelString, double error) 
{
	if (_codeDash != nullptr) 
	{
		_codeDash->UpdateScore(_sessionId, epoch, error);
		_codeDash->UpdateSolution(_sessionId, modelString);
	}
	if (_logger != nullptr) _logger->Log(1, "Current Error: %f", error);
}
