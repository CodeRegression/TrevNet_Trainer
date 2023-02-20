//--------------------------------------------------
// The main logic for communicating with the code dash library
//
// @author: Wild Boar
//
// @date: 2022-10-24
//--------------------------------------------------

#pragma once

#include <sstream>
#include <unordered_map>
#include <iostream>
using namespace std;

#include <NVLib/StringUtils.h>
#include <NVLib/Formatter.h>

#include "Socket.h"

namespace NVL_AI
{
	class CodeDash
	{
	private:
		string _server;
		string _port;
		string _uri;

		struct Response 
		{ 
			Response(int sessionId, const string& message, const string& error) : SessionId(sessionId), Message(message), Error(error) {}
			int SessionId; 
			string Error; 
			string Message;
		};

	public:
		CodeDash(const string& server, const string& uri, const string& port);

		int CreateSession(const string& algorithmCode, const string& problemCode, const string& machineName);
		void StartSession(int sessionId);
		void PauseSession(int sessionId);
		void EndSession(int sessionId);
		void FailSession(int sessionId, const string& message);
		string GetSessionState(int sessionId);

		void UpdateScore(int sessionId, int epoch, double score);
		void UpdateSolution(int sessionId, const string& solution);
		void SetMessage(int sessionId, const string& message);
		string Ping();

		string GetProblems(const string& searchString);
		string CheckProblem(const string& problemCode);
		string GetProblemDetails(const string& problemCode);
		string GetHash(const string& problemCode);
		string GetFile(const string& problemCode);

		int AddSolution(const string& problemCode, const string& dna, double score, const string& grammar, const string& evaluation, int depth);
		string GetSolutions(const string& problemCode, const string& grammar, const string& evaluation, int depthLimit, int rowLimit);

		string GetAlgorithmDetails(const string& algorithmCode);

		static CodeDash::Response Parse(const string& value);
	private:
		CodeDash::Response FireRequest(const unordered_map<string, string>& parameters);
		string BuildParamString(const unordered_map<string, string>& parameters);

		static string GetTagContent(const string& tag);

		static string Escape(const string& value);
	};
}
