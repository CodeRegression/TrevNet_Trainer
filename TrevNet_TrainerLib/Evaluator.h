//--------------------------------------------------
// Evaluates the outputs of the system
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

#include <TrevNetLib/NetworkUtils.h>

namespace NVL_AI
{
	class Evaluator
	{
	private:
		Mat _data;
		int _outputs;
	public:
		Evaluator(Mat& data, int outputs);

		int GetRowCount();
		void GetInputs(int rowId, vector<double>& values);
		void GetOutputs(int rowId, vector<double>& outputs);
		
		double GetError(vector<double>& expected, vector<double>& actual);

		inline int& GetOutputs() { return _outputs; }
	private:
		int GetBestValue(const vector<double>& values);
	};
}
