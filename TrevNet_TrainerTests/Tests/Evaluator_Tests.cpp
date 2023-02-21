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
 * @brief A single pin output value
 */
TEST(Evaluator_Test, one_pin_value_output)
{
	FAIL() << "Not implemented";

	// Setup

	// Execute

	// Confirm

	// Teardown
}

/**
 * @brief Multiple pin output value
 */
TEST(Evaluator_Test, multi_pin_value_output)
{
	FAIL() << "Not implemented";

	// Setup

	// Execute

	// Confirm

	// Teardown
}

/**
 * @brief A single pin index output
 */
TEST(Evaluator_Test, one_pin_index_output)
{
	FAIL() << "Not implemented";

	// Setup

	// Execute

	// Confirm

	// Teardown
}

/**
 * @brief Multiple pin index output
 */
TEST(Evaluator_Test, multi_pin_index_output)
{
	FAIL() << "Not implemented";

	// Setup

	// Execute

	// Confirm

	// Teardown
}

/**
 * @brief Wrong number of outputs
 */
TEST(Evaluator_Test, index_output_mismatch)
{
	// Setup
	auto expected = string("Not implemented");

	// Execute
	try
	{
		// TODO: Add call here
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
