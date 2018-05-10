#pragma once
#ifndef POINT_H
#define POINT_H
#include <vector>
using namespace std;
class Point
{
private:
	vector<double> x; /* Координаты точки в пространстве */
	bool inRegion; /* Нахождение в области */
	int spaceSize; /* Размер пространства */
public:
	Point(vector<double> _x) : x(_x) {
		spaceSize = x.size();
		inRegion = true;
	}
	Point() {}
	/* Getter */
	vector<double> getCoords() { return x; }
	bool getInRegionsStatus() { return inRegion; }
	int getSpaceSize() { return spaceSize; }
	/* Setter */
	void setCoords(vector<double> numbers);
	void setInRegionStatus(bool flag) { inRegion = flag; }
	void setSpaceSize(int number) { spaceSize = number; }
	/* Operator */
	Point operator*(double num);
	Point operator+(Point b);
	/* Utils*/
	void printPoint();
	void printFunction();
};

#endif // !POINT_H

