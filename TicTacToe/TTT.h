#pragma once
#include <memory>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "Field.h"

using namespace sf;

class TTT : public Field
{
public:
    TTT(int size);
    ~TTT();

    void mouseTyped(Vector2i point);
    Socket::Status connect(IpAddress adress, unsigned short port);
protected:
    void draw(RenderTarget & target, RenderStates states) const override;
private:
    Font font;
    Text text;

    TcpSocket socket;
    bool canClick = false;

    //0 - plaing, 1 - won, -1 - lost
    char status = 0;
    std::unique_ptr<Thread> socketChecker;
};
