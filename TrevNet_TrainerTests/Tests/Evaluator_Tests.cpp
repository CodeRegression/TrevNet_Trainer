//--------------------------------------------------
// Unit Tests for class Evaluator
//
// @author: Wild Boar
//
// @date: 2023-02-21
//--------------------------------------------------

#include <gtest/gtest.h>

#include <TrevNet_TrainerLib/Evaluator.h>
using namespace NVL_AI;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Confirm that the basic getter functionality is working as expected
 */
TEST(Evaluator_Test, getter_functionality) 
{
	// Setup
	Mat data = (Mat_<double>(3,3) << 2.0, 1.0, 3.0, 1.0, 1.0, 2.0, 7.0, 6.0, 13.0);

	// Execute
	auto evaluator = Evaluator(data, 1, true);
	auto inputs = vector<double>(); evaluator.GetInputs(2, inputs);
	int rows = evaluator.GetRowCount();

	// Compare
	ASSERT_EQ(rows, 3);
	ASSERT_EQ(inputs.size(), 2);
	ASSERT_EQ(inputs[0], 7);
	ASSERT_EQ(inputs[1], 6);
}

/**
 * @brief A single pin output value
 */
TEST(Evaluator_Test, one_pin_value_output)
{
	// Setup
	Mat data = (Mat_<double>(1, 3) << 1.0, 1.0, 2.0);
	auto evaluator = Evaluator(data, 1, true);

	// Execute
	auto outputs = vector<double>();
	evaluator.GetOutputs(0, outputs);

	// Confirm
	ASSERT_EQ(outputs.size(), 1);
	ASSERT_EQ(outputs[0], 2);
}

/**
 * @brief Multiple pin output value
 */
TEST(Evaluator_Test, multi_pin_value_output)
{
	// Setup
	Mat data = (Mat_<double>(1, 4) << 1.0, 1.0, 2.0, 1.0);
	auto evaluator = Evaluator(data, 2, true);

	// Execute
	auto outputs = vector<double>();
	evaluator.GetOutputs(0, outputs);

	// Confirm
	ASSERT_EQ(outputs.size(), 2);
	ASSERT_EQ(outputs[0], 2);
	ASSERT_EQ(outputs[1], 1);
}

/**
 * @brief A single pin index output
 */
TEST(Evaluator_Test, one_pin_index_output)
{
	// Setup
	Mat data = (Mat_<double>(1, 3) << 1.0, 1.0, 2.0);
	auto evaluator = Evaluator(data, 1, false, vector<int> { 3 });

	// Execute
	auto outputs = vector<double>();
	evaluator.GetOutputs(0, outputs);

	// Confirm
	ASSERT_EQ(outputs.size(), 3);
	ASSERT_EQ(outputs[0], 0);
	ASSERT_EQ(outputs[1], 0);
	ASSERT_EQ(outputs[2], 1);
}

/**
 * @brief Multiple pin index output
 */
TEST(Evaluator_Test, multi_pin_index_output)
{
	// Setup
	Mat data = (Mat_<double>(1, 4) << 1.0, 1.0, 2.0, 1.0);
	auto evaluator = Evaluator(data, 2, false, vector<int> {3, 3});

	// Execute
	auto outputs = vector<double>();
	evaluator.GetOutputs(0, outputs);

	// Confirm
	ASSERT_EQ(outputs.size(), 6);
	ASSERT_EQ(outputs[0], 0);
	ASSERT_EQ(outputs[1], 0);
	ASSERT_EQ(outputs[2], 1);
	ASSERT_EQ(outputs[3], 0);
	ASSERT_EQ(outputs[4], 1);
	ASSERT_EQ(outputs[5], 0);
}


/**
 * @brief Row count out of range
 */
TEST(Evaluator_Test, row_out_of_range)
{
	// Setup
	auto expected = string("RowId is out of range");

	Mat data = (Mat_<double>(1, 4) << 1.0, 1.0, 2.0, 0.1);
	auto evaluator = Evaluator(data, 2, false, vector<int> {3, 3});

	auto output = vector<double>();

	// Execute
	try
	{
		evaluator.GetOutputs(1, output);
		FAIL() << "Expected exception: " << expected;
	}
	catch(runtime_error exception)
	{
		ASSERT_EQ(exception.what(), expected);
	}
	catch(...)
	{
		FAIL() << "Expected exception: " << expected;
	}
}