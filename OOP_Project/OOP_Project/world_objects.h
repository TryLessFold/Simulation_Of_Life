#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
#include "sstream"

#define PI 3.14159265  

using namespace std;
using namespace sf;

class listc
{
private: 
protected:
	struct list
	{
		int id;
		int weigth;
		int value;
		list* next;
		list* prev;
	};
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
	virtual void push(int i, int v = 0 , int w = 0)
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
		if (tmp != NULL)
		{
			while ((tmp->next != NULL) && (tmp->id != i))
				tmp = tmp->next;
			if (tmp->id == i) return tmp;
			else
			{
				tmp = new list;
				tmp->value = 0;
				tmp->weigth = 0;
				tmp->id = 0;
				return 0;
			}
		}
		tmp = new list;
		tmp->value = 0;
		tmp->weigth = 0;
		tmp->id = 0;
		return 0;
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

class SupportClass
{
protected:
	static int ScreenHeigth;
	static int ScreenWidth;
	static listc NonGo;
	static listc SlowGo;
	static listc FastGo;
	static int size_of_cube;
	float const_timer_step;
public:
	struct XY
	{
		int mode;
		float x;
		float y;
	};
	static void push_NonGo(int i)
	{
		NonGo.push(i);
	}
	static void push_SlowGo(int i)
	{
		SlowGo.push(i);
	}
	static void SetScreen(int s_h = 720, int s_w = 1280)
	{
		ScreenHeigth = s_h;
		ScreenWidth = s_w;
	}
	static void SetCube(int s = 20)
	{
		size_of_cube = s;
	}
	static int GetCube()
	{
		return size_of_cube;
	}
	int retSH()
	{
		return ScreenHeigth;
	}
	int retSW()
	{
		return ScreenWidth;
	}
};

class object : public SupportClass
{
protected:
	int hp;
	int id;
	int sq_x;
	int sq_y;
	double x;
	double y;
	Texture texture;
	Sprite sprite;
	inventory Inv;
	object(const object &copy)
	{
		x = copy.x;
		y = copy.y;
		sq_x = copy.sq_x;
		sq_y = copy.sq_y;
		id = copy.id;
		hp = copy.hp;
		texture = copy.texture;
		sprite = copy.sprite;
		Inv = copy.Inv;
	}
public:
	object() {}
	virtual ~object()
	{
		Inv.DeleteList();
	}
	virtual object* copy() const = 0;
	virtual void f() = 0;
	Sprite getSprite()
	{
		return sprite;
	}
	int ID()
	{
		return id;
	}
	virtual void reload()
	{
		sprite.setPosition(x, y);
		Objects[(int)y / size_of_cube][(int)x / size_of_cube] = id;
	}
	inventory* inv()
	{
		return &Inv;
	}
	float retX()
	{
		return x;
	}
	float retY()
	{
		return y;
	}
	XY masCoord()
	{
		XY ll;
		ll.mode = -1;
		ll.x = x/ size_of_cube;
		ll.y = y/ size_of_cube;
		return ll;
	}
	int getHP()
	{
		return hp;
	}
	void setHP(int i = 10)
	{
		hp = i;
	}
};

class nonOrg : public object
{
private:
	static int i;
	int time_to_break;
	String back;
public:
	static int getI()
	{
		return i;
	}
	nonOrg() {}
	nonOrg(String s, int ID, int xe, int ye, int xe_s, int ye_s, int t_b)
	{
		time_to_break = t_b;
		back = s;
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
	nonOrg(const nonOrg &copy) : object(copy)
	{
		Image image;
		image.loadFromFile(back);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, sq_x, sq_y));
		sprite.setPosition(x, y);
	}
	nonOrg* copy() const
	{
		nonOrg *ret = new nonOrg(*this);
		return ret;
	}
	void reload()
	{
		sprite.setPosition(x, y);
	}
	void f()
	{}
};  

class village : public object
{
private:
	static int i;
	String back;
public:
	static int getI()
	{
		return i;
	}
	village() {}
	village(String s, int ID, int xe, int ye, int xe_s, int ye_s)
	{
		back = s;
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
	village(const village &copy) : object(copy)
	{
		Image image;
		image.loadFromFile(back);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, sq_x, sq_y));
		sprite.setPosition(x, y);
	}
	village* copy() const
	{
		village *ret = new village(*this);
		return ret;
	}
	void f()
	{}
};

class flora : public object
{
private:
	static int i;
	String growing[5];
	int time_to_break;
	int lvl_gr;
	int maxgr;
	bool isGrow;
protected:
public:
	static int getI()
	{
		return i;
	}
	static void setI(int ch, int ii)
	{
		if (ch == 0) i -= ii;
		else if (ch == 1) i += ii;
		else i = ii;
	}
	flora()
	{}
	flora(String *s, int ID, int xe, int ye, int xe_s, int ye_s, int maxgrow, int t_b)
	{
		time_to_break = t_b;
		maxgr = maxgrow;
		++i;
		id = ID;
		x = xe;
		y = ye;
		sq_x = xe_s;
		sq_y = ye_s;
		isGrow = 0;
		lvl_gr = 0;
		Image image;
		image.loadFromFile(s[0]);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, sq_x, sq_y));
		sprite.setPosition(x, y);
		for (int i = 0; i < maxgr; i++)
		{
			growing[i] = s[i];
		}
	}
	flora(const flora &copy) : object(copy)
	{
		for (int i = 0; i < 5; i++)
		{
			growing[i] = copy.growing[i];
		}
		lvl_gr = copy.lvl_gr;
		maxgr = copy.maxgr;
		isGrow = copy.isGrow;
		Image image;
		image.loadFromFile(growing[lvl_gr]);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, sq_x, sq_y));
		sprite.setPosition(x, y);
	}
	virtual flora* copy() const
	{
		flora *ret = new flora(*this);
		return ret;
	}
	void grow()
	{
		if (lvl_gr < maxgr-1)
		{
			lvl_gr++;
			Image image;
			image.loadFromFile(growing[lvl_gr]);
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			if (lvl_gr == maxgr) isGrow = 1;
		}
	}
	void take()
	{
		isGrow = 0;
		lvl_gr = 0;
		Image image;
		image.loadFromFile(growing[lvl_gr]);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
	bool isgrow()
	{
		return isGrow;
	}
	void isgrow(bool x)
	{
		isGrow = x;
	}
	void f()
	{}
};

class fauna : public object
{
private:
protected:
	String sex_t[2];
	float base_move;
	int hunger;
	int radar;
	int mating_time;
	int to_x;
	int to_y;
	float step_x;
	float step_y;
	int sex;
	bool isAttack;
	bool isMating;
	bool isMove;
	bool isNon;
	bool isFear;
	bool isSelect;
	float timer_mating;
	float timer_step;
	listc ration;
	fauna(const fauna &copy) : object(copy)
	{
		step_x = copy.step_x;
		step_y = copy.step_y;
		sex = copy.sex;
		base_move = copy.base_move;
		hunger = copy.hunger;
		for (int i = 0; i < 2; i++)
		{
			sex_t[i] = copy.sex_t[i];
		}
		radar = copy.radar;
		mating_time = copy.mating_time;
		to_x = copy.to_x;
		to_y = copy.to_y;
		isAttack = copy.isAttack;
		isMove = copy.isMove;
		isNon = copy.isNon;
		isFear = copy.isFear;
		isSelect = copy.isSelect;
		timer_step = copy.timer_step;
	}
public:
	virtual void f() = 0;
	virtual ~fauna() {}
	fauna() : timer_step(0), hunger(0), radar(8)
	{
		const_timer_step = 1000 + rand() % 2000;
	}

	void changeStep(float step)
	{
		step_x = step;
		step_y = step;
	}
	virtual void goTO(int t_x, int t_y, int s_x, int s_y)
	{
		//cout << retSW() << " " << t_x << endl;
		while((t_x<0)||(t_x+s_x>retSH())) t_x = (x - 40) + rand() % 100;
		to_x = (t_x / 20) * 20;
		//cout << retSH() << " " << t_y << endl;
		while ((t_y<0) || (t_y+s_y>retSW())) t_y = (y - 40) + rand() % 100;
		to_y = (t_y / 20) * 20;
		isMove = 1;
	}
	virtual void Move(float time1)
	{
		double distance;
		int ox=x/20, oy=y/20;
		if ((isMove)&&(timer_step>const_timer_step))
		{
			
			distance = sqrt((to_x - x)*(to_x - x) + (to_y - y)*(to_y - y));
			if ((distance > 2)&&(timer_step>const_timer_step))
			{
				Objects[oy][ox] = id;
				x += step_x * time1*(to_x - x) / distance;
				y += step_y * time1*(to_y - y) / distance;
				int xx = x / 20, yy = y / 20;
				int sxx = (x + sq_x) / 20; int syy = (y + sq_y) / 20;
				if (NonGo.search(TileMap[yy][xx])|| NonGo.search(TileMap[syy][sxx]))
				{
					x -= step_x * time1*(to_x - x) / distance;
					y -= step_y * time1*(to_y - y) / distance;
					int ranx = (x - 40) + rand() % 100;
					int rany = (y - 40) + rand() % 100;
					if(isNon)
					goTO(ranx, rany, sq_x, sq_y);
					else isMove = 0;
				}
				if (SlowGo.search(TileMap[yy][xx]) || SlowGo.search(TileMap[syy][sxx]))
				{
					changeStep(0.02);
				}
				else if (isAttack) changeStep(0.06);
				else changeStep(base_move);
				if ((((int)(x / 20)) != ox) || (((int)(y / 20)) != oy))
				{
					char tmp = Objects[oy][ox];
					Objects[oy][ox] = '0';
				}
			}
			else if (timer_step <= const_timer_step)
			{
				timer_step += time1;
			}
			else if ((isAttack)||(isMating))
			{
				x = to_x;
				y = to_y;
				int xx = x / 20, yy = y / 20;
				Objects[oy][ox] = '0';
				Objects[yy][xx] = id;
				isNon = 1;
			}
			else
			{
				x = to_x;
				y = to_y;
				int xx = x / 20, yy = y/20;
				Objects[oy][ox] = '0';
				Objects[yy][xx] = id;
				isMove = 0;
				//cout << "x = " << x << " ";
				if (isNon)
				{
					int ranx = (x - 40) + rand() % 100;
					int rany = (y - 40) + rand() % 100;
					goTO(ranx, rany, sq_x, sq_y);
					timer_step = 0;
					const_timer_step = 1000 + rand() % 2000;
					//cout << "x = " << const_timer_step << " ";
				}
			}
		}
		else
		{
			timer_step += time1;
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
	bool isnon()
	{
		return isNon;
	}
	void isnon(bool x)
	{
		isNon = x;
	}
	bool isattack()
	{
		return isAttack;
	}
	void isattack(bool x)
	{
		isAttack = x;
	}
	bool ismating()
	{
		return isMating;
	}
	void ismating(bool x)
	{
		isMating = x;
	}
	virtual XY target(int sex=0)
	{
		int cos_x, sin_y, tmp_x, tmp_y;
		XY ll;
		ll.x = 0;
		ll.y = 0;
		ll.mode = 0;
		isAttack = 0;
		isNon = 1;
		for (int i = 1; i <= radar; i++)
		{
			for (int j = 0; j <= 360; j++)
			{
				cos_x = i*cos(j * PI / 180); 
				sin_y = i*sin(j * PI / 180);
				if ((cos_x != 0) && (sin_y != 0))
				{
					//cout << cos_x << " " << sin_y << endl;
					tmp_x = ((int)(x / size_of_cube) + cos_x);
					tmp_y = ((int)(y / size_of_cube) + sin_y);
					if ((tmp_x >= 0)&&(tmp_x< WIDTH_MAP) && (tmp_y >= 0)&& (tmp_y < HEIGHT_MAP))
					{
						if (Objects[tmp_y][tmp_x] != '0')
						{
							if ((hunger >= 5) && (ration.search(Objects[tmp_y][tmp_x])))
							{
								isAttack = 1;
								isNon = 0;
								if (((tmp_x * 2 + tmp_y * 2) < (to_x / size_of_cube * 2 + to_y / size_of_cube * 2))||((to_y == y)&&(to_x==x)))
								{
									//goTO((tmp_x) * size_of_cube, (tmp_y) * size_of_cube, size_of_cube, size_of_cube);
									ll.x = tmp_x;
									ll.y = tmp_y;
									ll.mode = 1;
								}
							}
							if ((timer_mating >= mating_time) && (Objects[tmp_y][tmp_x] == id))
							{
								if (((tmp_x * 2 + tmp_y * 2) < (to_x / size_of_cube * 2 + to_y / size_of_cube * 2)) || ((to_y == y) && (to_x == x)))
								{
									ll.x = tmp_x;
									ll.y = tmp_y;
									ll.mode = 2;
								}
							}
						}
					}
				}
			}
		}
		return ll;
	};
	int hung()
	{
		return hunger;
	}
	void hung(int i)
	{
		hunger = i;
	}
	void hung(int ch ,int i)
	{
		if (ch == 0)
			hunger -= i;
		else 
			hunger += i;
		if (hunger < 0) hunger = 0;
	}
	float getStep()
	{
		return step_x;
	}
	listc* rat()
	{
		return &ration;
	}
	bool mating(float time1)
	{
		if(timer_mating<=mating_time)
		timer_mating += time1;
		//cout << timer_mating <<" "<< mating_time << endl;
		if (timer_mating >= mating_time) return 1;
		return 0;
	}
	void matings(int i)
	{
		timer_mating = i;
	}
	int getSex()
	{
		return sex;
	}
	void setTimer_S(float s)
	{
		timer_step = s;
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
	static void setI(int ch, int ii)
	{
		if (ch == 0) i -= ii;
		else if (ch == 1) i += ii;
		else i = ii;
	}
	human() {}
	human(String *s, int ID, int hitp, int xe, int ye, int xe_s, int ye_s, int p, int m_t)
	{
		timer_mating = 0;
		mating_time = m_t;
		hunger = 0;
		base_move = 0.04;
		++i;
		hp = hitp;
		id = ID;
		x = xe;
		y = ye;
		sq_x = xe_s;
		sq_y = ye_s;
		sex = p;
		Image image;
		isAttack = 0;
		isMove = 1;
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
		int ranx = (x - 40) + rand() % 100;
		int rany = (y - 40) + rand() % 100;
		goTO(ranx, rany, sq_x, sq_y);
		for (int i = 0; i < 2; i++)
		{
			sex_t[i] = s[i];
		}
	}
	human(const human &copy) : fauna(copy)
	{
		Image image;
		if (sex == 0)
			image.loadFromFile(sex_t[0]);
		else
			image.loadFromFile(sex_t[1]);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, sq_x, sq_y));
		sprite.setPosition(x, y);
	}
	human* copy() const
	{
		human *ret = new human(*this);
		return ret;
	}
	void f()
	{}
}; 

class beast : public fauna 
{
private:
	static int i;
protected:
	int dam;
public:
	static int getI()
	{
		return i;
	}
	static void setI(int ch, int ii)
	{
		if (ch == 0) i -= ii;
		else if (ch == 1) i += ii;
		else i = ii;
	}
	beast(String *s, int ID, int hitp, int xe, int ye, int xe_s, int ye_s, int p, int a, int m_t)
	{
		timer_mating = 0;
		mating_time = m_t;
		dam = a;
		hunger = 0;
		base_move = 0.04;
		++i;
		id = ID;
		hp = hitp;
		x = xe;
		y = ye;
		sq_x = xe_s;
		sq_y = ye_s;
		sex = p;
		Image image;
		isAttack = 0;
		isMove = 1;
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
		int ranx = (x - 40) + rand() % 100;
		int rany = (y - 40) + rand() % 100;
		goTO(ranx, rany, sq_x, sq_y);
		for (int i = 0; i < 2; i++)
		{
			sex_t[i] = s[i];
		}
	}
	beast(const beast &copy) : fauna(copy)
	{
		dam = copy.dam;
		Image image;
		if (sex == 0)
			image.loadFromFile(sex_t[0]);
		else
			image.loadFromFile(sex_t[1]);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, sq_x, sq_y));
		sprite.setPosition(x, y);
	}
	beast* copy() const 
	{ 
		beast *ret = new beast(*this);
		return ret; 
	}
	int Dam()
	{
		return dam;
	}
	void Dam(int i)
	{
		dam = i;
	}
	void f()
	{}
};

class animal : public fauna //It's dangerous animal: tiger, bear
{
private:
	static int i;
protected:
public:
	static int getI()
	{
		return i;
	}
	static void setI(int ch, int ii)
	{
		if (ch == 0) i -= ii;
		else if (ch == 1) i += ii;
		else i = ii;
	}
	animal(String *s, int ID, int hitp, int xe, int ye, int xe_s, int ye_s, int p, int m_t)
	{
		timer_mating = 0;
		mating_time = m_t;
		hunger = 0;
		base_move = 0.04;
		radar = 5;
		++i;
		id = ID;
		hp = hitp;
		x = xe;
		y = ye;
		sq_x = xe_s;
		sq_y = ye_s;
		sex = p;
		Image image;
		isAttack = 0;
		isMove = 0;
		isNon = 1;
		isFear = 0;
		step_x = 0.04;
		step_y = 0.04;
		if (sex ==0)
		image.loadFromFile(s[0]);
		else image.loadFromFile(s[1]);
		isAttack = 0;
		isMove = 0;
		isNon = 1;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, sq_x, sq_y));
		sprite.setPosition(x, y);
		int ranx = (x - 40) + rand() % 100;
		int rany = (y - 40) + rand() % 100;
		goTO(ranx, rany, sq_x, sq_y);
		for (int i = 0; i < 2; i++)
		{
			sex_t[i] = s[i];
		}
	}
	animal(const animal &copy) : fauna(copy)
	{
		Image image;
		if (sex == 0)
			image.loadFromFile(sex_t[0]);
		else
			image.loadFromFile(sex_t[1]);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, sq_x, sq_y));
		sprite.setPosition(x, y);
	}
	animal* copy() const
	{
		animal *ret = new animal(*this);
		return ret;
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
listc SupportClass::NonGo;
listc SupportClass::SlowGo;
int SupportClass::ScreenHeigth = 720;
int SupportClass::ScreenWidth = 1280;
int SupportClass::size_of_cube = 20;