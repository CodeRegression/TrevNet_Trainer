//--------------------------------------------------
// Unit Tests for class NetworkFactory
//
// @author: Wild Boar
//
// @date: 2023-02-21
//--------------------------------------------------

#include <gtest/gtest.h>

#include <TrevNet_TrainerLib/NetworkFactory.h>
using namespace NVL_AI;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Verify the creation of a network with just a random generation string
 */
TEST(NetworkFactory_Test, random_network_creation)
{
	// Setup
	auto configuration = string("1, 2, 3");

	// Execute
	auto network = NetworkFactory::Create(configuration);

	// Confirm
	ASSERT_EQ(network->GetLayers().size(), 3);
	ASSERT_EQ(network->GetLayers()[0]->GetNodeCount(), 1);
	ASSERT_EQ(network->GetLayers()[1]->GetNodeCount(), 2);
	ASSERT_EQ(network->GetLayers()[2]->GetNodeCount(), 3);

	// Teardown
	delete network;
}
