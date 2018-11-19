#include <SFML/Graphics.hpp>
#include <iostream>
#include "world_objects.h"
#include "map.h"

using namespace sf;
using namespace std;
int stone::i = -1;
int water::i = -1;
int tree::i = -1;
int human::i = -1;
int village::i = -1;
int bear::i = -1;
int wolf::i = -1;
int mouse::i = -1;
int deer::i = -1;
int cat::i = -1;

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
	tree* trees[WIDTH_MAP];
	bear* b[10];
	wolf* w[10];
	mouse* m[10];
	deer* d[10];
	cat* c[10];
	human man(600, 300, 20, 20, 1);
	human woman(610, 300, 20, 20, 0);
	village home(630, 300, 20, 20);
	for (int i = 0; i<HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == '2')
			{
				stones[stone::getI()] = new stone(j * 20, i * 20, 20, 20);
				//cout << stone::getI() << endl;
			}
			if (TileMap[i][j] == '1')
			{
				h20[water::getI()] = new water(j * 20, i * 20, 20, 20);
				//cout << water::getI() << endl;
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
		for (int i = 0; i < WIDTH_MAP; i++)
		{
			trees[i] = new tree(i * 20, 570, 200, 200);
			window.draw(trees[i]->getSprite());
		}
		for (int i = 0; i < 10; i++)
		{
			b[i] = new bear(i * 20, 400, 20, 20);
			w[i] = new wolf(i * 20, 500, 20, 20);
			m[i] = new mouse(20 + i * 20, 200, 20, 20);
			d[i] = new deer(20 + i * 20, 300, 20, 20);
			c[i] = new cat(20 + i * 20, 100, 20, 20);
			window.draw(b[i]->getSprite());
			window.draw(w[i]->getSprite());
			window.draw(m[i]->getSprite());
			window.draw(d[i]->getSprite());
			window.draw(c[i]->getSprite());
		}
		window.draw(man.getSprite());
		window.draw(woman.getSprite());
		window.draw(home.getSprite());
		window.display();
	}

	return 0;
}
