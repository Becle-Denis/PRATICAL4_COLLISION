#ifndef RAY_H
#define RAY_H

#include <SFML/Graphics.hpp>
#include <tinyc2.h>

class Ray
{
	sf::RectangleShape shape;
	float m_length;
	float m_rotation;


public:
	Ray(sf::Vector2f position, float length, float rotation);
	c2Ray getC2Ray();
	void setColor(sf::Color color);
	void render(sf::RenderWindow& window);
	void move(sf::Vector2i position);
};

#endif // !RAY_H

