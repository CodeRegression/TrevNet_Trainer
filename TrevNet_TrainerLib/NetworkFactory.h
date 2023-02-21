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

#include <TrevNetLib/Network.h>

namespace NVL_AI
{
	class NetworkFactory
	{
	public:
		static Network * Create(const string& configuration);
	};
}