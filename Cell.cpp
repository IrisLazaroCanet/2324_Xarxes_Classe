#include "Cell.h"

Cell::Cell(vector2 position)
{
    _piece = nullptr;
    _button = nullptr;
    pos = position;
    
}

Cell::Cell(Piece* p, Button* b, vector2 position)
{
    _piece = p;
    _button = b;
    pos = position;
}

Cell::~Cell()
{
    delete _piece;
    delete _button;
}

bool Cell::hasPiece()
{
    return _piece != nullptr;
}

Piece* Cell::getPiece()
{
    return _piece;
}

OnClick Cell::getOnclick()
{
    return _button->onClick;
}

void Cell::setOnclick(OnClick function)
{
    _button->onClick = function;
}
