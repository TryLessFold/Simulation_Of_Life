#include <SFML/Graphics.hpp>
#include <iostream>
#include "world_objects.h"
#include "map.h"

using namespace sf;
using namespace std;

int main()
{
	RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	Texture tx1;
	tx1.loadFromFile("texture/0.png");
	Sprite s1;
	nonOrg* world[3000];
	flora* trees[500];
	String s[5] = { "texture/3.png","","","","" };
	s1.setTexture(tx1);
	s1.setTextureRect(IntRect(0, 0, 20, 20));
	for (int i = 0; i<HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == '2')
			{
				world[nonOrg::getI()] = new nonOrg("texture/2.png", 2, j*20, i*20, 20, 20);
			}
			if (TileMap[i][j] == '1')
			{
				world[nonOrg::getI()] = new nonOrg("texture/1.png", 1, j * 20, i * 20, 20, 20);
			}
			if (Objects[i][j] == '3')
			{
				trees[flora::getI()] = new flora(s, 3, j * 20, i * 20, 30, 30);
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
		for (int i = 0; i <= nonOrg::getI(); i++)
			window.draw(world[i]->getSprite());
		for (int i = 0; i <= flora::getI(); i++)
			window.draw(trees[i]->getSprite());
		window.display();
	}
	return 0;
}
