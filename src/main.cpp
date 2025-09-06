// #include <SFML/Graphics.hpp>
// #include <bits/stdc++.h>

// // #include "Application.hpp"
// #include "Defs.hpp"
// #include "LinePlotter.hpp"

// int main()
// {
//     using lp = LinePlotter;
//     lp::setDrawColor(FOREGROUND_COLOR);

//     ContextSettings ctxSettings;
//     ctxSettings.antialiasingLevel=MULTI_SAMPLE_DEPTH;

//     RenderWindow window(VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),
//     WINDOW_TITLE, WINDOW_STYLE, ctxSettings);

//     Font font;
//     if (!font.loadFromFile("res/fonts/" + string(DISPLAY_FONT))) {
//         printf("Error loading font segoeui.ttf!\n");
//         return -1;
//     }
//     Text t;
//     t.setFont(font);
//     t.setFillColor(FOREGROUND_COLOR);
//     t.setCharacterSize(32);

//     float mouseX, mouseY;
//     std::vector<vector<v2f>> plotFrames;
//     plotFrames.reserve(MAX_FRAME_CAPACITY);
//     plotFrames.push_back({});
//     auto plotPoints = plotFrames.begin();

//     bool printNormalizedCoords=false;
//     while (window.isOpen()) {
//         Event e;
//         while (window.pollEvent(e)) {
//             if (e.type==Event::Closed)
//                 window.close();
            
//             if (e.type==Event::MouseButtonPressed) {
//                 if (Mouse::isButtonPressed(Mouse::Left))
//                     plotPoints->push_back(v2f(mouseX, mouseY));
//                 if (Mouse::isButtonPressed(Mouse::Right))
//                     printNormalizedCoords=true;
//             }
//             else if (e.type == Event::KeyPressed) {
//                 if (Keyboard::isKeyPressed(Keyboard::I)
//                 && !plotPoints->empty()) {
//                     plotFrames.push_back({});
//                     plotPoints++;
//                 }
//             }
//         }
        
//         window.clear();
        
//         mouseX=Mouse::getPosition(window).x;
//         mouseY=Mouse::getPosition(window).y;


//         // text rendering
//         t.setPosition({ mouseX, mouseY });

//         char info[50];

//         if (printNormalizedCoords)
//             sprintf(info, "(%.2f,%.2f)", mouseX/static_cast<float>(WINDOW_WIDTH), mouseY/static_cast<float>(WINDOW_HEIGHT));
//         else
//             sprintf(info, "(%.2f,%.2f)", mouseX, mouseY);
//         t.setString(string(info));

//         // drawing
//         // live
        
//         if (plotPoints->size()) {
//             Vertex vertices[2] = {
//                 { v2f(mouseX, mouseY), FOREGROUND_COLOR },
//                 { plotPoints->back(), FOREGROUND_COLOR }
//             };
//             window.draw(vertices, 2, Lines);
//         }

//         window.draw(t);

//         for (const auto& plotPoints : plotFrames) {
//             lp::beginShape();
//             for (const auto& p : plotPoints) {
//                 lp::plot(p);
//             }
//             lp::endShape();
//             lp::display(window);
//         }

//         window.display();
//     }

//     // write to a file
//     FILE* fp=fopen("res/registry/outline.dat", "w");

//     for (const auto& plotPoints : plotFrames) {
//         for (auto p : plotPoints) {
//             p.x /= static_cast<float>(WINDOW_WIDTH);
//             p.y /= static_cast<float>(WINDOW_HEIGHT);
//             fprintf(fp, "%.2f\t%.2f\n", p.x, p.y);
//         }
//         fprintf(fp, "\n");
//     }
//     fclose(fp);

//     return 0;
// }

#include "Application.hpp"

int main() {
    Application app;
    app.Start();
    return 0;
}