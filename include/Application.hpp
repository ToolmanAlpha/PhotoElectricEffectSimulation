#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "Defs.hpp"

// TODO: THINK
#include "linePlotter.hpp"
#include "ApplicationState.hpp"
#include "Input.hpp"
// namespaces
using namespace sf;
using namespace std;


class Application {
public:
    enum Modes { Edit, Simulate };
    
    Application() {

        
        lp::setDrawColor(FOREGROUND_COLOR);
        
        ContextSettings ctxSettings;
        ctxSettings.antialiasingLevel=MULTI_SAMPLE_DEPTH;
        
        m_Window = std::make_unique<RenderWindow>(
            VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),
            WINDOW_TITLE, WINDOW_STYLE, ctxSettings
        );

        // initialize application context information
        m_AppContext = std::make_shared<ApplicationContext>();
        if (!m_AppContext->uiFont.loadFromFile("res/fonts/" + string(DISPLAY_FONT))) {
            printf("Error loading font segoeui.ttf!\n");
        }

        m_AppContext->uiText.setFont(m_AppContext->uiFont);
        m_AppContext->uiText.setFillColor(FOREGROUND_COLOR);
        m_AppContext->uiText.setCharacterSize(32);
    
        
        m_Mode = Modes::Edit;
        InitState(m_Mode);
    }
   
    
    void Start() {
        bool isRunning = true;

        while (isRunning && !m_State->m_AppClose) {
            if (!m_Window->isOpen()) {
                isRunning = false; break;
            }

            Event event;
            while (m_Window->pollEvent(event))
                OnEvent(event);

            UpdateResources();

            float dt = m_AppClock.restart().asSeconds();
            OnUpdate(dt);
            OnRender();
        }
        m_Window->close();
    }

    ~Application() {
        
    }
private:
        using lp = LinePlotter;

private:
    void InitState(int mode) {
        switch (mode) {
            case Modes::Edit: m_State.reset(new EditorState()); break;
            case Modes::Simulate: m_State.reset(new SimulationState()); break;
            default: printf("Mode selection mismatch!\n"); break;
        }

        m_State->CollectResources(m_AppContext);
        m_State->OnEnter();
    }

    void UpdateResources() {
        m_AppContext->mousePos = 
        static_cast<v2f>(Mouse::getPosition(*m_Window));
    }

    void OnEvent(sf::Event e) {
        Input::update();

        if (e.type==Event::Closed)
            m_Window->close();

        Input::handleEvent(e);
        if (e.type == Event::KeyPressed) {
            if (e.key.code == Keyboard::E) {
                m_Mode = Modes::Edit;
                InitState(m_Mode);
            }
            else if (e.key.code == Keyboard::S) {
                m_Mode = Modes::Simulate;
                InitState(m_Mode);
            }
        }
        m_State->OnEvent(e);
    }

    void OnUpdate(float dt) {
        m_State->OnUpdate(dt);
    }

    void OnRender() {
        m_State->OnRender(*m_Window);
        m_Window->display();
    }


private:
    int m_Mode;
    unique_ptr<RenderWindow> m_Window;
    unique_ptr<ApplicationState> m_State;
    shared_ptr<ApplicationContext> m_AppContext;

    Clock m_AppClock;
};