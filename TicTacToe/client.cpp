#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "TTT.h"

using namespace sf;

const int CELL_SIZE = 101;

int main()
{
    RenderWindow window(VideoMode(CELL_SIZE * 3, CELL_SIZE * 3), "Tic tac toe");
    bool pressed = false;

    TTT ttt(CELL_SIZE);
    if (ttt.connect("192.168.0.104", 9999) != Socket::Status::Done) {
        exit(-1);
    }

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::MouseButtonPressed) {
                if (event.key.code == Mouse::Left)
                    pressed = true;
            } else if (event.type == Event::MouseMoved && pressed) {
                pressed = false;
            } else if (event.type == Event::MouseButtonReleased && pressed) {
                if (event.key.code == Mouse::Left) {
                    ttt.mouseTyped(Mouse::getPosition(window));
                }
            }
        }

        window.clear(Color::White);
        window.draw(ttt);
        window.display();
    }

    return 0;
}