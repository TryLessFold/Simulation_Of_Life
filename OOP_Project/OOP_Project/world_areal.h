#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class areal
{
private:
	int type;
	int sq_x;
	int areal_color;
protected:
	areal(int value1, int value2, int value3) :: type(value1), sq_x(value2), areal_color(value3)
	{
	}
public:
	virtual void setAreal() = 0;
	{
	}
};

class water : public areal
{
	
}

class stone : public areal
{
	
};

class earth : public areal
{
	
};

class wind : public areal
{
	
};

