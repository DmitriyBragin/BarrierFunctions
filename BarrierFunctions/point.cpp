#include "point.h"
#include <iostream>
using namespace std;

void Point::setCoords(vector<double> numbers)
{
	for (int i = 0; i < spaceSize; i++)
	{
		x[i] = numbers[i];
	}
}

void Point::printPoint()
{
	cout << "Point: " << endl;
	for (int i = 0; i < spaceSize; i++)
	{
		cout << "Coord [" << i <<"] : " << x[i] << endl;
	}
}

Point Point::operator*(double num)
{
	vector<double> coords(spaceSize);
	for (int i = 0; i < spaceSize; i++)
	{
		coords[i] = x[i] * num;
	}
	Point P(coords);
	return P;
}

Point Point::operator+(Point b)
{
	vector<double> coords(spaceSize);
	vector<double> bData(spaceSize);
	bData = b.getCoords();
	for (int i = 0; i < spaceSize; i++)
	{
		coords[i] = x[i] + bData[i];
	}
	Point P(coords);
	return P;
}