#include <iostream>
#include <math.h>
#include <time.h>

class Point {
public:
	int x;
	int y;

	void print() {
		std::cout << "x:" << x << " y:" << y << std::endl;
	}
};

class Circle {
public:
	Point p;
	int r;

	void print() {
		std::cout << "x:" << p.x << " y:" << p.y << " r:" << r << std::endl;
	}
};

class Box {
public:
	Point p;
	int width;
	int height;

	void print()
	{
		std::cout << "x:" << p.x << " y:" << p.y << " width:" << width << " height:" << height << std::endl;
	}

};

int calculate_hypotenuse(Point a, Point b) {
	int result = 0;

	// Find the distance (Length) of X and Y  

	int x_Distance = b.x - a.x;
	int y_Distance = b.y - a.y;

	// Now that we have the distance (Length)
	// of x and y, use Pythagoras theorem 
	// to get the distance (length of hypotenuse) 
	// between Point a and Point b 
	result = sqrt(pow(x_Distance, 2) + pow(y_Distance, 2));

	return result;
}

bool collideBoxToBox(Box a, Box b)
{
	return (a.p.x < b.p.x + b.width && a.p.x + a.width > b.p.x && a.p.x + a.width > b.p.x && a.p.y < b.p.y + b.height && a.p.y + a.height > b.p.y);
}

int main() {

	srand(time(NULL));

	// Point Collision
	Point player_point;
	player_point.x = rand() % 10 + 1;
	player_point.y = rand() % 10 + 1;

	Point npc_point;
	npc_point.x = rand() % 10 + 1;
	npc_point.y = rand() % 10 + 1;

	// Circle Collision
	Circle player_circle;
	player_circle.p.x = rand() % 10 + 1;
	player_circle.p.y = rand() % 10 + 1;
	player_circle.r = rand() % 2 + 1;
	
	Circle npc_circle;
	npc_circle.p.x = rand() % 10 + 1;
	npc_circle.p.y = rand() % 10 + 1;
	npc_circle.r = rand() % 2 + 1;

	//Box Collision 
	Box player_box;
	player_box.p.x = rand() % 10 + 1;
	player_box.p.y = rand() % 10 + 1;
	player_box.height = rand() % 3 + 1;
	player_box.width = rand() % 3 + 1;

	Box npc_box;
	npc_box.p.x = rand() % 10 + 1;
	npc_box.p.y = rand() % 10 + 1;
	npc_box.height = rand() % 3 + 1;
	npc_box.width = rand() % 3 + 1;


	while (true) {

		// Point Collision check
		if (calculate_hypotenuse(player_point, npc_point) == 0)
		{
			std::cout << "Point Collision" << std::endl;
			player_point.print();
			npc_point.print();
			std::cin.get();
		}
		else
		{
			std::cout << "No Collision" << std::endl;
			player_point.print();
			npc_point.print();
		}


		// Circle Collision check
		if (calculate_hypotenuse(player_circle.p, npc_circle.p) < (player_circle.r + npc_circle.r))
		{
			std::cout << "Circle Collision" << std::endl;
			player_circle.print();
			npc_circle.print();
			std::cin.get();
		}
		else
		{
			std::cout << "No Collision" << std::endl;
			player_circle.print();
			npc_circle.print();
		}
		

		// Point NPC to PLayer NPC Collision check
		if (calculate_hypotenuse(npc_point, player_circle.p) < (player_circle.r))
		{
			std::cout << "Point to circle Collision" << std::endl;
			npc_point.print();
			player_circle.print();
			std::cin.get();
		}
		else
		{
			std::cout << "No Collision" << std::endl;
			npc_point.print();
			player_circle.print();
		}

		//Box to Box collision 
		if (collideBoxToBox(player_box, npc_box))
		{
			std::cout << "Box to Box Collision" << std::endl;
			player_box.print();
			npc_box.print();
			std::cin.get();
		}
		else
		{
			std::cout << "No Collision" << std::endl;
			player_box.print();
			npc_box.print();
		}

		//moving
		player_circle.p.x = rand() % 10 + 1; // circle X
		player_circle.p.y = rand() % 10 + 1; // circle Y
		player_circle.r = rand() % 2 + 1; // circle radius

		player_point.x = rand() % 10 + 1; // point X
		player_point.y = rand() % 10 + 1; // point Y

		player_box.p.x = rand() % 10 + 1; // box X
		player_box.p.y = rand() % 10 + 1; // box Y
		player_box.height = rand() % 3 + 1; // box height
		player_box.width = rand() % 3 + 1; // box width

	}


	return 0;
}