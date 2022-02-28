#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<iostream>
#include<sstream>
#include<string>
using namespace std;
using namespace sf;

class nodeplayer
{
public:
	int location;
	int playerselect;
	//playerselect= nomor player
	nodeplayer* next;
	Sprite playersprite;
	Sprite infosprite;
	Font fonts;
	string nama;
	Text playertext;
	Texture playertexture;
	std::stringstream playerstring;
	float x, y;
	float xinfo, xsinfo;
};
class Players
{
public:
	nodeplayer* head, * tail;
	int playercount;
	nodeplayer* current;
	Players();
	~Players();
	void initPlayer(int count,float scalingx,float scalingy);
	void reset(int count, float scalingx, float scalingy);
	void deleteplayer(int x);
	void render(RenderTarget& target);
};