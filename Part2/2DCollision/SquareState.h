#ifndef SQUARESTATE_H
#define SQUARESTATE_H

#include <State.h>
#include "Polygon.h"

class SquareState : public State
{
private:
	sf::RectangleShape shape;
public:
	SquareState();

	void handleInput(Input in, PlayerFSM* a) override;

	void update(PlayerFSM* a) override;

	void cirle(PlayerFSM* a) override;

	void ray(PlayerFSM* a) override;

	void move(sf::Vector2i position) override;

	void impact() override;

	void render(sf::RenderWindow& window) override;
};

#endif // !SQUARESTATE_H



