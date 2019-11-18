#ifndef RAYSTATE_H
#define RAYSTATE_H

#include <State.h>

class RayState : public State
{
public:
	void handleInput(Input in, PlayerFSM* a) override;

	void update(PlayerFSM* a) override;

	void cirle(PlayerFSM* a) override;

	void square(PlayerFSM* a) override;

	void impact() override;

	void render(sf::RenderWindow& window) override;
};

#endif // !RAYSTATE_H



