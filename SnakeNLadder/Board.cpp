#include "Board.h"

Board::Board()
{
	snake = 0;
	ladder = 0;
	head = NULL;
	tail = NULL;
	int snakecd = 0, laddercd = 0;
	//loop dibawah inisialisasi petak 1 - 100 
	for (int i = 0; i < gamesize; i++)
	{
		node* newnode = new node;
		newnode->location = i + 1;
		int tempx, tempy;
		//mengatur lokasi y dari setiap petak
		newnode-> locy = (660 - ((i) / 10 * 64));

		//mengatur lokasi x dari setiap petak
		if (((i  / 10) % 2) == 0) {//jika di 
			newnode->locx = 120 + ((i) % 10 * 96);
		}
		else {
			newnode->locx = 984 - ((i) % 10 * 96);
		}



		//jika rando=7 maka di petak itu ada surprise nya
		int rando = rand() % supriselevel + 1;
		if (rando == 7 && newnode->location != 100) {
			newnode->surprise = true;
		}
		else {
			newnode->surprise = false;
		}

		newnode->jump = NULL;
		newnode->next = NULL;
		if (!head) {
			newnode->prev = NULL;
			head = newnode;
			tail = newnode;
		}
		else {
			tail->next = newnode;
			newnode->prev = tail;
			tail = newnode;
		}
	}
	//iniliasisasi snake dan ladder dan inisialisasi jump
	node* newnodetemp = head;
	
	for (int i = 0; i < gamesize; i++)
	{
		int rando = rand() % laddersnakespawnlevel + 1;
		
			if (!newnodetemp->surprise) {
				if (newnodetemp->location % 5 == 0 && newnodetemp->location <= 90) {
					node* jumptarget = newnodetemp;
					for (int j = 0; j < 10; j++)
					{
						jumptarget = jumptarget->next;
					}
					newnodetemp->jump = jumptarget;
				}
				else {
					if (rando == 1 && snake < maxsnake && newnodetemp->location>20 && newnodetemp->location != 100 && snakecd > 5) {
						int target = rand() % (newnodetemp->location - 10) + (newnodetemp->location / 2);
						//jumptarget adalah node yang nantinya jadi lokasi ujung snake dan di set berada pada petak yang lagi di injak oleh player;
						node* jumptarget = newnodetemp;
						//jumptarget di setting lokasi nya ke target kepala snake yang di mau
						for (int j = 0; j < newnodetemp->location - target; j++)
						{
							jumptarget = jumptarget->prev;
						}
						newnodetemp->jump = jumptarget;
						snake++;
						snakecd = 0;
					}
					else if (rando == 2 && ladder < maxladder && newnodetemp->location < 80 && newnodetemp->location>20 && laddercd>5) {
						//90=max ladder target
						int rndtarget = 90 - newnodetemp->location;
						int target = rand() % newnodetemp->location + rndtarget;
						//sama dengan snake
						node* jumptarget = newnodetemp;
						for (int j = newnodetemp->location; j < target; j++)
						{
							jumptarget = jumptarget->next;
						}
						newnodetemp->jump = jumptarget;
						ladder++;
						laddercd = 0;
					}
					//kalau rando tidak masuk maka target dari jumpnya adalah ke diri sendiri
					else {
						newnodetemp->jump = newnodetemp;
					}
					snakecd++;
					laddercd++;
				}
			}

			//else dibawah adalah ketika petak tersebut sudah merupakan suprise, maka jumptargetnya ke diri dia sendiri(kletika petak adalah surprise dia tidak boleh ladder/snake)
			else {
				newnodetemp->jump = newnodetemp;
			}
			newnodetemp = newnodetemp->next;
		}
		//ke petak berikutnya
	current = head;
}

Board::~Board()
{
	while (head) {
		node* temp=head->next;
		delete head;
		head = temp;
	}
}



void Board::reset(float scalingx, float scalingy)
{
	this->~Board();
	snake = 0;
	ladder = 0;
	int snakecd = 0, laddercd = 0;
	head = NULL;
	tail = NULL;
	//loop dibawah inisialisasi petak 1 - 100 
	for (int i = 0; i < gamesize; i++)
	{
		node* newnode = new node;
		newnode->location = i + 1;
		int tempx, tempy;
		//mengatur lokasi y dari setiap petak
		newnode->locy = (660 - ((i) / 10 * 64))*scalingy;

		//mengatur lokasi x dari setiap petak
		if (((i / 10) % 2) == 0) {//jika di 
			newnode->locx = (120 + ((i) % 10 * 96))*scalingx;
		}
		else {
			newnode->locx = (984 - ((i) % 10 * 96))*scalingx;
		}


		//jika rando=1 maka di petak itu ada surprise nya
		int rando = rand() % supriselevel + 1;
		if (rando == 1 && newnode->location != 100&&newnode->location>10) {
			newnode->surprise = true;
		}
		else {
			newnode->surprise = false;
		}
		newnode->jump = NULL;
		newnode->next = NULL;
		if (!head) {
			newnode->prev = NULL;
			head = newnode;
			tail = newnode;
		}
		else {
			tail->next = newnode;
			newnode->prev = tail;
			tail = newnode;
		}
	}
	//iniliasisasi snake dan ladder dan inisialisasi jump
	node* newnodetemp = head;

	//for (int i = 0; i < gamesize; i++)
	//{
	//	int rando = rand() % laddersnakespawnlevel + 1;
	//	if (!newnodetemp->surprise) {
	//		if (rando == 1 && snake < maxsnake && newnodetemp->location>20 && newnodetemp->location != 100 && snakecd > 10) {
	//			int target = rand() % (newnodetemp->location - 10) + (newnodetemp->location / 2);
	//			//jumptarget adalah node yang nantinya jadi lokasi ujung snake dan di set berada pada petak yang lagi di injak oleh player;
	//			node* jumptarget = newnodetemp;
	//			//jumptarget di setting lokasi nya ke target kepala snake yang di mau
	//			for (int j = 0; j < newnodetemp->location - target; j++)
	//			{
	//				jumptarget = jumptarget->prev;
	//			}
	//			newnodetemp->jump = jumptarget;
	//			snake++;
	//			snakecd = 0;
	//		}
	//		else if (rando == 2 && ladder < maxladder && newnodetemp->location < 80 && newnodetemp->location>20 && laddercd>10) {
	//			//90=max ladder target
	//			int rndtarget = 98 - newnodetemp->location;
	//			int target = rand() % newnodetemp->location + rndtarget;
	//			//sama dengan snake
	//			node* jumptarget = newnodetemp;
	//			for (int j = newnodetemp->location; j < target; j++)
	//			{
	//				jumptarget = jumptarget->next;
	//			}
	//			newnodetemp->jump = jumptarget;
	//			ladder++;
	//			laddercd = 0;
	//		}
	//		//kalau rando tidak masuk maka target dari jumpnya adalah ke diri sendiri
	//		else {
	//			newnodetemp->jump = newnodetemp;
	//		}
	//		snakecd++;
	//		laddercd++;
	//	}
	//	//else dibawah adalah ketika petak tersebut sudah merupakan suprise, maka jumptargetnya ke diri dia sendiri(kletika petak adalah surprise dia tidak boleh ladder/snake)
	//	else {
	//		newnodetemp->jump = newnodetemp;
	//	}
	//	//ke petak berikutnya
	//	newnodetemp = newnodetemp->next;
	//}
	for (int i = 0; i < gamesize; i++)
	{
		int rando = rand() % laddersnakespawnlevel + 1;

		if (!newnodetemp->surprise) {
			if (newnodetemp->location % 5 == 0 && newnodetemp->location <= 90) {
				node* jumptarget = newnodetemp;
				for (int j = 0; j < 10; j++)
				{
					jumptarget = jumptarget->next;
				}
				newnodetemp->jump = jumptarget;
			}
			else {
				if (rando == 1 && snake < maxsnake && newnodetemp->location>20 && newnodetemp->location != 100 && snakecd > 5) {
					int target = rand() % (newnodetemp->location - 10) + (newnodetemp->location / 2);
					//jumptarget adalah node yang nantinya jadi lokasi ujung snake dan di set berada pada petak yang lagi di injak oleh player;
					node* jumptarget = newnodetemp;
					//jumptarget di setting lokasi nya ke target kepala snake yang di mau
					for (int j = 0; j < newnodetemp->location - target; j++)
					{
						jumptarget = jumptarget->prev;
					}
					newnodetemp->jump = jumptarget;
					snake++;
					snakecd = 0;
				}
				else if (rando == 2 && ladder < maxladder && newnodetemp->location < 80 && newnodetemp->location>20 && laddercd>5) {
					//90=max ladder target
					int rndtarget = 90 - newnodetemp->location;
					int target = rand() % newnodetemp->location + rndtarget;
					//sama dengan snake
					node* jumptarget = newnodetemp;
					for (int j = newnodetemp->location; j < target; j++)
					{
						jumptarget = jumptarget->next;
					}
					newnodetemp->jump = jumptarget;
					ladder++;
					laddercd = 0;
				}
				//kalau rando tidak masuk maka target dari jumpnya adalah ke diri sendiri
				else {
					newnodetemp->jump = newnodetemp;
				}
				snakecd++;
				laddercd++;
			}
		}

		//else dibawah adalah ketika petak tersebut sudah merupakan suprise, maka jumptargetnya ke diri dia sendiri(kletika petak adalah surprise dia tidak boleh ladder/snake)
		else {
			newnodetemp->jump = newnodetemp;
		}
		newnodetemp = newnodetemp->next;
	}
	current = head;
}



