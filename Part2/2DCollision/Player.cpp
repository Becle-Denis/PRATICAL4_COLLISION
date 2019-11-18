#include <iostream>
#include <Player.h>
#include <Debug.h>
#include <SquareState.h>

Player::Player() : GameObject()
{
	m_player_fsm.setCurrent(new SquareState());
	m_player_fsm.setPrevious(new SquareState());
}

Player::Player(const AnimatedSprite& s) : GameObject(s)
{
	m_player_fsm.setCurrent(new SquareState());
	m_player_fsm.setPrevious(new SquareState());
}

Player::~Player()
{
	delete m_player_fsm.getPrevious();
	delete m_player_fsm.getCurrent();
}

AnimatedSprite& Player::getAnimatedSprite()
{
	int frame = m_animated_sprite.getCurrentFrame();
	m_animated_sprite.setTextureRect(m_animated_sprite.getFrame(frame));
	return m_animated_sprite;
}

void Player::handleInput(Input in)
{
	m_player_fsm.handleInput(in);
}

void Player::update()
{
	//std::cout << "Handle Update" << std::endl;
	m_player_fsm.update();
}

void Player::move(sf::Vector2i newPosition)
{
	m_player_fsm.move(newPosition);
}

void Player::render(sf::RenderWindow& window)
{
	m_player_fsm.render(window);
}

int Player::colideWithAABB(c2AABB& aabb)
{
	return m_player_fsm.colideWithAABB(aabb);
}

int Player::colideWithCapsule(Capsule& cap)
{
	return m_player_fsm.colideWithCapsule(cap);
}

int Player::colideWithPolygon(Polygon& pol)
{
	return m_player_fsm.colideWithPolygon(pol);
}

int Player::colideWithCircle(Circle& cir)
{
	return m_player_fsm.colideWithCircle(cir);
}

int Player::colideWithRay(Ray& ray)
{
	return m_player_fsm.colideWithRay(ray);
}

void Player::hit()
{
	m_player_fsm.hit();
}

