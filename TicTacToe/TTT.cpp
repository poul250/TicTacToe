#include "TTT.h"

TTT::TTT(int size)
    : Field(size)
{
    socketChecker = std::make_unique<Thread>([&]() {
        bool running = true;
        while (running) {
            char msg = 0;
            char newCells[9] = { 0 };
            std::size_t received;

            socket.receive(newCells, 9, received);
            for (char i = 0; i < 9; ++i) {
                cells[i] = newCells[i];
            }
            socket.receive(&msg, 1, received);

            switch (msg) {
            case 0:
                canClick = true;
                break;
            case 1:
                socket.receive(&status, 1, received);
                running = false;
                if (status == 0) {
                    text.setString("DRAW");
                    text.setFillColor(Color::Blue);
                } else if (status == 1) {
                    text.setString("YOU WIN");
                    text.setFillColor(Color::Green);
                } else if (status == -1) {
                    text.setString("YOU LOST");
                    text.setFillColor(Color::Red);
                }

                break;
            }
        }

    });
    if (!font.loadFromFile("res\\font.ttf")) {
        while (true);
        exit(-2);
    }
    text.setFont(font);
    text.setCharacterSize(30);
    text.setPosition(Vector2f(50, 50));
    text.setString("");
}

TTT::~TTT()
{
}

void TTT::mouseTyped(Vector2i point)
{
    int cell = getCellNumber(point);
    if (canClick) {
        canClick = false;
        cells[cell] = PLAYER;
        socket.send(&cell, 1);
    }
}

Socket::Status TTT::connect(IpAddress adress, unsigned short port)
{
    auto status = socket.connect(adress, port);
    if (status == Socket::Status::Done)
        socketChecker->launch();
    return status;
}

void TTT::draw(RenderTarget & target, RenderStates states) const
{
    Field::draw(target, states);
    target.draw(text, states);
}
