#include<iostream>
#include"Game.h"
#include<time.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h> 

using namespace sf;

void main() {
	//dibawah adalah untuk membersihan memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtDumpMemoryLeaks();
	//


	srand(time(NULL));
	int players;
	do {
		cout << "Players: ";  cin >> players;
	} while (players > 4 || players < 2);
	cin.ignore();
	Game SnakeAndLadder(players);
	while (SnakeAndLadder.isRunning()){
		SnakeAndLadder.update();
		SnakeAndLadder.render();
	}
	std::cout << "\n\n\n\nCreated by:\nc14190059 - Nyoto Wijaya\nc14190227 - Jeremy Mulyawan\nc14190231 - Handrian Alandi\nSpecial Thanks to our beloved Lecturer, Ce Anita for teaching us Data Structure in this amazing semester\nMay God bless you!\n";
}