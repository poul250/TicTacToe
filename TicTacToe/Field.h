#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;

enum Cell
{
    EMPTY = 0,
    PLAYER = 1,
    ENEMY = -1
};

enum Player
{
    ZERO, 
    CROSS
};

class Field : public Drawable
{
public:
    Field(int size);
    virtual ~Field();

    void reset();
    int getCellNumber(Vector2i point);
    void setCells(const char * cells);
    const char * getCells() const;
protected:
    virtual void draw(RenderTarget & target, RenderStates states) const override;
    char cells[9];
private:
    void drawCross(RenderTarget & target, Vector2f point) const;
    void drawZero(RenderTarget & target, Vector2f point) const;
    void drawSym(RenderTarget & target, Vector2f point, Player player) const;

    int size;

    Player player;
    Player enemy;
    VertexArray lines;
    VertexArray cross;
    CircleShape circle;
};
