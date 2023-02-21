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

namespace NVL_AI
{
	class Evaluator
	{
	private:
		Mat _data;
		int _outputs;
		bool _valueOut;
	public:
		Evaluator(Mat& data, int outputs, bool valueOut);

		int GetRowCount();
		void GetInputs(int rowId, vector<double>& values);

		bool Evaluate(int rowId, vector<double>& values, vector<double>& deltas);

		inline int& GetOutputs() { return _outputs; }
		inline bool GetValueOut() { return _valueOut; }
	};
}
