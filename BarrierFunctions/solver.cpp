#include "solver.h"
#include "FletcherReeves.h"
#include <iostream>
double Solver::solve(Point x)
{
	Point xk = x; /* Fletcher-Reeves or Gradient Methoda */
	FletcherReeves FR(S, x);
	xk = FR.minimizeFunc();
	double M = S.getM();
	if (M * S.betaFunc(xk) < 0.001)
	{
		xk.printPoint();
		function<double(Point)> func = S.getTargetFunction();
		std::cout << func(xk) << std::endl;
		system("pause");
		return func(xk); /* RECURSION EXIT? */
	}
	S.setM(M / 2);
	std::cout << "IMSTILL WORKING, M = " << M << endl;
	solve(xk);
}