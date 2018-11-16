#include <SFML/Graphics.hpp>
#include <iostream>
#include "world_objects.h"
#include "map.h"

using namespace sf;
using namespace std;
int stone::i = -1;
int water::i = -1;

int main()
{
	RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	Texture tx1;
	tx1.loadFromFile("texture/0.png");
	Sprite s1;
	s1.setTexture(tx1);
	s1.setTextureRect(IntRect(0, 0, 20, 20));
	stone* stones[1000];
    water* h20[1000];
	for (int i = 0; i<HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == '2')
			{
				stones[stone::getI()] = new stone(j * 20, i * 20, 20, 20);
				cout << stone::getI() << endl;
			}
			if (TileMap[i][j] == '1')
			{
				h20[water::getI()] = new water(j * 20, i * 20, 20, 20);
				cout << water::getI() << endl;
			}
		}
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		for (int i = 0; i<HEIGHT_MAP; i++)
			for (int j = 0; j <WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == '0')
				{
					s1.setPosition(j * 20, i * 20);
					window.draw(s1);
				}
			}
		if (stone::getI() >= 0)
			for (int i = 0; i <= stone::getI(); i++)
				window.draw(stones[i]->getSprite());
		if (water::getI() >= 0)
			for (int i = 0; i <= water::getI(); i++)
				window.draw(h20[i]->getSprite());
		window.display();
	}

	return 0;
}
