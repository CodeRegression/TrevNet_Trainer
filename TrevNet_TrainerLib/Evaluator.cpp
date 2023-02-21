//--------------------------------------------------
// Implementation of class Evaluator
//
// @author: Wild Boar
//
// @date: 2023-02-21
//--------------------------------------------------

#include "Evaluator.h"
using namespace NVL_AI;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param data The data that we are testing against
 * @param outputs The number of data fields can be considered outputs
 * @param valueOut Indicates if the truth outputs are values or pin indices
 */
Evaluator::Evaluator(Mat& data, int outputs, bool valueOut)
{
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// Getter
//--------------------------------------------------

/**
 * @brief Retrieve the number of rows we are testing against
 * @return int Returns a int
 */
int Evaluator::GetRowCount()
{
	throw runtime_error("Not implemented");
}

/**
 * @brief Retrieve the inputs at a given index
 * @param rowId The index of the row that we want to get the inputs for
 * @param values The values that we are getting from the system
 */
void Evaluator::GetInputs(int rowId, vector<double>& values)
{
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// Evaluate
//--------------------------------------------------

/**
 * @brief Retrieve the given outputs for the associated row
 * @param rowId The index of the row that we went to evaluate
 * @param values The values that we are comparing
 * @param deltas The deltas produced by the system
 */
void Evaluator::GetOutputs(int rowId, vector<double>& values, vector<double>& deltas)
{
	throw runtime_error("Not implemented");
}
