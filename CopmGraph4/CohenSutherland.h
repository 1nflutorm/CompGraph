#pragma once

#include <QRectF>
#include <QLineF>
#include <QPoint>

/*
|=========================
| 1001 |   0001   |	0101 |
|------############------|
|      #          #      |
| 1000 #   0000   # 0100 |
|      #          #      |
|------############------|
| 1010 |   0010   | 0110 |
|=========================
*/

enum ECodes
{
	CENTER = 0b0000,
	TOP = 0b0001,
	BOTTOM = 0b0010,
	LEFT = 0b1000,
	RIGHT = 0b0100,
	TOP_LEFT = 0b1001,
	TOP_RIGHT = 0b0101,
	BOTTOM_LEFT = 0b1010,
	BOTTOM_RIGHT = 0b0110
};

class CohenSutherland
{
public :
	CohenSutherland(const QRectF& rect);

public:
	bool operator()(const QLineF& f);

private:
	ECodes getCode(const QPointF& p);

	bool isInRect(const ECodes& a, const ECodes& b);

private:
	//for convinient comparsion
	int m_top;//y top
	int m_bottom;//y bottom
	int m_left;//x left
	int m_right;//x right
};

