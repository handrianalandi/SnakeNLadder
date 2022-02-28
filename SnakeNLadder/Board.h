#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<math.h>
#define gamesize 100
#define maxsnake 6
#define maxladder 6
#define laddersnakespawnlevel 3
//higher laddersnakespawnlevel, less snake and ladder
#define supriselevel 10
using namespace sf;
class node
{
public:
	bool surprise;
	int location;
	node* next, * prev, * jump;
	float locx, locy;
	//next= petak berikutnya
	//prev= petak sebelumnya
	//jump= petak tujuan jump(ladder/snake)
	//surprise=petak surprise(bisa maju atau mundur)
	//location=lokasi dari petak yang sekarang
};
class Board
{
public:
	node* head, * tail;
	int snake, ladder;
	node* current;
	Board();
	~Board();
	void reset(float scalingx,float scalingy);
};