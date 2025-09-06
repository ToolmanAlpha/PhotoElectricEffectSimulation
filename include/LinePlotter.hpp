#pragma once

#include <SFML/Graphics.hpp>

#include "Defs.hpp"

// namespace
using namespace sf;
using namespace std;

class LinePlotter
{
public:

    static void beginShape() {
        s_Vertices.clear();
    }

    static void plot(const v2f& v) {
        s_Vertices.emplace_back(Vertex(v,s_Color));
    }

    static void display(RenderTarget& target,
        RenderStates states=RenderStates::Default) {
        target.draw(s_Vertices.data(), s_Vertices.size(),
        LineStrip, states);
    }

    static void setDrawColor(Color color) {
        s_Color = color;
    }


private:
    static vector<Vertex> s_Vertices;
    static Color s_Color;
};

vector<Vertex> LinePlotter::s_Vertices;
Color LinePlotter::s_Color;
