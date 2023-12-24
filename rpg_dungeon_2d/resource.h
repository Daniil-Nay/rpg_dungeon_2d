#include<iostream>
#include <sstream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <vector>
#include <list>
#include "map.h"
#include "info.h"
#include "view.h"
#include<iostream>
#include <sstream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <vector>
#include <list>
#include "map.h"
#include "info.h"
#include "view.h"
//
using namespace std;
using namespace sf;
char objmassive[8] = { '#','@',')','$','+','*','~','_' };
/*const map<char, IntRect> sprites{
		{'#', IntRect(0,0,32,32)},
		{'*', IntRect(16,0,32,32)},
		{'~', IntRect(32,0,32,32)},
		{'!', IntRect(64,0,32,32)},
		{'+', IntRect(96,0,32,32)},
		{'*', IntRect(128,0,32,32)},
		{'i', IntRect(160,0,32,32)},
		{'p', IntRect(192,0,32,32)},
		{'x', IntRect(224,0,32,32)},
		{'d', IntRect(256,0,32,32)},
		{'_', IntRect(288,0,32,32)},
		{')', IntRect(320,0,32,32)},
		{'@', IntRect(352,0,32,32)},
		{'$', IntRect(384,0,32,32)},
		{' ', IntRect(400,0,32,32)},
		{'r', IntRect(255,0,32,32)},
		{'z', IntRect(211,0,32,32)},
		{'h', IntRect(322,0,32,32)},
		{'b', IntRect(233,0,32,32)},
};*/


class Entity {
public:
	double x, y, w, h, dx, dy, speed = 0;
	bool life;
	int health;
	Image image;
	Texture texture;
	Sprite sprite;
	string type;
	Entity(double X, double Y, double W, double H, string TYPE) {
		x = X;
		y = Y;
		w = W;
		h = H;
		type = TYPE;
		speed = 0;
		life = true;
		health = 5;
	}
	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}
	~Entity() {

	}

};
class InteractiveObj :public Entity {
private:
public:
	InteractiveObj(float X, float Y, float W, float H, String TYPE) :Entity(X, Y, W, H, TYPE) {
		if (TYPE == "Chest") {
			image.loadFromFile("images/chests.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(32, 0, w, h));
			sprite.setOrigin(w / 2, h / 2);
			sprite.setPosition(x - 10, y + 1200);
		}
		if (TYPE == "Ball") {
			image.loadFromFile("images/ball.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, w, h));
			sprite.setOrigin(w / 2, h / 2);
			sprite.setPosition(x + 870, y + 1233);
		}
	}
};
class Player :public Entity { // класс Игрока
private:
public:
	int money_score = 0;
	int direction = 0; // куда?
	SoundBuffer buff;
	Sound sound_play;
	/*enum movements {
		up,
		down,
		right,
		left
	} movings*/
	Player(float X, float Y, float W, float H, String TYPE) :Entity(X, Y, W, H, TYPE) {
		if (TYPE == "Main_character") {
			money_score = 0;
			image.loadFromFile("images/Character_SpriteSheet.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, w, h)); //sprite.setTextureRect(IntRect(0, 0, w, h));
			sprite.setOrigin(w / 2, h / 2); // убрать
		}
	}
	void movement_update(double time)
	{
		switch (direction) {
		case (0): // вправо
			dx = speed;
			dy = 0;
			break;
		case (1): // вниз
			dx = 0;
			dy = speed;
			break;
		case (2): //влево
			dx = -speed;
			dy = 0;
			break;
		case (3):  //вверх
			dx = 0;
			dy = -speed;
			break;
		}
		x += dx * time;
		y += dy * time;
		speed = 0;
		sprite.setPosition(x, y);
		player_solid();
		if (health <= 0) {
			life = false;
		}
	}
	void Sounding(const string& N) {
		buff.loadFromFile(N);
		sound_play.setBuffer(buff);
		sound_play.play();
	}
	void movement(double& Cur_frame, double& time, int& n, int& k, &sprite) {
		if (life == true) {
			if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D))) { // влево вправо
				Cur_frame += 0.005 * time;//?
				if (Keyboard::isKeyPressed(Keyboard::A)) {
					direction = 2;
					if (Cur_frame > n) {
						Cur_frame -= n;
					}
					sprite.setTextureRect(IntRect(k * int(Cur_frame), 192, 64, 64));
					PlayerView(x, y);
					sprite.move(-0.15 * time, 0);

				}
				else {
					direction = 0;
					if (Cur_frame > n) {
						Cur_frame -= n;
					}
					sprite.setTextureRect(IntRect(k * int(Cur_frame), 128, 64, 64)); //128 64 64 
					PlayerView(x, y);
					sprite.move(0.15 * time, 0);
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::S) || (Keyboard::isKeyPressed(Keyboard::W))) { // вниз вверх
				Cur_frame += 0.005 * time;//?
				if (Keyboard::isKeyPressed(Keyboard::S)) {
					direction = 1;
					if (Cur_frame > n) {
						Cur_frame -= n;
					}
					sprite.setTextureRect(IntRect(k * int(Cur_frame), 0, 64, 64)); // 0,64,64
					PlayerView(x, y);
					sprite.move(0, 0.15 * time);
				}
				else {
					direction = 3;
					if (Cur_frame > n) {
						Cur_frame -= n;
					}
					sprite.setTextureRect(IntRect(k * int(Cur_frame), 74, 64, 64)); // 64 64 64
					PlayerView(x, y);
					sprite.move(0, -0.15 * time);
				}
			}
		}

	}
	void player_solid() {
		for (int i = (y / 32); i < (y + h) / 32; i++) { // 34 
			for (int j = (x / 32); j < (x + w) / 32; j++) { //16
				for (int z = 0; z < 8; z++) {
					if (TileMap[i][j] == objmassive[z]) {
						if (dy > 0 || dy < 0) {
							if (dy > 0) {
								y = i * 32 - h;
							}
							else {
								y = i * 32 + 32;//+34
							}
						}
						if (dx > 0 || dx < 0) {
							if (dx > 0) {
								x = j * 32 - w;
							}
							else {
								x = j * 32 + 32;
							}
						}
					}
					if (TileMap[i][j] == 'c') { // 
						money_score++;
						Sounding("Validation.ogg");
						TileMap[i][j] = (' ');
					}
					if (TileMap[i][j] == 's' && health != 0) {
						health--;
						Sounding("Hit.wav");
						TileMap[i][j] = (' '); // изменить шипы и добавить второй вид с коллизией.
					}
					if (TileMap[i][j] == 'h') { // изменить спрайт на бутылек 
						health++;
						Sounding("Healing.wav");
						TileMap[i][j] = (' ');
					}
				}
			}
		}
	}
};
void CheckLShift(Player& player) {
	if (Keyboard::isKeyPressed(Keyboard::LShift)) {
		player.speed = 0.3;
	}
	else {
		player.speed = 0.1;
	}
}
int Random(int min, int max) {
	return min + rand() % (max - min);
}
class Enemy :public Entity {
public:
	string TYPE = "";
	Enemy(float X, float Y, float W, float H, string TYPE) :Entity(X, Y, W, H, TYPE) { //(double X, double Y, double W, double H, string TYPE)
		if (TYPE == "skeleton") {
			this->TYPE = TYPE;
			image.loadFromFile("images/skeletik.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, w, h));
			sprite.setOrigin(w / 2, h / 2); // убрать
			dx = 0.07;
		}
		if (TYPE == "Suriken") {
			this->TYPE = TYPE;
			image.loadFromFile("images/Suriken");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, w, h));
			sprite.setOrigin(w / 2, h / 2);

		}
	}
	/*if (enemy.life) {
		if (enemy.dx < 0) {
			s_frame += 0.005 * time;
			if (s_frame > 5) {
				s_frame -= 5;
			}
			enemy.sprite.setTextureRect(IntRect(64 * int(s_frame), 128, 64, 64));
			enemy.sprite.move(-0.15 * time, 0);
		}
		if (enemy.dx > 0) {
			s_frame += 0.005 * time;
			if (s_frame > 5) {
				s_frame -= 5;
			}
			enemy.sprite.setTextureRect(IntRect(64 * int(s_frame), 192, 64, 64)); //128 64 64
			enemy.sprite.move(0.15 * time, 0);
		}
	}*/

	void checkc(float DX, float DY) {
		for (int i = y / 32; i < (y + h) / 32; i++) {
			for (int j = x / 32; j < (x + w) / 32; j++) {
				for (int z = 0; z < 8; z++) {
					if (TileMap[i][j] == objmassive[z] && health) {
						if (DY > 0 && TYPE == "skeleton") {//>
							y = i * 32 - h;
						}
						if (DY < 0 && TYPE == "skeleton") {//<
							y = i * 32 + Random(-4, 37); // -3 35 ,-4 37
						}
						if (DX < 0) { //<
							x = j * 32 + 32;
							dx = 0.07;
							/*	s_frame += 0.005 * time;
								y = i * 32;
								if (s_frame > 5) {
									s_frame -= 5;
								}
								sprite.setTextureRect(IntRect(64 * double(s_frame), 192, 64, 64)); //128 64 64
								sprite.move(0.15 * time, 0);*/
						}
						if (DX > 0) {//>
							x = j * 32 - w;
							dx = -0.07;
							/*	if (s_frame > 5) {
									s_frame -= 5;
								}
								sprite.setTextureRect(IntRect(64 * int(s_frame), 128, 64, 64));
								sprite.move(-0.15 * time, 0);*/
						}
					}
				}
			}
		}
	}
	void update(float time) {
		checkc(dx, dy);
		x += dx * time;
		sprite.setPosition(x, y);
		if (health <= 0) {
			life = false;
		}
	}
};
/*void Coin() {
	Image i_coin;
	i_coin.loadFromFile("images/coins.png");
	Texture t_coin;
	Sprite s_coin;
	t_coin.loadFromImage(i_coin);
	s_coin.setTexture(t_coin);
	s_coin.setPosition(view.getCenter().x - 320, view.getCenter().y - 230);
	s_coin.setTextureRect(IntRect(0, 0, 40, 30));
	s_coin.setScale(1.5, 1.5);
}*/
/*
* void Souding(string N) {
		buff.loadFromFile(N);
		sound_play.setBuffer(buff);
		sound_play.play();
	}
*/
int main() {
	RenderWindow window(VideoMode(800, 540), "The bravest knight");
	view.reset(FloatRect(0, 0, 640, 480));
	Image map_image;
	map_image.loadFromFile("images/Dungeon tileset.png");
	Texture map_texture;
	map_texture.loadFromImage(map_image);
	Sprite map_sprite;
	map_sprite.setTexture(map_texture);
	//Player player(250, 250, 32.0, 32.0, "Character.png");
	Enemy enemy(250, 250, 32.0, 32.0, "skeleton");
	Enemy enemy2(250, 250, 32.0, 32.0, "Suriken");
	Player player(250, 250, 32.0, 32.0, "Main_character");
	InteractiveObj  Chest(250, 250, 32.0, 32.0, "Chest");
	InteractiveObj  Stone_ball(250, 250, 64.0, 64.0, "Ball");
	double Cur_frame(0);
	double s_frame(0);
	bool showtext = true;
	Clock clock;
	Font font;
	int n(5), k(64);
	font.loadFromFile("images/font_pixel.ttf");
	Text player_score("", font, 30);
	Text insane("", font, 30);
	insane.setStyle(Text::Bold);
	insane.setFillColor(Color::Cyan);
	player_score.setFillColor(Color::Yellow);
	player_score.setStyle(Text::Bold);
	Text heart_score("", font, 30);
	heart_score.setFillColor(Color::Red);
	heart_score.setStyle(Text::Bold);
	int createObjectForMapTimer = 0;
	while (window.isOpen()) {
		Event event;
		double time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Q) {
				int a = 0;
				switch (showtext) {
				case (true): {
					ostringstream info;
					info << (user_info(User_Info(a)));
					insane.setString(info.str());
					showtext = false;
					break;
				}
				case (false): {
					showtext = true;
					break;
				}
				}
			}
			if (event.type = Event::Closed)
				window.close();
		}
		if (enemy.life) {
			if (enemy.dx < 0) {
				s_frame += 0.005 * time;
				if (s_frame > 5) {
					s_frame -= 5;
				}
				enemy.sprite.setTextureRect(IntRect(64 * int(s_frame), 128, 64, 64));
				enemy.sprite.move(-0.15 * time, 0);
			}
			if (enemy.dx > 0) {
				s_frame += 0.005 * time;
				if (s_frame > 5) {
					s_frame -= 5;
				}
				enemy.sprite.setTextureRect(IntRect(64 * int(s_frame), 192, 64, 64)); //128 64 64 
				enemy.sprite.move(0.15 * time, 0);
			}
		}
		player.movement(Cur_frame, time, n, k);
		if (player.life) {
			int n(5), k(64);
			if (Mouse::isButtonPressed(Mouse::Left)) {
				n = 2;
				k = 380;
				//player.sprite.setTextureRect(IntRect(64 * int(Cur_frame), 192, 64, 64));
			}
		}
		createObjectForMapTimer += time;
		if (createObjectForMapTimer > 3000) {
			randomgen();
			createObjectForMapTimer = 0;
		}
		enemy.update(time);
		player.movement_update(time);
		FloatRect playerbounds = player.sprite.getGlobalBounds();
		FloatRect enemybounds = enemy.sprite.getGlobalBounds();
		//playerbounds.intersects(enemybounds)
		if (playerbounds.intersects(enemy.getRect())) {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				enemy.health--;
			}
			if (player.dx > 0) {
				player.x = enemy.x - enemy.w;
			}
			if (player.dx < 0) {
				player.x = enemy.x + player.w;
			}
		}
		if (enemy.life == false) {
			enemy.dx = 0;
			enemy.sprite.setTextureRect(IntRect(160, 267, w + 32, h + 32));
		}
		sf::RectangleShape rectangle1(sf::Vector2f(64, 32));// исправить этот говнокод. Switch maybe?
		sf::RectangleShape rectangle2(sf::Vector2f(64, 32));
		sf::RectangleShape rectangle3(sf::Vector2f(64, 32));
		rectangle1.setFillColor(Color::Yellow);
		rectangle1.setPosition(510, 90);
		rectangle2.setFillColor(Color::Yellow);
		rectangle2.setPosition(1150, 390);
		rectangle3.setFillColor(Color::Yellow);
		rectangle3.setPosition(1150, 905);
		sf::FloatRect rectanglebounds1 = rectangle1.getGlobalBounds();
		sf::FloatRect rectanglebounds2 = rectangle2.getGlobalBounds();
		sf::FloatRect rectanglebounds3 = rectangle3.getGlobalBounds();
		if (playerbounds.intersects(rectanglebounds1)) {
			player.y += 180;
			player.sprite.setPosition(player.x, player.y + 180);
		}
		if (playerbounds.intersects(rectanglebounds2)) {
			player.y -= 140;
			player.sprite.setPosition(player.x, player.y - 140);
		}
		if (playerbounds.intersects(rectanglebounds3)) {
			player.y -= 180;
			player.sprite.setPosition(player.x, player.y - 180);
		}
		window.setView(view);
		window.clear();
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++) {
				{
					if (TileMap[i][j] == '3') {
						map_sprite.setTextureRect(IntRect(305, 126, 32, 32));
					}
					if (TileMap[i][j] == 'g') {
						map_sprite.setTextureRect(IntRect(80, 48, 32, 32));
					}
					if (TileMap[i][j] == 'e') {
						map_sprite.setTextureRect(IntRect(335, 160, 32, 32));
					}
					if (TileMap[i][j] == 'l') {
						map_sprite.setTextureRect(IntRect(338, 128, 32, 32));
					}
					if (TileMap[i][j] == '#') {
						map_sprite.setTextureRect(IntRect(0, 16, 32, 32));
					}
					if (TileMap[i][j] == '*') {
						map_sprite.setTextureRect(IntRect(310, 32, 32, 32));
					}
					if (TileMap[i][j] == '~') {
						map_sprite.setTextureRect(IntRect(330, 32, 32, 32));
					}
					if (TileMap[i][j] == '!') {
						map_sprite.setTextureRect(IntRect(311, 0, 32, 32));
					}
					if (TileMap[i][j] == '+') {
						map_sprite.setTextureRect(IntRect(202, -2, 32, 32));
					}
				}
				if (TileMap[i][j] == 'i') {
					map_sprite.setTextureRect(IntRect(56, 112, 37, 32));
				}
				if (TileMap[i][j] == 'p') {
					map_sprite.setTextureRect(IntRect(200, 159, 32, 32));
				}
				if (TileMap[i][j] == 'o') {
					map_sprite.setTextureRect(IntRect(189, 159, 32, 32));

				}
				if (TileMap[i][j] == 't') {
					map_sprite.setTextureRect(IntRect(170, 158, 32, 32));
				}
				if (TileMap[i][j] == ']') {
					map_sprite.setTextureRect(IntRect(275, 64, 32, 32));
				}
				if (TileMap[i][j] == '[') {
					map_sprite.setTextureRect(IntRect(275, 96, 32, 32));
				}
				if (TileMap[i][j] == '{') {
					map_sprite.setTextureRect(IntRect(170, 158, 32, 32));
				}
				if (TileMap[i][j] == 'x') {
					map_sprite.setTextureRect(IntRect(273, 125, 32, 32));
				}
				if (TileMap[i][j] == 'd') {
					map_sprite.setTextureRect(IntRect(242, 130, 32, 32));
				}
				{
					if (TileMap[i][j] == '_') {
						map_sprite.setTextureRect(IntRect(329, 0, 32, 32));
					}
					if (TileMap[i][j] == ')') {
						map_sprite.setTextureRect(IntRect(220, -4, 32, 32));
					}
					if (TileMap[i][j] == '@') {
						map_sprite.setTextureRect(IntRect(248, 2, 32, 32));
					}
					if (TileMap[i][j] == '$') {
						map_sprite.setTextureRect(IntRect(266, 2, 32, 32));
					}
					if (TileMap[i][j] == ' ') {
						map_sprite.setTextureRect(IntRect(70, 153, 32, 32));
					}
					if (TileMap[i][j] == '-') {
						map_sprite.setTextureRect(IntRect(70, 153, 32, 32));
					}
					if (TileMap[i][j] == 'c') {
						map_sprite.setTextureRect(IntRect(208, 90, 32, 32));
					}
					if (TileMap[i][j] == 's') {
						map_sprite.setTextureRect(IntRect(304, 160, 32, 32));
					}
					if (TileMap[i][j] == 'h') {
						map_sprite.setTextureRect(IntRect(208, 33, 32, 32));
					}
					if (TileMap[i][j] == 'b') {
						map_sprite.setTextureRect(IntRect(0, 0, 1, 1));
					}
				}
				map_sprite.setPosition(j * 32, i * 32); //32 32
				window.draw(map_sprite);
			}
		//		if (spritebounds.intersects());
				//возможно ли перенейсти код с монеткой в функцию ?
		{

			Image i_coin;
			i_coin.loadFromFile("images/coins.png");
			Texture t_coin;
			Sprite s_coin;
			t_coin.loadFromImage(i_coin);
			s_coin.setTexture(t_coin);
			s_coin.setPosition(view.getCenter().x - 320, view.getCenter().y - 230);
			s_coin.setTextureRect(IntRect(0, 0, 40, 30));
			s_coin.setScale(1.5, 1.5);
			window.draw(s_coin);
		}
		if (!showtext) {
			insane.setPosition(view.getCenter().x - 300, view.getCenter().y - 170);
			window.draw(insane);
		}
		player_score.setString("Money score: " + to_string(player.money_score));
		heart_score.setString("Lives:" + to_string(player.health));
		player_score.setPosition(view.getCenter().x - 280, view.getCenter().y - 230);
		heart_score.setPosition(view.getCenter().x - 280, view.getCenter().y - 200);
		window.draw(player.sprite);
		window.draw(Chest.sprite);
		window.draw(Stone_ball.sprite);
		window.draw(enemy.sprite);
		window.draw(rectangle1);
		window.draw(rectangle2);
		window.draw(rectangle3);
		window.draw(enemy2.sprite);
		window.draw(player_score);
		window.draw(heart_score);
		//	window.draw(rectangle);
		window.display();
	}
	return 0;
}
///
using namespace std;
using namespace sf;
char objmassive[8] = { '#','@',')','$','+','*','~','_' };
/*const map<char, IntRect> sprites{
		{'#', IntRect(0,0,32,32)},
		{'*', IntRect(16,0,32,32)},
		{'~', IntRect(32,0,32,32)},
		{'!', IntRect(64,0,32,32)},
		{'+', IntRect(96,0,32,32)},
		{'*', IntRect(128,0,32,32)},
		{'i', IntRect(160,0,32,32)},
		{'p', IntRect(192,0,32,32)},
		{'x', IntRect(224,0,32,32)},
		{'d', IntRect(256,0,32,32)},
		{'_', IntRect(288,0,32,32)},
		{')', IntRect(320,0,32,32)},
		{'@', IntRect(352,0,32,32)},
		{'$', IntRect(384,0,32,32)},
		{' ', IntRect(400,0,32,32)},
		{'r', IntRect(255,0,32,32)},
		{'z', IntRect(211,0,32,32)},
		{'h', IntRect(322,0,32,32)},
		{'b', IntRect(233,0,32,32)},
};*/


class Entity {
public:
	double x, y, w, h, dx, dy, speed = 0;
	bool life;
	int health;
	Image image;
	Texture texture;
	Sprite sprite;
	string type;
	Entity(double X, double Y, double W, double H, string TYPE) {
		x = X;
		y = Y;
		w = W;
		h = H;
		type = TYPE;
		speed = 0;
		life = true;
		health = 5;
	}
	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}
	~Entity() {

	}

};
class InteractiveObj :public Entity {
private:
public:
	InteractiveObj(float X, float Y, float W, float H, String TYPE) :Entity(X, Y, W, H, TYPE) {
		if (TYPE == "Chest") {
			image.loadFromFile("images/chests.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(32, 0, w, h));
			sprite.setOrigin(w / 2, h / 2);
			sprite.setPosition(x - 10, y + 1200);
		}
		if (TYPE == "BAll") {

		}
	}
};
class Player :public Entity { // класс Игрока
private:
public:
	int money_score = 0;
	int direction = 0; // куда?
	SoundBuffer buff;
	Sound sound_play;
	/*enum movements {
		up,
		down,
		right,
		left
	} movings*/
	Player(float X, float Y, float W, float H, String TYPE) :Entity(X, Y, W, H, TYPE) {
		if (TYPE == "Main_character") {
			money_score = 0;
			image.loadFromFile("images/Character_SpriteSheet.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, w, h)); //sprite.setTextureRect(IntRect(0, 0, w, h));
			sprite.setOrigin(w / 2, h / 2); // убрать
		}
	}
	void movement_update(double time)
	{
		switch (direction) {
		case (0): // вправо
			dx = speed;
			dy = 0;
			break;
		case (1): // вниз
			dx = 0;
			dy = speed;
			break;
		case (2): //влево
			dx = -speed;
			dy = 0;
			break;
		case (3):  //вверх
			dx = 0;
			dy = -speed;
			break;
		}
		x += dx * time;
		y += dy * time;
		speed = 0;
		sprite.setPosition(x, y);
		player_solid();
		if (health <= 0) {
			life = false;
		}
	}
	void Sounding(const string& N) {
		buff.loadFromFile(N);
		sound_play.setBuffer(buff);
		sound_play.play();
	}
	void player_solid() {
		for (int i = (y / 32); i < (y + h) / 32; i++) { // 34 
			for (int j = (x / 32); j < (x + w) / 32; j++) { //16
				for (int z = 0; z < 8; z++) {
					if (TileMap[i][j] == objmassive[z]) {
						if (dy > 0 || dy < 0) {
							if (dy > 0) {
								y = i * 32 - h;
							}
							else {
								y = i * 32 + 32;//+34
							}
						}
						if (dx > 0 || dx < 0) {
							if (dx > 0) {
								x = j * 32 - w;
							}
							else {
								x = j * 32 + 32;
							}
						}
					}
					if (TileMap[i][j] == 'c') { // 
						money_score++;
						Sounding("Validation.ogg");
						TileMap[i][j] = (' ');
					}
					if (TileMap[i][j] == 's' && health != 0) {
						health--;
						Sounding("Hit.wav");
						TileMap[i][j] = (' '); // изменить шипы и добавить второй вид с коллизией.
					}
					if (TileMap[i][j] == 'h') { // изменить спрайт на бутылек 
						health++;
						Sounding("Healing.wav");
						TileMap[i][j] = (' ');
					}
				}
			}
		}
	}
};
void CheckLShift(Player& player) {
	if (Keyboard::isKeyPressed(Keyboard::LShift)) {
		player.speed = 0.3;
	}
	else {
		player.speed = 0.1;
	}
}
int Random(int min, int max, string& TYPE) {
	if (TYPE == "skeleton") {
		return min + rand() % (max - min);
	}
	else {
		return 32;
	}
}
class Enemy :public Entity {
public:
	string TYPE = "";
	Enemy(float X, float Y, float W, float H, string TYPE) :Entity(X, Y, W, H, TYPE) { //(double X, double Y, double W, double H, string TYPE)
		if (TYPE == "skeleton") {
			this->TYPE = TYPE;
			image.loadFromFile("images/skeletik.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, w, h));
			sprite.setOrigin(w / 2, h / 2); // убрать
			dx = 0.07;
		}
		if (TYPE == "Suriken") {
			this->TYPE = TYPE;
			image.loadFromFile("images/Suriken");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, w, h));
			sprite.setOrigin(w / 2, h / 2);

		}
	}
	void checkc(float DX, float DY) {
		for (int i = y / 32; i < (y + h) / 32; i++) {
			for (int j = x / 32; j < (x + w) / 32; j++) {
				for (int z = 0; z < 8; z++) {
					if (TileMap[i][j] == objmassive[z] && health) {
						if (DY > 0) {//>
							y = i * 32 - h;
						}
						if (DY < 0) {//<
							y = i * 32 + Random(-4, 37, TYPE); // -3 35 ,-4 37
						}
						if (DX < 0) { //<
							x = j * 32 + 32;
							dx = 0.07;
							/*	s_frame += 0.005 * time;
								y = i * 32;
								if (s_frame > 5) {
									s_frame -= 5;
								}
								sprite.setTextureRect(IntRect(64 * double(s_frame), 192, 64, 64)); //128 64 64
								sprite.move(0.15 * time, 0);*/
						}
						if (DX > 0) {//>
							x = j * 32 - w;
							dx = -0.07;
							/*	if (s_frame > 5) {
									s_frame -= 5;
								}
								sprite.setTextureRect(IntRect(64 * int(s_frame), 128, 64, 64));
								sprite.move(-0.15 * time, 0);*/
						}
					}
				}
			}
		}
	}
	void update(float time) {
		checkc(dx, dy);
		x += dx * time;
		sprite.setPosition(x, y);
		if (health <= 0) {
			life = false;
		}
	}
};
/*void Coin() {
	Image i_coin;
	i_coin.loadFromFile("images/coins.png");
	Texture t_coin;
	Sprite s_coin;
	t_coin.loadFromImage(i_coin);
	s_coin.setTexture(t_coin);
	s_coin.setPosition(view.getCenter().x - 320, view.getCenter().y - 230);
	s_coin.setTextureRect(IntRect(0, 0, 40, 30));
	s_coin.setScale(1.5, 1.5);
}*/
/*
* void Souding(string N) {
		buff.loadFromFile(N);
		sound_play.setBuffer(buff);
		sound_play.play();
	}
*/
int main() {
	RenderWindow window(VideoMode(800, 540), "The bravest knight");
	view.reset(FloatRect(0, 0, 640, 480));
	Image map_image;
	map_image.loadFromFile("images/Dungeon tileset.png");
	Texture map_texture;
	map_texture.loadFromImage(map_image);
	Sprite map_sprite;
	map_sprite.setTexture(map_texture);
	//Player player(250, 250, 32.0, 32.0, "Character.png");
	Enemy Enemy(250, 250, 32.0, 32.0, "skeleton");
	Player player(250, 250, 32.0, 32.0, "Main_character");
	InteractiveObj  InteractiveObj(250, 250, 32.0, 32.0, "Chest");
	double Cur_frame(0);
	double s_frame(0);
	bool showtext = true;
	Clock clock;
	Font font;
	font.loadFromFile("images/font_pixel.ttf");
	Text player_score("", font, 30);
	Text insane("", font, 30);
	insane.setStyle(Text::Bold);
	insane.setFillColor(Color::Cyan);
	player_score.setFillColor(Color::Yellow);
	player_score.setStyle(Text::Bold);
	Text heart_score("", font, 30);
	heart_score.setFillColor(Color::Red);
	heart_score.setStyle(Text::Bold);
	int createObjectForMapTimer = 0;
	while (window.isOpen()) {
		Event event;
		double time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Q) {
				int a = 0;
				switch (showtext) {
				case (true): {
					ostringstream info;
					info << (user_info(User_Info(a)));
					insane.setString(info.str());
					showtext = false;
					break;
				}
				case (false): {
					showtext = true;
					break;
				}
				}
			}
			if (event.type = Event::Closed)
				window.close();
		}
		if (Enemy.life) {
			if (Enemy.dx < 0) {
				s_frame += 0.005 * time;
				if (s_frame > 5) {
					s_frame -= 5;
				}
				Enemy.sprite.setTextureRect(IntRect(64 * int(s_frame), 128, 64, 64));
				Enemy.sprite.move(-0.15 * time, 0);
			}
			if (Enemy.dx > 0) {
				s_frame += 0.005 * time;
				if (s_frame > 5) {
					s_frame -= 5;
				}
				Enemy.sprite.setTextureRect(IntRect(64 * int(s_frame), 192, 64, 64)); //128 64 64 
				Enemy.sprite.move(0.15 * time, 0);
			}
		}
		if (player.life) {
			int n(5), k(64);
			if (Mouse::isButtonPressed(Mouse::Left)) {
				n = 2;
				k = 380;
				//player.sprite.setTextureRect(IntRect(64 * int(Cur_frame), 192, 64, 64));
			}
			if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D))) { // влево вправо
				CheckLShift(player);
				Cur_frame += 0.005 * time;//?
				if (Keyboard::isKeyPressed(Keyboard::A)) {
					player.direction = 2;
					if (Cur_frame > n) {
						Cur_frame -= n;
					}
					player.sprite.setTextureRect(IntRect(k * int(Cur_frame), 192, 64, 64));
					PlayerView(player.x, player.y);
					player.sprite.move(-0.15 * time, 0);

				}
				else {
					player.direction = 0;
					if (Cur_frame > n) {
						Cur_frame -= n;
					}
					player.sprite.setTextureRect(IntRect(k * int(Cur_frame), 128, 64, 64)); //128 64 64 
					PlayerView(player.x, player.y);
					player.sprite.move(0.15 * time, 0);
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::S) || (Keyboard::isKeyPressed(Keyboard::W))) { // вниз вверх
				CheckLShift(player);
				Cur_frame += 0.005 * time;//?
				if (Keyboard::isKeyPressed(Keyboard::S)) {
					player.direction = 1;
					if (Cur_frame > n) {
						Cur_frame -= n;
					}
					player.sprite.setTextureRect(IntRect(k * int(Cur_frame), 0, 64, 64)); // 0,64,64
					PlayerView(player.x, player.y);
					player.sprite.move(0, 0.15 * time);
				}
				else {
					player.direction = 3;
					if (Cur_frame > n) {
						Cur_frame -= n;
					}
					player.sprite.setTextureRect(IntRect(k * int(Cur_frame), 74, 64, 64)); // 64 64 64
					PlayerView(player.x, player.y);
					player.sprite.move(0, -0.15 * time);
				}
			}
		}
		createObjectForMapTimer += time;
		if (createObjectForMapTimer > 3000) {
			randomgen();
			createObjectForMapTimer = 0;
		}
		Enemy.update(time);
		player.movement_update(time);
		FloatRect playerbounds = player.sprite.getGlobalBounds();
		FloatRect enemybounds = Enemy.sprite.getGlobalBounds();
		//playerbounds.intersects(enemybounds)
		if (playerbounds.intersects(Enemy.getRect())) {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				Enemy.health--;
			}
			if (player.dx > 0) {
				player.x = Enemy.x - Enemy.w;
			}
			if (player.dx < 0) {
				player.x = Enemy.x + player.w;
			}
		}
		if (Enemy.life == false) {
			Enemy.dx = 0;
			Enemy.sprite.setTextureRect(IntRect(160, 267, w + 32, h + 32));
		}
		sf::RectangleShape rectangle(sf::Vector2f(120, 50));
		rectangle.setPosition(580, 65);
		sf::FloatRect rectanglebounds = rectangle.getGlobalBounds();
		if (playerbounds.intersects(rectanglebounds)) {
			player.x -= 150;
			player.y += 200;
			player.sprite.setPosition(player.x - 100, player.y + 200);
		}
		window.setView(view);
		window.clear();
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++) {
				{
					if (TileMap[i][j] == '3') {
						map_sprite.setTextureRect(IntRect(305, 126, 32, 32));
					}
					if (TileMap[i][j] == 'g') {
						map_sprite.setTextureRect(IntRect(80, 48, 32, 32));
					}
					if (TileMap[i][j] == 'e') {
						map_sprite.setTextureRect(IntRect(335, 160, 32, 32));
					}
					if (TileMap[i][j] == 'l') {
						map_sprite.setTextureRect(IntRect(338, 128, 32, 32));
					}
					if (TileMap[i][j] == '#') {
						map_sprite.setTextureRect(IntRect(0, 16, 32, 32));
					}
					if (TileMap[i][j] == '*') {
						map_sprite.setTextureRect(IntRect(310, 32, 32, 32));
					}
					if (TileMap[i][j] == '~') {
						map_sprite.setTextureRect(IntRect(330, 32, 32, 32));
					}
					if (TileMap[i][j] == '!') {
						map_sprite.setTextureRect(IntRect(311, 0, 32, 32));
					}
					if (TileMap[i][j] == '+') {
						map_sprite.setTextureRect(IntRect(202, -2, 32, 32));
					}
				}
				if (TileMap[i][j] == 'i') {
					map_sprite.setTextureRect(IntRect(56, 112, 37, 32));
				}
				if (TileMap[i][j] == 'p') {
					map_sprite.setTextureRect(IntRect(200, 159, 32, 32));
				}
				if (TileMap[i][j] == 'o') {
					map_sprite.setTextureRect(IntRect(189, 159, 32, 32));

				}
				if (TileMap[i][j] == 't') {
					map_sprite.setTextureRect(IntRect(170, 158, 32, 32));
				}
				if (TileMap[i][j] == ']') {
					map_sprite.setTextureRect(IntRect(275, 64, 32, 32));
				}
				if (TileMap[i][j] == '[') {
					map_sprite.setTextureRect(IntRect(275, 96, 32, 32));
				}
				if (TileMap[i][j] == '{') {
					map_sprite.setTextureRect(IntRect(170, 158, 32, 32));
				}
				if (TileMap[i][j] == 'x') {
					map_sprite.setTextureRect(IntRect(273, 125, 32, 32));
				}
				if (TileMap[i][j] == 'd') {
					map_sprite.setTextureRect(IntRect(242, 130, 32, 32));
				}
				{
					if (TileMap[i][j] == '_') {
						map_sprite.setTextureRect(IntRect(329, 0, 32, 32));
					}
					if (TileMap[i][j] == ')') {
						map_sprite.setTextureRect(IntRect(220, -4, 32, 32));
					}
					if (TileMap[i][j] == '@') {
						map_sprite.setTextureRect(IntRect(248, 2, 32, 32));
					}
					if (TileMap[i][j] == '$') {
						map_sprite.setTextureRect(IntRect(266, 2, 32, 32));
					}
					if (TileMap[i][j] == ' ') {
						map_sprite.setTextureRect(IntRect(70, 153, 32, 32));
					}
					if (TileMap[i][j] == '-') {
						map_sprite.setTextureRect(IntRect(70, 153, 32, 32));
					}
					if (TileMap[i][j] == 'c') {
						map_sprite.setTextureRect(IntRect(208, 90, 32, 32));
					}
					if (TileMap[i][j] == 's') {
						map_sprite.setTextureRect(IntRect(304, 160, 32, 32));
					}
					if (TileMap[i][j] == 'h') {
						map_sprite.setTextureRect(IntRect(208, 33, 32, 32));
					}
					if (TileMap[i][j] == 'b') {
						map_sprite.setTextureRect(IntRect(0, 0, 1, 1));
					}
				}
				map_sprite.setPosition(j * 32, i * 32); //32 32
				window.draw(map_sprite);
			}
		//		if (spritebounds.intersects());
				//возможно ли перенейсти код с монеткой в функцию ?
		{

			Image i_coin;
			i_coin.loadFromFile("images/coins.png");
			Texture t_coin;
			Sprite s_coin;
			t_coin.loadFromImage(i_coin);
			s_coin.setTexture(t_coin);
			s_coin.setPosition(view.getCenter().x - 320, view.getCenter().y - 230);
			s_coin.setTextureRect(IntRect(0, 0, 40, 30));
			s_coin.setScale(1.5, 1.5);
			window.draw(s_coin);
		}
		if (!showtext) {
			insane.setPosition(view.getCenter().x - 300, view.getCenter().y - 170);
			window.draw(insane);
		}
		player_score.setString("Money score: " + to_string(player.money_score));
		heart_score.setString("Lives:" + to_string(player.health));
		player_score.setPosition(view.getCenter().x - 280, view.getCenter().y - 230);
		heart_score.setPosition(view.getCenter().x - 280, view.getCenter().y - 200);
		window.draw(player.sprite);
		window.draw(InteractiveObj.sprite);
		window.draw(Enemy.sprite);
		window.draw(player_score);
		window.draw(heart_score);
		//	window.draw(rectangle);
		window.display();
	}
	return 0;
}
#include<iostream>
#include <sstream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <vector>
#include <list>
#include "map.h"
#include "info.h"
#include "view.h"
using namespace std;
using namespace sf;
char objmassive[8] = { '#','@',')','$','+','*','~','_' };
/*const map<char, IntRect> sprites{
		{'#', IntRect(0,0,32,32)},
		{'*', IntRect(16,0,32,32)},
		{'~', IntRect(32,0,32,32)},
		{'!', IntRect(64,0,32,32)},
		{'+', IntRect(96,0,32,32)},
		{'*', IntRect(128,0,32,32)},
		{'i', IntRect(160,0,32,32)},
		{'p', IntRect(192,0,32,32)},
		{'x', IntRect(224,0,32,32)},
		{'d', IntRect(256,0,32,32)},
		{'_', IntRect(288,0,32,32)},
		{')', IntRect(320,0,32,32)},
		{'@', IntRect(352,0,32,32)},
		{'$', IntRect(384,0,32,32)},
		{' ', IntRect(400,0,32,32)},
		{'r', IntRect(255,0,32,32)},
		{'z', IntRect(211,0,32,32)},
		{'h', IntRect(322,0,32,32)},
		{'b', IntRect(233,0,32,32)},
};*/


class Entity {
public:
	double x, y, w, h, dx, dy, speed = 0;
	bool life;
	int health;
	Image image;
	Texture texture;
	Sprite sprite;
	string type;
	Entity(double X, double Y, double W, double H, string TYPE) {
		x = X;
		y = Y;
		w = W;
		h = H;
		type = TYPE;
		speed = 0;
		life = true;
		health = 5;
	}
	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}
	~Entity() {

	}

};
class InteractiveObj :public Entity {
private:
public:
	InteractiveObj(float X, float Y, float W, float H, String TYPE) :Entity(X, Y, W, H, TYPE) {
		if (TYPE == "Chest") {
			image.loadFromFile("images/chests.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(32, 0, w, h));
			sprite.setOrigin(w / 2, h / 2);
			sprite.setPosition(x - 10, y + 1200);
		}
		if (TYPE == "BAll") {

		}
	}
};
class Player :public Entity { // класс Игрока
private:
public:
	int money_score = 0;
	int direction = 0; // куда?
	SoundBuffer buff;
	Sound sound_play;
	/*enum movements {
		up,
		down,
		right,
		left
	} movings*/
	Player(float X, float Y, float W, float H, String TYPE) :Entity(X, Y, W, H, TYPE) {
		if (TYPE == "Main_character") {
			money_score = 0;
			image.loadFromFile("images/Character_SpriteSheet.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, w, h)); //sprite.setTextureRect(IntRect(0, 0, w, h));
			sprite.setOrigin(w / 2, h / 2); // убрать
		}
	}
	void movement_update(double time)
	{
		switch (direction) {
		case (0): // вправо
			dx = speed;
			dy = 0;
			break;
		case (1): // вниз
			dx = 0;
			dy = speed;
			break;
		case (2): //влево
			dx = -speed;
			dy = 0;
			break;
		case (3):  //вверх
			dx = 0;
			dy = -speed;
			break;
		}
		x += dx * time;
		y += dy * time;
		speed = 0;
		sprite.setPosition(x, y);
		player_solid();
		if (health <= 0) {
			life = false;
		}
	}
	void Sounding(const string& N) {
		buff.loadFromFile(N);
		sound_play.setBuffer(buff);
		sound_play.play();
	}
	void player_solid() {
		for (int i = (y / 32); i < (y + h) / 32; i++) { // 34 
			for (int j = (x / 32); j < (x + w) / 32; j++) { //16
				for (int z = 0; z < 8; z++) {
					if (TileMap[i][j] == objmassive[z]) {
						if (dy > 0 || dy < 0) {
							if (dy > 0) {
								y = i * 32 - h;
							}
							else {
								y = i * 32 + 32;//+34
							}
						}
						if (dx > 0 || dx < 0) {
							if (dx > 0) {
								x = j * 32 - w;
							}
							else {
								x = j * 32 + 32;
							}
						}
					}
					if (TileMap[i][j] == 'c') { // 
						money_score++;
						Sounding("Validation.ogg");
						TileMap[i][j] = (' ');
					}
					if (TileMap[i][j] == 's' && health != 0) {
						health--;
						Sounding("Hit.wav");
						TileMap[i][j] = (' '); // изменить шипы и добавить второй вид с коллизией.
					}
					if (TileMap[i][j] == 'h') { // изменить спрайт на бутылек 
						health++;
						Sounding("Healing.wav");
						TileMap[i][j] = (' ');
					}
				}
			}
		}
	}
};
void CheckLShift(Player& player) {
	if (Keyboard::isKeyPressed(Keyboard::LShift)) {
		player.speed = 0.3;
	}
	else {
		player.speed = 0.1;
	}
}
int Random(int min, int max) {
	return min + rand() % (max - min);
}
class Enemy :public Entity {
public:
	string TYPE = "";
	Enemy(float X, float Y, float W, float H, string TYPE) :Entity(X, Y, W, H, TYPE) { //(double X, double Y, double W, double H, string TYPE)
		if (TYPE == "skeleton") {
			this->TYPE = TYPE;
			image.loadFromFile("images/skeletik.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, w, h));
			sprite.setOrigin(w / 2, h / 2); // убрать
			dx = 0.07;
		}
		if (TYPE == "Suriken") {
			this->TYPE = TYPE;
			image.loadFromFile("images/Suriken");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, w, h));
			sprite.setOrigin(w / 2, h / 2);

		}
	}
	void checkc(float DX, float DY) {
		for (int i = y / 32; i < (y + h) / 32; i++) {
			for (int j = x / 32; j < (x + w) / 32; j++) {
				for (int z = 0; z < 8; z++) {
					if (TileMap[i][j] == objmassive[z] && health) {
						if (DY > 0 && TYPE == "skeleton") {//>
							y = i * 32 - h;
						}
						if (DY < 0 && TYPE == "skeleton") {//<
							y = i * 32 + Random(-4, 37); // -3 35 ,-4 37
						}
						if (DX < 0) { //<
							x = j * 32 + 32;
							dx = 0.07;
							/*	s_frame += 0.005 * time;
								y = i * 32;
								if (s_frame > 5) {
									s_frame -= 5;
								}
								sprite.setTextureRect(IntRect(64 * double(s_frame), 192, 64, 64)); //128 64 64
								sprite.move(0.15 * time, 0);*/
						}
						if (DX > 0) {//>
							x = j * 32 - w;
							dx = -0.07;
							/*	if (s_frame > 5) {
									s_frame -= 5;
								}
								sprite.setTextureRect(IntRect(64 * int(s_frame), 128, 64, 64));
								sprite.move(-0.15 * time, 0);*/
						}
					}
				}
			}
		}
	}
	void update(float time) {
		checkc(dx, dy);
		x += dx * time;
		sprite.setPosition(x, y);
		if (health <= 0) {
			life = false;
		}
	}
};
/*void Coin() {
	Image i_coin;
	i_coin.loadFromFile("images/coins.png");
	Texture t_coin;
	Sprite s_coin;
	t_coin.loadFromImage(i_coin);
	s_coin.setTexture(t_coin);
	s_coin.setPosition(view.getCenter().x - 320, view.getCenter().y - 230);
	s_coin.setTextureRect(IntRect(0, 0, 40, 30));
	s_coin.setScale(1.5, 1.5);
}*/
/*
* void Souding(string N) {
		buff.loadFromFile(N);
		sound_play.setBuffer(buff);
		sound_play.play();
	}
*/
int main() {
	RenderWindow window(VideoMode(800, 540), "The bravest knight");
	view.reset(FloatRect(0, 0, 640, 480));
	Image map_image;
	map_image.loadFromFile("images/Dungeon tileset.png");
	Texture map_texture;
	map_texture.loadFromImage(map_image);
	Sprite map_sprite;
	map_sprite.setTexture(map_texture);
	//Player player(250, 250, 32.0, 32.0, "Character.png");
	Enemy enemy(250, 250, 32.0, 32.0, "skeleton");
	Enemy enemy2(250, 250, 32.0, 32.0, "Suriken");
	Player player(250, 250, 32.0, 32.0, "Main_character");
	InteractiveObj  InteractiveObj(250, 250, 32.0, 32.0, "Chest");
	double Cur_frame(0);
	double s_frame(0);
	bool showtext = true;
	Clock clock;
	Font font;
	font.loadFromFile("images/font_pixel.ttf");
	Text player_score("", font, 30);
	Text insane("", font, 30);
	insane.setStyle(Text::Bold);
	insane.setFillColor(Color::Cyan);
	player_score.setFillColor(Color::Yellow);
	player_score.setStyle(Text::Bold);
	Text heart_score("", font, 30);
	heart_score.setFillColor(Color::Red);
	heart_score.setStyle(Text::Bold);
	int createObjectForMapTimer = 0;
	while (window.isOpen()) {
		Event event;
		double time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Q) {
				int a = 0;
				switch (showtext) {
				case (true): {
					ostringstream info;
					info << (user_info(User_Info(a)));
					insane.setString(info.str());
					showtext = false;
					break;
				}
				case (false): {
					showtext = true;
					break;
				}
				}
			}
			if (event.type = Event::Closed)
				window.close();
		}
		if (enemy.life) {
			if (enemy.dx < 0) {
				s_frame += 0.005 * time;
				if (s_frame > 5) {
					s_frame -= 5;
				}
				enemy.sprite.setTextureRect(IntRect(64 * int(s_frame), 128, 64, 64));
				enemy.sprite.move(-0.15 * time, 0);
			}
			if (enemy.dx > 0) {
				s_frame += 0.005 * time;
				if (s_frame > 5) {
					s_frame -= 5;
				}
				enemy.sprite.setTextureRect(IntRect(64 * int(s_frame), 192, 64, 64)); //128 64 64 
				enemy.sprite.move(0.15 * time, 0);
			}
		}
		if (player.life) {
			int n(5), k(64);
			if (Mouse::isButtonPressed(Mouse::Left)) {
				n = 2;
				k = 380;
				//player.sprite.setTextureRect(IntRect(64 * int(Cur_frame), 192, 64, 64));
			}
			if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D))) { // влево вправо
				CheckLShift(player);
				Cur_frame += 0.005 * time;//?
				if (Keyboard::isKeyPressed(Keyboard::A)) {
					player.direction = 2;
					if (Cur_frame > n) {
						Cur_frame -= n;
					}
					player.sprite.setTextureRect(IntRect(k * int(Cur_frame), 192, 64, 64));
					PlayerView(player.x, player.y);
					player.sprite.move(-0.15 * time, 0);

				}
				else {
					player.direction = 0;
					if (Cur_frame > n) {
						Cur_frame -= n;
					}
					player.sprite.setTextureRect(IntRect(k * int(Cur_frame), 128, 64, 64)); //128 64 64 
					PlayerView(player.x, player.y);
					player.sprite.move(0.15 * time, 0);
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::S) || (Keyboard::isKeyPressed(Keyboard::W))) { // вниз вверх
				CheckLShift(player);
				Cur_frame += 0.005 * time;//?
				if (Keyboard::isKeyPressed(Keyboard::S)) {
					player.direction = 1;
					if (Cur_frame > n) {
						Cur_frame -= n;
					}
					player.sprite.setTextureRect(IntRect(k * int(Cur_frame), 0, 64, 64)); // 0,64,64
					PlayerView(player.x, player.y);
					player.sprite.move(0, 0.15 * time);
				}
				else {
					player.direction = 3;
					if (Cur_frame > n) {
						Cur_frame -= n;
					}
					player.sprite.setTextureRect(IntRect(k * int(Cur_frame), 74, 64, 64)); // 64 64 64
					PlayerView(player.x, player.y);
					player.sprite.move(0, -0.15 * time);
				}
			}
		}
		createObjectForMapTimer += time;
		if (createObjectForMapTimer > 3000) {
			randomgen();
			createObjectForMapTimer = 0;
		}
		enemy.update(time);
		player.movement_update(time);
		FloatRect playerbounds = player.sprite.getGlobalBounds();
		FloatRect enemybounds = enemy.sprite.getGlobalBounds();
		//playerbounds.intersects(enemybounds)
		if (playerbounds.intersects(enemy.getRect())) {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				enemy.health--;
			}
			if (player.dx > 0) {
				player.x = enemy.x - enemy.w;
			}
			if (player.dx < 0) {
				player.x = enemy.x + player.w;
			}
		}
		if (enemy.life == false) {
			enemy.dx = 0;
			enemy.sprite.setTextureRect(IntRect(160, 267, w + 32, h + 32));
		}
		sf::RectangleShape rectangle(sf::Vector2f(120, 50));
		rectangle.setPosition(580, 65);
		sf::FloatRect rectanglebounds = rectangle.getGlobalBounds();
		if (playerbounds.intersects(rectanglebounds)) {
			player.x -= 150;
			player.y += 200;
			player.sprite.setPosition(player.x - 100, player.y + 200);
		}
		window.setView(view);
		window.clear();
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++) {
				{
					if (TileMap[i][j] == '3') {
						map_sprite.setTextureRect(IntRect(305, 126, 32, 32));
					}
					if (TileMap[i][j] == 'g') {
						map_sprite.setTextureRect(IntRect(80, 48, 32, 32));
					}
					if (TileMap[i][j] == 'e') {
						map_sprite.setTextureRect(IntRect(335, 160, 32, 32));
					}
					if (TileMap[i][j] == 'l') {
						map_sprite.setTextureRect(IntRect(338, 128, 32, 32));
					}
					if (TileMap[i][j] == '#') {
						map_sprite.setTextureRect(IntRect(0, 16, 32, 32));
					}
					if (TileMap[i][j] == '*') {
						map_sprite.setTextureRect(IntRect(310, 32, 32, 32));
					}
					if (TileMap[i][j] == '~') {
						map_sprite.setTextureRect(IntRect(330, 32, 32, 32));
					}
					if (TileMap[i][j] == '!') {
						map_sprite.setTextureRect(IntRect(311, 0, 32, 32));
					}
					if (TileMap[i][j] == '+') {
						map_sprite.setTextureRect(IntRect(202, -2, 32, 32));
					}
				}
				if (TileMap[i][j] == 'i') {
					map_sprite.setTextureRect(IntRect(56, 112, 37, 32));
				}
				if (TileMap[i][j] == 'p') {
					map_sprite.setTextureRect(IntRect(200, 159, 32, 32));
				}
				if (TileMap[i][j] == 'o') {
					map_sprite.setTextureRect(IntRect(189, 159, 32, 32));

				}
				if (TileMap[i][j] == 't') {
					map_sprite.setTextureRect(IntRect(170, 158, 32, 32));
				}
				if (TileMap[i][j] == ']') {
					map_sprite.setTextureRect(IntRect(275, 64, 32, 32));
				}
				if (TileMap[i][j] == '[') {
					map_sprite.setTextureRect(IntRect(275, 96, 32, 32));
				}
				if (TileMap[i][j] == '{') {
					map_sprite.setTextureRect(IntRect(170, 158, 32, 32));
				}
				if (TileMap[i][j] == 'x') {
					map_sprite.setTextureRect(IntRect(273, 125, 32, 32));
				}
				if (TileMap[i][j] == 'd') {
					map_sprite.setTextureRect(IntRect(242, 130, 32, 32));
				}
				{
					if (TileMap[i][j] == '_') {
						map_sprite.setTextureRect(IntRect(329, 0, 32, 32));
					}
					if (TileMap[i][j] == ')') {
						map_sprite.setTextureRect(IntRect(220, -4, 32, 32));
					}
					if (TileMap[i][j] == '@') {
						map_sprite.setTextureRect(IntRect(248, 2, 32, 32));
					}
					if (TileMap[i][j] == '$') {
						map_sprite.setTextureRect(IntRect(266, 2, 32, 32));
					}
					if (TileMap[i][j] == ' ') {
						map_sprite.setTextureRect(IntRect(70, 153, 32, 32));
					}
					if (TileMap[i][j] == '-') {
						map_sprite.setTextureRect(IntRect(70, 153, 32, 32));
					}
					if (TileMap[i][j] == 'c') {
						map_sprite.setTextureRect(IntRect(208, 90, 32, 32));
					}
					if (TileMap[i][j] == 's') {
						map_sprite.setTextureRect(IntRect(304, 160, 32, 32));
					}
					if (TileMap[i][j] == 'h') {
						map_sprite.setTextureRect(IntRect(208, 33, 32, 32));
					}
					if (TileMap[i][j] == 'b') {
						map_sprite.setTextureRect(IntRect(0, 0, 1, 1));
					}
				}
				map_sprite.setPosition(j * 32, i * 32); //32 32
				window.draw(map_sprite);
			}
		//		if (spritebounds.intersects());
				//возможно ли перенейсти код с монеткой в функцию ?
		{

			Image i_coin;
			i_coin.loadFromFile("images/coins.png");
			Texture t_coin;
			Sprite s_coin;
			t_coin.loadFromImage(i_coin);
			s_coin.setTexture(t_coin);
			s_coin.setPosition(view.getCenter().x - 320, view.getCenter().y - 230);
			s_coin.setTextureRect(IntRect(0, 0, 40, 30));
			s_coin.setScale(1.5, 1.5);
			window.draw(s_coin);
		}
		if (!showtext) {
			insane.setPosition(view.getCenter().x - 300, view.getCenter().y - 170);
			window.draw(insane);
		}
		player_score.setString("Money score: " + to_string(player.money_score));
		heart_score.setString("Lives:" + to_string(player.health));
		player_score.setPosition(view.getCenter().x - 280, view.getCenter().y - 230);
		heart_score.setPosition(view.getCenter().x - 280, view.getCenter().y - 200);
		window.draw(player.sprite);
		window.draw(InteractiveObj.sprite);
		window.draw(enemy.sprite);
		window.draw(enemy2.sprite);
		window.draw(player_score);
		window.draw(heart_score);
		//	window.draw(rectangle);
		window.display();
	}
	return 0;
}
