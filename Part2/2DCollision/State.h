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
	virtual void handleInput(Input in) {}

	virtual void update() {}

	virtual void square() {}

	virtual void cirle() {}

	virtual void ray() {}

	virtual void impact() {}

	void render(sf::RenderWindow& window) {};
};

#endif // ! ANIMATION_H

