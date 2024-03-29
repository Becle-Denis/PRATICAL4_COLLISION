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
	m_current->move(newPosition);
}

void PlayerFSM::render(sf::RenderWindow& window)
{
	m_current->render(window);
}

int PlayerFSM::colideWithAABB(c2AABB& aabb)
{
	return m_current->colideWithAABB(aabb);
}

int PlayerFSM::colideWithCapsule(Capsule& cap)
{
	return m_current->colideWithCapsule(cap);
}

int PlayerFSM::colideWithPolygon(Polygon& pol)
{
	return m_current->colideWithPolygon(pol);
}

int PlayerFSM::colideWithCircle(Circle& cir)
{
	return m_current->colideWithCircle(cir);
}

int PlayerFSM::colideWithRay(Ray& ray)
{
	return m_current->colideWithRay(ray);
}

void PlayerFSM::hit()
{
	m_current->impact();
}

