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
#include <NVLib/Formatter.h>

#include <TrevNetLib/Network.h>

#include "Evaluator.h"
#include "CodeDash.h"

namespace NVL_AI
{
	class Trainer
	{
	private:
		int _sessionId;
		NVLib::Logger * _logger;
		Network * _network;
		Evaluator * _evaluator;
		CodeDash * _codeDash;
	public:
		Trainer(int sessionId, NVLib::Logger * logger, Network * network, Evaluator * evaluator, CodeDash * codeDash);
		bool Train(int Iterations, double threshold, double learnRate);
	private:
		void SendMessage(const string& message);
		void PostUpdate(int epoch, const string& modelString, double error);
	};
}
