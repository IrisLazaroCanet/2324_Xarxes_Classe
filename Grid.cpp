#include "Grid.h"

Grid::Grid()
{
    _pieceSelected = [this](Cell* c) {
        std::vector<vector2> locations = c->getPiece()->GetMoveOptions(this, c->pos);

        for (int i = 0; i < locations.size(); i++)
        {
            this->cells[locations[i].x][locations[i].y]->setOnclick(_pieceMoved);
        }

        if (c->getPiece()->type == KING)
        {
            if (this->cells[c->pos.y][c->pos.x + 1]->getPiece() == nullptr &&
                this->cells[c->pos.y][c->pos.x + 2]->getPiece() == nullptr &&
                King(c->getPiece()).moved == false &&
                Tower(this->cells[c->pos.y][c->pos.x + 3]->getPiece()).moved == false)
            {
                this->cells[c->pos.y][c->pos.x + 2]->setOnclick(_castle);
            }
            else if (this->cells[c->pos.y][c->pos.x - 1]->getPiece() == nullptr &&
                this->cells[c->pos.y][c->pos.x - 2]->getPiece() == nullptr &&
                this->cells[c->pos.y][c->pos.x - 3]->getPiece() == nullptr &&
                King(c->getPiece()).moved == false &&
                Tower(this->cells[c->pos.y][c->pos.x - 4]->getPiece()).moved == false)
            {
                this->cells[c->pos.y][c->pos.x -3]->setOnclick(_castle);
            }
        }
        else if (c->getPiece()->type == PAWN)
        {
            if (c->pos.y == 1 && c->getPiece()->isWhite == true)
            {
                this->cells[0][c->pos.x]->setOnclick(_promotion);
            }
            else if (c->pos.y == 6 && c->getPiece()->isWhite == false)
            {
                this->cells[7][c->pos.x]->setOnclick(_promotion);
            }
        }
    };

    _unSelectPiece = [this](Cell* c) {
        
    };

    _pieceMoved = [this](Cell* c) {
        
    };

    _promotion = [this](Cell* c) {
        
    };

    _castle = [this](Cell* c) {
        
    };


    //Inicialitzar cel·les buides
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            vector2 pos;
            pos.x = j;
            pos.y = i;
            cells[i][j] = new Cell(pos);
        }
    }

    Piece* newPiece;
    Button* bt;
    vector2 newPos;

    //Peces negres

#pragma region BlackPawns
    for (int i = 0; i < 8; i++)
    {
        newPos.x = i;
        newPos.y = 1;

        newPiece = new Pawn(false);

        bt = new Button(50, 20, newPiece->spritepath);
        bt->onClick = _pieceSelected;

        cells[1][i] = new Cell(newPiece, bt, newPos);
    }
#pragma endregion
    
    newPos.y = 0;

#pragma region BlackTowers
    newPiece = new Tower(false);

    bt = new Button(50, 20, newPiece->spritepath);
    bt->onClick = _pieceSelected;

    newPos.x = 0;

    cells[newPos.y][newPos.x] = new Cell(newPiece, bt, newPos);
    newPos.x = 7;
    cells[newPos.y][newPos.x] = new Cell(newPiece, bt, newPos);

#pragma endregion

#pragma region BlackKnights
    newPiece = new Knight(false);

    bt = new Button(50, 20, newPiece->spritepath);
    bt->onClick = _pieceSelected;

    newPos.x = 1;

    cells[newPos.y][newPos.x] = new Cell(newPiece, bt, newPos);
    newPos.x = 6;
    cells[newPos.y][newPos.x] = new Cell(newPiece, bt, newPos);

#pragma endregion

#pragma region BlackBishops
    newPiece = new Bishop(false);

    bt = new Button(50, 20, newPiece->spritepath);
    bt->onClick = _pieceSelected;

    newPos.x = 2;

    cells[newPos.y][newPos.x] = new Cell(newPiece, bt, newPos);
    newPos.x = 5;
    cells[newPos.y][newPos.x] = new Cell(newPiece, bt, newPos);

#pragma endregion

#pragma region BlackQueen
    newPiece = new Queen(false);

    bt = new Button(50, 20, newPiece->spritepath);
    bt->onClick = _pieceSelected;

    newPos.x = 3;

    cells[newPos.y][newPos.x] = new Cell(newPiece, bt, newPos);

#pragma endregion

#pragma region BlackKing
    newPiece = new Queen(false);

    bt = new Button(50, 20, newPiece->spritepath);
    bt->onClick = _pieceSelected;

    newPos.x = 4;

    cells[newPos.y][newPos.x] = new Cell(newPiece, bt, newPos);

#pragma endregion

    //Peces blanques

#pragma region WhitePawns
    for (int i = 0; i < 8; i++)
    {
        vector2 pos;
        pos.x = i;
        pos.y = 6;

        Piece* newPawn = new Pawn(true);

        Button* bt = new Button(50, 20, newPawn->spritepath);
        bt->onClick = _pieceSelected;

        cells[6][i] = new Cell(newPawn, bt, pos);
    }
#pragma endregion

    newPos.y = 7;

#pragma region WhiteTowers
    newPiece = new Tower(true);

    bt = new Button(50, 20, newPiece->spritepath);
    bt->onClick = _pieceSelected;

    newPos.x = 0;

    cells[newPos.y][newPos.x] = new Cell(newPiece, bt, newPos);
    newPos.x = 7;
    cells[newPos.y][newPos.x] = new Cell(newPiece, bt, newPos);

#pragma endregion

#pragma region WhiteKnights
    newPiece = new Knight(true);

    bt = new Button(50, 20, newPiece->spritepath);
    bt->onClick = _pieceSelected;

    newPos.x = 1;

    cells[newPos.y][newPos.x] = new Cell(newPiece, bt, newPos);
    newPos.x = 6;
    cells[newPos.y][newPos.x] = new Cell(newPiece, bt, newPos);

#pragma endregion

#pragma region WhiteBishops
    newPiece = new Bishop(true);

    bt = new Button(50, 20, newPiece->spritepath);
    bt->onClick = _pieceSelected;

    newPos.x = 2;

    cells[newPos.y][newPos.x] = new Cell(newPiece, bt, newPos);
    newPos.x = 5;
    cells[newPos.y][newPos.x] = new Cell(newPiece, bt, newPos);

#pragma endregion

#pragma region WhiteQueen
    newPiece = new Queen(true);

    bt = new Button(50, 20, newPiece->spritepath);
    bt->onClick = _pieceSelected;

    newPos.x = 3;

    cells[newPos.y][newPos.x] = new Cell(newPiece, bt, newPos);

#pragma endregion

#pragma region WhiteKing
    newPiece = new Queen(true);

    bt = new Button(50, 20, newPiece->spritepath);
    bt->onClick = _pieceSelected;

    newPos.x = 4;

    cells[newPos.y][newPos.x] = new Cell(newPiece, bt, newPos);

#pragma endregion


}

Grid::~Grid()
{
}
