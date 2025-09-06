#pragma once

#include <SFML/Graphics.hpp>

#include "ApplicationContext.hpp"
#include "Input.hpp"
#include <iostream>

using namespace sf;

class Application;
class ApplicationState
{
public:
    ApplicationState() = default;
    virtual ~ApplicationState() {}

    void CollectResources(const shared_ptr<ApplicationContext>& res) {
        m_Resources = res;
    }

    virtual void OnEnter() = 0;
    virtual void OnRender(RenderTarget& target) const = 0;
    virtual void OnUpdate(float ts) = 0;
    virtual void OnEvent(Event event) = 0;
    virtual const char* name() const = 0;
    
    void CloseApplication() { m_AppClose = true; }
    // TODO: Work on this later
    // template <typename... Args>
    // void Log(const char* format, Args&&... args) {
    //     printf("[%s]: ", name());
    //     printf(format, args);
    // }

protected:
    shared_ptr<ApplicationContext> m_Resources;
private:
    bool m_AppClose = false;


    friend class Application;
};

class EditorState : public ApplicationState
{
public:
    using lp = LinePlotter;
    
    enum EditStates { Outline, Particles };
    enum RenderModes { };
    const char* name() const override { return "Editor"; }

    void OnEnter() override {
        // take user choices
        // take a few prompts from the user preferably

        // basic setup    
        m_PlotFrames.reserve(MAX_FRAME_CAPACITY);
        m_PlotFrames.push_back({});
        m_PlotPoints = m_PlotFrames.begin();
    }

    void OnRender(RenderTarget& target) const override {
        // On Render controls what part of the scene we ought to render
        // based on RenderModes

        // clear window
        target.clear(EDITOR_BACKGROUND_COLOR);
        target.draw(m_Resources->uiText);

        // live        
        if (m_PlotPoints->size()) {
            Vertex vertices[2] = {
                { m_Resources->mousePos, FOREGROUND_COLOR },
                { m_PlotPoints->back(), FOREGROUND_COLOR }
            };
            target.draw(vertices, 2, Lines);
        }


        for (const auto& plotPoints : m_PlotFrames) {
            lp::beginShape();
            for (const auto& p : plotPoints) {
                lp::plot(p);
            }
            lp::display(target);
        }
    }

    void OnUpdate(float ts) override {
        // On Update is the zen state of all, the flow of the application
        
        // text rendering
        auto mp = m_Resources->mousePos;

        m_Resources->uiText.setPosition(mp);

        char info[50];

        if (m_PrintNormalizedCoords)
            sprintf(info, "(%.2f,%.2f)", mp.x/static_cast<float>(WINDOW_WIDTH), mp.y/static_cast<float>(WINDOW_HEIGHT));
        else
            sprintf(info, "(%.2f,%.2f)", mp.x, mp.y);
        m_Resources->uiText.setString(string(info));
    }

    void OnEvent(Event e) override {
        // On Event is how we interact with the editor as a client / user
        if (e.type == Event::KeyPressed) {
            if (e.key.code == Keyboard::N)
                m_PrintNormalizedCoords = !m_PrintNormalizedCoords;
            else if (e.key.code == Keyboard::I && !m_PlotPoints->empty()) {
                m_PlotFrames.push_back({});
                m_PlotPoints++;
            }
        }
        
        if (e.type==Event::MouseButtonPressed) {
            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (!Input::isHeld(Keyboard::C))
                    m_PlotPoints->push_back(m_Resources->mousePos);
                else if (m_PlotPoints->size() >= 2)
                    m_PlotPoints->push_back((*m_PlotPoints)[0]);
            }
        }
    }

private:
    bool m_PrintNormalizedCoords = false;

    vector<vector<v2f>>::iterator m_PlotPoints;
    vector<vector<v2f>> m_PlotFrames;
};

class SimulationState : public ApplicationState
{
public:
const char* name() const override { return "Editor"; }

    void OnEnter() override {
        
    }

    void OnRender(RenderTarget& target) const override {
       
    }

    void OnUpdate(float ts) override {
        
    }

    void OnEvent(Event e) override {
    
    }

private:
};