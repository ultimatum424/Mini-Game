#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <signal.h>
#include "view.h"

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
struct  structMap
{
	int mass_map[100];
	int long_map;
	Sprite sprite;
};

const int WINDOW_X = 300;
const int WINDOW_Y = 600;
const int OUT_TC = 100000;


structImages map_load;
structImages player;
structImages background;
structMap map;

Font font;
Text info;

int out_time = OUT_TC;
int num_score = 0;

int stage = 0;
