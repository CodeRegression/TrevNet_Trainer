//--------------------------------------------------
// Create a network
//
// @author: Wild Boar
//
// @date: 2023-02-21
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <NVLib/StringUtils.h>

#include <TrevNetLib/Network.h>
#include <TrevNetLib/Generator/RandomGenerator.h>

namespace NVL_AI
{
	class NetworkFactory
	{
	public:
		static Network * Create(const string& configuration);
	private:
		static void String2Vector(const string& configuration, vector<int>& output);
	};
}