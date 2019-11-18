#include <iostream>
#include <SFML/Graphics.hpp>
#include <AnimatedSprite.h>
#include <GameObject.h>
#include <Player.h>
#include <NPC.h>
#include <Input.h>
#include <Debug.h>
#include <Capsule.h>
#include <Circle.h>
#include <Polygon.h>
#include <Ray.h>

#define TINYC2_IMPL
#include <tinyc2.h>

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

	// Setup the NPC
	GameObject &npc = NPC(npc_animated_sprite);

	// Setup the Player
	Player &player = Player();

	//Setup NPC AABB
	c2AABB aabb_npc;
	aabb_npc.min = c2V(npc.getAnimatedSprite().getPosition().x, npc.getAnimatedSprite().getPosition().y);
	aabb_npc.max = c2V(
		npc.getAnimatedSprite().getPosition().x +
		npc.getAnimatedSprite().getGlobalBounds().width, 
		npc.getAnimatedSprite().getPosition().y +
		npc.getAnimatedSprite().getGlobalBounds().height);

	//Setup NPC Capsule 
	Capsule capsuleNPC(50,100,sf::Vector2f(200,400));
	c2Capsule cap_NPC = capsuleNPC.getC2Capsule();

	//Setup NPC Polygon
	Polygon poly({ sf::Vector2f(100,210),sf::Vector2f(253,300),sf::Vector2f(222,212) });
	c2Poly poly_NPC = poly.getC2Poly();

	//Setup the NPC Ray
	Ray ray1(sf::Vector2f(500,50),200,30);
	c2Ray ray1_NPC = ray1.getC2Ray();

	//Setup the NPC Cirlce
	Circle circle1(sf::Vector2f(600, 300), 50);
	c2Circle circle_NPC = circle1.getC2Circle();

	// Initialize Input
	Input input;

	// Collision result
	int result = 0;
	c2Raycast rayResult;
	c2Raycast* ptr_rayResult = &rayResult;

	// Direction of movement of NPC
	sf::Vector2f direction(0.1f, 0.2f);
	
	// Start the game loop
	while (window.isOpen())
	{
		std::cout << "-" << std::endl;

		// Move Sprite Follow Mouse
		player.move(sf::Mouse::getPosition(window));
		
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

		// Update Capsule 
		capsuleNPC.setColor(goodColor);

		// Update Polyone 
		poly.setColor(goodColor);

		// Update Ray
		ray1.setColor(goodColor);

		// Update Circle
		circle1.setColor(goodColor);

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
		
		//Colision NPCAABB to Capsule 
		result = c2AABBtoCapsule(aabb_npc, cap_NPC);
		if (result)
		{
			std::cout << "Colision";
			bondingRectangleNPC.setOutlineColor(sf::Color::Magenta);
			capsuleNPC.setColor(colisionColor);
		}

		//Colision NPCAABB to polygon 
		result = c2AABBtoPoly(aabb_npc, &poly_NPC, NULL);
		if (result)
		{
			std::cout << "Colision";
			bondingRectangleNPC.setOutlineColor(sf::Color::Magenta);
			poly.setColor(colisionColor);
		}

		//Colision NPCAABB to Ray 
		result = c2RaytoAABB(ray1_NPC, aabb_npc, ptr_rayResult);
		if (result)
		{
			std::cout << "Colision";
			bondingRectangleNPC.setOutlineColor(sf::Color::Magenta);
			ray1.setColor(colisionColor);
		}

		//Colision NPCAABB to Circle 
		result = c2CircletoAABB(circle_NPC, aabb_npc);
		if (result)
		{
			std::cout << "Colision";
			bondingRectangleNPC.setOutlineColor(sf::Color::Magenta);
			circle1.setColor(colisionColor);
		}

		//Colision with player
		if (player.colideWithAABB(aabb_npc))
		{
			std::cout << "Colision";
			bondingRectangleNPC.setOutlineColor(sf::Color::Magenta);
			player.hit();
		}

		if (player.colideWithCapsule(capsuleNPC))
		{
			std::cout << "Colision";
			capsuleNPC.setColor(colisionColor);
			player.hit();
		}

		if (player.colideWithCircle(circle1))
		{
			std::cout << "Colision";
			circle1.setColor(colisionColor);
			player.hit();
		}

		if (player.colideWithPolygon(poly))
		{
			std::cout << "Colision";
			poly.setColor(colisionColor);
			player.hit();
		}

		if (player.colideWithRay(ray1))
		{
			std::cout << "Colision";
			ray1.setColor(colisionColor);
			player.hit();
		}

		// Clear screen
		window.clear();

		// Draw the Players Current Animated Sprite
		player.render(window);

		// Draw the NPC's Current Animated Sprite
		window.draw(npc.getAnimatedSprite());

		// Draw the NPC' s bounding rectangle
		window.draw(bondingRectangleNPC);

		//Draw the NPC Capsule
		capsuleNPC.render(window);

		//draw the NPC polygon
		poly.render(window);

		//draw the NPC Ray
		ray1.render(window);

		//draw the NPC Circle
		circle1.render(window);

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};