//--------------------------------------------------
// A tool for training a neural network
//
// @author: Wild Boar
//
// @date: 2023-02-21
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include <NVLib/Logger.h>

#include <TrevNetLib/Network.h>
#include "Evaluator.h"

namespace NVL_AI
{
	class Trainer
	{
	private:
		NVLib::Logger * _logger;
		Network * _network;
		Evaluator * _evaluator;
	public:
		Trainer(NVLib::Logger * logger, Network * network, Evaluator * evaluator);
		bool Train(int Iterations, double threshold);
	};
}
