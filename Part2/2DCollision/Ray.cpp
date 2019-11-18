#include "Ray.h"

Ray::Ray(sf::Vector2f position, float length, float rotation) :
	m_length(length), m_rotation(rotation), shape(sf::Vector2f(length, 1))
{
	shape.setPosition(position);
	shape.rotate(rotation);
}

c2Ray Ray::getC2Ray()
{
	sf::Vector2f position = shape.getPosition();
	c2Ray r;
	r.p = c2V(position.x, position.y);
	r.d = c2Norm(c2V(cos(m_rotation * 0.01745329252), sin(m_rotation * 0.01745329252)));
	r.t = m_length;
	return r;
}


void Ray::setColor(sf::Color color)
{
	shape.setFillColor(color);
}

void Ray::render(sf::RenderWindow& window)
{
	window.draw(shape);
}