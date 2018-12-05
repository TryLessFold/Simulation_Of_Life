#include <SFML/Graphics.hpp>
#include <iostream>
#include "world_objects.h"

using namespace sf;
using namespace std;

int main()
{
	RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	SupportClass::SetScreen(1280, 720);
	SupportClass::SetCube();
	//SupportClass::push_NonGo('0'+1);
	SupportClass::push_NonGo('0' + 2);
	SupportClass::push_SlowGo('0' + 1);
	Texture tx1;
	tx1.loadFromFile("texture/0.png");
	Sprite s1;
	Clock clock;
	float timer_of_day = 0;
	int number_day = 1;
	nonOrg* world[3000];
	flora* trees[500];
	human* people[2];
	village* home[2];
	beast* beasts[50];
	animal* animals[50];
	s1.setTexture(tx1);
	s1.setTextureRect(IntRect(0, 0, 20, 20));
	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == '2')
			{
				world[nonOrg::getI()] = new nonOrg("texture/2.png", 2, j * 20, i * 20, 20, 20);
			}
			if (TileMap[i][j] == '1')
			{
				world[nonOrg::getI()] = new nonOrg("texture/1.png", 1, j * 20, i * 20, 20, 20);
			}
			if (Objects[i][j] == '3')
			{
				trees[flora::getI()] = new flora(3, j * 20, i * 20, 20, 20);
			}
			if (Objects[i][j] == '-')
			{
				people[human::getI()] = new human('0' + 12, 100, j * 20, i * 20, 20, 20, 0);
			}
			if (Objects[i][j] == '+')
			{
				people[human::getI()] = new human(13, 100, j * 20, i * 20, 20, 20, 1);
			}
			if (Objects[i][j] == '*')
			{
				home[village::getI()] = new village("texture/14.png", 14, j * 20, i * 20, 20, 20);
			}
			if (Objects[i][j] == '6')
			{
				beasts[beast::getI()] = new beast(6, 100, j * 20, i * 20, 10, 10, 0);
			}
			if (Objects[i][j] == '9')
			{
				beasts[beast::getI()] = new beast(9, 100, j * 20, i * 20, 20, 20, 1);
			}
			if (Objects[i][j] == '7')
			{
				animals[animal::getI()] = new animal(7, 100, j * 20, i * 20, 5, 5, 0, 0);
			}
			if (Objects[i][j] == '8')
			{
				animals[animal::getI()] = new animal(8, 100, j * 20, i * 20, 20, 20, 1, 0);
			}
			if (Objects[i][j] == '=')
			{
				animals[animal::getI()] = new animal(10, 100, j * 20, i * 20, 20, 20, 2, 0);
			}
			if (Objects[i][j] == '|')
			{
				animals[animal::getI()] = new animal(11, 100, j * 20, i * 20, 20, 20, 2, 1);
			}
		}

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		float time_d = clock.getElapsedTime().asSeconds();
		clock.restart();
		time = time / 800;
		timer_of_day += time_d;
		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);
		sf::Event event;
		while (window.pollEvent(event))
		{
			for (int i = 0; i <= animal::getI(); i++)
			{
				if (event.type == Event::MouseButtonPressed)
				{
					if (event.key.code == Mouse::Left)
					{
						if (animals[i]->getSprite().getGlobalBounds().contains(pos.x, pos.y))
						{
							animals[i]->isselect(1);
						}
					}
				}
			}
			for (int i = 0; i <= human::getI(); i++)
			{
				if (event.type == Event::MouseButtonPressed)
				{
					if (event.key.code == Mouse::Left)
					{
						if (people[i]->getSprite().getGlobalBounds().contains(pos.x, pos.y))
						{
							people[i]->isselect(1);
						}
					}
				}
			}
			for (int i = 0; i <= beast::getI(); i++)
			{
				if (event.type == Event::MouseButtonPressed)
				{
					if (event.key.code == Mouse::Left)
					{
						if (beasts[i]->getSprite().getGlobalBounds().contains(pos.x, pos.y))
						{
							beasts[i]->isselect(1);
						}
					}
				}
			}
			for (int i = 0; i <= animal::getI(); i++)
			{
				if (animals[i]->isselect())
				{
					if (event.type == Event::MouseButtonPressed)
					{
						if (event.key.code == Mouse::Right)
						{
							animals[i]->ismove(1);
							animals[i]->isselect(0);
							animals[i]->goTO(pos.x, pos.y, 20, 20);
						}
					}
				}
			}
			for (int i = 0; i <= human::getI(); i++)
			{
				if (people[i]->isselect())
				{
					if (event.type == Event::MouseButtonPressed)
					{
						if (event.key.code == Mouse::Right)
						{
							people[i]->ismove(1);
							people[i]->isselect(0);
							people[i]->goTO(pos.x, pos.y, 20, 20);
						}
					}
				}
			}
			for (int i = 0; i <= beast::getI(); i++)
			{
				if (beasts[i]->isselect())
				{
					if (event.type == Event::MouseButtonPressed)
					{
						if (event.key.code == Mouse::Right)
						{
							beasts[i]->ismove(1);
							beasts[i]->isselect(0);
							beasts[i]->goTO(pos.x, pos.y, 20, 20);
						}
					}
				}
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
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
		{
			window.draw(trees[i]->getSprite());
			if (timer_of_day >= 1)
			{
				trees[i]->grow();
			}
			trees[i]->reload();
		}
		for (int i = 0; i <= village::getI(); i++)
			window.draw(home[i]->getSprite());
		for (int i = 0; i <= beast::getI(); i++)
		{
			window.draw(beasts[i]->getSprite());
			beasts[i]->Move(time);
			beasts[i]->reload();
			//beasts[i]->target();
		}
		for (int i = 0; i <= animal::getI(); i++)
		{
			window.draw(animals[i]->getSprite());
			animals[i]->Move(time);
			animals[i]->reload();
			//animals[i]->target();
		}
		for (int i = 0; i <= human::getI(); i++)
		{
			window.draw(people[i]->getSprite());
			people[i]->Move(time);
			people[i]->reload();
			people[i]->target();
		}
		if (timer_of_day >= 10)
		{
			number_day++;
			timer_of_day = 0;
		}
		//cout << timer_of_day<<endl;
		/*for (int i = 0; i <= 10; i++)
		{
			for (int j = 0; j <= 10; j++) cout << Objects[i][j];
			cout << endl;
		}*/
		//system("CLS");
		window.display();
		//sleep(milliseconds(10));
	}
	return 0;
}
