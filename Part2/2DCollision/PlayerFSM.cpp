#include <PlayerFSM.h>
#include "State.h"

PlayerFSM::PlayerFSM()
{
	
}

PlayerFSM::~PlayerFSM() {}

void PlayerFSM::setCurrent(State* s)
{
	m_current = s;
}

State* PlayerFSM::getCurrent()
{
	return m_current;
}

void PlayerFSM::setPrevious(State* s)
{
	m_previous = s;
}

State* PlayerFSM::getPrevious()
{
	return m_previous;
}

void PlayerFSM::handleInput(Input in)
{
	m_current->handleInput(in,this);
}

void PlayerFSM::update()
{
	m_current->update(this);
}

void PlayerFSM::move(sf::Vector2i newPosition)
{
	
}

void PlayerFSM::render(sf::RenderWindow& window)
{
	m_current->render(window);
}

