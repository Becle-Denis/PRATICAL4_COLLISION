#include "Polygon.h"

Polygon::Polygon(std::vector<sf::Vector2f> points) : m_points(points)
{
	shape.setPointCount(m_points.size());
	for (int i = 0; i < m_points.size(); i++)
	{
		shape.setPoint(i, m_points.at(i));
	}
}

c2Poly Polygon::getC2Poly()
{
	c2Poly p;
	p.count = m_points.size();
	for (int i = 0; i < m_points.size(); i++)
	{
		p.verts[i] = c2V(m_points.at(i).x, m_points.at(i).y);
	}
	c2MakePoly(&p);
	return p;
}


void Polygon::setColor(sf::Color color)
{
	shape.setFillColor(color);
}

void Polygon::render(sf::RenderWindow& window)
{
	window.draw(shape);
}