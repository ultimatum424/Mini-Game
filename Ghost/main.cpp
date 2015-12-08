#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <signal.h>
#include "view.h"
#include "const.h"
 
using namespace sf;
struct structImages
{
	Image image;
	String file;
	Texture texture;
	Sprite sprite;
	int pos_x;
	int pos_y;
};
struct heroes
{
	Sprite sprite;
	Vector2f heroesPosition;
	int hp;
	int max_hp;
	float damage;
	float def;
	int position;
	Sprite icon;
};
void loadImage(struct structImages& image, String file)
{
	image.image.loadFromFile(file);
	image.texture.loadFromImage(image.image);
	image.sprite.setTexture(image.texture);
}
int map_creat(int mum_1)
{
	int flag = 0;
	while (flag != 1)
	{
		int random_num = rand() % 3;
		if ((mum_1 == 0) && ((random_num != -1) )) { flag = 1; return random_num;  }
		if ((mum_1 == 1) && ((random_num != -1))) { flag = 1; return random_num;  }
		if ((mum_1 == 2) && ((random_num != -1))) { flag = 1; return random_num; }
		if (mum_1 == -1) { flag = 1; return random_num; }
	}
}
void collision_check(int& num_core, Sprite& player, int map[100], int& j)
{
	int size_player_x = 50;
	int size_player_y = 14;
	int i = (-1 * (player.getPosition().y - 25))/ 100;
	j--;
	if ((player.getPosition().x == 0) && (map[i] == 0)) { num_core++; }
	else if ((player.getPosition().x == 100) && (map[i] == 1)) { num_core++; }
	else if ((player.getPosition().x == 200) && (map[i] == 2)) { num_core++; }
	else { num_core--; }
}
void Stage0(Text& info, RenderWindow& window)
{
	std::ostringstream start;
	start << "Press SPACE to START \n	  LEFT - left \n UP or DOWN - Centre \n  	RIGHT - Right";
	info.setString(start.str());
	info.setPosition(10, view.getCenter().y);
	window.draw(info);
}
void Stage1(int mass_map[100],int long_map)
{
		mass_map[0] = mass_map[6];
		mass_map[1] = mass_map[7];
		mass_map[2] = mass_map[8];
		mass_map[3] = mass_map[9];

		for (int i = 4; i < long_map; i++)
		{
			if (i == 0) { mass_map[i] = map_creat(-1); }
			if (i == 1) { mass_map[i] = map_creat(mass_map[i - 1]); }
			if (i > 1) { mass_map[i] = map_creat(mass_map[i - 1]); }
		}
	
}
void Stage2(Text& info, int& num_score, RenderWindow& window)
{
	std::ostringstream out;
	out << "Press ESC \n Game Over \n your Score \n";
	info.setString(out.str());
	info.setPosition(10, view.getCenter().y - 100);
	window.draw(info);
	info.setString(((std::ostringstream&)(std::ostringstream() << num_score)).str());
	info.setPosition(10, view.getCenter().y);
	window.draw(info);
}
void DrawMap(int long_map, int mass_map[100], structImages& map_load, RenderWindow& window)
{
	for (int i = 0; i < long_map; i++)
	{
		map_load.sprite.setTextureRect((IntRect(0, (mass_map[i]) * 100, 300, 100)));
		map_load.sprite.setPosition(0, -(i * 100));
		window.draw(map_load.sprite);
	}
}
void DrawInfo(Text& info, structImages& player, int& num_score, structImages& block)
{
	info.setString(((std::ostringstream&)(std::ostringstream() << num_score)).str());
	info.setPosition(10, player.sprite.getPosition().y + 250);
	player.sprite.setPosition(player.sprite.getPosition().x, view.getCenter().y - 70);
	block.sprite.setPosition(view.getCenter().x - 150, view.getCenter().y + 100);
}
void IventKeyboard(int& stage, int& out_time, int& num_score, int& long_map, int mass_map[100])
{
	if ((Keyboard::isKeyPressed(Keyboard::Escape) && ((stage == 1) || (stage == 2))))
	{
		stage = 0;
		out_time = OUT_TC;
		num_score = 0;
	}
	if ((Keyboard::isKeyPressed(Keyboard::LShift) && (stage == 2))) { stage = 0; }

	if ((Keyboard::isKeyPressed(Keyboard::Space) && (stage == 0)))
	{
		long_map = 10;
		stage = 1;
		for (int i = 0; i < long_map; i++) { mass_map[i] = -1; }
		for (int i = 0; i < long_map; i++)
		{
			if (i == 0) { mass_map[i] = map_creat(-1); }
			if (i == 1) { mass_map[i] = map_creat(mass_map[i - 1]); }
			if (i > 1) { mass_map[i] = map_creat(mass_map[i - 1]); }
		}
	}
}
void Run_Game(RenderWindow& window)
{
	structImages map_load;
	structImages player;
	structImages block;

	view.setSize(sf::Vector2f(WINDOW_X, WINDOW_Y));
	view.setCenter(WINDOW_X / 2, view.getSize().y - 300);

	loadImage(map_load, "D:/Универ/ИИП и игра/Mini-Game/Ghost/map.png");
	map_load.sprite.setPosition(0, 0);
	loadImage(player, "D:/Универ/ИИП и игра/Mini-Game/Ghost/1.png");
	loadImage(block, "D:/Универ/ИИП и игра/Mini-Game/Ghost/2.png");
	block.sprite.setPosition(0, 0);
	Font font;
	font.loadFromFile("D:/Универ/ИИП и игра/Mini-Game/Ghost/9447.otf");
	Text info("", font, 20);
	info.setColor(Color::Red);
	int out_time = OUT_TC;
	int num_score = 0;
	float CurrentFrame = 0;
	Clock clock;
	clock.restart();
	Vector2f f;
	int long_map;
	srand(time(NULL));
	int mass_map[100];
	int stage = 0;
	player.sprite.setPosition(100, -50);

	while (window.isOpen())
	{
		window.clear(sf::Color::White);
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 1000;
		sf::Event event;

		while (window.pollEvent(event))
		{
			IventKeyboard(stage, out_time, num_score, long_map, mass_map);
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if ((Keyboard::isKeyPressed(Keyboard::Left)))  player.sprite.setPosition(0, view.getCenter().y - 70); 
		if ((Keyboard::isKeyPressed(Keyboard::Right))) player.sprite.setPosition(200, view.getCenter().y - 70); 
		if (out_time <= 0) { stage = 2; }
		if ((Keyboard::isKeyPressed(Keyboard::Down)) || (Keyboard::isKeyPressed(Keyboard::Up)))
		{ 
			player.sprite.setPosition(100, view.getCenter().y - 70); 
		}

		if (stage == 0) Stage0(info, window);

		if (stage == 1)		
		{
			if (view.getCenter().y < -600) Stage1(mass_map, long_map);
			DrawMap(long_map, mass_map, map_load, window);
			collision_check(num_score, player.sprite, mass_map, out_time);
			DrawInfo(info, player, num_score, block);
			window.draw(player.sprite);
			window.draw(block.sprite);
			window.draw(info);
			window.setView(view);
			ViewMove(time, f);
		}
		if (stage == 2) Stage2(info, num_score, window);
		window.display();
	}
}

int main()
{
	setlocale(LC_CTYPE, "rus");
	sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Mini Game");
	Run_Game(window);
	return 0;
}

