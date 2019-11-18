#include "Circle.h"

Circle::Circle(sf::Vector2f position, float radius) : shape(radius)
{
	shape.setOrigin(sf::Vector2f(radius, radius));
	shape.setPosition(position);
}

c2Circle Circle::getC2Circle()
{
	sf::Vector2f position = shape.getPosition();
	c2Circle c;
	c.p = c2V(position.x, position.y);
	c.r = shape.getRadius();
	return c;
}

void Circle::setColor(sf::Color color)
{
	shape.setFillColor(color);
}

void Circle::render(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Circle::move(sf::Vector2i position)
{
	shape.setPosition(sf::Vector2f(position.x,position.y));
}
