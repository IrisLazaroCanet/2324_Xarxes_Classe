#include "Grid.h"

Grid::Grid()
{
    _pieceSelected = [this](vector2* p, vector2* p2) {
        std::vector<vector2> locations = this->GetMoveOptions(p);

        for (int i = 0; i < locations.size(); i++)
        {
            if (locations[i].x >= 0 &&
                locations[i].x <= 7 &&
                locations[i].y >= 0 &&
                locations[i].x <= 7)
            {
                //Falten els botons en vermell
                this->cells[locations[i].y][locations[i].x]->setOnclick(_pieceMoved);
            }
        }


        //Castle case
        if (this->cells[p->y][p->x]->getPiece()->type == KING)
        {
            if (this->cells[p->y][p->x + 1]->getPiece() == nullptr &&
                this->cells[p->y][p->x + 2]->getPiece() == nullptr &&
                static_cast<King*>(this->cells[p->y][p->x]->getPiece())->moved == false &&
                static_cast<Tower*>(this->cells[p->y][p->x]->getPiece())->moved == false)
            {
                //Falten els botons en vermell
                this->cells[p->y][p->x + 2]->setOnclick(_castle);
            }
            else if (this->cells[p->y][p->x - 1]->getPiece() == nullptr &&
                this->cells[p->y][p->x - 2]->getPiece() == nullptr &&
                this->cells[p->y][p->x - 3]->getPiece() == nullptr &&
                static_cast<King*>(this->cells[p->y][p->x]->getPiece())->moved == false &&
                static_cast<Tower*>(this->cells[p->y][p->x]->getPiece())->moved == false)
            {
                //Falten els botons en vermell
                this->cells[p->y][p->x -3]->setOnclick(_castle);
            }
        }

        //Promotion case
        else if (this->cells[p->y][p->x]->getPiece()->type == PAWN)
        {
            if (p->y== 1 && this->cells[p->y][p->x]->getPiece()->isWhite == true)
            {
                //Falten els botons en vermell
                this->cells[0][p->x]->setOnclick(_promotion);
            }
            else if (p->y == 6 && this->cells[p->y][p->x]->getPiece()->isWhite == false)
            {
                //Falten els botons en vermell
                this->cells[7][p->x]->setOnclick(_promotion);
            }
        }


        this->cells[p->y][p->x]->setOnclick(_unSelectPiece);
    };

    _unSelectPiece = [this](vector2* p, vector2* p2) {

        this->DeselectPiece(p);

        this->cells[p->y][p->x]->setOnclick(_pieceSelected); 
    };

    _pieceMoved = [this](vector2* p, vector2* p2) {
        this->DeselectPiece(p);
        this->MovePiece(p, p2);
    };

    _promotion = [this](vector2* p, vector2* p2) {

        
    };

    _castle = [this](vector2* p, vector2* p2) {

        this->DeselectPiece(p);

        vector2 newPos = *p;
        //Long
        if (this->cells[p2->y][p2->x]->pos.x == 0)
        {
            //Move King
            newPos.x = p->x - 3;
            this->MovePiece(p, &newPos);
            //Move Tower
            newPos.x = p2->x + 2;
            this->MovePiece(p2, &newPos);
        }
        //Short
        else
        {
            //Move King
            newPos.x = p->x + 2;
            this->MovePiece(p, &newPos);
            //Move Tower
            newPos.x = p2->x - 2;
            this->MovePiece(p2, &newPos);
        }
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
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            delete cells[i][j];
        }
    }
}

std::vector<vector2> Grid::GetMoveOptions(vector2* c)
{
    bool color = cells[c->y][c->x]->getPiece()->isWhite;

    std::vector<vector2> moveOptions;

    vector2 newPos = *c;

    switch (cells[c->y][c->x]->getPiece()->type)
    {
    case KING:

        newPos.x += 1;
        moveOptions.push_back(newPos);
        newPos.x -= 2;
        moveOptions.push_back(newPos);

        newPos.x = c->x;

        newPos.y += 1;
        moveOptions.push_back(newPos);
        newPos.y -= 2;
        moveOptions.push_back(newPos);

        break;
    case QUEEN:

        for (int i = 1; i < 8; i++)
        {
            newPos.x += i;
            moveOptions.push_back(newPos);
            newPos = *c;
            newPos.x -= i;
            moveOptions.push_back(newPos);
            newPos = *c;
            newPos.y += i;
            moveOptions.push_back(newPos);
            newPos = *c;
            newPos.y -= i;
            moveOptions.push_back(newPos);
            newPos = *c;
        }

        for (int i = 1; i < 8; i++)
        {
            newPos.x += i;
            newPos.y += i;
            moveOptions.push_back(newPos);
            newPos = *c;
            newPos.x += i;
            newPos.y -= i;
            moveOptions.push_back(newPos);
            newPos = *c;
            newPos.x -= i;
            newPos.y += i;
            moveOptions.push_back(newPos);
            newPos = *c;
            newPos.x -= i;
            newPos.y -= i;
            moveOptions.push_back(newPos);
            newPos = *c;
        }


        break;
    case KNIGHT:
        newPos.x += 2;
        newPos.y += 1;
        moveOptions.push_back(newPos);
        newPos = *c;

        newPos.x += 2;
        newPos.y -= 1;
        moveOptions.push_back(newPos);
        newPos = *c;

        newPos.x -= 2;
        newPos.y += 1;
        moveOptions.push_back(newPos);
        newPos = *c;

        newPos.x -= 2;
        newPos.y -= 1;
        moveOptions.push_back(newPos);
        newPos = *c;

        newPos.x += 1;
        newPos.y += 2;
        moveOptions.push_back(newPos);
        newPos = *c;

        newPos.x += 1;
        newPos.y -= 2;
        moveOptions.push_back(newPos);
        newPos = *c;

        newPos.x -= 1;
        newPos.y += 2;
        moveOptions.push_back(newPos);
        newPos = *c;

        newPos.x -= 1;
        newPos.y -= 2;
        moveOptions.push_back(newPos);
        newPos = *c;
        break;
    case TOWER:

        for (int i = 1; i < 8; i++)
        {
            newPos.x += i;
            moveOptions.push_back(newPos);
            newPos = *c;
            newPos.x -= i;
            moveOptions.push_back(newPos);
            newPos = *c;
            newPos.y += i;
            moveOptions.push_back(newPos);
            newPos = *c;
            newPos.y -= i;
            moveOptions.push_back(newPos);
            newPos = *c;
        }

        break;
    case BISHOP:

        for (int i = 1; i < 8; i++)
        {
            newPos.x += i;
            newPos.y += i;
            moveOptions.push_back(newPos);
            newPos = *c;
            newPos.x += i;
            newPos.y -= i;
            moveOptions.push_back(newPos);
            newPos = *c;
            newPos.x -= i;
            newPos.y += i;
            moveOptions.push_back(newPos);
            newPos = *c;
            newPos.x -= i;
            newPos.y -= i;
            moveOptions.push_back(newPos);
            newPos = *c;
        }

        break;
    case PAWN:


        if (color)
            newPos.y -= 1;
        else
            newPos.y += 1;
        
        moveOptions.push_back(newPos);

        if (cells[c->y][c->x + 1]->getPiece() != nullptr)
        {
            if (cells[c->y][c->x + 1]->getPiece()->isWhite != color)
            {
                newPos.x += 1;
                moveOptions.push_back(newPos);
            }

            newPos = *c;

            if (cells[c->y][c->x - 1]->getPiece()->isWhite != color)
            {

                if (color)
                    newPos.y -= 1;
                else
                    newPos.y += 1;


                newPos.x -= 1;
                moveOptions.push_back(newPos);
            }
        }

        break;
    default:
        break;
    }

    for (int i = 0; i < moveOptions.size(); i++)
    {
        if (cells[moveOptions[i].y][moveOptions[i].x]->getPiece()->isWhite == color) {
            moveOptions.erase(moveOptions.begin() + i);
        }
    }



    return moveOptions;
}

void Grid::MovePiece(vector2* from, vector2* to)
{

    //Si és torre o rei posem el moved a true
    if (cells[from->y][from->x]->getPiece()->type == KING)
        static_cast<King*>(cells[from->y][from->x]->getPiece())->moved = true;
    else if (cells[from->y][from->x]->getPiece()->type == TOWER)
        static_cast<Tower*>(cells[from->y][from->x]->getPiece())->moved = true;


    cells[from->y][from->x]->setOnclick(nullptr);
    cells[to->y][to->x]->setPiece(cells[from->y][from->x]->getPiece());
    cells[to->y][to->x]->setOnclick(_pieceSelected);
    cells[from->y][from->x]->setPiece(nullptr);
}

void Grid::DeselectPiece(vector2* p)
{
    std::vector<vector2> locations = GetMoveOptions(p);

    for (int i = 0; i < locations.size(); i++)
    {
        //Falta treure els botons en vermell
        cells[locations[i].x][locations[i].y]->setOnclick(nullptr);
    }


    //Castle Case
    if (cells[p->y][p->x]->getPiece()->type == KING)
    {
        if (cells[p->y][p->x + 1]->getPiece() == nullptr &&
            cells[p->y][p->x + 2]->getPiece() == nullptr &&
            static_cast<King*>(cells[p->y][p->x]->getPiece())->moved == false &&
            static_cast<Tower*>(cells[p->y][p->x]->getPiece())->moved == false)
        {
            //Falta treure els botons en vermell
            cells[p->y][p->x + 2]->setOnclick(nullptr);
        }
        else if (cells[p->y][p->x - 1]->getPiece() == nullptr &&
            cells[p->y][p->x - 2]->getPiece() == nullptr &&
            cells[p->y][p->x - 3]->getPiece() == nullptr &&
            static_cast<King*>(cells[p->y][p->x]->getPiece())->moved == false &&
            static_cast<Tower*>(cells[p->y][p->x]->getPiece())->moved == false)
        {
            //Falta treure els botons en vermell
            cells[p->y][p->x - 3]->setOnclick(nullptr);
        }
    }

    //Promotion case
    else if (cells[p->y][p->x]->getPiece()->type == PAWN)
    {
        if (p->y == 1 && cells[p->y][p->x]->getPiece()->isWhite == true)
        {
            //Falta treure els botons en vermell
            cells[0][p->x]->setOnclick(nullptr);
        }
        else if (p->y == 6 && cells[p->y][p->x]->getPiece()->isWhite == false)
        {
            //Falta treure els botons en vermell
            cells[7][p->x]->setOnclick(nullptr);
        }
    }
}
