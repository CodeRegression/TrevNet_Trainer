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
	auto test = vector<double> { 0.5 }; auto deltas = vector<double>();
	evaluator.Evaluate(0, test, deltas);

	// Confirm
	ASSERT_EQ(deltas.size(), 1);
	ASSERT_EQ(deltas[0], 1.5);
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
	auto test = vector<double> { 0.5, 2.0 }; auto deltas = vector<double>();
	evaluator.Evaluate(0, test, deltas);

	// Confirm
	ASSERT_EQ(deltas.size(), 2);
	ASSERT_EQ(deltas[0], 1.5);
	ASSERT_EQ(deltas[1], 1.0);
}

/**
 * @brief A single pin index output
 */
TEST(Evaluator_Test, one_pin_index_output)
{
	// Setup
	Mat data = (Mat_<double>(1, 4) << 1.0, 1.0, 2.0);
	auto evaluator = Evaluator(data, 1, false);

	// Execute
	auto test = vector<double> { 0.1, 0.2, 0.9 }; auto deltas = vector<double>();
	auto correct = evaluator.Evaluate(0, test, deltas);

	// Confirm
	ASSERT_EQ(deltas.size(), 3);
	ASSERT_EQ(deltas[0], 0.1);
	ASSERT_EQ(deltas[1], 0.2);
	ASSERT_EQ(deltas[2], 0.1);
	ASSERT_TRUE(correct);
}

/**
 * @brief Multiple pin index output
 */
TEST(Evaluator_Test, multi_pin_index_output)
{
	// Setup
	Mat data = (Mat_<double>(1, 4) << 1.0, 1.0, 2.0, 0.1);
	auto evaluator = Evaluator(data, 2, false);

	// Execute
	auto test = vector<double> { 0.1, 0.2, 0.9, 0.0, 0.3, 0.6 }; auto deltas = vector<double>();
	auto correct = evaluator.Evaluate(0, test, deltas);

	// Confirm
	ASSERT_EQ(deltas.size(), 6);
	ASSERT_EQ(deltas[0], 0.1);
	ASSERT_EQ(deltas[1], 0.2);
	ASSERT_EQ(deltas[2], 0.1);
	ASSERT_EQ(deltas[3], 0.0);
	ASSERT_EQ(deltas[4], 0.7);
	ASSERT_EQ(deltas[5], 0.6);
	ASSERT_FALSE(correct);
}

/**
 * @brief Wrong number of outputs
 */
TEST(Evaluator_Test, index_output_mismatch)
{
	// Setup
	auto expected = string("Input Mismatch");

	Mat data = (Mat_<double>(1, 4) << 1.0, 1.0, 2.0, 0.1);
	auto evaluator = Evaluator(data, 2, false);

	// Execute
	auto test = vector<double> { 0.1 }; auto deltas = vector<double>();

	// Execute
	try
	{
		evaluator.Evaluate(0, test, deltas);
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

/**
 * @brief Row count out of range
 */
TEST(Evaluator_Test, row_out_of_range)
{
	// Setup
	auto expected = string("RowId is out of range");

	Mat data = (Mat_<double>(1, 4) << 1.0, 1.0, 2.0, 0.1);
	auto evaluator = Evaluator(data, 2, false);

	// Execute
	auto test = vector<double> { 0.1, 0.2, 0.9, 0.0, 0.3, 0.6 }; auto deltas = vector<double>();
	// Execute
	try
	{
		auto correct = evaluator.Evaluate(1, test, deltas);
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