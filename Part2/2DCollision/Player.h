#ifndef PLAYER_H
#define PLAYER_H

#include <GameObject.h>
#include <Input.h>
#include <PlayerFSM.h>
#include <AnimatedSprite.h>
#include <SFML/Graphics.hpp>
#include "Capsule.h"
#include "Polygon.h"
#include "Circle.h"
#include "Ray.h"

class Player : public GameObject
{

public:
	Player();
	~Player();
	Player(const AnimatedSprite&);
	AnimatedSprite& getAnimatedSprite();
	void handleInput(Input);
	void update();
	void move(sf::Vector2i newPosition);

	void render(sf::RenderWindow& window);

	int colideWithAABB(c2AABB& aabb);

	int colideWithCapsule(Capsule& cap);

	int colideWithPolygon(Polygon& pol);

	int colideWithCircle(Circle& cir);

	int colideWithRay(Ray& ray);

	void hit();
};

#endif // !PLAYER_H
