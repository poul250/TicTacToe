#include "Field.h"

Field::Field(int size)
    : size(size)
    , lines(Lines)
    , cross(Lines)
    , circle(float(size) / 2 - 1)
    , player(CROSS)
    , enemy(ZERO)
{
    lines.append(Vertex(Vector2f(1 * size, 0 * size), Color::Black));
    lines.append(Vertex(Vector2f(1 * size, 3 * size), Color::Black));
    lines.append(Vertex(Vector2f(2 * size, 0 * size), Color::Black));
    lines.append(Vertex(Vector2f(2 * size, 3 * size), Color::Black));
    lines.append(Vertex(Vector2f(0 * size, 1 * size), Color::Black));
    lines.append(Vertex(Vector2f(3 * size, 1 * size), Color::Black));
    lines.append(Vertex(Vector2f(0 * size, 2 * size), Color::Black));
    lines.append(Vertex(Vector2f(3 * size, 2 * size), Color::Black));

    cross.append(Vertex(Vector2f(0,    0   ), Color::Blue));
    cross.append(Vertex(Vector2f(size, size), Color::Blue));
    cross.append(Vertex(Vector2f(size, 0   ), Color::Blue));
    cross.append(Vertex(Vector2f(0,    size), Color::Blue));

    reset();

    circle.setFillColor(Color(0, 0, 0, 0));
    circle.setOutlineColor(Color::Red);
    circle.setOutlineThickness(1);
}

Field::~Field()
{}

void Field::reset()
{
    for (int i = 0; i < 9; ++i) {
        cells[i] = EMPTY;
    }
}

int Field::getCellNumber(Vector2i point)
{
    int x = point.x / size;
    int y = point.y / size;
    return y * 3 + x;
}

void Field::setCells(const char * cells)
{
    for (int i = 0; i < 9; ++i) {
        this->cells[i] = cells[i];
    }
}

const char * Field::getCells() const
{
    return cells;
}

void Field::draw(RenderTarget & target, RenderStates states) const
{
    target.draw(lines, states);
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (cells[i * 3 + j] == PLAYER)
                drawSym(target, Vector2f(size * j, size * i), player);
            else if (cells[i * 3 + j] == ENEMY)
                drawSym(target, Vector2f(size * j, size * i), enemy);
        }
    }
}

void Field::drawCross(RenderTarget & target, Vector2f point) const
{
    RenderStates states;
    states.transform = Transform().translate(point);
    target.draw(cross, states);
}

void Field::drawZero(RenderTarget & target, Vector2f point) const
{
    RenderStates states;
    states.transform = Transform().translate(point + Vector2f(1.f, 1.f));
    target.draw(circle, states);
}

void Field::drawSym(RenderTarget & target, Vector2f point, Player player) const
{
    if (player == ZERO) {
        drawZero(target, point);
    } else if (player == CROSS) {
        drawCross(target, point);
    }
}
