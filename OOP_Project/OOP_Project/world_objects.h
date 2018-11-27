#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
//#include "stdlib.h"
using namespace std;
using namespace sf;

class SupportClass
{
protected:
	int ScreenHeight;
	int ScreenWeight;
	struct list
	{
		int id;
		int weigth;
		int value;
		list* next;
		list* prev;
	};
public:
	virtual void f() = 0;
	void SetScreen(int s_h, int s_w)
	{
		ScreenHeight = s_h;
		ScreenWeight = s_w;
	}
	int retSH()
	{
		return ScreenHeight;
	}
	int retSW()
	{
		return ScreenWeight;
	}
};

class listc : public SupportClass
{
protected:
	list *head, *tail;
	int length;
public:
	listc(int i, int v) : head(NULL), tail(NULL)
	{
		length = 0;
		push(i, v);
	}
	listc() : head(NULL), tail(NULL)
	{
		length = 0;
	}
	~listc() { DeleteList(); }
	void setLength(int x)
	{
		if (x == 0) length = 0;
		else length += x;
	}
	void setHead(list* x)
	{
		head = x;
	}
	void setTail(list* x)
	{
		tail = x;
	}
	int getLength()
	{
		return length;
	}
	list* getHead()
	{
		return head;
	}
	list* getTail()
	{
		return tail;
	}
	virtual void push(int i, int v, int w=0)
	{
		length++;
		if (head == NULL)
		{
			struct list* tmp = new list;
			tmp->id = i;
			tmp->value = v;
			tmp->next = NULL;
			tmp->prev = NULL;
			head = tmp;
			tail = tmp;
		}
		else
		{
			struct list* tmp = head;
			while ((tmp->id != i) && (tmp->next != NULL))
				tmp = tmp->next;
			if (tmp->id == i)
			{
				tmp->value += v;
			}
			else
			{
				tmp->next = new list;
				tmp->next->prev = tmp;
				tmp = tmp->next;
				tail = tmp;
				tmp->next = NULL;
				tmp->id = i;
				tmp->value = v;
			}
		}
	}
	virtual void output()
	{
		struct list* tmp = head;
		if (tmp == NULL) cout << "List is empty" << endl;
		else
		{
			try
			{
				while (1)
				{
					cout << tmp->id <<" "<<tmp->value;
					tmp = tmp->next;
					if (tmp == NULL) throw 1;
				}
			}
			catch (int i)
			{
			};
		}
		cout << endl;
	}
	list* search(int i)
	{
		list*tmp = head;
			while ((tmp->next != NULL)&&(tmp->id!=i))
				tmp = tmp->next;
		if (tmp->id == i) return tmp;
		else return 0;
	}
	void DeleteList()
	{
		list* tmp = getHead();
		while (tmp != NULL)
		{
			setHead(tmp->next);
			delete tmp;
			tmp = getHead();
		}
	}
};

class inventory : public listc
{
private:
	int Weigth;
public:
	inventory() 
	{
		Weigth = 0;
	}
	int weigth()
	{
		return Weigth;
	}
	void push(int i, int v, int w) override
	{
		length++;
		Weigth += v*w;
		if (head == NULL)
		{
			struct list* tmp = new list;
			tmp->id = i;
			tmp->value = v;
			tmp->weigth = w;
			tmp->next = NULL;
			tmp->prev = NULL;
			head = tmp;
			tail = tmp;
		}
		else
		{
			struct list* tmp = head;
			while ((tmp->id != i) && (tmp->next != NULL))
				tmp = tmp->next;
			if (tmp->id == i)
			{
				tmp->value += v;
			}
			else
			{
				tmp->next = new list;
				tmp->next->prev = tmp;
				tmp = tmp->next;
				tail = tmp;
				tmp->next = NULL;
				tmp->id = i;
				tmp->value = v;
				tmp->weigth = w;
			}
		}
	}
	void output() override
	{
		struct list* tmp = head;
		if (tmp == NULL) cout << "List is empty" << endl;
		else
		{
			try
			{
				while (1)
				{
					cout << tmp->id << " " << tmp->weigth << " " << tmp->value << endl;
					tmp = tmp->next;
					if (tmp == NULL) throw 1;
				}
			}
			catch (int i)
			{
			};
		}
		cout << endl;
	}
	list *take(int l)
	{
		length--;
		list* tmp = head, *r = new list;
		if (head)
		{
			if ((tmp->value*tmp->weigth) <= l)
			{
				Weigth -= tmp->value*tmp->weigth;
				*r = *tmp;
				head = tmp->next;
				delete tmp;
				return r;
			}
			else
			{
				while (tmp)
				{
					if (tmp->weigth <= l)
					{
						int i = 0;
						for (i = 0; l >= tmp->weigth*i; i++);
						i--;
						Weigth -= i*tmp->weigth;
						tmp->value -= i;
						*r = *tmp;
						if (tmp->value == 0)
						{
							tmp->prev->next = tmp->next;
							tmp->next->prev = tmp->prev;
							delete tmp;
						}
						r->value = i;
						return r;
					}
					else tmp = tmp->next;
				}
			}
			return 0;
		}
		else return 0;
	}
};

class object : public SupportClass
{
protected:
	int id;
	int sq_x;
	int sq_y;
	int rad_x;
	int rad_y;
	double x;
	double y;
	Texture texture;
	Sprite sprite;
	inventory* Inv;
public:
	object() {}
	virtual ~object()
	{
		Inv->DeleteList();
		delete Inv;
	}
	virtual void f() = 0;
	Sprite getSprite()
	{
		return sprite;
	}
	int ID()
	{
		return id;
	}
	void reload()
	{
		sprite.setPosition(x, y);
	}
	inventory* inv()
	{
		return Inv;
	}
	int Radius()
	{
		return rad_x;
	}
	float retX()
	{
		return x;
	}
	float retY()
	{
		return y;
	}
};

class nonOrg : public object
{
private:
	static int i;
public:
	static int getI()
	{
		return i;
	}
	nonOrg() {}
	nonOrg(String s, int ID, int xe, int ye, int xe_s, int ye_s)
	{
		++i;
		id = ID;
		x = xe;
		y = ye;
		sq_x = xe_s;
		sq_y = ye_s;
		Image image;
		image.loadFromFile(s);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, sq_x, sq_y));
		sprite.setPosition(x, y);
	}
	void f()
	{}
};  

class village : public object
{
private:
	static int i;
public:
	static int getI()
	{
		return i;
	}
	village() {}
	village(String s, int ID, int xe, int ye, int xe_s, int ye_s)
	{
		++i;
		id = ID;
		x = xe;
		y = ye;
		sq_x = xe_s;
		sq_y = ye_s;
		Image image;
		image.loadFromFile(s);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, sq_x, sq_y));
		sprite.setPosition(x, y);
	}
	void f()
	{}
};

class flora : public object
{
private:
	static int i;
	int lvl_gr;
	Image s[5];
protected:
public:
	static int getI()
	{
		return i;
	}
	flora()
	{}
	flora(String *s, int ID, int xe, int ye, int xe_s, int ye_s)
	{
		++i;
		id = ID;
		x = xe;
		y = ye;
		sq_x = xe_s;
		sq_y = ye_s;
		rad_x = x;
		rad_y = y;
		lvl_gr = 0;
		Image image;
		image.loadFromFile(s[0]);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, sq_x, sq_y));
		sprite.setPosition(x, y);
	}
	void f()
	{}
};

class fauna : public object
{
private:
protected:
	int hp;
	int to_x;
	int to_y;
	float step_x;
	float step_y;
	int ranx;
	int rany;
	int sex;
	bool isAttack;
	bool isMove;
	bool isNon;
	bool isFear;
	bool isSelect;
	listc* ration;
public:
	virtual void f() = 0;
	void changeStep(float step)
	{
		step_x = step;
		step_y = step;
	}
	virtual void goTO(int t_x, int t_y)
	{
		to_x = (t_x / 20) * 20;
		cout << to_x << endl;
		to_y = (t_y / 20) * 20;
		isMove = 1;
	}
	virtual void Move(float time1)
	{
		double distance;
		if (isMove)
		{
			distance = sqrt((to_x - x)*(to_x - x) + (to_y - y)*(to_y - y));
			if (distance > 2)
			{
				x += step_x * time1*(to_x - x) / distance;
				y += step_y * time1*(to_y - y) / distance;
			}
			else
			{
				x = to_x;
				y = to_y;
				isMove = 0;
				cout << "x = " << x << " ";
				ranx = (x - 40) + rand() % 100;
				rany = (y - 40) + rand() % 100;
				if (isNon) goTO(ranx, rany);
			}
		}
	}
	bool ismove()
	{
		return isMove;
	}
	void ismove(bool x)
	{
		isMove = x;
	}
	bool isselect()
	{
		return isSelect;
	}
	void isselect(bool x)
	{
		isSelect = x;
	}
};

class human : public fauna
{
private:
	static int i;
public:
	static int getI()
	{
		return i;
	}
	human() {}
	human(String *s, int ID, int hitp, int xe, int ye, int xe_s, int ye_s, int p)
	{
		++i;
		hp = hitp;
		id = ID;
		x = xe;
		y = ye;
		sq_x = xe_s;
		sq_y = ye_s;
		rad_x = x;
		rad_y = y;
		sex = p;
		Image image;
		isAttack = 0;
		isMove = 0;
		isSelect = 0;
		isNon = 1;
		isFear = 0;
		step_x = 0.04;
		step_y = 0.04;
		if (sex == 0)
			image.loadFromFile(s[0]);
		else
			image.loadFromFile(s[1]);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, sq_x, sq_y));
		sprite.setPosition(x, y);
	}
	void f()
	{}
}; 

class beast : public fauna 
{
private:
	static int i;
protected:
public:
	static int getI()
	{
		return i;
	}
	beast(String *s, int ID, int hitp, int xe, int ye, int xe_s, int ye_s, int p)
	{
		++i;
		id = ID;
		hp = hitp;
		x = xe;
		y = ye;
		sq_x = xe_s;
		sq_y = ye_s;
		rad_x = x;
		rad_y = y;
		sex = p;
		Image image;
		isAttack = 0;
		isMove = 0;
		isNon = 1;
		isFear = 0;
		step_x = 0.1;
		step_y = 0.1;
		if (sex == 0)
			image.loadFromFile(s[0]);
		else
			image.loadFromFile(s[1]);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, sq_x, sq_y));
		sprite.setPosition(x, y);
	}
	void f()
	{}
};

class animal : public fauna //It's dangerous animal: tiger, bear
{
private:
	static int i;
	int skin;
protected:
public:
	static int getI()
	{
		return i;
	}
	animal(String *s, int ID, int hitp, int xe, int ye, int xe_s, int ye_s, int p, int sk)
	{
		++i;
		id = ID;
		hp = hitp;
		x = xe;
		y = ye;
		sq_x = xe_s;
		sq_y = ye_s;
		rad_x = x;
		rad_y = y;
		sex = p;
		skin = sk;
		Image image;
		isAttack = 0;
		isMove = 0;
		isNon = 1;
		isFear = 0;
		step_x = 0.1;
		step_y = 0.1;
		if (sex == 0)
			image.loadFromFile(s[0]);
		else if(sex == 1)
			image.loadFromFile(s[1]);
		else
		{
			if (skin == 0)
				image.loadFromFile(s[2]);
			else
				image.loadFromFile(s[3]);
		}
		isAttack = 0;
		isMove = 0;
		isNon = 1;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, sq_x, sq_y));
		sprite.setPosition(x, y);
	}
	void f()
	{}
};

int flora::i = -1;
int nonOrg::i = -1;
int human::i = -1;
int village::i = -1;
int beast::i = -1;
int animal::i = -1;