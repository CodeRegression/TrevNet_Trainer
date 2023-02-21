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
 * @param logger The logger to show the the process
 * @param network The network that we are training
 * @param evaluator The evaluator that we are dealing with
 */
Trainer::Trainer(NVLib::Logger * logger, Network * network, Evaluator * evaluator)
{
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// Training
//--------------------------------------------------

/**
 * @brief Add the training logic to the system
 * @param Iterations The number of iterations to train at
 * @param threshold The threshold to to determine when the answer is close enough
 * @return bool Returns a bool
 */
bool Trainer::Train(int Iterations, double threshold)
{
	throw runtime_error("Not implemented");
}
