#ifndef PLAYER_FSM_H
#define PLAYER_FSM_H

#include "Input.h"
#include <SFML/Graphics.hpp>
#include "Capsule.h"
#include "Polygon.h"
#include "Circle.h"
#include "Ray.h"

class PlayerFSM
{

	// Please review very good article on Stackoverflow
	// which covers some solutions to circular dependacies
	// https://stackoverflow.com/questions/625799/resolve-build-errors-due-to-circular-dependency-amongst-classes

private:
	class State* m_current; // note order of m_current is 
							// prior to setCurrent
	class State* m_previous;
public:
	PlayerFSM();
	~PlayerFSM();
	void setCurrent(State* s);
	void setPrevious(State* s);
	State* getCurrent();
	State* getPrevious();
	
	void handleInput(Input in);

	void update();
	void move(sf::Vector2i newPosition);

	void render(sf::RenderWindow& window);

	int colideWithAABB(c2AABB& aabb);

	int colideWithCapsule(Capsule& cap);

	int colideWithPolygon(Polygon& pol);

	int colideWithCircle(Circle& cir);

	int colideWithRay(Ray& ray);

	void hit();

// Try uncommenting and comment the declaration above
//private:
//	class State* m_current;
};

#endif // !PLAYER_FSM_H
