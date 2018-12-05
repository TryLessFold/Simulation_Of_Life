#include <SFML/Graphics.hpp>
#include <iostream>
#include "world_objects.h"

using namespace sf;
using namespace std;

int main()
{
	const int time_day = 10;
	const int time_eat = 2;
	RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	SupportClass::SetScreen(1280, 720);
	SupportClass::SetCube();
	//SupportClass::push_NonGo('0'+1);
	SupportClass::push_SlowGo('0' + 1);
	SupportClass::push_NonGo('0'+2);
	Texture tx1;
	tx1.loadFromFile("texture/0.png");
	Sprite s1;
	Clock clock;
	float timer_of_day = 0;
	float timer_of_hunger = 0;
	int number_day = 1;
	nonOrg* world[3000];
	flora* trees[500];
	human* people[2];
	village* home[2];
	beast* beasts[50];
	animal* animals[50];
	String tree_t[5] = {"texture/3.png","texture/3.png","texture/3.png","texture/3.png","texture/3.png"};
	String tree_b[5] = { "texture/4_1.png","texture/4_2.png","texture/4_2.png","texture/4_2.png","texture/4_2.png" };
	String p[2] = {"texture/12.png","texture/13.png"};
	String rabbit[2] = { "texture/6.png","texture/6.png" };
	String wolf[2] = { "texture/10.png","texture/10.png" };
	String fox[2] = { "texture/11.png","texture/11.png" };
	String deer[2] = { "texture/8.png","texture/8.png" };
	String bear[2] = { "texture/9.png","texture/9.png" };
	String mouse[2] = { "texture/7.png","texture/7.png" };
	s1.setTexture(tx1);
	s1.setTextureRect(IntRect(0, 0, 20, 20));
	for (int i = 0; i<HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == '2')
			{
				world[nonOrg::getI()] = new nonOrg("texture/2.png", '0' + 2, j*20, i*20, 20, 20);
			}
			if (TileMap[i][j] == '1')
			{
				world[nonOrg::getI()] = new nonOrg("texture/1.png", '0' + 1, j * 20, i * 20, 20, 20);
			}
			if (Objects[i][j] == '3')
			{
				trees[flora::getI()] = new flora(tree_t, '0'+3, j * 20, i * 20, 30, 30, 3);
			}
			if (Objects[i][j] == '4')
			{
			trees[flora::getI()] = new flora(tree_b, '0' + 3, j * 20, i * 20, 20, 20, 2);
			}
			if (Objects[i][j] == 'C')
			{
				people[human::getI()] = new human(p, '0'+12, 100, j * 20, i * 20, 20, 20, 0);
			}
			if (Objects[i][j] == 'D')
			{
				people[human::getI()] = new human(p, '0'+13, 100, j * 20, i * 20, 20, 20, 1);
			}
			if (Objects[i][j] == 'E')
			{
				home[village::getI()] = new village("texture/14.png", 14, j * 20, i * 20, 20, 20);
			}
			if (Objects[i][j] == '6')
			{
				animals[animal::getI()] = new animal(rabbit, '0'+6, 100, j * 20, i * 20, 10, 10, rand() % 1);
			}
			if (Objects[i][j] == '9')
			{
				beasts[beast::getI()] = new beast(bear, '0'+9, 100, j * 20, i * 20, 20, 20, rand() % 1);
			}
			if (Objects[i][j] == '7')
			{
				animals[animal::getI()] = new animal(mouse, '0'+7, 100, j * 20, i * 20, 5, 5, rand() % 1);
			}
			if (Objects[i][j] == '8')
			{
				animals[animal::getI()] = new animal(deer, '0' + 8, 100,  j * 20, i * 20, 20, 20, rand() % 1);
			}
			if (Objects[i][j] == 'A')
			{
				beasts[beast::getI()] = new beast(wolf, '0' + 10, 100, j * 20, i * 20, 20, 20, rand()%1);
			}
			if (Objects[i][j] == 'B')
			{
				beasts[beast::getI()] = new beast(fox, '0' + 11, 100, j * 20, i * 20, 20, 20, rand() % 1);
			}
		}
	
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		float time_S = clock.getElapsedTime().asSeconds();
		clock.restart();
		time = time / 800;
		timer_of_day += time_S;
		timer_of_hunger += time_S;
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
							people[i]->goTO(pos.x, pos.y,20,20);
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
							beasts[i]->goTO(pos.x, pos.y,20,20);
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
			if (timer_of_day >= time_day)
			{
				trees[i]->grow();
				trees[i]->reload();
			}
		}
		for (int i = 0; i <= village::getI(); i++)
			window.draw(home[i]->getSprite());
		for (int i = 0; i <= beast::getI(); i++)
		{
			if (timer_of_hunger >= time_eat)
			{
				beasts[2]->hung(1, 1);
				if (beasts[2]->hung() == 2)
				{
					//delete beasts[2];
					*beasts[2] = *beasts[beast::getI()];
				//	beasts[2]->hung(0);
				//	cout << beasts[2]->ID() << endl;
				//	cout << beasts[beast::getI()]->ID() << endl;
				//	beasts[2]->goTO(500, 500, 20, 20);
					//delete beasts[beast::getI()];
					//beast::setI(0, 1);
				}
			}
			window.draw(beasts[i]->getSprite());
			beasts[i]->Move(time);
			beasts[i]->reload();
			//beasts[i]->target();
		}
		for (int i = 0; i <= animal::getI(); i++)
		{
			if (timer_of_hunger >= time_eat)
			{
				animals[i]->hung(1, 1);
			}
			window.draw(animals[i]->getSprite());
			animals[i]->Move(time);
			animals[i]->reload();
			//animals[i]->target();
		}
		for (int i = 0; i <= human::getI(); i++)
		{
			window.draw(people[i]->getSprite());
			if (timer_of_hunger >= time_eat)
			{
				people[i]->hung(1, 1);
			}
			people[i]->Move(time);
			people[i]->reload();
			people[i]->target();
		}
		if (timer_of_day >= time_day)
		{
			number_day++;
			timer_of_day = 0;
		}
		if (timer_of_hunger >= time_eat)
		{
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
