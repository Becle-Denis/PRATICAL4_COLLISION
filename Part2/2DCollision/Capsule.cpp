#include "Capsule.h"

Capsule::Capsule(int radius, int height, sf::Vector2f position)
	: m_radius(radius), m_height(height), m_position(position),
	shape1(sf::Vector2f(2 * radius, height)), shape2(radius), shape3(radius)

{
	shape1.setPosition(m_position);
	shape2.setPosition(sf::Vector2f(m_position.x, m_position.y - m_radius));
	shape3.setPosition(sf::Vector2f(m_position.x, m_position.y + m_height - m_radius));
}

c2Capsule Capsule::getC2Capsule()
{
	c2Capsule cap;
	c2v a;
	c2v b;
	a.x = m_position.x + m_radius;
	a.y = m_position.y;
	b.x = m_position.x + m_radius;
	b.y = m_position.y + m_height;
	cap.a = a;
	cap.b = b;
	cap.r = m_radius;
	return cap;
}


void Capsule::setColor(sf::Color color)
{
	shape1.setFillColor(color);
	shape2.setFillColor(color);
	shape3.setFillColor(color);
}

void Capsule::render(sf::RenderWindow& window)
{
	window.draw(shape1);
	window.draw(shape2);
	window.draw(shape3);
}