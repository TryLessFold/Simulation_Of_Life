#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

struct list
{
	int id;
	int weigth;
	int value;
	list* next;
	list* prev;
};

class listc
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

class stone : public object
{
	
};  //2

class village : public object
{

};

class water : public object
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