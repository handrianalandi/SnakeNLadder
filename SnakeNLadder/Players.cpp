#include "Players.h"

Players::Players()
{
	head = NULL;
	tail = NULL;
	playercount = 0;
}

Players::~Players()
{
	delete head;
}

void Players::initPlayer(int count ,float scalingx,float scalingy)
{
	//inisialisasi player sesuai input user(berapa player yang di mau)
	playercount = count;
	float xinfo = 1130 * scalingx, yinfo = 100 * scalingx;
	for (int i = 0; i < playercount; i++)
	{
		nodeplayer* newnode = new nodeplayer;
		newnode->location = 1;//basic=1
		newnode->playerselect = i + 1;
		newnode->next = head;
		if (i == 0) {
			newnode->playertexture.loadFromFile("Assets/images/pieceBlue.png");
			newnode->x = 120;
			newnode->y = 660;
			newnode->infosprite.setPosition(xinfo ,yinfo);
			newnode->playertext.setPosition(xinfo + 50*scalingx, yinfo + 15 * scalingy); yinfo += 50*scalingy;
		}
		else if (i == 1) {
			newnode->playertexture.loadFromFile("Assets/images/pieceGreen.png");
			newnode->x = 145 ;
			newnode->y = 660;
			newnode->infosprite.setPosition(xinfo, yinfo);
			newnode->playertext.setPosition(xinfo + 50 * scalingx, yinfo + 15 * scalingy); yinfo += 50 * scalingy;
		}
		else if (i == 2) {
			newnode->playertexture.loadFromFile("Assets/images/pieceRed.png");
			newnode->x = 120 ;
			newnode->y = 685;
			newnode->infosprite.setPosition(xinfo, yinfo);
			newnode->playertext.setPosition(xinfo + 50 * scalingx, yinfo + 15 * scalingy); yinfo += 50 * scalingy;
		}
		else if (i == 3) {
			newnode->playertexture.loadFromFile("Assets/images/pieceYellow.png");
			newnode->x = 145;
			newnode->y = 685;
			newnode->infosprite.setPosition(xinfo, yinfo);
			newnode->playertext.setPosition(xinfo + 50 * scalingx, yinfo + 15*scalingy);
		}
		//text
		newnode->fonts.loadFromFile("Assets/fonts/try1.ttf");
		newnode->playertext.setFont(newnode->fonts);
		newnode->playertext.setOutlineColor(Color::Black);
		newnode->playertext.setOutlineThickness(3.f);
		newnode->playertext.setCharacterSize(15);
		
		newnode->playerstring << "Player " << i + 1;
		newnode->playertext.setString(newnode->playerstring.str());


		newnode->playerstring << newnode->nama;
		newnode->playertext.setString(newnode->playerstring.str());

		//moving player sprite
		newnode->x = newnode->x * scalingx;
		newnode->y = newnode->y * scalingy;
		newnode->playersprite.setTexture(newnode->playertexture);
		newnode->playersprite.setPosition(newnode->x, newnode->y);
		newnode->playersprite.setScale(Vector2f(.5f*scalingx, .5f*scalingy));

		//infosprite
		newnode->infosprite.setTexture(newnode->playertexture);
		newnode->infosprite.setScale(Vector2f(.7f * scalingx, .7f * scalingy));

		if (!head) {
			head = newnode;
			tail = newnode;
			current = head;
		}
		else {
			tail->next = newnode;
			tail = newnode;
		}

	}
}

void Players::reset(int count,float scalingx,float scalingy)
{
	//inisialisasi player sesuai input user(berapa player yang di mau)
	playercount = count;
	float xinfo = 1130 * scalingx, yinfo = 100 * scalingx;
	for (int i = 0; i < playercount; i++)
	{
		nodeplayer* newnode = new nodeplayer;
		newnode->location = 1;//basic=1
		newnode->playerselect = i + 1;
		newnode->next = head;
		if (i == 0) {
			newnode->playertexture.loadFromFile("Assets/images/pieceBlue.png");
			newnode->x = 120;
			newnode->y = 660;
			newnode->infosprite.setPosition(xinfo, yinfo);
			newnode->playertext.setPosition(xinfo + 50 * scalingx, yinfo + 15 * scalingy); yinfo += 50 * scalingy;
		}
		else if (i == 1) {
			newnode->playertexture.loadFromFile("Assets/images/pieceGreen.png");
			newnode->x = 145;
			newnode->y = 660;
			newnode->infosprite.setPosition(xinfo, yinfo);
			newnode->playertext.setPosition(xinfo + 50 * scalingx, yinfo + 15 * scalingy); yinfo += 50 * scalingy;
		}
		else if (i == 2) {
			newnode->playertexture.loadFromFile("Assets/images/pieceRed.png");
			newnode->x = 120;
			newnode->y = 685;
			newnode->infosprite.setPosition(xinfo, yinfo);
			newnode->playertext.setPosition(xinfo + 50 * scalingx, yinfo + 15 * scalingy); yinfo += 50 * scalingy;
		}
		else if (i == 3) {
			newnode->playertexture.loadFromFile("Assets/images/pieceYellow.png");
			newnode->x = 145;
			newnode->y = 685;
			newnode->infosprite.setPosition(xinfo, yinfo);
			newnode->playertext.setPosition(xinfo + 50 * scalingx, yinfo + 15 * scalingy);
		}
		//text
		newnode->fonts.loadFromFile("Assets/fonts/try1.ttf");
		newnode->playertext.setFont(newnode->fonts);
		newnode->playertext.setOutlineColor(Color::Black);
		newnode->playertext.setOutlineThickness(3.f);
		newnode->playertext.setCharacterSize(15);

		newnode->playerstring << "Player " << i + 1;
		newnode->playertext.setString(newnode->playerstring.str());


		newnode->playerstring << newnode->nama;
		newnode->playertext.setString(newnode->playerstring.str());

		//moving player sprite
		newnode->x = newnode->x * scalingx;
		newnode->y = newnode->y * scalingy;
		newnode->playersprite.setTexture(newnode->playertexture);
		newnode->playersprite.setPosition(newnode->x, newnode->y);
		newnode->playersprite.setScale(Vector2f(.5f * scalingx, .5f * scalingy));

		//infosprite
		newnode->infosprite.setTexture(newnode->playertexture);
		newnode->infosprite.setScale(Vector2f(.7f * scalingx, .7f * scalingy));

		if (!head) {
			head = newnode;
			tail = newnode;
			current = head;
		}
		else {
			tail->next = newnode;
			tail = newnode;
		}

	}
}



void Players::deleteplayer(int x)
{
	nodeplayer* temp = head;
	nodeplayer* previous = temp;
	nodeplayer* deletion = temp;
	bool ended = 0;
	if (temp->playerselect == x) {
		if (head->next == head){
			ended = 1;
		}
		head = head->next;
		tail->next = head;
		delete deletion;
		if (ended) {
			head = NULL;
			tail = NULL;
			current = NULL;
		}
	}
	else {
		while (temp->playerselect != x) {
			previous = temp;
			temp = temp->next;
		}
		deletion = temp;
		previous->next = temp->next;
		if (temp->next == head) {
			tail = previous;
		}
		delete deletion;
	}
}


void Players::render(RenderTarget& target)
{
	nodeplayer* temp = head;
	if (temp) {
		target.draw(temp->playersprite);
		target.draw(temp->infosprite);
		target.draw(temp->playertext);
		temp = temp->next;
		while (temp != head) {
			target.draw(temp->playersprite);
			target.draw(temp->infosprite);
			target.draw(temp->playertext);
			temp = temp->next;
		}
	}
}