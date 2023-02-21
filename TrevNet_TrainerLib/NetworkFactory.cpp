//--------------------------------------------------
// Implementation of class NetworkFactory
//
// @author: Wild Boar
//
// @date: 2023-02-21
//--------------------------------------------------

#include "NetworkFactory.h"
using namespace NVL_AI;

//--------------------------------------------------
// Create Network
//--------------------------------------------------

/**
 * @brief Create a network
 * @param configuration The network configuration
 * @return Network * Returns a Network *
 */
Network * NetworkFactory::Create(const string& configuration)
{
	auto initVector = vector<int>(); String2Vector(configuration, initVector);
	auto randomGenerator = RandomGenerator();
	return new Network(&randomGenerator, initVector);
}

//--------------------------------------------------
// Create Network
//--------------------------------------------------

/**
 * @brief Convert the incoming string into a vector  
 * @param configuration The configuration that we are dealing with
 * @param output The output value that we are dealing with
 */
void NetworkFactory::String2Vector(const string& configuration, vector<int>& output) 
{
	// Break the configuration into parts
	auto parts = vector<string>(); NVLib::StringUtils::Split(configuration, ',', parts);

	// Clear the given output
	output.clear();

	// Get the values into the array
	for (auto& entry : parts) 
	{
		auto count = NVLib::StringUtils::String2Int(entry);
		output.push_back(count);
	}
}
