module;

#include <string>
#include <cassert>
#include <sstream>
#include <iostream>
#include <cstdlib>


export module TicTacToe;//module decleration
using namespace std;

//==============================================Enumerations=========================================
export enum GameThings
{
        SPACE,
        STAR,
        CROSS,
};

export enum GameTurn
{
        PLAYER_1,
        PLAYER_2,
};

//===============================================Typedefs=============================================
using Rows = GameThings*;
using Grid = Rows*;

//
export class TicTacToe
{
        public:
                TicTacToe();
                ~TicTacToe();
                //accessors
                int getRows() const;
                int getCols() const;
                GameThings getChar(int r, int c) const;
                std::string ShowGrid() const;
                //bool IsDraw();
                //mutators
                void setCharAt(int r, int c, GameThings thing);
        private:
                int _Rows;
                int _Cols;
                Grid _grid;
                void Alloc();
                void Dealloc();
                //utillity method
                bool IsinGrd(int r, int c) const;
                //class constants
                static constexpr int DefaultCols = 3;
                static constexpr int DefaultRows = 3;
                static constexpr char GameChars[3] = {'.','*','+'};
};

//==========================================================public=====================================

TicTacToe::TicTacToe()
{
        //assert(_grid == nullptr);//safety check
        _Rows = DefaultRows;
        _Cols = DefaultCols;
        Alloc();
}
TicTacToe::~TicTacToe()
{
        //safety
        assert(_grid != nullptr);
        Dealloc();
}

int TicTacToe::getRows() const{return _Rows;}
int TicTacToe::getCols() const{return _Cols;}


//============================================== Private =====================================================
GameThings TicTacToe::getChar(int r, int c) const
{
        assert(IsinGrd(r, c));//check if the statement is true else quit
        return _grid[r][c];
}
std::string TicTacToe::ShowGrid() const
{
        using namespace std;//safe to use here
        stringstream ss;
        ss<<"==============TicTacToe Game=========="<<endl;
        for(int k = 0;k<_Rows; k++)
        {
                for(int j = 0;j<_Cols; j++)
                {
                        ss<<GameChars[_grid[k][j]]<<' ';//can i use static_cast
                }
                ss<<endl;
        }
        return ss.str();
}
                //mutators
void TicTacToe::setCharAt(int r, int c, GameThings thing)
{
        assert(IsinGrd(r, c));
        if(_grid[r][c] == SPACE)
                 _grid[r][c] = thing;
        else
        {
                cout<<"Cannot Place there!"<<endl;
                system("pause");
        }
}
void TicTacToe::Alloc()
{
        _grid = new Rows[_Rows];
        for(int k = 0;k< _Rows;k++)
        {
                _grid[k] = new GameThings[_Cols];
                for(int j = 0; j<_Cols;j++)
                {
                        _grid[k][j] = SPACE;
                }
        }
}
void TicTacToe::Dealloc()
{
        for(int k = 0;k<_Rows;k++)
                delete[] _grid[k];
        delete[] _grid;
        _grid = nullptr;//avoid dangling memory
}
bool TicTacToe::IsinGrd(int r, int c) const
{
        return r>=0 && r<_Rows && c>=0 && c<_Cols;
}
