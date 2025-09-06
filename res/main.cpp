#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "Application.hpp"
// namespaces
using namespace sf;
using namespace std;

// type aliases
typedef Vector2f v2f;
typedef Vector2i v2i;
typedef Vector2u v2u;

class LinePlotter
{
public:

    static void beginShape() {
        s_Vertices.clear();
    }

    static void endShape(bool close = false) {
        if (close) 
            s_Vertices.push_back(*s_Vertices.begin());
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

// constants
const Color BACKGROUND_COLOR = Color(  0,   0,   0,   0);
const Color FOREGROUND_COLOR = Color(255, 255, 255, 255); 

// window properties
const int MULTI_SAMPLE_DEPTH=4;
const int WINDOW_WIDTH=640;
const int WINDOW_HEIGHT=360;
const int WINDOW_STYLE=Style::Default & ~Style::Resize;

const char WINDOW_TITLE[]="PhotoElectricEffectSimulation";

const char DISPLAY_FONT[] = "segoeui.ttf";

// very crucial, do not tamper with
const int MAX_FRAME_CAPACITY=50;

int main()
{
    using lp = LinePlotter;
    lp::setDrawColor(FOREGROUND_COLOR);

    ContextSettings ctxSettings;
    ctxSettings.antialiasingLevel=MULTI_SAMPLE_DEPTH;

    RenderWindow window(VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),
    WINDOW_TITLE, WINDOW_STYLE, ctxSettings);

    Font font;
    if (!font.loadFromFile("res/fonts/" + string(DISPLAY_FONT))) {
        printf("Error loading font segoeui.ttf!\n");
        return -1;
    }
    Text t;
    t.setFont(font);
    t.setFillColor(FOREGROUND_COLOR);
    t.setCharacterSize(32);

    float mouseX, mouseY;
    std::vector<vector<v2f>> plotFrames;
    plotFrames.reserve(MAX_FRAME_CAPACITY);
    plotFrames.push_back({});
    auto plotPoints = plotFrames.begin();

    bool printNormalizedCoords=false;
    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type==Event::Closed)
                window.close();
            
            if (e.type==Event::MouseButtonPressed) {
                if (Mouse::isButtonPressed(Mouse::Left))
                    plotPoints->push_back(v2f(mouseX, mouseY));
                if (Mouse::isButtonPressed(Mouse::Right))
                    printNormalizedCoords=true;
            }
            else if (e.type == Event::KeyPressed) {
                if (Keyboard::isKeyPressed(Keyboard::I)
                && !plotPoints->empty()) {
                    plotFrames.push_back({});
                    plotPoints++;
                }
            }
        }
        
        window.clear();
        
        mouseX=Mouse::getPosition(window).x;
        mouseY=Mouse::getPosition(window).y;


        // text rendering
        t.setPosition({ mouseX, mouseY });

        char info[50];

        if (printNormalizedCoords)
            sprintf(info, "(%.2f,%.2f)", mouseX/static_cast<float>(WINDOW_WIDTH), mouseY/static_cast<float>(WINDOW_HEIGHT));
        else
            sprintf(info, "(%.2f,%.2f)", mouseX, mouseY);
        t.setString(string(info));

        // drawing
        // live
        
        if (plotPoints->size()) {
            Vertex vertices[2] = {
                { v2f(mouseX, mouseY), FOREGROUND_COLOR },
                { plotPoints->back(), FOREGROUND_COLOR }
            };
            window.draw(vertices, 2, Lines);
        }

        window.draw(t);

        for (const auto& plotPoints : plotFrames) {
            lp::beginShape();
            for (const auto& p : plotPoints) {
                lp::plot(p);
            }
            lp::endShape();
            lp::display(window);
        }

        window.display();
    }

    // write to a file
    FILE* fp=fopen("figure_outline.dat", "w");

    for (const auto& plotPoints : plotFrames) {
        for (auto p : plotPoints) {
            p.x /= static_cast<float>(WINDOW_WIDTH);
            p.y /= static_cast<float>(WINDOW_HEIGHT);
            fprintf(fp, "%.2f\t%.2f\n", p.x, p.y);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

    return 0;
}