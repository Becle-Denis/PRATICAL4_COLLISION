#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <typeinfo>

#include <Input.h>
#include <PlayerFSM.h>
#include <Debug.h>
#include <SFML/Graphics.hpp>
#include "Capsule.h"
#include "Polygon.h"
#include "Circle.h"
#include "Ray.h"

class State
{
public:
	virtual void handleInput(Input in, PlayerFSM* a) {}

	virtual void update(PlayerFSM* a) {}

	virtual void square(PlayerFSM* a) {}

	virtual void cirle(PlayerFSM* a) {}

	virtual void ray(PlayerFSM* a) {}

	virtual void impact() {}

	virtual void move(sf::Vector2i newPosition) {};

	virtual void render(sf::RenderWindow& window) {};

	virtual int colideWithAABB(c2AABB& aabb) { return 0; };

	virtual int colideWithCapsule(Capsule& cap) { return 0; };

	virtual int colideWithPolygon(Polygon& pol) { return 0; };

	virtual int colideWithCircle(Circle& cir) { return 0; };

	virtual int colideWithRay(Ray& ray) { return 0; };
};

#endif // ! ANIMATION_H

