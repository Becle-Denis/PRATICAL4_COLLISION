#include <iostream>
#include <NPC.h>
#include <Debug.h>

NPC::NPC() : GameObject()
{

}

NPC::NPC(const AnimatedSprite& s) : GameObject(s)
{

}

NPC::~NPC()
{
}

AnimatedSprite& NPC::getAnimatedSprite()
{
	int frame = m_animated_sprite.getCurrentFrame();
	m_animated_sprite.setTextureRect(m_animated_sprite.getFrame(frame));
	return m_animated_sprite;
}

void NPC::handleInput(Input in)
{

}

void NPC::update()
{
	//std::cout << "Handle Update" << std::endl;
	m_animated_sprite.update();
}