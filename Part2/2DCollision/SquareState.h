#ifndef SQUARESTATE_H
#define SQUARESTATE_H

#include <State.h>
#include "Polygon.h"

class SquareState : public State
{
private:
	sf::RectangleShape shape;
	c2AABB c2;
public:
	SquareState();

	void handleInput(Input in, PlayerFSM* a) override;

	void update(PlayerFSM* a) override;

	void cirle(PlayerFSM* a) override;

	void ray(PlayerFSM* a) override;

	void move(sf::Vector2i position) override;

	void impact() override;

	void render(sf::RenderWindow& window) override;

	int colideWithAABB(c2AABB& aabb) override;

	int colideWithCapsule(Capsule& cap) override;

	int colideWithPolygon(Polygon& pol) override;

	int colideWithCircle(Circle& cir) override;

	int colideWithRay(Ray& ray) override;
};

#endif // !SQUARESTATE_H



