#pragma once
#include <SFML/Graphics.hpp>
#include "map.h"
using namespace sf;
View view;
View PlayerView(float x, float y) {
	view.setCenter(x, y);
	return view;
}