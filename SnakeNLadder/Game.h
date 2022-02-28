#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include"Players.h"
#include"Board.h"
#include<time.h>
#include<queue>

using namespace sf;
using namespace std;

class Game
{
private:
	RenderWindow *window;
	Event ev;
	FloatRect scallingwindow;

	//background
	Sprite boardsprite;
	Texture boardTexture;
	Sprite backgroundsprite;
	Texture backgroundtexture;
	

	//snakeandladdertest
	Sprite laddersprite, snakesprite;
	Texture laddertexture, snaketexture;

	//variables
	float width;
	float height;
	float scalingx;
	float scalingy;
	bool surp;
	//scalling berfungsi agar tampilan game sama di setiap layar komputer

	//main vars
	Board board;
	Players players;

	/*queue<int>winners;*/
	int wincount;
	int spacePressed;
	bool moving;
	bool win;
	bool someonewin;

	//texts
	Font playerfont;
	Text playertext;
	Text surprisetext;
	Text winnertext;
	stringstream playerselecttext;
	stringstream surprisestring;
	stringstream winnerstring;

	//timehandling
	Clock delays;

	//dice
	IntRect dicerect;
	Sprite dicesprite;
	Texture dicetexture;

	//surprise
	Clock surprisetimer;
public:
	Game(int x);
	~Game();
	const bool isRunning() const;
	void pollEvents();


	//initializations!!
	void initVariables(int x);
	void initWindow();
	void initBoard();
	void initBackground();
	void initText();
	void initsnakeladder();
	void initdice();

	//update
	void update();
	void updateplayer(int x);
	void updatetext();
	void updatedice(int x=0);
	void updatewinnertext();
	int randomize();
	//render
	void render();
	void playerspritemove(bool snakeladder);
	//snakeandladder test
	void snakeladderrender();
	void surpriserender();

	//reset
	void reset();
};