#include <iostream>
#include <SFML/Graphics.hpp>
#define TINYC2_IMPL
#include <tinyc2.h>
#include <AnimatedSprite.h>
#include <GameObject.h>
#include <Player.h>
#include <NPC.h>
#include <Input.h>
#include <Debug.h>

using namespace std;

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	// Load a NPC's sprites to display
	sf::Texture npc_texture;
	if (!npc_texture.loadFromFile("assets\\grid.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	// Load a mouse texture to display
	sf::Texture player_texture;
	if (!player_texture.loadFromFile("assets\\player.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	//Color variable 
	sf::Color goodColor = sf::Color(125, 125, 255);
	sf::Color colisionColor = sf::Color(255, 200, 150);

	//Settp NPC' s bouding Rectangle
	sf::RectangleShape bondingRectangleNPC(sf::Vector2f(80,80));
	bondingRectangleNPC.setOutlineThickness(8);
	bondingRectangleNPC.setFillColor(sf::Color::Transparent);

	// Setup NPC's Default Animated Sprite
	AnimatedSprite npc_animated_sprite(npc_texture);
	npc_animated_sprite.addFrame(sf::IntRect(3, 3, 84, 84));


	// Setup Players Default Animated Sprite
	AnimatedSprite player_animated_sprite(player_texture);
	player_animated_sprite.addFrame(sf::IntRect(3, 3, 84, 84));


	// Setup the NPC
	GameObject &npc = NPC(npc_animated_sprite);

	// Setup the Player
	GameObject &player = Player(player_animated_sprite);

	//Setup NPC AABB
	c2AABB aabb_npc;
	aabb_npc.min = c2V(npc.getAnimatedSprite().getPosition().x, npc.getAnimatedSprite().getPosition().y);
	aabb_npc.max = c2V(
		npc.getAnimatedSprite().getPosition().x +
		npc.getAnimatedSprite().getGlobalBounds().width, 
		npc.getAnimatedSprite().getPosition().y +
		npc.getAnimatedSprite().getGlobalBounds().height);

	//Setup NPC Capsule 
	c2Capsule cap_NPC;
	int capsuleRadius = 50;
	int capsuleHeight = 100;
	sf::Vector2f capsulePosition(200,400);
	
		//C2
	c2v capsulea;
	c2v capsuleb;
	capsulea.x = capsulePosition.x + capsuleRadius;
	capsulea.y = capsulePosition.y;
	capsuleb.x = capsulePosition.x + capsuleRadius;
	capsuleb.y = capsulePosition.y + capsuleHeight;
	cap_NPC.a = capsulea;
	cap_NPC.b = capsuleb;
	cap_NPC.r = capsuleRadius;

		//Shapes
	RectangleShape capsuleShape1Rect(sf::Vector2f(2 * capsuleRadius, capsuleHeight));
	CircleShape capsuleShape2Circ(capsuleRadius);
	CircleShape capsuleShape3Circ(capsuleRadius);
	capsuleShape1Rect.setPosition(capsulePosition);
	capsuleShape2Circ.setPosition(sf::Vector2f(capsulePosition.x, capsulePosition.y - capsuleRadius));
	capsuleShape3Circ.setPosition(sf::Vector2f(capsulePosition.x, capsulePosition.y  + capsuleHeight - capsuleRadius));

	//Setup Player AABB
	c2AABB aabb_player;
	aabb_player.min = c2V(player.getAnimatedSprite().getPosition().x, player.getAnimatedSprite().getPosition().y);
	aabb_player.max = c2V(player.getAnimatedSprite().getGlobalBounds().width / 6, player.getAnimatedSprite().getGlobalBounds().width / 6);


	// Initialize Input
	Input input;

	// Collision result
	int result = 0;

	// Direction of movement of NPC
	sf::Vector2f direction(0.1f, 0.2f);
	
	// Start the game loop
	while (window.isOpen())
	{
		// Move Sprite Follow Mouse
		player.getAnimatedSprite().setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		
		// Move The NPC
		sf::Vector2f move_to(npc.getAnimatedSprite().getPosition().x + direction.x, npc.getAnimatedSprite().getPosition().y + direction.y);

		if (move_to.x < 0) {
			direction.x *= -1;
			move_to.x = 0 + npc.getAnimatedSprite().getGlobalBounds().width;
		}
		else if (move_to.x + npc.getAnimatedSprite().getGlobalBounds().width >= 800) { 
			direction.x *= -1;
			move_to.x = 800 - npc.getAnimatedSprite().getGlobalBounds().width;
		}
		else if (move_to.y < 0) { 
			direction.y *= -1;
			move_to.y = 0 + npc.getAnimatedSprite().getGlobalBounds().height;
		}
		else if (move_to.y + npc.getAnimatedSprite().getGlobalBounds().height >= 600) {
			direction.y *= -1;
			move_to.y = 600 - npc.getAnimatedSprite().getGlobalBounds().height;
		}
		
		npc.getAnimatedSprite().setPosition(move_to);

		//Update Bounding rectangle 
		bondingRectangleNPC.setOutlineColor(sf::Color::Yellow);
		bondingRectangleNPC.setPosition(move_to);

		// Update NPC AABB set x and y
		aabb_npc.min = c2V(
			npc.getAnimatedSprite().getPosition().x, 
			npc.getAnimatedSprite().getPosition().y
		);

		aabb_npc.max = c2V(
			npc.getAnimatedSprite().getPosition().x +
			npc.getAnimatedSprite().getGlobalBounds().width,
			npc.getAnimatedSprite().getPosition().y +
			npc.getAnimatedSprite().getGlobalBounds().height
		);

		// Update Player AABB
		aabb_player.min = c2V(
			player.getAnimatedSprite().getPosition().x, 
			player.getAnimatedSprite().getPosition().y
		);
		aabb_player.max = c2V(
			player.getAnimatedSprite().getPosition().x +
			player.getAnimatedSprite().getGlobalBounds().width, 
			player.getAnimatedSprite().getPosition().y + 
			player.getAnimatedSprite().getGlobalBounds().height
		);

		// Update Capsule 
		capsuleShape1Rect.setFillColor(goodColor);
		capsuleShape2Circ.setFillColor(goodColor);
		capsuleShape3Circ.setFillColor(goodColor);

		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				// Close window : exit
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					input.setCurrent(Input::Action::LEFT);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					input.setCurrent(Input::Action::RIGHT);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					input.setCurrent(Input::Action::UP);
				}
				break;
			default:
				input.setCurrent(Input::Action::IDLE);
				break;
			}
		}

		// Handle input to Player
		player.handleInput(input);

		// Update the Player
		player.update();

		// Update the Player
		npc.update();

		// Check for collisions
		// Colision AABBtoAABB
		result = c2AABBtoAABB(aabb_player, aabb_npc);
		cout << ((result != 0) ? ("Collision") : "") << endl;
		if (result){
			//colision
			player.getAnimatedSprite().setColor(sf::Color(255,0,0));
			bondingRectangleNPC.setOutlineColor(sf::Color::Magenta);
		}
		else {
			player.getAnimatedSprite().setColor(sf::Color(0, 255, 0));
		}

		//Colision  PlayerAABB to Capsule
		result = c2AABBtoCapsule(aabb_player, cap_NPC);
		if (result)
		{
			//colision 
			std::cout << "Colision";
			player.getAnimatedSprite().setColor(sf::Color(255, 0, 0));
			capsuleShape1Rect.setFillColor(colisionColor);
			capsuleShape2Circ.setFillColor(colisionColor);
			capsuleShape3Circ.setFillColor(colisionColor);
		}

		//Colision NPCAABB to Capsule 
		result = c2AABBtoCapsule(aabb_npc, cap_NPC);
		if (result)
		{
			std::cout << "Colision";
			bondingRectangleNPC.setOutlineColor(sf::Color::Magenta);
			capsuleShape1Rect.setFillColor(colisionColor);
			capsuleShape2Circ.setFillColor(colisionColor);
			capsuleShape3Circ.setFillColor(colisionColor);
		}

		// Clear screen
		window.clear();

		// Draw the Players Current Animated Sprite
		window.draw(player.getAnimatedSprite());

		// Draw the NPC's Current Animated Sprite
		window.draw(npc.getAnimatedSprite());

		// Draw the NPC' s bounding rectangle
		window.draw(bondingRectangleNPC);


		//Draw the NPC Capsule
		window.draw(capsuleShape1Rect);
		window.draw(capsuleShape2Circ);
		window.draw(capsuleShape3Circ);

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};