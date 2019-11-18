#ifndef SQUARESTATE_H
#define SQUARESTATE_H

#include <State.h>

class SquareState : public State
{
public:
	void handleInput(Input in, PlayerFSM* a) override;

	void update(PlayerFSM* a) override;

	void cirle(PlayerFSM* a) override;

	void ray(PlayerFSM* a) override;

	void impact() override;

	void render(sf::RenderWindow& window) override;
};

#endif // !SQUARESTATE_H



