#include <SFML/Graphics.hpp>
#include <iostream>
#include "world_objects.h"

using namespace sf;
using namespace std;

int main()
{
	const int time_day = 20;
	const int time_eat = 3;
	const int time_mating = 1;
	const int trigger_hunger = 20;
	RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	SupportClass::SetScreen(1280, 720);
	SupportClass::SetCube();
	//SupportClass::push_NonGo('0'+1);
	SupportClass::push_SlowGo('0' + 1);
	SupportClass::push_NonGo('0' + 2);
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
	String tree_t[5] = { "texture/3.png","texture/3.png","texture/3.png","texture/3.png","texture/3.png" };
	String tree_b[5] = { "texture/4_1.png","texture/4_2.png","texture/4_2.png","texture/4_2.png","texture/4_2.png" };
	String p[2] = { "texture/12.png","texture/13.png" };
	String rabbit[2] = { "texture/6.png","texture/6.png" };
	String wolf[2] = { "texture/10.png","texture/10.png" };
	String fox[2] = { "texture/11.png","texture/11.png" };
	String deer[2] = { "texture/8.png","texture/8.png" };
	String bear[2] = { "texture/9.png","texture/9.png" };
	String mouse[2] = { "texture/7.png","texture/7.png" };
	s1.setTexture(tx1);
	s1.setTextureRect(IntRect(0, 0, 20, 20));
	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == '2')
			{
				world[nonOrg::getI()] = new nonOrg("texture/2.png", '0' + 2, j * 20, i * 20, 20, 20, 10);
				world[nonOrg::getI()]->inv()->push(5, 1 + rand() % 3, 3);
				world[nonOrg::getI()]->inv()->push(7, 0 + rand() % 1, 3);
			}
			if (TileMap[i][j] == '1')
			{
				world[nonOrg::getI()] = new nonOrg("texture/1.png", '0' + 1, j * 20, i * 20, 20, 20, 2);
				world[nonOrg::getI()]->inv()->push(10, 1, 1);
			}
			if (Objects[i][j] == '3')
			{
				trees[flora::getI()] = new flora(tree_t, '0' + 3, j * 20, i * 20, 30, 30, 3, 8);
				trees[flora::getI()]->inv()->push(4, 2 + rand() % 3, 3);
				trees[flora::getI()]->inv()->push(9, 0 + rand() % 1, 1);
			}
			if (Objects[i][j] == '4')
			{
				trees[flora::getI()] = new flora(tree_b, '0' + 4, j * 20, i * 20, 20, 20, 2, 5);
			}
			if (Objects[i][j] == 'C')
			{
				people[human::getI()] = new human(p, '0' + 12, 100, j * 20, i * 20, 20, 20, 0, 10 * time_day);
				people[human::getI()]->inv()->push(6, 1, 1);
				people[human::getI()]->rat()->push('0' + 6, 1);
				people[human::getI()]->rat()->push('0' + 8, 1);
				people[human::getI()]->rat()->push('0' + 12, 4);
				people[human::getI()]->rat()->push('0' + 11, 3);
				people[human::getI()]->rat()->push('0' + 9, 1);
			}
			if (Objects[i][j] == 'D')
			{
				people[human::getI()] = new human(p, '0' + 13, 100, j * 20, i * 20, 20, 20, 1, 10 * time_day);
				people[human::getI()]->inv()->push(6, 1, 1);
				people[human::getI()]->rat()->push('0' + 6, 1);
				people[human::getI()]->rat()->push('0' + 8, 1);
				people[human::getI()]->rat()->push('0' + 12, 4);
				people[human::getI()]->rat()->push('0' + 11, 3);
				people[human::getI()]->rat()->push('0' + 9, 1);
			}
			if (Objects[i][j] == 'E')
			{
				home[village::getI()] = new village("texture/14.png", 14, j * 20, i * 20, 20, 20);
			}
			if (Objects[i][j] == '6')
			{
				animals[animal::getI()] = new animal(rabbit, '0' + 6, 5, j * 20, i * 20, 10, 10, rand() % 2, 10);
				animals[animal::getI()]->inv()->push(1, 2, 1);
				animals[animal::getI()]->inv()->push(2, 1, 1);
			}
			if (Objects[i][j] == '9')
			{
				beasts[beast::getI()] = new beast(bear, '0' + 9, 100, j * 20, i * 20, 20, 20, rand() % 2, 7, 5 * time_day);
				beasts[beast::getI()]->inv()->push(1, 4, 1);
				beasts[beast::getI()]->inv()->push(2, 4, 1);
				beasts[beast::getI()]->rat()->push('0' + 8, 4);
				beasts[beast::getI()]->rat()->push('0' + 6, 4);
				//beasts[beast::getI()]->rat()->push('0' + 4, 1);
			}
			if (Objects[i][j] == '7')
			{
				animals[animal::getI()] = new animal(mouse, '0' + 7, 3, j * 20, i * 20, 5, 5, rand() % 2, 10);
				animals[animal::getI()]->inv()->push(1, 1, 1);
			}
			if (Objects[i][j] == '8')
			{
				animals[animal::getI()] = new animal(deer, '0' + 8, 10, j * 20, i * 20, 20, 20, rand() % 2, 2 * time_day);
				animals[animal::getI()]->inv()->push(1, 4, 1);
				animals[animal::getI()]->inv()->push(2, 3, 1);
			}
			if (Objects[i][j] == 'A')
			{
				beasts[beast::getI()] = new beast(wolf, '0' + 10, 10, j * 20, i * 20, 20, 20, rand() % 2, 5, 3 * time_day);
				beasts[beast::getI()]->inv()->push(1, 2, 1);
				beasts[beast::getI()]->inv()->push(2, 2, 1);
				beasts[beast::getI()]->rat()->push('0' + 6, 4);
				beasts[beast::getI()]->rat()->push('0' + 8, 4);
			}
			if (Objects[i][j] == 'B')
			{
				beasts[beast::getI()] = new beast(fox, '0' + 11, 10, j * 20, i * 20, 20, 20, rand() % 2, 5, 3 * time_day);
				beasts[beast::getI()]->inv()->push(1, 2, 1);
				beasts[beast::getI()]->inv()->push(2, 2, 1);
				beasts[beast::getI()]->rat()->push('0' + 6, 4);
				beasts[beast::getI()]->rat()->push('0' + 7, 4);
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
			if (timer_of_day >= time_day)
			{
				trees[i]->grow();
				trees[i]->reload();
			}
		}
		for (int i = 0; i <= village::getI(); i++)
			window.draw(home[i]->getSprite());
		for (int i = beast::getI(); i >= 0; i--)
		{
			beasts[i]->mating(time_S);
			if (timer_of_hunger >= time_eat)
			{
				beasts[i]->hung(1, 1);
			}
			SupportClass::XY tmp = beasts[i]->target();
			if (tmp.mode == 1)
			{
				beasts[i]->goTO((tmp.x) * SupportClass::GetCube(), (tmp.y) * SupportClass::GetCube(), SupportClass::GetCube(), SupportClass::GetCube());
			}
			if (beasts[i]->isattack())
			{
				for (int j = animal::getI(); j >= 0; j--)
				{
					if ((abs(beasts[i]->retX() - animals[j]->retX()) <= 20)
						&& (abs(beasts[i]->retY() - animals[j]->retY()) <= 20) && (beasts[i]->rat()->search(animals[j]->ID()) != 0))
					{
						animals[j]->setHP((animals[j]->getHP()) - (beasts[i]->Dam()));
						if (animals[j]->getHP() <= 0)
						{
							if (animals[j]->inv()->search(1))
								beasts[i]->hung(0, beasts[i]->rat()->search(animals[j]->ID())->value*animals[j]->inv()->search(1)->value);
							Objects[(int)animals[j]->masCoord().y][(int)animals[j]->masCoord().x] = '0';
							delete animals[j];
							animals[j] = new animal(*animals[animal::getI()]);
							animal::setI(0, 1);
						}
					}
				}
			}
			if (beasts[i]->hung() >= trigger_hunger)
			{
				Objects[(int)beasts[i]->masCoord().y][(int)beasts[i]->masCoord().x] = '0';
				beasts[i] = new beast(*beasts[beast::getI()]);
				beast::setI(0, 1);
			}
			if (tmp.mode == 2)
			{
				for (int j = 0; j <= beast::getI(); j++)
				{
					if (j == i)
					{
						if (j == beast::getI()) break;
						j++;
					}
					if ((beasts[j]->masCoord().x == tmp.x) && (beasts[j]->masCoord().y == tmp.y))
					{
						cout << beasts[i]->getSex() << " " << beasts[j]->getSex() << endl;

						if ((beasts[i]->getSex() != beasts[j]->getSex()) && (beasts[j]->mating(0)))
						{
							cout << 1 << endl;
							beasts[i]->goTO((tmp.x) * SupportClass::GetCube(), (tmp.y) * SupportClass::GetCube(), SupportClass::GetCube(), SupportClass::GetCube());
							beasts[i]->ismating(1);
							beasts[i]->isnon(0);
						}
					}
				}
			}
			if (beasts[i]->ismating())
			{
				for (int j = 0; j <= beast::getI(); j++)
				{
					if (j == i)
					{
						if (j == beast::getI()) break;
						j++;
					}
					if ((abs(beasts[i]->retX() - beasts[j]->retX()) <= 10)
						&& (abs(beasts[i]->retY() - beasts[j]->retY()) <= 10) && (beasts[j]->mating(0)))
					{
						int xt = beasts[i]->retX(), yt = beasts[i]->retY();
						if (beasts[i]->ID() == '0' + 9)
						{
							beasts[beast::getI()] = new beast(bear, '0' + 9, 100, xt, yt + 20, 20, 20, rand() % 2, 7, 5 * time_day);
							beasts[beast::getI()]->inv()->push(1, 4, 1);
							beasts[beast::getI()]->inv()->push(2, 4, 1);
							beasts[beast::getI()]->rat()->push('0' + 8, 4);
							beasts[beast::getI()]->rat()->push('0' + 6, 4);
							//beasts[beast::getI()]->rat()->push('0' + 4, 1);
						}
						if (beasts[i]->ID() == '0' + 10)
						{
							beasts[beast::getI()] = new beast(wolf, '0' + 10, 10, xt, yt + 20, 20, 20, rand() % 2, 5, 3 * time_day);
							beasts[beast::getI()]->inv()->push(1, 2, 1);
							beasts[beast::getI()]->inv()->push(2, 2, 1);
							beasts[beast::getI()]->rat()->push('0' + 6, 4);
							beasts[beast::getI()]->rat()->push('0' + 8, 4);
						}
						if (beasts[i]->ID() == '0' + 11)
						{
							beasts[beast::getI()] = new beast(fox, '0' + 11, 10, xt, yt + 20, 20, 20, rand() % 2, 5, 3 * time_day);
							beasts[beast::getI()]->inv()->push(1, 2, 1);
							beasts[beast::getI()]->inv()->push(2, 2, 1);
							beasts[beast::getI()]->rat()->push('0' + 6, 4);
							beasts[beast::getI()]->rat()->push('0' + 7, 4);
						}
						beasts[i]->matings(0);
						beasts[j]->matings(0);
						beasts[i]->ismating(0);
						beasts[j]->ismating(0);
					}
				}
			}
			window.draw(beasts[i]->getSprite());
			beasts[i]->Move(time);
			beasts[i]->reload();
		}
		for (int i = animal::getI(); i >= 0; i--)
		{
			animals[i]->mating(time_S);
			if (animals[i]->hung() >= trigger_hunger)
			{
				Objects[(int)animals[i]->masCoord().y][(int)animals[i]->masCoord().x] = '0';
				animals[i] = new animal(*animals[animal::getI()]);
				animal::setI(0, 1);
			}
			window.draw(animals[i]->getSprite());
			animals[i]->Move(time);
			animals[i]->reload();
			SupportClass::XY tmp = animals[i]->target();
			if (tmp.mode == 2)
			{
				for (int j = 0; j <= animal::getI(); j++)
				{
					if (j == i)
					{
						if (j == animal::getI()) break;
						j++;
					}
					if ((animals[j]->masCoord().x == tmp.x) && (animals[j]->masCoord().y == tmp.y))
					{
						//cout << animals[i]->getSex() << " " << animals[j]->getSex() << endl;
						//cout <<animals[j]->getMat()<<" "<< animals[j]->imating();
						if ((animals[i]->getSex() != animals[j]->getSex()) && (animals[j]->mating(0)))
						{
							cout << 2 << endl;
							animals[i]->goTO((tmp.x) * SupportClass::GetCube(), (tmp.y) * SupportClass::GetCube(), SupportClass::GetCube(), SupportClass::GetCube());
							animals[i]->ismating(1);
							animals[i]->isnon(0);
						}
					}
				}
			}
			if (animals[i]->ismating())
			{
				for (int j = 0; j <= animal::getI(); j++)
				{
					if (j == i)
					{
						if (j == animal::getI()) break;
						j++;
					}
					if ((abs(animals[i]->retX() - animals[j]->retX()) <= 10)
						&& (abs(animals[i]->retY() - animals[j]->retY()) <= 10) && (animals[j]->mating(0)))
					{
						int xt = animals[i]->retX(), yt = animals[i]->retY();
						if (animals[i]->ID() == '0' + 6)
						{
							animals[animal::getI()] = new animal(rabbit, '0' + 6, 5, xt, yt + 20, 10, 10, rand() % 2, 5);
							animals[animal::getI()]->inv()->push(1, 2, 1);
							animals[animal::getI()]->inv()->push(2, 1, 1);
						}
						if (animals[i]->ID() == '0' + 8)
						{
							animals[animal::getI()] = new animal(deer, '0' + 8, 7, xt, yt + 20, 20, 20, rand() % 2, 2 * time_day);
							animals[animal::getI()]->inv()->push(1, 4, 1);
							animals[animal::getI()]->inv()->push(2, 4, 1);
						}
						if (animals[i]->ID() == '0' + 7)
						{
							animals[animal::getI()] = new animal(mouse, '0' + 7, 3, xt, yt + 20, 5, 5, rand() % 2, 5);
							animals[animal::getI()]->inv()->push(1, 1, 1);
						}
						animals[i]->matings(0);
						animals[j]->matings(0);
						animals[i]->ismating(0);
						animals[j]->ismating(0);
					}
				}
			}
		}
		for (int i = human::getI(); i >= 0; i--)
		{
			people[i]->mating(time_S);
			window.draw(people[i]->getSprite());
			if (timer_of_hunger >= time_eat)
			{
				people[i]->hung(1, 1);
			}
			if (people[i]->hung() >= trigger_hunger)
			{
				Objects[(int)people[i]->masCoord().y][(int)people[i]->masCoord().x] = '0';
				people[i] = new human(*people[human::getI()]);
				human::setI(0, 1);
			}
			SupportClass::XY tmp = people[i]->target();
			if (tmp.mode == 1)
			{
				people[i]->goTO((tmp.x) * SupportClass::GetCube(), (tmp.y) * SupportClass::GetCube(), SupportClass::GetCube(), SupportClass::GetCube());
			}
			people[i]->Move(time);
			people[i]->reload();
		}
		if (timer_of_day >= time_day)
		{
			number_day++;
			timer_of_day = 0;
		}
		if (timer_of_hunger >= time_eat)
		{
			timer_of_hunger = 0;
		}
		//	cout << timer_of_day<<" "<<timer_of_hunger<<endl;
			/*for (int i = 20; i <= 30; i++)
			{
				for (int j = 40; j <= 50; j++) cout << Objects[i][j];
				cout << endl;
			}*/
			//system("CLS");
		window.display();
	}
	return 0;
}
