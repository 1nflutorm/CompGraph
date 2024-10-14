#include "CSpline.h"
#include <cassert>

CSpline::CSpline(const CMatrix<double>& matrix)
{
	m_pointCount = matrix.getRowCount();

	m_matrix = matrix;
}

void CSpline::calculateSpline()
{
	double step = 0.01;
	for (double t = 0; t < 1 + step; t += step)
	{
		m_px.push_back(calculatePx(t));
		m_py.push_back(calculatePy(t));
	}
}

QVector<double> CSpline::getPx() const
{
	return m_px;
}

QVector<double> CSpline::getPy() const
{
	return m_py;
}

double CSpline::calculatePx(const float& t)
{
	double result = 0.0f;
	int n = m_pointCount - 1; 
	for (int i = 0; i <= n; i++)
	{
		result = result + m_matrix[i][0] * (factorial(n) / (factorial(i) * factorial(n - i))) * pow(t, i) * pow((1 - t), (n - i));
	}

	return result;
}

double CSpline::calculatePy(const float& t)
{
	double result = 0.0f;
	int n = m_pointCount - 1;
	for (int i = 0; i <= n; i++)
	{
		result = result + m_matrix[i][1] * (factorial(n) / (factorial(i) * factorial(n - i))) * pow(t, i) * pow((1 - t), (n - i));
	}

	return result;
}

int CSpline::factorial(const int& val)
{
	return val > 1 ? val * factorial(val - 1) : 1;
}


