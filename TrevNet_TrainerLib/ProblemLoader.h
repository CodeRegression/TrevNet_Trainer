//--------------------------------------------------
// Defines the functionality for loading the details associated with the given problem
//
// @author: Wild Boar
//
// @date: 2022-12-28
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include <NVLib/FileUtils.h>
#include <NVLib/ARFF/ARFFReader.h>

#include "CodeDash.h"

namespace NVL_AI
{
	class ProblemLoader
	{
	private:
		int _id;
		string _code;
		string _name;
		string _description;
		string _file;
		string _fileHash;
		Mat _data;

		NVLib::ARFFReader * _reader;
	public:
		ProblemLoader(const string& problemCode, const string& dataFile);
		~ProblemLoader();

		void Load(CodeDash * codeDash);

		inline int& GetId() { return _id; }
		inline string& GetCode() { return _code; }
		inline string& GetName() { return _name; }
		inline string& GetDescription() { return _description; }
		inline string& GetFile() { return _file; }
		inline string& GetFileHash() { return _fileHash; }
		inline Mat& GetData() { return _data; }
		inline NVLib::ARFFHeader * GetFileHeader() { return _reader->GetHeader(); }
	};
}