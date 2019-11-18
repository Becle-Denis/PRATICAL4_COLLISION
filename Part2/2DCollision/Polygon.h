#ifndef POLYGON_H
#define POLYGON_H

#include <SFML/Graphics.hpp>
#include <tinyc2.h>

class Polygon
{
private:
	std::vector<sf::Vector2f> m_points;
	sf::ConvexShape shape;

public:
	Polygon(std::vector<sf::Vector2f> points);
	c2Poly getC2Poly();
	void setColor(sf::Color color);
	void render(sf::RenderWindow& window);
};


#endif // !POLYGON_H


