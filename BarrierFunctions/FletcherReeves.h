#pragma once
#ifndef FLETCHERREEVES_H
#define FLETCHERREEVES_H
#include "system.h"
#include "point.h"
#include <vector>
using namespace std;

class FletcherReeves
{
private:
	System Sys;
	Point startPoint;
	Point nextPoint;
	double alpha;
	double beta;
	int spaceSize;
	int curIter;
	vector<vector<double>> S;
public:
	FletcherReeves(System _s, Point _sp) : Sys(_s), startPoint(_sp) {
		spaceSize = _sp.getSpaceSize();
		for(int i = 0; i < spaceSize; i++)
			S.push_back(vector<double>(spaceSize));
		curIter = 0;
	}
	Point minimizeFunc();
	vector<double> gradient(Point x);
	double normVec(vector<double> vec);
	void createS0();
	void findAlpha();
	Point createPoint(double num);
	void findBeta();
	void createSCur();
	Point createNextPoint();
	vector<double> grad_minus_grad();
	double grad_cross_grad(vector<double> gradB);
};

#endif
