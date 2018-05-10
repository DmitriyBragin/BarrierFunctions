#include "point.h"
#include "constraint.h"
#include "system.h"
#include <iostream>
#include <vector>
#include "solver.h"

double targetFunction(Point x) /* Целевая функция */
{
	std::vector<double> z(x.getSpaceSize());
	z = x.getCoords();
	return (z[0] - 1.0)*(z[0] - 1.0) + (z[1] - 1.0)*(z[1] - 1.0) + (z[2] - 1.0)*(z[2] - 1.0) + sqrt(z[0]*z[0] + z[1]*z[1] + z[2]*z[2]);
}

double constr1(Point x) /* Ограничение */
{
	std::vector<double> z(x.getSpaceSize());
	z = x.getCoords();
	//return -1;
	return (-z[0]);
}
double constr2(Point x) /* Ограничение */
{
	std::vector<double> z(x.getSpaceSize());
	z = x.getCoords();
	//return -1;
	return (-z[1]);
}
double constr3(Point x) /* Ограничение */
{
	std::vector<double> z(x.getSpaceSize());
	z = x.getCoords();
	//return -1;
	return (z[0]*z[0] + z[1]*z[1] + z[2]*z[2] - 1.0);
}

int main(void)
{
	std::vector<double> coeff(3);
	coeff[0] = 0.1;
	coeff[1] = 0.1;
	coeff[2] = 0.1;
	Point p(coeff);
	Constraint C1,C2,C3;
	C1.setConstraint(constr1);
	C2.setConstraint(constr2);
	C3.setConstraint(constr3);
	System S;
	S.setM(1);
	S.addConstraint(C1);
	S.addConstraint(C2);
	S.addConstraint(C3);
	S.setTargetFunction(targetFunction);
	Solver solver(S);
	solver.solve(p);
	return 0;
}