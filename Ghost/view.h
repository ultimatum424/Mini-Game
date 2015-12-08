#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

View view;
void ViewMove(float& time, Vector2f f)
{
	if (view.getCenter().y  < -600) {view.setCenter(150, -0);}
	view.move(0, -0.4*time);
	f = view.getCenter();
}