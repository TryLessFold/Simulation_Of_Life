#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class object
{
private:
	int id;
	int x;
	int sq_x;
	int y;
	int sq_y;
	int weigth;
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
	int ID()
	{
		return id;
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

};  //2

class village : public nonOrg
{

};

class water : public nonOrg
{

}; //1

class flora : public object
{
private:
protected:
	virtual void f() = 0;
public:
};

class tree : public flora
{

}; //3

class berry : public flora
{

}; //4

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

}; //3, 4, 5

class animal : public fauna //It's friendly animal: rabbit, deer
{

}; //5, 6, 7