#include <SFML/Graphics.hpp>
#include <iostream>
#include "world_objects.h"
#include "map"

using namespace sf;
using namespace std;

int main()
{
	inventory l;
	l.push(1, 1, 10);
	l.push(2, 1, 3);
	l.push(2, 2, 3);
	l.push(3, 3, 1);
	l.output();
	l.take(12);
	l.take(2);
	l.output();
	system("PAUSE");
	/*sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
*/
	return 0;
}
