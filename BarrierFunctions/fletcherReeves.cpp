#include "FletcherReeves.h"

vector<double> FletcherReeves::gradient(Point x)
{
	function<double(Point)> tarFunc = Sys.getTargetFunction();
	double lambda = 1e-10;
	vector<vector<double>> normale;
	for (int i = 0; i < spaceSize; i++)
	{
		normale.push_back(vector<double>(spaceSize));
		normale[i][i] = 1;
	}
	vector<Point> lambdaVec(spaceSize);
	for (int i = 0; i < spaceSize; i++)
	{
		lambdaVec[i] = normale[i];
		lambdaVec[i] = lambdaVec[i] * lambda;
	}

	double phi = tarFunc(x) + Sys.getM() * Sys.betaFunc(x); /* phi(x) */

	vector<double> phi_lambda_normale(spaceSize);
	for (int i = 0; i < spaceSize; i++)
	{
		phi_lambda_normale[i] = tarFunc(x + lambdaVec[i]) + Sys.getM() * Sys.betaFunc(x + lambdaVec[i]); /* phi(x + lambda z) */
	}
	vector<double> grad(spaceSize);
	for (int i = 0; i < spaceSize; i++)
	{
		grad[i] = (phi_lambda_normale[i] - phi) / lambda;
	}
	return grad;
}

void FletcherReeves::createS0()
{
	vector<double> grad = gradient(startPoint); /* Производная по направлению численно! */
	for (int i = 0; i < spaceSize; i++)
	{
		S[0][i] = -grad[i];
	}
}

Point FletcherReeves::createPoint(double num)
{
	vector<double> coords(spaceSize);
	for (int i = 0; i < spaceSize; i++)
	{
		coords[i] = S[curIter][i] * num;
	}
	vector<double> x_coords = startPoint.getCoords();
	for (int i = 0; i < spaceSize; i++)
	{
		coords[i] += x_coords[i];
	}
	Point p(coords);
	//p.setCoords(coords);
	return p;
}

void FletcherReeves::createSCur()
{
	for (int i = 0; i < spaceSize; i++)
	{
		S[curIter][i] = S[curIter - 1][i] * beta;
	}
	vector<double> gradNeed = gradient(nextPoint);
	for (int i = 0; i < spaceSize; i++)
	{
		S[curIter][i] -= gradNeed[i];
	}
}

void FletcherReeves::findAlpha()
{
	function<double(Point)> tarFunc = Sys.getTargetFunction();
	double alpha_fib = (sqrt(5) - 1) / 2;
	double a = 0, b = 1;
	double l, m, fl, fm;
	l = a + (1 - alpha_fib) * (b - a);
	m = a + b - l;
	Point pl = createPoint(l);
	Point pm = createPoint(m);
	fl = tarFunc(pl) + Sys.betaFunc(pl);
	fm = tarFunc(pm) + Sys.betaFunc(pl);
	while (fabs(m - l) > .00000001)
	{
		if (fl < fm)
		{
			b = m;
			m = l;
			fm = fl;
			l = a + (1 - alpha_fib) * (b - a);
			pl = createPoint(l);
			fl = tarFunc(pl) + Sys.betaFunc(pl);
		}
		else
		{
			a = l;
			l = m;
			fl = fm;
			m = a + alpha_fib * (b - a);
			pm = createPoint(m);
			fm = tarFunc(pm) + Sys.betaFunc(pm);
		}
	}
	alpha = l;

}

Point FletcherReeves::createNextPoint()
{
	vector<double> coords(spaceSize);
	for (int i = 0; i < spaceSize; i++)
	{
		coords[i] = S[curIter - 1][i] * alpha;
	}
	vector<double> x_coords = startPoint.getCoords();
	for (int i = 0; i < spaceSize; i++)
	{
		coords[i] += x_coords[i];
	}
	Point p(coords);
	return p;
}

double FletcherReeves::normVec(vector<double> vec)
{
	double res = 0;
	for (int i = 0; i < spaceSize; i++)
	{
		res += vec[i] * vec[i];
	}
	res = sqrt(res);
	return res;
}

vector<double> FletcherReeves::grad_minus_grad()
{
	vector<double> gradCur = gradient(nextPoint);
	vector<double> gradPrev = gradient(startPoint);
	vector<double> res(spaceSize);
	for (int i = 0; i < spaceSize; i++)
	{
		res[i] = gradCur[i] - gradPrev[i];
	}
	return res;
}

double FletcherReeves::grad_cross_grad(vector<double> gradB)
{
	double res = 0;
	vector<double> gradCur = gradient(nextPoint);
	for (int i = 0; i < spaceSize; i++)
	{
		res += gradCur[i] * gradB[i];
	}
	return res;
}

void FletcherReeves::findBeta()
{
	beta = 0;
	if ((curIter != 0) &&(curIter % (spaceSize) != 0))
	{
		vector<double> gradCur = gradient(startPoint);
		vector<double> gradPrev = gradient(startPoint);
		vector<double> temp = grad_minus_grad();
		double denominator = normVec(gradCur) * normVec(gradCur);
		double nominator = grad_cross_grad(temp);
		beta = nominator / denominator;
	}
}



Point FletcherReeves::minimizeFunc()
{
	vector<double> grad = gradient(startPoint); /* Производная по направлению численно! */
	double stop = normVec(grad);
	alpha = 0.01;
	stop = 1;
	while (stop > 0.00001)
	{
		if (curIter == spaceSize)
			curIter = 0;
		if (curIter == 0)
		{
			createS0();
			S;
			//findAlpha();
			curIter = 1;
			continue;
		}
		Point tempPoint = createNextPoint();
		if (Sys.checkRegion(tempPoint) == false)
		{
			return startPoint;
		}
		nextPoint = createNextPoint();
		findBeta();
		createSCur();
		//findAlpha();
		curIter++;
		startPoint = nextPoint;
		grad = gradient(nextPoint);;
		stop = normVec(grad);
	}
	return nextPoint;
}
