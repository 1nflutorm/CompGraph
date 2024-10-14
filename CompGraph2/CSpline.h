#pragma once

#include <cmath>
#include <QVector>
#include "Matrix.h"

class CSpline
{
public:
	CSpline(const CMatrix<double>& matrix);
	
	void calculateSpline();
	QVector<double> getPx() const;
	QVector<double> getPy() const;

private:
	double calculatePx(const float& t);
	double calculatePy(const float& t);
	int factorial(const int& val);

private:
	CMatrix<double> m_matrix;

	QVector<double> m_px;
	QVector<double> m_py;

	int m_pointCount;
};

