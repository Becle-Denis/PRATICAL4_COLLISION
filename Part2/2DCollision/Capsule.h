#ifndef CAPSULE_H
#define CAPSULE_H

#include <SFML/Graphics.hpp>
#include <tinyc2.h>

class Capsule {

	int m_radius;
	int m_height;
	sf::Vector2f m_position;
	sf::RectangleShape shape1;
	sf::CircleShape shape2;
	sf::CircleShape shape3;

public:
	Capsule(int radius, int height, sf::Vector2f position);

	c2Capsule getC2Capsule();


	void setColor(sf::Color color);

	void render(sf::RenderWindow& window);
};

#endif // !CAPSULE_H