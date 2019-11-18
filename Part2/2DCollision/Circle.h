#ifndef CIRCLE_H
#define CIRCLE_H

#include <SFML/Graphics.hpp>
#include <tinyc2.h>

class Circle
{
	sf::CircleShape shape;

public:
	Circle(sf::Vector2f position, float radius);

	c2Circle getC2Circle();

	void setColor(sf::Color color);

	void render(sf::RenderWindow& window);

	void move(sf::Vector2i position);
};

#endif // !CIRCLE_H


