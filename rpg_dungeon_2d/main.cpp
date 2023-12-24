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
	char collision_objects[13] = { '#','@',')','$','+','*','~','_',']','l','g','i','3' };
	double x, y, w, h, dx, dy, speed = 0;
	bool life;
	int health;
	double cur_frame = 0;
	Image image;
	Texture texture;
	Sprite sprite;
	string type;
	Entity(double X, double Y, double W, double H, string TYPE, double current_frame) {
		x = X;
		y = Y;
		w = W;
		h = H;
		type = TYPE;
		speed = 0;
		life = true;
		health = 5;
		cur_frame = current_frame;
	}
	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}
	~Entity() {
	}

};
class Player :public Entity { 
public:
	int money_score = 0;
	int direction = 0;
	int n = 0, k= 0;
	SoundBuffer buff;
	Sound sound_play;
	/*enum movements {
		up,
		down,
		right,
		left
	} movings*/
	Player(float X, float Y, float W, float H, String TYPE, double current_frame) :Entity(X, Y, W, H, TYPE, current_frame) {
		if (TYPE == "Main_character") {
			money_score = 0;
			current_frame = 0;
			image.loadFromFile("images/Character_SpriteSheet.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, w, h));
			sprite.setOrigin(w / 2, h / 2);
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
	void SoundEffect(const string& N) {
		buff.loadFromFile(N);
		sound_play.setBuffer(buff);
		sound_play.play();
	}
	void CheckDirection(double& time) {
		if (life == true) {
			n = 5;
			k = 64;
			if (Mouse::isButtonPressed(Mouse::Left)) {
				n = 2;
				k = 380;
			}
			if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D))) { // влево вправо
				IsLShiftPressed();
				cur_frame += 0.005 * time;//?
				if (Keyboard::isKeyPressed(Keyboard::A)) {
					direction = 2;
					if (cur_frame > n) {
						cur_frame -= n;
					}
					sprite.setTextureRect(IntRect(k * int(cur_frame), 192, 64, 64));
					PlayerView(x, y);
					//sprite.move(-0.15 * time, 0);

				}
				else {
					IsLShiftPressed();
					direction = 0;
					if (cur_frame > n) {
						cur_frame -= n;
					}
					sprite.setTextureRect(IntRect(k * int(cur_frame), 128, 64, 64)); //128 64 64 
					PlayerView(x, y);
					//sprite.move(0.15 * time, 0);
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::S) || (Keyboard::isKeyPressed(Keyboard::W))) { // вниз вверх
				IsLShiftPressed();
				cur_frame += 0.005 * time;//?
				if (Keyboard::isKeyPressed(Keyboard::S)) {
					direction = 1;
					if (cur_frame > n) {
						cur_frame -= n;
					}
					sprite.setTextureRect(IntRect(k * int(cur_frame), 0, 64, 64)); // 0,64,64
					PlayerView(x, y);
					//sprite.move(0, 0.15 * time);
				}
				else {
					IsLShiftPressed();
					direction = 3;
					if (cur_frame > n) {
						cur_frame -= n;
					}
					sprite.setTextureRect(IntRect(k * int(cur_frame), 70, 64, 64)); // 64 64 64
					PlayerView(x, y);
					//sprite.move(0, -0.15 * time);
				}
			}
		}
	}
	void player_solid() {
		for (int i = (y / 32); i < (y + h) / 32; i++) { // 34 
			for (int j = (x / 32); j < (x + w) / 32; j++) { //16
				for (int z = 0; z < 13; z++) {
					if (TileMap[i][j] == collision_objects[z]) {
						if (dy > 0 || dy < 0) {
							if (dy > 0) {
								y = i * 32 - h;
							}
							else {
								y = i * 32 + h;//+34
							}
						}
						if (dx > 0 || dx < 0) {
							if (dx > 0) {
								x = j * 32 - w;
							}
							else {
								x = j * 32 + w;
							}
						}
					}
					if (TileMap[i][j] == 'c') { // 
						money_score++;
						SoundEffect("Validation.ogg");
						TileMap[i][j] = (' ');
					}
					if (TileMap[i][j] == 's' && health != 0) {
						health--;
						SoundEffect("Hit.wav");
						TileMap[i][j] = (' ');
					}
					if (TileMap[i][j] == 'h') {
						health++;
						SoundEffect("Healing.wav");
						TileMap[i][j] = (' ');
					}
				}
			}
		}
	}
	void IsLShiftPressed() {
		if (Keyboard::isKeyPressed(Keyboard::LShift)) {
			speed = 0.3;
	}
		else {
			speed =  0.1;
		}
	}
};
class Enemy :public Entity {
public:
	string TYPE = "";
	Enemy(float X, float Y, float W, float H, string TYPE, double current_frame) :Entity(X, Y, W, H, TYPE, current_frame) { //(double X, double Y, double W, double H, string TYPE)
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
			image.loadFromFile("images/Suriken.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, w, h));
			sprite.setOrigin(w / 2, h / 2);

		}
	}
	int RandomMovementByY(int min, int max) {
		return min + rand() % (max - min);
	}
	void CheckEnemyDirection(double & time) {
		if (dx < 0) {
			cur_frame += 0.005 * time;
			if (cur_frame > 5) {
				cur_frame -= 5;
			}
			sprite.setTextureRect(IntRect(64 * int(cur_frame), 128, 64, 64));
			sprite.move(-0.15 * time, 0);
		}
		if (dx > 0) {
			cur_frame += 0.005 * time;
			if (cur_frame > 5) {
				cur_frame -= 5;
			}
			sprite.setTextureRect(IntRect(64 * int(cur_frame), 192, 64, 64)); //128 64 64 
			sprite.move(0.15 * time, 0);
		}
	}
	void CheckEnemyCollisionWObjects(float DX, float DY) {
		for (int i = y / 32; i < (y + h) / 32; i++) {
			for (int j = x / 32; j < (x + w) / 32; j++) {
				for (int z = 0; z < 8; z++) {
					if (TileMap[i][j] == collision_objects[z] && health) {
						if (DY > 0) {//>
							y = i * 32 - w;
						}
						if (DY < 0) {//<
							y = i * 32 + RandomMovementByY(-4, 37); // -3 35 ,-4 37
						}
						if (DX < 0) { //<
							x = j * 32 + h;
							dx = 0.07;
						}
						if (DX > 0) {//>
							x = j * 32 - h;
							dx = -0.07;
						}
					}
				}
			}
		}
	}
	void update(float time) {
		CheckEnemyCollisionWObjects(dx, dy);
		x += dx * time;
		sprite.setPosition(x, y);
		if (health <= 0) {
			life = false;
			dx = 0;
			sprite.setTextureRect(IntRect(160, 267, w + 32, h + 32));
			
		}
	}
};
class InteractiveObj :public Entity {
private:
public:
	InteractiveObj(float X, float Y, float W, float H, String TYPE, double current_frame) :Entity(X, Y, W, H, TYPE, current_frame) {
		if (TYPE == "Chest") {
			image.loadFromFile("images/chests.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(32, 0, w, h));
			sprite.setOrigin(w / 2, h / 2);
			sprite.setPosition(x, y); // -10, +1200
		}
		if (TYPE == "Ball") {
			image.loadFromFile("images/ball.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(0, 0, w, h));
			sprite.setOrigin(w / 2, h / 2);
			sprite.setPosition(x, y); // 870 1233
		}
	}
};
int main() {
	RenderWindow window(VideoMode(1200, 800), "The bravest knight");
	view.reset(FloatRect(0, 0, 640, 480));
	Enemy enemy(100, 250, 32.0, 32.0, "skeleton", 0);
	Player player(100, 100, 32.0, 32.0, "Main_character", 0);
	InteractiveObj  Chest(240, 1450, 32.0, 32.0, "Chest", 0);
	InteractiveObj  Stone_ball(1120, 1483, 64.0, 64.0, "Ball", 0);
	Image map_image;
	Texture map_texture;
	Sprite map_sprite;
	map_image.loadFromFile("images/Dungeon tileset.png");
	map_texture.loadFromImage(map_image);
	map_sprite.setTexture(map_texture);
	Image i_coin;
	Texture t_coin;
	Sprite s_coin;
	i_coin.loadFromFile("images/coins.png");
	t_coin.loadFromImage(i_coin);
	s_coin.setTexture(t_coin);
	s_coin.setTextureRect(IntRect(0, 0, 40, 30));
	s_coin.setScale(1.5, 1.5);
	Clock clock; // Часы в игре нужны для привязки ко времени, а не к привязке от процессора (Если процессор будет нагружен, то картинка без часов будет глючить)
	Font font;
	font.loadFromFile("images/font_pixel.ttf");
	Text player_score("", font, 30);
	RectangleShape rectangle1(sf::Vector2f(64, 32));
	rectangle1.setPosition(510, 90);
	FloatRect rectanglebounds1 = rectangle1.getGlobalBounds();
	RectangleShape rectangle2(sf::Vector2f(64, 32));
	rectangle2.setPosition(1150, 390);
	sf::FloatRect rectanglebounds2 = rectangle2.getGlobalBounds();
	RectangleShape rectangle3(sf::Vector2f(64, 32));
	rectangle3.setPosition(1150, 900);
	sf::FloatRect rectanglebounds3 = rectangle3.getGlobalBounds();
	FloatRect ChestBoards = Chest.sprite.getGlobalBounds();
	player_score.setFillColor(Color::Yellow);
	player_score.setStyle(Text::Bold);
	Text HelpText("", font, 30);
	HelpText.setStyle(Text::Bold);
	HelpText.setFillColor(Color::Cyan);
	Text heart_score("", font, 30);
	heart_score.setFillColor(Color::Red);
	heart_score.setStyle(Text::Bold);
	bool IsChestClosed = true;
	bool showtext = true;
	int createObjectForMapTimer = 0;
	while (window.isOpen()) {
		Event event;
		double time = clock.getElapsedTime().asMicroseconds(); 
		clock.restart();
		time = time / 800; // Чем больше делитель, тем плавнее игра
		createObjectForMapTimer += time;
		enemy.CheckEnemyDirection(time);
		player.CheckDirection(time);
		enemy.update(time);
		player.movement_update(time);
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Q) {
				switch (showtext) {
				case (true): {
					ostringstream info;
					info << (UserInfoText(CurrentScoreInfo(player.money_score)));
					HelpText.setString(info.str());
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
		if (createObjectForMapTimer > 3000) {
			randomgen();
			createObjectForMapTimer = 0;
		}
		if (player.getRect().intersects(enemy.getRect())) {
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
		FloatRect BallBoards = Stone_ball.sprite.getGlobalBounds();
		if (player.getRect().intersects(BallBoards)) {
			Stone_ball.sprite.move(-1.5, 0);
			player.x = player.x + player.w / 7;
		}
		if (player.getRect().intersects(ChestBoards)) {
			if (IsChestClosed == true && Keyboard::isKeyPressed(Keyboard::E)) {
				IsChestClosed = false;
				player.money_score += 10;
				Chest.sprite.setTextureRect(IntRect(0, 0, 32.0, 32.0));
			}
			player.y = player.y + 6;
		}
		if (player.getRect().intersects(rectanglebounds1)) {
			player.y += 180;
			player.sprite.setPosition(player.x, player.y + 180);
		}
		if (player.getRect().intersects(rectanglebounds2)) {
			player.y -= 140;
			player.sprite.setPosition(player.x, player.y - 140);
		}
		if (player.getRect().intersects(rectanglebounds3)) {
			player.y -= 180;
			player.sprite.setPosition(player.x, player.y - 180);
		}
		window.setView(view);
		window.clear();
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++) {
				{ //walls
				 if (TileMap[i][j] == '3') map_sprite.setTextureRect(IntRect(305, 126, 32, 32));
				 if (TileMap[i][j] == 'g') map_sprite.setTextureRect(IntRect(80, 48, 32, 32));
				 if (TileMap[i][j] == 'e') map_sprite.setTextureRect(IntRect(335, 160, 32, 32));
				 if (TileMap[i][j] == 'l') map_sprite.setTextureRect(IntRect(338, 128, 32, 32));
				 if (TileMap[i][j] == '#') map_sprite.setTextureRect(IntRect(0, 16, 32, 32));
				 if (TileMap[i][j] == '*') map_sprite.setTextureRect(IntRect(310, 32, 32, 32));
				 if (TileMap[i][j] == '~') map_sprite.setTextureRect(IntRect(330, 32, 32, 32));
				 if (TileMap[i][j] == '!') map_sprite.setTextureRect(IntRect(311, 0, 32, 32));
				 if (TileMap[i][j] == '+') map_sprite.setTextureRect(IntRect(202, -2, 32, 32));
				 if (TileMap[i][j] == 'i') map_sprite.setTextureRect(IntRect(56, 112, 37, 32));
				 if (TileMap[i][j] == 'p') map_sprite.setTextureRect(IntRect(200, 159, 32, 32));
				 if (TileMap[i][j] == 'o') map_sprite.setTextureRect(IntRect(189, 159, 32, 32));
				 if (TileMap[i][j] == 't') map_sprite.setTextureRect(IntRect(170, 158, 32, 32));
				 if (TileMap[i][j] == ']') map_sprite.setTextureRect(IntRect(275, 64, 32, 32));
				 if (TileMap[i][j] == '{') map_sprite.setTextureRect(IntRect(170, 158, 32, 32));
				 if (TileMap[i][j] == 'x') map_sprite.setTextureRect(IntRect(273, 125, 32, 32));
				 if (TileMap[i][j] == 'd') map_sprite.setTextureRect(IntRect(242, 130, 32, 32));
				 if (TileMap[i][j] == '_') map_sprite.setTextureRect(IntRect(329, 0, 32, 32));
				 if (TileMap[i][j] == ')') map_sprite.setTextureRect(IntRect(220, -4, 32, 32));
				 if (TileMap[i][j] == '@') map_sprite.setTextureRect(IntRect(248, 2, 32, 32));
				 if (TileMap[i][j] == '$') map_sprite.setTextureRect(IntRect(266, 2, 32, 32));
				}
				{ // floor 
					if (TileMap[i][j] == ' ') map_sprite.setTextureRect(IntRect(70, 153, 32, 32));
					if (TileMap[i][j] == '-') map_sprite.setTextureRect(IntRect(70, 153, 32, 32));
					if (TileMap[i][j] == 'b') map_sprite.setTextureRect(IntRect(0, 0, 1, 1));
					if (TileMap[i][j] == '[') map_sprite.setTextureRect(IntRect(275, 96, 32, 32));
				}
				{ // interactive objects
					if (TileMap[i][j] == 'c') map_sprite.setTextureRect(IntRect(208, 90, 32, 32));
					if (TileMap[i][j] == 's') map_sprite.setTextureRect(IntRect(304, 160, 32, 32));
					if (TileMap[i][j] == 'h') map_sprite.setTextureRect(IntRect(208, 33, 32, 32));
				}
				map_sprite.setPosition(j * 32, i * 32); //32 32
				window.draw(map_sprite);
			}
		if (!showtext) {
			HelpText.setPosition(view.getCenter().x - 300, view.getCenter().y - 170);
			window.draw(HelpText);
		}
		player_score.setString("Money score: " + to_string(player.money_score));
		player_score.setPosition(view.getCenter().x - 280, view.getCenter().y - 230);
		window.draw(player_score);
		heart_score.setString("Lives:" + to_string(player.health));
		heart_score.setPosition(view.getCenter().x - 280, view.getCenter().y - 200);
		window.draw(heart_score);
		s_coin.setPosition(view.getCenter().x - 320, view.getCenter().y - 230);
		window.draw(s_coin);
		window.draw(player.sprite);
		window.draw(Chest.sprite);
		window.draw(Stone_ball.sprite);
		window.draw(enemy.sprite);
		window.display();
	}
	return 0;
}
