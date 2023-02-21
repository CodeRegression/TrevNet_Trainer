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
Evaluator::Evaluator(Mat& data, int outputs, bool valueOut, const vector<int>& outputSizes) : _data(data), _outputs(outputs), _valueOut(valueOut), _outputSizes(outputSizes)
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
// Evaluate
//--------------------------------------------------

/**
 * @brief Retrieve the given outputs for the associated row
 * @param rowId The index of the row that we went to evaluate
 * @param values The values that we are comparing
 * @param deltas The deltas produced by the system
 * @return Indicates if the value was "correct" or not
 */
bool Evaluator::Evaluate(int rowId, vector<double>& values, vector<double>& deltas)
{
	if (rowId < 0 || rowId >= _data.rows) throw runtime_error("RowId is out of range");

	auto dataLink = (double *)_data.data;
	auto solutionStart = _data.cols - _outputs;

	auto indexStart = rowId * _data.cols + solutionStart;

	deltas.clear();

	auto success = true;

	if (_valueOut) 
	{
		if (values.size() != _outputs) throw runtime_error("There appears to be a mismatch with the outputs size");

		for (auto i = 0; i < _outputs; i++) 
		{
			auto index = indexStart + i;
			auto& expected = dataLink[index];
			auto& actual = values[i];
			auto delta = NetworkUtils::GetError(expected, actual);
			if (abs(delta) > 1e-4) success = false;
			deltas.push_back(delta);
		}
	}
	else 
	{
		if (_outputSizes.size() != _outputs) throw runtime_error("Output sizes have not been correctly set");

		// Verify the output size
		auto sum = 0; for (auto& value : _outputSizes) sum+= value;
		if (sum != values.size()) throw runtime_error("There appears to be a mismatch with the output sizes");

		int outputOffset = 0;

		for (auto i = 0; i < _outputs; i++) 
		{
			auto index = indexStart + i; 
			auto trueIndex = (int)dataLink[index];
			if (trueIndex < 0 || trueIndex >= _outputSizes[i]) throw runtime_error("True index mismatches with output index");

			for (int j=0; j < _outputSizes[i]; j++) 
			{
				auto expected = (j == trueIndex) ? 1.0 : 0.0;
				auto& actual = values[j + outputOffset]; 
				auto delta = NetworkUtils::GetError(expected, actual);
				auto diff = abs(expected - actual);
				if (abs(diff) > 0.4) success = false;
				deltas.push_back(delta);
			}

			outputOffset += _outputSizes[i];						
		}
	}

	return success;
}
