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
 * @param outputSizes The sizes of the various outputs in the case of "Index Out"
 */
Evaluator::Evaluator(Mat& data, int outputs) : _data(data), _outputs(outputs)
{
	if (outputs >= data.cols) throw runtime_error("The number of outputs cannot match the column count");
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
	return _data.rows;
}

/**
 * @brief Retrieve the inputs at a given index
 * @param rowId The index of the row that we want to get the inputs for
 * @param values The values that we are getting from the system
 */
void Evaluator::GetInputs(int rowId, vector<double>& values)
{
	if (rowId < 0 || rowId >= _data.rows) throw runtime_error("RowId is out of range");

	auto dataLink = (double *)_data.data;
	auto index = rowId * _data.cols;

	values.clear();
	for (auto i = 0; i < (_data.cols - _outputs); i++) 
	{
		values.push_back(dataLink[index + i]);
	}
}

//--------------------------------------------------
// Retrieve Outputs
//--------------------------------------------------

/**
 * @brief Retrieve the given outputs for the associated row
 * @param rowId The index of the row that we went to evaluate
 * @param outputValues The values that we are comparing
 */
void Evaluator::GetOutputs(int rowId, vector<double>& outputs)
{
	if (rowId < 0 || rowId >= _data.rows) throw runtime_error("RowId is out of range");

	auto dataLink = (double *)_data.data;
	auto solutionStart = _data.cols - _outputs;

	auto indexStart = rowId * _data.cols + solutionStart;

	outputs.clear();

	for (auto i = 0; i < _outputs; i++) 
	{
		auto index = indexStart + i;
		auto& value = dataLink[index];
		outputs.push_back(value);
	}
}

//--------------------------------------------------
// Error Calculation
//--------------------------------------------------

/**
 * @brief Retrieve the error
 * @param expected The expected value
 * @param actual The actual value
 * @return double The resultant value
 */
double Evaluator::GetError(vector<double>& expected, vector<double>& actual) 
{
if (expected.size() != actual.size()) throw runtime_error("Error evaluation size mismatch");

	auto total = 0.0;

	for (auto i = 0; i < expected.size(); i++) 
	{
		auto error = abs(expected[i] - actual[i]);
		total += error;
	}

	return total / expected.size();
}

/**
 * @brief Retrieve the best value
 * @param values The values that we are getting
 * @return int The resultant value
 */
int Evaluator::GetBestValue(const vector<double>& values) 
{
	auto bestIndex = 0; auto bestScore = values[0];

	for (auto i = 0; i < values.size(); i++) 
	{
		auto currentScore = values[i];
		if (currentScore > bestScore) { bestIndex = i; bestScore = currentScore; }
	}

	return bestIndex;
}
