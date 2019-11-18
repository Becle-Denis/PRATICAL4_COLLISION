#ifndef RAYSTATE_H
#define RAYSTATE_H

#include <State.h>
#include "Ray.h"

class RayState : public State
{
private:
	Ray ray;
public:
	RayState();

	void handleInput(Input in, PlayerFSM* a) override;

	void update(PlayerFSM* a) override;

	void cirle(PlayerFSM* a) override;

	void square(PlayerFSM* a) override;

	void impact() override;

	void move(sf::Vector2i position) override;

	void render(sf::RenderWindow& window) override;
};

#endif // !RAYSTATE_H



