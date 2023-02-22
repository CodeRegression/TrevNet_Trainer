//--------------------------------------------------
// Unit Tests for class Trainer
//
// @author: Wild Boar
//
// @date: 2023-02-21
//--------------------------------------------------

#include <gtest/gtest.h>

#include <TrevNetLib/Generator/RandomGenerator.h>

#include <TrevNet_TrainerLib/Trainer.h>
using namespace NVL_AI;

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
bool XOR(Network& network, bool input1, bool input2);

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Verify that the trainer is capable of making XOR
 */
TEST(Trainer_Test, train_XOR)
{
	// Setup
	auto logger = NVLib::Logger(1);
	Mat data = (Mat_<double>(4,3) << 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0);
	auto evaluator = Evaluator(data, 1);
	auto generator = NVL_AI::RandomGenerator();
	auto network = NVL_AI::Network(&generator, vector<int> {2, 10, 1});

	auto trainer = Trainer(-1, &logger, &network, &evaluator, nullptr);

	// Execute
	auto success = trainer.Train(400, 0.25, 1e-2);

	// Confirm
	ASSERT_FALSE(XOR(network, 0, 0));
	ASSERT_TRUE(XOR(network, 0, 1));
	ASSERT_TRUE(XOR(network, 1, 0));
	ASSERT_FALSE(XOR(network, 1, 1));
}

//--------------------------------------------------
// Helpers
//--------------------------------------------------

/**
 * @brief Helper wrapper for the XOR call
 * @param network The basis network
 * @param input1 The first input
 * @param input2 The second input
 * @return The output result
 */
bool XOR(Network& network, bool input1, bool input2) 
{
	auto input = vector<double> { input1 ? 1.0 : 0.0, input2 ? 1.0 : 0.0 };
	auto output = vector<double>();
	network.Evaluate(input, output);
	return output[0] > 0.5;
}
