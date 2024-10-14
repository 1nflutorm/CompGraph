#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	setupWindow();

	connect(m_addPointsButton, &QPushButton::clicked, this, &MainWindow::addPoints);
	connect(m_redrawButton, &QPushButton::clicked, this, &MainWindow::redraw);
}

MainWindow::~MainWindow() 
{
}

void MainWindow::redraw()
{
	m_matrix = CMatrix<double>(m_pointCountSpinBox->value(), 2);
	for (int i = 0; i < m_uiPoints.size(); i++)
	{
		m_matrix[i][0] = m_uiPoints[i]->m_xSpinBox->value();
		m_matrix[i][1] = m_uiPoints[i]->m_ySpinBox->value();
	}

	m_plot->clearGraphs();
	QCPGraph* splineGraph = m_plot->addGraph();//index 0 - always spline graph
	for (int i = 0; i < m_matrix.getRowCount(); i++)
	{
		QCPGraph* graph = m_plot->addGraph();
		graph->setData(QVector{ m_matrix[i][0] }, QVector{ m_matrix[i][1]});
		graph->setPen(QColor(50, 50, 50, 255));
		graph->setLineStyle(QCPGraph::lsNone);
		graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
	}

	CSpline spline{ m_matrix };
	spline.calculateSpline();

	QVector<double> x = spline.getPx();
	QVector<double> y = spline.getPy();

	splineGraph->addData(x, y, true);

	m_plot->replot();
}

void MainWindow::setupWindow()
{
	m_centraWidget = new QWidget;
	m_layout = new QGridLayout(m_centraWidget);

	m_plot = new QCustomPlot(m_centraWidget);
	m_plot->setInteraction(QCP::iRangeZoom, true);
	m_plot->setInteraction(QCP::iRangeDrag, true);

	m_pointCountLabel = new QLabel("Количество точек", m_centraWidget);
	m_pointCountSpinBox = new QSpinBox(m_centraWidget);
	m_pointCountSpinBox->setMinimum(c_minPointCount);
	m_pointCountSpinBox->setMaximum(c_maxPointCount);
	m_pointCountSpinBox->setMinimumWidth(50);

	m_addPointsButton = new QPushButton("Добавить/удалить точки", m_centraWidget);

	m_redrawButton = new QPushButton("Построить кривую", m_centraWidget);

	m_layout->addWidget(m_plot, 0, 0, 6, 6);

	m_layout->addWidget(m_pointCountLabel, 6, 0, 1, 1);
	m_layout->addWidget(m_pointCountSpinBox, 6, 1, 1, 1);
	m_layout->addWidget(m_addPointsButton, 6, 2, 1, 2);
	m_lastRow = 7;
	m_layout->addWidget(m_redrawButton, 7, 4, 1, 2);

	setCentralWidget(m_centraWidget);
	setLayout(m_layout);
}

void MainWindow::addPoints()
{
	m_layout->removeWidget(m_redrawButton);

	int pointCount = m_pointCountSpinBox->value();

	if (pointCount < m_uiPoints.size() )
	{
		while (pointCount < m_uiPoints.size())
		{
			m_layout->removeWidget(m_uiPoints[m_uiPoints.size() - 1]->m_xLabel);
			m_layout->removeWidget(m_uiPoints[m_uiPoints.size() - 1]->m_yLabel);
			m_layout->removeWidget(m_uiPoints[m_uiPoints.size() - 1]->m_xSpinBox);
			m_layout->removeWidget(m_uiPoints[m_uiPoints.size() - 1]->m_ySpinBox);
			delete m_uiPoints[m_uiPoints.size() - 1];
			m_uiPoints.remove(m_uiPoints.size() - 1);

			m_lastRow--;
		}
	}
	else
	{
		int pointsToAdd = pointCount - m_uiPoints.size();
		for (int i = 0; i < pointsToAdd; i++)
		{
			UIpoint* point = new UIpoint;

			point->m_xLabel = new QLabel(QString("Координата x%1").arg(QString::number(m_uiPoints.size() + 1)));
			point->m_yLabel = new QLabel(QString("Координата y%1").arg(QString::number(m_uiPoints.size() + 1)));

			point->m_xSpinBox = new QSpinBox;
			point->m_xSpinBox->setMaximum(100);
			point->m_xSpinBox->setMinimum(-100);

			point->m_ySpinBox = new QSpinBox;
			point->m_ySpinBox->setMaximum(100);
			point->m_ySpinBox->setMinimum(-100);

			m_layout->addWidget(point->m_xLabel, m_lastRow, 0, 1, 1);
			m_layout->addWidget(point->m_yLabel, m_lastRow, 2, 1, 1);
			m_layout->addWidget(point->m_xSpinBox, m_lastRow, 1, 1, 1);
			m_layout->addWidget(point->m_ySpinBox, m_lastRow, 3, 1, 1);

			m_uiPoints.push_back(point);
			m_lastRow++;
		}
	}

	m_layout->addWidget(m_redrawButton, m_lastRow + 1, 4, 1, 2);
}

UIpoint::~UIpoint()
{
	if (m_xLabel)
	{
		delete m_xLabel;
	}
	if (m_xSpinBox)
	{
		delete m_xSpinBox;
	}
	if (m_yLabel)
	{
		delete m_yLabel;
	}
	if (m_ySpinBox)
	{
		delete m_ySpinBox;
	}
}
