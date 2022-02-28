#include "Game.h"

Game::Game(int x)
{
	this->initVariables(x);
	this->players.initPlayer(x,scalingx,scalingy);
	this->initWindow();
	this->initBackground();
	this->initText();
	this->initBoard();
	this->initsnakeladder();
	this->initdice();
}

Game::~Game()
{
	delete this->window;
}

void Game::initVariables(int x)
{
	width = floor(VideoMode::getDesktopMode().width * 3 / 4);
	height = floor(VideoMode::getDesktopMode().height * 3 / 4);
	this->win = false;
	this->wincount = 0;
	this->someonewin = false;
	this->spacePressed = 0;
	this->moving = 0;
	this->scalingx = width / 1440;
	this->scalingy = height / 810;
	this->surp = 0;
}

void Game::initWindow(){
	/*scallingwindow.left = 0;
	scallingwindow.top = 0;
	scallingwindow.width = width;
	scallingwindow.height = height;*/
	this->window = new RenderWindow(VideoMode(width, height), "Snake and Ladder", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(60);
	/*this->window->setView(View(scallingwindow));*/
}

void Game::initBoard()
{
	this->boardTexture.loadFromFile("Assets/images/board.png");
	this->boardsprite.setTexture(boardTexture);
	this->boardsprite.setPosition(Vector2f(50 * scalingx, 40 * scalingy));
	this->boardsprite.setScale(Vector2f(1.5*scalingx, 1*scalingy));
	this->board.reset(scalingx, scalingy);
}

void Game::initBackground()
{
	backgroundtexture.loadFromFile("Assets/images/backgroundwooden.jpg");
	backgroundsprite.setTexture(backgroundtexture);
	backgroundsprite.setOrigin(backgroundtexture.getSize().x / 2, backgroundtexture.getSize().y / 2);
	backgroundsprite.setPosition(this->window->getSize().x / 2, this->window->getSize().y / 2);
	backgroundsprite.setScale(2.5f * scalingx , 2.f*scalingy);
}

void Game::initText()
{
	this->playerfont.loadFromFile("Assets/fonts/try1.ttf");
	this->playertext.setFont(this->playerfont);
	this->playertext.setOutlineColor(Color::Black);
	this->playertext.setOutlineThickness(3.f);
	this->playertext.setCharacterSize(25);
	this->playertext.setPosition(sf::Vector2f(window->getSize().x / 4, window->getSize().y - 50.f));
	this->playerselecttext.str("");
	this->playerselecttext.clear();
	this->playerselecttext << "Player " << players.current->playerselect << " Turn!";
	this->playertext.setString(this->playerselecttext.str());

	//surp
	this->surprisetext.setFont(this->playerfont);
	this->surprisetext.setOutlineColor(Color::Black);
	this->surprisetext.setOutlineThickness(3.f);
	this->surprisetext.setCharacterSize(30);
	this->surprisetext.setPosition(Vector2f(this->window->getSize().x / 2-100*scalingx, this->window->getSize().y / 2-100*scalingy));

	//winners
	this->winnertext.setFont(this->playerfont);
	this->winnertext.setOutlineColor(Color::Black);
	this->winnertext.setOutlineThickness(3.f);
	this->winnertext.setCharacterSize(20);
	this->winnertext.setPosition(Vector2f(this->window->getSize().x *4/5 , this->window->getSize().y *2/5 ));
	this->winnerstring << "Winners:\n";
	this->winnertext.setString(this->winnerstring.str());
	this->winnertext.setLineSpacing(2);
}
void Game::initsnakeladder()
{
	if (laddertexture.loadFromFile("Assets/images/ladder2.png")) {
		std::cout << "Succes Ladder\n";
		laddersprite.setTexture(laddertexture);
		laddersprite.setColor(Color(255, 255, 255, 210));
	}
	if (snaketexture.loadFromFile("Assets/images/snake4.png")) {
		std::cout << "Succes snake\n";
		snakesprite.setTexture(snaketexture);
		snakesprite.setColor(Color(255, 255, 255, 210));
	}
}

void Game::initdice()
{
	this->dicetexture.loadFromFile("Assets/images/dicesprite.png");
	this->dicesprite.setTexture(dicetexture);
	this->dicerect.top = 0;
	this->dicerect.left = 0;
	this->dicerect.width = 130;
	this->dicerect.height = 130;
	this->dicesprite.setTextureRect(dicerect);
	this->dicesprite.setPosition(this->window->getSize().x - 200*scalingx, this->window->getSize().y - 200*scalingy);
	this->dicesprite.setScale(.5f, .5f);
}



const bool Game::isRunning() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		}
	}
}

void Game::render()
{
	this->window->clear();

	//put all textures here

	this->window->draw(this->backgroundsprite);
	this->window->draw(this->boardsprite);
	this->window->draw(this->winnertext);
	this->window->draw(this->playertext);
	this->snakeladderrender();
	this->players.render(*this->window);
	this->window->draw(this->dicesprite);
	this->surpriserender();

	//textures end

	this->window->display();
}

void Game::playerspritemove(bool snakeladder)
{
	float movespeedx = (players.current->x - players.current->playersprite.getPosition().x) / 10;
	float movespeedy = (players.current->y - players.current->playersprite.getPosition().y) / 10;
	if(snakeladder) {
		movespeedx = (players.current->x - players.current->playersprite.getPosition().x) / 30;
		movespeedy = (players.current->y - players.current->playersprite.getPosition().y) / 30;

	}

	while (players.current->playersprite.getPosition().x != players.current->x || players.current->playersprite.getPosition().y != players.current->y) {
		if (players.current->playersprite.getPosition().x != players.current->x) {
			players.current->playersprite.move(movespeedx, 0);
			if (abs(players.current->playersprite.getPosition().x - players.current->x) <= 5) {
				players.current->playersprite.setPosition(players.current->x, players.current->playersprite.getPosition().y);
			}
		}
		if (players.current->playersprite.getPosition().y != players.current->y) {
			players.current->playersprite.move(0, movespeedy);
			if (abs(players.current->playersprite.getPosition().y - players.current->y) <= 5) {
				players.current->playersprite.setPosition(players.current->playersprite.getPosition().x, players.current->y);
			}
		}
		render();
	}
	delays.restart();
	while (delays.getElapsedTime().asSeconds() <= 0.1) {

	}
	delays.restart();
}

void Game::snakeladderrender()
{
	node* temp = board.head;
	while (temp) {
		if (temp->jump->location > temp->location) {
			float distance = pow(temp->locx - temp->jump->locx, 2) + pow(temp->locy - temp->jump->locy, 2);
			distance = sqrt(distance);
			float scaley = distance / laddersprite.getTexture()->getSize().y;
			laddersprite.setScale(1.5, scaley);
			laddersprite.setOrigin(laddersprite.getLocalBounds().width / 2, laddersprite.getLocalBounds().height);
			float angle = atan2(temp->jump->locx - temp->locx, temp->jump->locy - temp->locy)* 180 / 3.141;
			angle *= -1;
			angle += 180;
			laddersprite.setRotation(angle);
			laddersprite.setPosition(Vector2f(temp->locx+30*scalingx, temp->locy+30*scalingy));
			window->draw(laddersprite);
		}
		else if (temp->jump->location < temp->location) {
			float distance = pow(temp->locx - temp->jump->locx, 2) + pow(temp->locy - temp->jump->locy, 2);
			distance = sqrt(distance);
			float scaley = distance / snakesprite.getTexture()->getSize().y;
			snakesprite.setScale(1.2, scaley);
			snakesprite.setOrigin(snakesprite.getLocalBounds().width / 2, snakesprite.getLocalBounds().height);
			float angle = atan2(temp->jump->locx - temp->locx, temp->jump->locy - temp->locy) * 180 / 3.141;
			angle *= -1;
			angle += 180;
			snakesprite.setRotation(angle);
			snakesprite.setPosition(Vector2f(temp->locx + 30 * scalingx, temp->locy + 30 * scalingy));
			window->draw(snakesprite);
		}
		temp = temp->next;
	}
}

void Game::surpriserender()
{
	if (surp&&surprisetimer.getElapsedTime().asSeconds()<=3)
		this->window->draw(this->surprisetext);
}

void Game::reset()
{
	wincount = 0;
	cout << "Players: "; int playerbro;
	do {
		cout << "Players: ";  cin >> playerbro;
	} while (playerbro > 4 || playerbro < 2);
	cin.ignore();
	//reset winners
	this->initVariables(playerbro);
	board.reset(scalingx,scalingy);
	players.reset(playerbro,scalingx,scalingy);
	players.current = players.head;
	this->winnerstring.str("");
	this->winnerstring.clear();
	this->winnerstring << "Winners:\n";
	this->winnertext.setString(winnerstring.str());
}



void Game::update()
{
	pollEvents();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (!spacePressed&&!moving) {
			spacePressed = 1;
			int x = randomize();
			updateplayer(x);
			updatetext();
		}
	}
	else {
		spacePressed = 0;
	}

}

void Game::updateplayer(int x)
{
	if (x == 6) {
		int playcount = players.current->playerselect;
		players.current = players.current->next;
		players.deleteplayer(playcount);
		return;
	}
	moving = 1;
	//parameter x adalah berapa langkah(jumlah dadu)
	board.current = board.head;
	bool end = false;
	//end adalah ketika dia menyentuh 100 tapi masih ada langkah maka end berguna supaya players mundur
	//dibawah ini seolah2 yang gerak players tetapi yang sebenarnya gerak adalah board.current(dimana ia melambangkan gerakan players)
	for (int i = 1; i < players.current->location; i++)
	{
		board.current = board.current->next;
	}
	for (int i = 0; i < x; i++)
	{
		if (board.current->next == NULL) {
			end = true;
		}
		if (!end) {
			board.current = board.current->next;
		}
		else {
			board.current = board.current->prev;
		}
		//sprite move
		if (players.current->playerselect == 1) {
			players.current->x = board.current->locx; players.current->y = board.current->locy;
		}
		else if (players.current->playerselect == 2) {
			players.current->x = board.current->locx + 25 * scalingx; players.current->y = board.current->locy;
		}
		else if (players.current->playerselect == 3) {
			players.current->x = board.current->locx; players.current->y = board.current->locy + 25 * scalingy;
		}
		else if (players.current->playerselect == 4) {
			players.current->x = board.current->locx + 25 * scalingx; players.current->y = board.current->locy + 25 * scalingy;
		}
		playerspritemove(false);
		
	}
	
	/*if (board.current->location > players.current->location) {
		if (players.current->playerselect == 1) {
			players.current->x = board.current->locx; players.current->y = board.current->locy;
		}
		else if (players.current->playerselect == 2) {
			players.current->x = board.current->locx + 25*scalingx; players.current->y = board.current->locy;
		}
		else if (players.current->playerselect == 3) {
			players.current->x = board.current->locx; players.current->y = board.current->locy + 25 * scalingy;
		}
		else if (players.current->playerselect == 4) {
			players.current->x = board.current->locx + 25 * scalingx; players.current->y = board.current->locy + 25*scalingy;
		}
		playerspritemove(false);
	}
	players.current->location = board.current->location;*/

	//ketika menginjak petak surprise
	if (board.current->surprise) {
		surprisetimer.restart();
		surp = 1;
		//random jika genap=maju, ganjil=mundur
		surprisestring.str("");
		surprisestring.clear();
		int rando = rand() % 100 + 1;
		bool maju = 0;
		surprisestring << "Surprise!\n   ";
		if (rando % 2 == 0) {
			maju = 1;
			surprisestring << "+ ";
		}
		else {
			surprisestring << "- ";
		}
		//random berapa step
		int randostep = rand() % 5 + 1;
		surprisestring << randostep;
		surprisetext.setString(surprisestring.str());
		delays.restart();
		render();
		while (delays.getElapsedTime().asMilliseconds() <= 1000) {

		}
		delays.restart();
		
		render();
		//untuk mengetes >100 seperti diatas
		end = false;
		if (maju) {
			for (int i = 0; i < randostep; i++)
			{
				if (board.current->next == NULL) {
					end = true;
				}
				if (!end) {
					board.current = board.current->next;
				}
				else {
					board.current = board.current->prev;
				}
				if (players.current->playerselect == 1) {
					players.current->x = board.current->locx; players.current->y = board.current->locy;
				}
				else if (players.current->playerselect == 2) {
					players.current->x = board.current->locx + 25 * scalingx; players.current->y = board.current->locy;
				}
				else if (players.current->playerselect == 3) {
					players.current->x = board.current->locx; players.current->y = board.current->locy + 25 * scalingy;
				}
				else if (players.current->playerselect == 4) {
					players.current->x = board.current->locx + 25 * scalingx; players.current->y = board.current->locy + 25 * scalingy;
				}
				playerspritemove(false);
			}
		}
		else {
			for (int i = 0; i < randostep; i++)
			{
				board.current = board.current->prev;
				//ketika players mendapat surprise mundur tetapi melebihi petak 0 maka players berada di posisi 0
				
				if (players.current->playerselect == 1) {
					players.current->x = board.current->locx; players.current->y = board.current->locy;
				}
				else if (players.current->playerselect == 2) {
					players.current->x = board.current->locx + 25 * scalingx; players.current->y = board.current->locy;
				}
				else if (players.current->playerselect == 3) {
					players.current->x = board.current->locx; players.current->y = board.current->locy + 25 * scalingy;
				}
				else if (players.current->playerselect == 4) {
					players.current->x = board.current->locx + 25 * scalingx; players.current->y = board.current->locy + 25 * scalingy;
				}
				playerspritemove(false);
				if (board.current->prev == NULL) {
					break;
				}
			}
		}
		//mengeset lokasi players dengan lokasi boardcurrent seperti diatas
		
		
	}
	players.current->location = board.current->location;

	//ini adalah ketika players berada di petak snake/ladder
	while (board.current->jump->location != board.current->location) {
		players.current->location = board.current->jump->location;
		board.current = board.current->jump;
		if (players.current->playerselect == 1) {
			players.current->x = board.current->locx; players.current->y = board.current->locy;
		}
		else if (players.current->playerselect == 2) {
			players.current->x = board.current->locx + 25 * scalingx; players.current->y = board.current->locy;
		}
		else if (players.current->playerselect == 3) {
			players.current->x = board.current->locx; players.current->y = board.current->locy + 25 * scalingy;
		}
		else if (players.current->playerselect == 4) {
			players.current->x = board.current->locx + 25 * scalingx; players.current->y = board.current->locy + 25 * scalingy;
		}
		playerspritemove(true);
	}
	players.current->location = board.current->location;


	//jika players berada pas di lokasi 100(menang)
	if (players.current->location == 100) {
		/*winners.push(players.current->playerselect);*/
		wincount++;
		updatewinnertext();
		int playcount = players.current->playerselect;
		players.current = players.current->next;
		players.deleteplayer(playcount);
		someonewin = true;
		if (wincount == players.playercount - 1) {
			/*winners.push(players.current->playerselect);*/
			wincount++;
			updatewinnertext();
			players.deleteplayer(players.current->playerselect);
			win = true;
			render();
			//close when all win
			cout << "Play Again? enter Y if yes! : "; char isreset; cin >> isreset;
			cin.ignore();
			if (isreset=='Y'||isreset=='y') {
				this->reset();
			}
			else {
				this->window->close();
			}
			someonewin = true;
		}
	}
	//info text update
	if (players.current) {
		players.current->playerstring.str("");
		players.current->playerstring.clear();
		players.current->playerstring <<"Player "<< players.current->playerselect << " " << players.current->location;
		players.current->playertext.setString(players.current->playerstring.str());
	}
	if (someonewin) {
		someonewin = false;
	}
	else {
		players.current = players.current->next;
	}
	render();
	moving = 0;
}

void Game::updatetext()
{	
	if (players.current) {
		playerselecttext.str("");
		playerselecttext.clear();
		playerselecttext << "Player " << players.current->playerselect << " Turn!";
		playertext.setString(playerselecttext.str());
	}
}

void Game::updatedice(int x)
{
	if (x==0) {
		int rando;
		do { rando = rand() % 6 + 0; } while (dicerect.left / 130  == rando);
		this->dicerect.left = rando * 130;
		this->dicesprite.setTextureRect(this->dicerect);
	}
	else {
		this->dicerect.left = (x-1) * 130;
		this->dicesprite.setTextureRect(this->dicerect);
	}


}

void Game::updatewinnertext()
{
	winnerstring << wincount << ". Player " << players.current->playerselect << "\n";
	winnertext.setString(winnerstring.str());
}

int Game::randomize()
{
	//random animation
	for (int i = 0; i < 5; i++)
	{
		updatedice();
		delays.restart();
		while (delays.getElapsedTime().asMilliseconds() <= 400) {

		}
		render();
	}

	int x = /*(rand() % 100 + 1) % 6;*/rand() % 5 + 1;
	/*if (x == 0) {
		x = rand() % 6 + 1;
	}*/
	updatedice(x);
	render();
	delays.restart();
	while (delays.getElapsedTime().asMilliseconds() <= 1000) {

	}
	return x;
}
