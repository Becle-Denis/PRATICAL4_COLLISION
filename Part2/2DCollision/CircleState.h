#ifndef CIRCLESTATE_H
#define CIRCLESTATE_H

#include <State.h>
#include "Circle.h"

class CircleState : public State
{
	//Circle circle;
public:

	void handleInput(Input in, PlayerFSM* a) override;

	void update(PlayerFSM* a) override;

	void square(PlayerFSM* a) override;

	void ray(PlayerFSM* a) override;

	void impact() override;

	void render(sf::RenderWindow& window) override;
};

#endif // !CIRCLESTATE_H



