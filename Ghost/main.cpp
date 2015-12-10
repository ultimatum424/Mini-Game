#include "const.h"
 
void loadImage(struct structImages& image, String file)
{
	image.image.loadFromFile(file);
	image.texture.loadFromImage(image.image);
	image.sprite.setTexture(image.texture);
}
void InitializationMap(structImages& map_load, structMap& map)
{
	loadImage(map_load, "D:/”ÌË‚Â/»»œ Ë Ë„‡/Mini-Game/Ghost/map.png");
	map.sprite = map_load.sprite;
	map_load.sprite.setPosition(0, 0);
	map.long_map = 0;
}
void InitializationText(Font& font, Text& info)
{
	font.loadFromFile("D:/”ÌË‚Â/»»œ Ë Ë„‡/Mini-Game/Ghost/9447.otf");
	info.setFont(font);
	info.setCharacterSize(20);
	info.setColor(Color::Red);
}
int —reateBlockMap(int card_cage)
{
	int flag = 0;
	while (flag != 1)
	{
		int random_num = rand() % 3;
		if ((card_cage == 0) && ((random_num != -1) )) 
		{ 
			flag = 1; 
			return random_num;  
		}
		if ((card_cage == 1) && ((random_num != -1))) 
		{ 
			flag = 1; 
			return random_num;  
		}
		if ((card_cage == 2) && ((random_num != -1))) 
		{ 
			flag = 1; 
			return random_num; 
		}
		if (card_cage == -1) 
		{ 
			flag = 1; 
			return random_num; 
		}
	}
}
void CheckCollision(int& num_core, Sprite& player, structMap& map, int& out_score)
{
	int size_player_x = 50;
	int size_player_y = 14;
	int i = (-1 * (player.getPosition().y - 25))/ 100;
	out_score--;
	if ((player.getPosition().x == 0) && (map.mass_map[i] == 0)) { num_core++; }
	else if ((player.getPosition().x == 100) && (map.mass_map[i] == 1)) { num_core++; }
	else if ((player.getPosition().x == 200) && (map.mass_map[i] == 2)) { num_core++; }
	else { num_core--; }
}
void OutMenu(Text& info, RenderWindow& window)
{
	std::ostringstream start;
	start << "Press SPACE to START \n	  LEFT - left \n UP or DOWN - Centre \n  	RIGHT - Right";
	info.setString(start.str());
	info.setPosition(10, view.getCenter().y);
	window.draw(info);
}
void AddBlcokMap(structMap& map)
{
		map.mass_map[0] = map.mass_map[6];
		map.mass_map[1] = map.mass_map[7];
		map.mass_map[2] = map.mass_map[8];
		map.mass_map[3] = map.mass_map[9];

		for (int i = 4; i < map.long_map; i++)
		{
			if (i == 0) { map.mass_map[i] = —reateBlockMap(-1); }
			if (i == 1) { map.mass_map[i] = —reateBlockMap(map.mass_map[i - 1]); }
			if (i > 1) { map.mass_map[i] = —reateBlockMap(map.mass_map[i - 1]); }
		}
	
}
void ReturnGameOver(Text& info, int& num_score, RenderWindow& window)
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
void DrawMap(structMap& map, RenderWindow& window)
{
	for (int i = 0; i < map.long_map; i++)
	{
		map.sprite.setTextureRect((IntRect(0, (map.mass_map[i]) * 100, 300, 100)));
		map.sprite.setPosition(0, -(i * 100));
		window.draw(map.sprite);
	}
}
void ReturnInfo(Text& info, structImages& player, int& num_score, structImages& background)
{
	info.setString(((std::ostringstream&)(std::ostringstream() << num_score)).str());
	info.setPosition(10, player.sprite.getPosition().y + 250);
	player.sprite.setPosition(player.sprite.getPosition().x, view.getCenter().y - 70);
	background.sprite.setPosition(view.getCenter().x - 150, view.getCenter().y + 100);
}
void IventKeyboard(int& stage, int& out_time, int& num_score, structMap& map)
{
	if ((Keyboard::isKeyPressed(Keyboard::Escape) && ((stage == 1) || (stage == 2))))
	{
		stage = 0;
		out_time = OUT_TC;
		num_score = 0;
	}
	if ((Keyboard::isKeyPressed(Keyboard::LShift) && (stage == 2)))  stage = 0; 

	if ((Keyboard::isKeyPressed(Keyboard::Space) && (stage == 0)))
	{
		map.long_map = 10;
		stage = 1;
		for (int i = 0; i < map.long_map; i++)
		{
			map.mass_map[i] = -1;
		}
		for (int i = 0; i < map.long_map; i++)
		{
			if (i == 0) map.mass_map[i] = —reateBlockMap(-1);
			if (i == 1) map.mass_map[i] = —reateBlockMap( map.mass_map[i - 1]);
			if (i > 1) map.mass_map[i] = —reateBlockMap(map.mass_map[i - 1]);
		}
	}
}
void ControlPlayer(structImages& player)
{
	if ((Keyboard::isKeyPressed(Keyboard::Left)))  player.sprite.setPosition(0, view.getCenter().y - 70);
	if ((Keyboard::isKeyPressed(Keyboard::Right))) player.sprite.setPosition(200, view.getCenter().y - 70);
	if ((Keyboard::isKeyPressed(Keyboard::Down)) || (Keyboard::isKeyPressed(Keyboard::Up)))
	{
		player.sprite.setPosition(100, view.getCenter().y - 70);
	}
}
void DrawGame(RenderWindow& window, structImages player, structImages background, Text info)
{
	window.draw(player.sprite);
	window.draw(background.sprite);
	window.draw(info);
}

void Run_Game(RenderWindow& window)
{
	view.setSize(sf::Vector2f(WINDOW_X, WINDOW_Y));
	view.setCenter(WINDOW_X / 2, view.getSize().y - 300);
	InitializationMap(map_load, map);
	loadImage(player, "D:/”ÌË‚Â/»»œ Ë Ë„‡/Mini-Game/Ghost/1.png");
	player.sprite.setPosition(100, -50);
	loadImage(background, "D:/”ÌË‚Â/»»œ Ë Ë„‡/Mini-Game/Ghost/2.png");
	background.sprite.setPosition(0, 0);
	InitializationText(font, info);

	float CurrentFrame = 0;
	Clock clock;
	clock.restart();
	Vector2f f;
	srand(time(NULL));
	while (window.isOpen())
	{
		window.clear(sf::Color::White);

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 1000;

		sf::Event event;
		while (window.pollEvent(event))
		{
			IventKeyboard(stage, out_time, num_score, map);
			if (event.type == sf::Event::Closed)
				window.close();
		}
		ControlPlayer(player);
		if (out_time <= 0) stage = 2;
		if (stage == 0) OutMenu(info, window);
		if (stage == 1)		
		{
			if (view.getCenter().y < -600) AddBlcokMap(map);
			DrawMap(map, window);
			CheckCollision(num_score, player.sprite, map, out_time);
			ReturnInfo(info, player, num_score, background);
			DrawGame(window, player, background, info);
			window.setView(view);
			ViewMove(time, f);
		}
		if (stage == 2) ReturnGameOver(info, num_score, window);
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

