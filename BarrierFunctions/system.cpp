#include "system.h"
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

void System::addConstraint(Constraint c)
{
	spaceSize = c.getSpaceSize();
	cons.resize(cons.size() + 1);
	cons[cons.size() - 1] = c.getConstraint();
	sysStrings++;
}

bool System::checkRegion(Point x)
{
	for (int i = 0; i < sysStrings; i++)
	{
		double res = cons[i](x);
		if (res > 0)
			return false;
	}
	return true;
}

double System::betaFunc(Point x)
{
	double res = 0;
	for (int i = 0; i < sysStrings; i++)
	{
		double temp = cons[i](x);
		res += log(-temp);
	}
	res *= -1;
	return res;
}
