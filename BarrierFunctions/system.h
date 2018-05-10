#pragma once
#ifndef SYSTEM_H
#define SYSTEM_H
#include "constraint.h"
#include "point.h"
#include <vector>
#include <functional>
using namespace std;
class System 
{
private:
	int spaceSize;
	int sysStrings = 0;
	double M;
	vector<function<double(Point)>> cons;
	function<double(Point)> targetFunction;
public:
	void addConstraint(Constraint c);
	void setTargetFunction(function<double(Point)> tar) { targetFunction = tar; }
	bool checkRegion(Point x);
	double betaFunc(Point x);
	void setM(double num) { M = num; }
	double getM() { return M; }
	function<double(Point)> getTargetFunction() {return targetFunction; }

};
#endif // ! SYSTEM_H
