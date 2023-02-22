//--------------------------------------------------
// Defines a basic engine for a vanilla C++ project.
//
// @author: Wild Boar
//
// @date: 2023-02-20
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <NVLib/Logger.h>

#include <TrevNet_TrainerLib/ArgUtils.h>
#include <TrevNet_TrainerLib/ProblemLoader.h>
#include <TrevNet_TrainerLib/NetworkFactory.h>
#include <TrevNet_TrainerLib/Evaluator.h>
#include <TrevNet_TrainerLib/Trainer.h>

namespace NVL_App
{
	class Engine
	{
	private:
		NVLib::Parameters * _parameters;
		NVLib::Logger* _logger;

		NVL_AI::ProblemLoader * _problem;
		NVL_AI::CodeDash * _codeDash;
		NVL_AI::Network * _network;

		int _sessionId;

	public:
		Engine(NVLib::Logger* logger, NVLib::Parameters * parameters);
		~Engine();

		void Run();
	private:
		void SaveModel(const string& filename);
	};
}
