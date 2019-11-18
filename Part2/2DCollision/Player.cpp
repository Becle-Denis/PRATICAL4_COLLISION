#include <iostream>
#include <Player.h>
#include <Debug.h>

Player::Player() : GameObject()
{

}

Player::Player(const AnimatedSprite& s) : GameObject(s)
{

}

Player::~Player()
{
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
	m_animated_sprite.update();
}