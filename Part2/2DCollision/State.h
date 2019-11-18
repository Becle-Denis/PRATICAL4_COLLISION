#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <typeinfo>

#include <Input.h>
#include <PlayerFSM.h>
#include <Debug.h>
#include <SFML/Graphics.hpp>

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
};

#endif // ! ANIMATION_H

