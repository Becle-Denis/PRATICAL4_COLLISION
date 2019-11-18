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

class Capsule {
public: 
	int m_radius;
	int m_height;
	sf::Vector2f m_position;
	sf::RectangleShape shape1;
	sf::CircleShape shape2;
	sf::CircleShape shape3;

	Capsule(int radius, int height, sf::Vector2f position)
		: m_radius(radius),m_height(height), m_position(position),
		shape1(sf::Vector2f(2 * radius, height)), shape2(radius), shape3(radius)

	{
		shape1.setPosition(m_position);
		shape2.setPosition(sf::Vector2f(m_position.x, m_position.y - m_radius));
		shape3.setPosition(sf::Vector2f(m_position.x, m_position.y + m_height - m_radius));
	}

	c2Capsule getC2Capsule()
	{
		c2Capsule cap;
		c2v a;
		c2v b;
		a.x = m_position.x + m_radius;
		a.y = m_position.y;
		b.x = m_position.x + m_radius;
		b.y = m_position.y + m_height;
		cap.a = a;
		cap.b = b;
		cap.r = m_radius;
		return cap;
	}


	void setColor(sf::Color color)
	{
		shape1.setFillColor(color);
		shape2.setFillColor(color);
		shape3.setFillColor(color);
	}

	void render(sf::RenderWindow& window)
	{
		window.draw(shape1);
		window.draw(shape2);
		window.draw(shape3);
	}
};

class Polygon
{
private:
	std::vector<sf::Vector2f> m_points;
	sf::ConvexShape shape;

public:
	Polygon(std::vector<sf::Vector2f> points) : m_points(points)
	{
		shape.setPointCount(m_points.size());
		for (int i = 0; i < m_points.size(); i++)
		{
			shape.setPoint(i, m_points.at(i));
		}
	}
	
	c2Poly getC2Poly()
	{
		c2Poly p;
		p.count = m_points.size();
		for (int i = 0; i < m_points.size(); i++)
		{
			p.verts[i] = c2V(m_points.at(i).x, m_points.at(i).y);
		}
		c2MakePoly(&p);
		return p;
	} 
	

	void setColor(sf::Color color)
	{
		shape.setFillColor(color);
	}

	void render(sf::RenderWindow& window)
	{
		window.draw(shape);
	}
};

class Ray
{
	RectangleShape shape;
	float m_length;
	float m_rotation;
	

public:
	Ray(sf::Vector2f position,float length, float rotation) : 
		m_length(length), m_rotation(rotation), shape(sf::Vector2f(length,1))
	{
		shape.setPosition(position);
		shape.rotate(rotation);
	}

	c2Ray getC2Ray()
	{
		sf::Vector2f position = shape.getPosition();
		c2Ray r;
		r.p = c2V(position.x,position.y);
		r.d = c2Norm(c2V(cos(m_rotation * 0.01745329252),sin(m_rotation * 0.01745329252)));
		r.t = m_length;
		return r;
	}


	void setColor(sf::Color color)
	{
		shape.setFillColor(color);
	}

	void render(sf::RenderWindow& window)
	{
		window.draw(shape);
	}
};

class Circle
{
	CircleShape shape;

public:
	Circle(sf::Vector2f position, int radius) : shape(radius)
	{
		shape.setPosition(position);
	}

	void setColor(sf::Color color)
	{
		shape.setFillColor(color);
	}

	void render(sf::RenderWindow& window)
	{
		window.draw(shape);
	}
};


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

	//Setup Player AABB
	c2AABB aabb_player;
	aabb_player.min = c2V(player.getAnimatedSprite().getPosition().x, player.getAnimatedSprite().getPosition().y);
	aabb_player.max = c2V(player.getAnimatedSprite().getGlobalBounds().width / 6, player.getAnimatedSprite().getGlobalBounds().width / 6);


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
			capsuleNPC.setColor(colisionColor);
		}

		//Colision NPCAABB to Capsule 
		result = c2AABBtoCapsule(aabb_npc, cap_NPC);
		if (result)
		{
			std::cout << "Colision";
			bondingRectangleNPC.setOutlineColor(sf::Color::Magenta);
			capsuleNPC.setColor(colisionColor);
		}

		//Colision PLayerAABB to Polygon
		result = c2AABBtoPoly(aabb_player,&poly_NPC, NULL);
		if (result)
		{
			std::cout << "Colision";
			player.getAnimatedSprite().setColor(sf::Color(255, 0, 0));
			poly.setColor(colisionColor);
		}

		//Colision NPCAABB to polygon 
		result = c2AABBtoPoly(aabb_npc, &poly_NPC, NULL);
		if (result)
		{
			std::cout << "Colision";
			bondingRectangleNPC.setOutlineColor(sf::Color::Magenta);
			poly.setColor(colisionColor);
		}

		//Colision PLayerAABB to Ray
		result = c2RaytoAABB(ray1_NPC,aabb_player, ptr_rayResult);
		if (result)
		{
			std::cout << "Colision";
			player.getAnimatedSprite().setColor(sf::Color(255, 0, 0));
			ray1.setColor(colisionColor);
		}

		//Colision NPCAABB to Ray 
		result = c2RaytoAABB(ray1_NPC, aabb_npc, ptr_rayResult);
		if (result)
		{
			std::cout << "Colision";
			bondingRectangleNPC.setOutlineColor(sf::Color::Magenta);
			ray1.setColor(colisionColor);
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