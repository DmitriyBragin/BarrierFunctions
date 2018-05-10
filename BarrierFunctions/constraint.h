#pragma once
#ifndef CONSTRAINT_H
#define CONSTRAINT_H
#include <vector>
#include <functional>
#include "point.h"
using namespace std;
class Constraint 
{
private:
	int spaceSize;
	function<double(Point)> c;
public:
	/* Getter */
	int getSpaceSize() { return spaceSize; }
	function<double(Point)> getConstraint() { return c; }
	/* Setter */
	void setConstraint(function<double(Point)> _c) { c = _c; }
	void setSpaceSize(int number) { spaceSize = number; }
	/* Utils */
};

#endif // !CONSTRAINT_H
