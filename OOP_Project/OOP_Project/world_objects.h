#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class object
{
private:
	int type;
	int x;
	int s_x;
	int y;
	int s_y;
	int weigth;
	int food_value;
	Texture texture;
	Sprite sprite;
protected:
	virtual void a() = 0;
	Sprite *getSprite()
	{
		return &sprite;
	}
public:
	virtual ~object() = 0
	{
	}
};

class nonOrg : public object
{
private:
protected:
public:
};

class stone : public nonOrg
{

};

class village : public nonOrg
{

};

class flora : public object
{
private:
protected:
	virtual void f() = 0;
public:
};

class tree : public flora
{

};

class berry : public flora
{

};

class fauna : public object
{
private:
	int step_x;
	int step_y;
protected:
public:
};

class human : public fauna
{

};

class beast : public fauna //It's dangerous animal: tiger, bear

{

};

class animal : public fauna //It's friendly animal: rabbit, deer
{

};