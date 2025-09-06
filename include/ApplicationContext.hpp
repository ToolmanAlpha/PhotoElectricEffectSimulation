#pragma once

#include <SFML/Graphics.hpp>
#include "Defs.hpp"

using namespace sf;

struct ApplicationContext {
    Font uiFont;
    Text uiText;

    // plotting information
    FILE* fwrite;
    FILE* fread;

    // mouse info, updated by the application itself
    v2f mousePos;
};