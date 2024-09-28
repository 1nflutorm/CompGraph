#include "mainwindow.h"

void print(Matrix a)
{
	for (int i = 0; i < 2; i++)
	{
		qDebug() << a[i][0] << " " << a[i][1];
	}
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	setupWindow();

	m_figure =
	{ 
		{30, -10},
		{40, 10},
		{20, 10}
	};

	setWindowContent();

	connect(m_xSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::pointChanged);
	connect(m_ySpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::pointChanged);

	connect(m_redrawButton, &QPushButton::clicked, this, &MainWindow::rotate);
}

void MainWindow::pointChanged(const int& val)
{
	Q_UNUSED(val);

	m_scene->removeItem(m_point);
	m_point = m_scene->addEllipse(m_xSpinBox->value(), -1 * m_ySpinBox->value(),
									1, 1, QPen(Qt::red), QBrush(Qt::SolidPattern));
}

MainWindow::~MainWindow() 
{
	if (m_centralWidget)
	{
		delete m_centralWidget;
	}
}

//void MainWindow::redraw()
//{
//	Matrix temp(m_figure);
//	Matrix rotate(2);
//
//	int x = m_xSpinBox->value();
//	int y = m_ySpinBox->value();
//	int a = m_angleSpinBox->value();
//
//	for (auto& point : temp)
//	{
//		point[0] -= x;
//		point[1] -= y;
//	}
//
//	float rad = a * M_PI / 180;
//
//	rotate[0].push_back(cos(rad));
//	rotate[0].push_back(sin(rad));
//	rotate[1].push_back(-1 * sin(rad));
//	rotate[1].push_back(cos(rad));
//
//	print(rotate);
//
//	Matrix res = matrixMultiplication(temp, rotate);
//
//	for (auto& point : res)
//	{
//		point[0] += x;
//		point[1] += y;
//	}
//
//	/*for (auto& row : temp)
//	{
//		row[0] = x + (row[0] - x) * cos(rad) - (row[1] - y) * sin(rad);
//		row[1] = y + (row[0] - x) * sin(rad) + (row[1] - y) * cos(rad);
//	}*/
//
//	m_figure = res;
//
//	m_scene->removeItem(m_poligon);
//
//	QPolygon pol;
//
//	pol << QPoint(invert[0][0], invert[0][1])
//		<< QPoint(invert[1][0], invert[1][1])
//		<< QPoint(invert[2][0], invert[2][1])
//		<< QPoint(invert[3][0], invert[3][1]);
//
//	m_poligon = m_scene->addPolygon(pol);
//}

void MainWindow::rotate()
{
	int x = m_xSpinBox->value();
	int y = m_ySpinBox->value();
	int alpha = m_angleSpinBox->value();

	float alphaRadian = alpha * M_PI / 180;

	CMatrix<double> rotate =
	{
		{cos(alphaRadian), sin(alphaRadian)},
		{-1 * sin(alphaRadian), cos(alphaRadian)}
	};

	for (int i = 0; i < m_figure.getRowCount(); i++)
	{
		m_figure[i][0] -= x;
		m_figure[i][1] -= y;
	}

	m_figure = m_figure * rotate;

	for (int i = 0; i < m_figure.getRowCount(); i++)
	{
		m_figure[i][0] += x;
		m_figure[i][1] += y;
	}
	
	redraw();
}

void MainWindow::redraw()
{
	CMatrix invert = invertY(m_figure);

	m_scene->removeItem(m_poligon);

	QPolygon pol(
		{
			QPoint(invert[0][0], invert[0][1]),
			QPoint(invert[1][0], invert[1][1]),
			QPoint(invert[2][0], invert[2][1])
		});

	m_poligon = m_scene->addPolygon(pol);
}

void MainWindow::setupWindow()
{
	m_centralWidget = new QWidget;
	setCentralWidget(m_centralWidget);

	m_view = new QGraphicsView(m_centralWidget);
	m_scene = new QGraphicsScene(m_centralWidget);
	m_view->setScene(m_scene);

	m_xLabel = new QLabel("Координата точки х", m_centralWidget);
	m_xSpinBox = new QSpinBox(m_centralWidget);

	m_yLabel = new QLabel("Координата точки y", m_centralWidget);
	m_ySpinBox = new QSpinBox(m_centralWidget);

	m_angleLabel = new QLabel("Угол поворота", m_centralWidget);
	m_angleSpinBox = new QSpinBox(m_centralWidget);

	m_redrawButton = new QPushButton("Рассчитать", m_centralWidget);

	m_layout = new QGridLayout(m_centralWidget);

	m_layout->addWidget(m_view, 0, 0, 6, 6);

	m_layout->addWidget(m_xLabel, 6, 0, 1, 2);
	m_layout->addWidget(m_xSpinBox, 6, 2, 1, 1);
	m_layout->addWidget(m_yLabel, 7, 0, 1, 2);
	m_layout->addWidget(m_ySpinBox, 7, 2, 1, 1);
	m_layout->addWidget(m_angleLabel, 8, 0, 1, 2);
	m_layout->addWidget(m_angleSpinBox, 8, 2, 1, 1);
	m_layout->addWidget(m_redrawButton, 9, 0, 1, 2);
}

void MainWindow::setWindowContent()
{
	m_point = m_scene->addEllipse(	0, 0, 1, 1,
									QPen(Qt::red), QBrush(Qt::SolidPattern));

	CMatrix invert = invertY(m_figure);

	QPolygon pol(
		{
			QPoint(invert[0][0], invert[0][1]),
			QPoint(invert[1][0], invert[1][1]),
			QPoint(invert[2][0], invert[2][1])
		});

	m_poligon = m_scene->addPolygon(pol);

	m_scene->addLine(0, 100, 0, -100);
	m_scene->addLine(100, 0, -100, 0);

	m_view->scale(3, 3);
}

CMatrix<double> MainWindow::invertY(const CMatrix<double>& m)
{
	CMatrix res(m);

	for (int i = 0; i < m.getRowCount(); i++)
	{
		res[i][1] *= -1;
	}

	return res;
}

Matrix MainWindow::matrixMultiplication(const Matrix& first, const Matrix& second)
{
	Matrix result(first.size());
	for (auto& row : result)
	{
		row.resize(second.size());
	}

	for (int i = 0; i < first.size(); i++)
	{
		for (int j = 0; j < second.size(); j++)
		{
			result[i][j] = 0.0f;
			for (int k = 0; k < first[i].size(); k++)
			{
				result[i][j] += first[i][k] * second[k][j];
			}
		}
	}

	return result;
}
