#pragma once
#include <QVector>
#include <exception>
#include <initializer_list>

template<class T>
class CMatrix
{
public:
	CMatrix();
	CMatrix(const int& row, const int& col);
	CMatrix(const CMatrix<T>& other);
	CMatrix(std::initializer_list< QVector<T> > init);

	QVector<T>& operator[](const int& row);
	CMatrix<T> operator*(CMatrix<T>& other);

	int getRowCount() const;
	int getColCount() const;

	T get(const int& row, const int& col) const;

private:
	QVector< QVector<T> > m_matrix;
	int m_rowCount;
	int m_colCount;
};

template<class T>
inline CMatrix<T>::CMatrix()
{
	m_colCount = 0;
	m_rowCount = 0;
}

template<class T>
inline CMatrix<T>::CMatrix(const int& row, const int& col)
{
	if (row < 1 || col < 1)
	{
		throw std::exception("incorrect matrix size!");
	}

	m_rowCount = row;
	m_colCount = col;

	m_matrix.resize(row);
	for (int i = 0; i < row; i++)
	{
		m_matrix[i] = QVector<T>(col);
	}
}

template<class T>
inline CMatrix<T>::CMatrix(const CMatrix<T>& other)
{
	m_rowCount = other.getRowCount();
	m_colCount = other.getColCount();

	m_matrix.resize(m_rowCount);

	for (int i = 0; i < m_rowCount; i++)
	{
		m_matrix[i].resize(m_colCount);
		for (int j = 0; j < m_colCount; j++)
		{
			m_matrix[i][j] = other.get(i, j);
		}
	}
}

template<class T>
inline CMatrix<T>::CMatrix(std::initializer_list< QVector<T> > init)
{
	m_rowCount = static_cast<int>(init.size());
	m_matrix.resize(init.size());
	
	for (int i = 0; init.begin() + i != init.end(); i++)
	{
		QVector<T> row = *(init.begin() + i);
		m_matrix[i].resize(row.size());
		m_colCount = row.size();
		for (int j = 0; j < row.size(); j++)
		{
			m_matrix[i][j] = row[j];
		}
	}
}

template<class T>
inline QVector<T>& CMatrix<T>::operator[](const int& row)
{
	if (row > m_matrix.size())
	{
		throw std::exception("incorrect matrix index!");
	}

 	return m_matrix[row];
}

template<class T>
inline CMatrix<T> CMatrix<T>::operator*(CMatrix<T>& other)
{
	CMatrix<T> result(m_matrix.size(), other.getRowCount());

	for (int i = 0; i < m_matrix.size(); i++)
	{
		for (int j = 0; j < other.getRowCount(); j++)
		{
			result[i][j] = 0;
			for (int k = 0; k < m_matrix[i].size(); k++)
			{
				result[i][j] += m_matrix[i][k] * other[k][j];
			}
		}
	}

	return result;
}

template<class T>
inline int CMatrix<T>::getRowCount() const
{
	return m_rowCount;
}

template<class T>
inline int CMatrix<T>::getColCount() const
{
	return m_colCount;
}

template<class T>
inline T CMatrix<T>::get(const int& row, const int& col) const
{
	return m_matrix[row][col];
}
