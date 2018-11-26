#include <SFML/Graphics.hpp>
#include <iostream>
#include "world_objects.h"

using namespace sf;
using namespace std;

int main()
{
	RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	Texture tx1;
	tx1.loadFromFile("texture/0.png");
	Sprite s1;
	Clock clock;
	int tempX = 0;
	int tempY = 0;
	float distance = 0;
	nonOrg* world[3000];
	flora* trees[500];
	human* people[2];
	village* home[2];
	beast* beasts[50];
	animal* animals[50];
	String s[5] = {"texture/3.png","","","",""};
	String p[2] = {"texture/12.png","texture/13.png"};
	String b[2] = { "texture/6.png","texture/9.png" };
	String a[4] = { "texture/7.png","texture/8.png","texture/10.png","texture/11.png" };
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
			if (Objects[i][j] == '-')
			{
				people[human::getI()] = new human(p, 12, 100, j * 20, i * 20, 30, 30, 0);
			}
			if (Objects[i][j] == '+')
			{
				people[human::getI()] = new human(p, 13, 100, j * 20, i * 20, 30, 30, 1);
			}
			if (Objects[i][j] == '*')
			{
				home[village::getI()] = new village("texture/14.png", 14, j * 20, i * 20, 20, 20);
			}
			if (Objects[i][j] == '6')
			{
				beasts[beast::getI()] = new beast(b, 6, 100, j * 20, i * 20, 10, 10, 0);
			}
			if (Objects[i][j] == '9')
			{
				beasts[beast::getI()] = new beast(b, 9, 100, j * 20, i * 20, 20, 20, 1);
			}
			if (Objects[i][j] == '7')
			{
				animals[animal::getI()] = new animal(a, 7, 100, j * 20, i * 20, 5, 5, 0, 0);
			}
			if (Objects[i][j] == '8')
			{
				animals[animal::getI()] = new animal(a, 8, 100,  j * 20, i * 20, 20, 20, 1, 0);
			}
			if (Objects[i][j] == '=')
			{
				animals[animal::getI()] = new animal(a, 10, 100, j * 20, i * 20, 20, 20, 2, 0);
			}
			if (Objects[i][j] == '|')
			{
				animals[animal::getI()] = new animal(a, 11, 100, j * 20, i * 20, 20, 20, 2, 1);
			}
		}
	
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 1000;
		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);
		sf::Event event;
		while (window.pollEvent(event))
		{
			for (int i = 0; i <= human::getI(); i++)
			{
				if (event.type == Event::MouseButtonPressed)
				{
					if (event.key.code == Mouse::Left)
					{
						if (people[i]->getSprite().getGlobalBounds().contains(pos.x, pos.y))
						{
							people[i]->isSelect = true;
						}
					}
				}
			}
			for (int i = 0; i <= human::getI(); i++)
			{
				if (people[i]->isSelect)
				{
					if (event.type == Event::MouseButtonPressed)
					{
						if (event.key.code == Mouse::Right)
						{
							people[i]->isMove = true;
							people[i]->isSelect = false;
							tempX = pos.x;
							tempY = pos.y;
						}
					}
				}
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		//////////////////СТАРОЕ ДВИЖЕНИЕ//////////////////////
		/*while (window.pollEvent(event))
		{
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.key.code == Mouse::Left) 
				{
					for (int i = 0; i <= human::getI(); i++)
					{
						if (people[i]->getSprite().getGlobalBounds().contains(pos.x, pos.y))
						{
							people[i]->isMove = true;
						}
					}
				}
				if (event.key.code == Mouse::Right) 
				{
					for (int i = 0; i <= human::getI(); i++)
					{
						if (people[i]->getSprite().getGlobalBounds().contains(pos.x, pos.y))
						{
							people[i]->isFear = true;
						}
					}
				}
			}
			if (event.type == Event::MouseButtonReleased)
			{
				if (event.key.code == Mouse::Left)
				{
					for (int i = 0; i <= human::getI(); i++)
					{
						if (people[i]->getSprite().getGlobalBounds().contains(pos.x, pos.y))
						{
							people[i]->isMove = false;
						}
					}
				}
				if (event.key.code == Mouse::Right)
				{
					for (int i = 0; i <= human::getI(); i++)
					{
						if (people[i]->getSprite().getGlobalBounds().contains(pos.x, pos.y))
						{
							people[i]->isFear = false;
						}
					}
				}
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();*/
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
		for (int i = 0; i <= village::getI(); i++)
			window.draw(home[i]->getSprite());
		for (int i = 0; i <= beast::getI(); i++)
			window.draw(beasts[i]->getSprite());
		for (int i = 0; i <= animal::getI(); i++)
			window.draw(animals[i]->getSprite());
		for (int i = 0; i <= human::getI(); i++)
		{
			window.draw(people[i]->getSprite());
			if (people[i]->isMove)
			{
				distance = sqrt((tempX - people[i]->retX())*(tempX - people[i]->retX()) + (tempY - people[i]->retY())*(tempY - people[i]->retY()));
				if (distance > 2)
				{
					people[i]->x += 0.1*time*(tempX - people[i]->retX()) / distance;//x и y пришлось сделать public, но
					people[i]->y += 0.1*time*(tempY - people[i]->retY()) / distance;//можно вернуть текущий x и y, но нельзя его зафиксировать
					//в идеале надо использовать Move, но как привинтить его к переменным, я хз
				}
				else
				{
					people[i]->isMove = false;
				}
				if (people[i]->isFear)
				{
					people[i]->changeStep(0.2);
				}
				else
				{
					people[i]->changeStep(0.1);
				}
			}
			else
			{
				people[i]->changeStep(0);
			}
			//people[i]->Move(1);
			people[i]->reload();
		}
		window.display();
		sleep(milliseconds(10));
	}
	return 0;
}
