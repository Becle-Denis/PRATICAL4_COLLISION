#ifndef PLAYER_H
#define PLAYER_H

#include <GameObject.h>
#include <Input.h>
#include <PlayerFSM.h>
#include <AnimatedSprite.h>
#include <SFML/Graphics.hpp>

class Player : public GameObject
{

public:
	Player();
	~Player();
	Player(const AnimatedSprite&);
	AnimatedSprite& getAnimatedSprite();
	void handleInput(Input);
	void update();
	void move(sf::Vector2i newPosition);

	void render(sf::RenderWindow& window);
};

#endif // !PLAYER_H
