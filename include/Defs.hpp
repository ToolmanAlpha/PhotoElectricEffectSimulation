#pragma once

#include <SFML/Graphics.hpp>
// type aliases
typedef sf::Vector2f v2f;
typedef sf::Vector2i v2i;
typedef sf::Vector2u v2u;

// constants
const sf::Color BACKGROUND_COLOR = sf::Color(  0,   0,   0,   0);
const sf::Color EDITOR_BACKGROUND_COLOR = sf::Color(  0,   0,   0,   0);
const sf::Color FOREGROUND_COLOR = sf::Color(255, 255, 255, 255); 

// window properties
const int MULTI_SAMPLE_DEPTH=4;
const int WINDOW_WIDTH=640;
const int WINDOW_HEIGHT=360;
const int WINDOW_STYLE=sf::Style::Default & ~sf::Style::Resize;

const char WINDOW_TITLE[]="PhotoElectricEffectSimulation";

const char DISPLAY_FONT[] = "segoeui.ttf";

// very crucial, do not tamper with
const int MAX_FRAME_CAPACITY=50;

const char EDITOR_REGISTRY_PATH[] = "res/registry/outline.dat";