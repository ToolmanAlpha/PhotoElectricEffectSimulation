#pragma once

#include <SFML/Window.hpp>
#include <map>

class Input {
public:
    static void update() {
        for (auto& [key, state] : keys) {
            state.justPressed = false;
            state.justReleased = false;
        }
    }

    static void handleEvent(const sf::Event& event) {
        if (event.type == sf::Event::KeyPressed) {
            auto& state = keys[event.key.code];
            if (!state.held) state.justPressed = true;
            state.held = true;
        }
        else if (event.type == sf::Event::KeyReleased) {
            auto& state = keys[event.key.code];
            state.held = false;
            state.justReleased = true;
        }
    }

    static bool isHeld(sf::Keyboard::Key key) {
        return keys[key].held;
    }

    static bool isJustPressed(sf::Keyboard::Key key) {
        return keys[key].justPressed;
    }

    static bool isJustReleased(sf::Keyboard::Key key) {
        return keys[key].justReleased;
    }

private:
    struct KeyState {
        bool held = false;
        bool justPressed = false;
        bool justReleased = false;
    };
    static inline std::map<sf::Keyboard::Key, KeyState> keys;
};
