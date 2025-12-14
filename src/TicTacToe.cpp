module;

//file directives to include
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
import Generics;

export module TicTacToe;


enum GameThings{SPACE, STAR, CROSS};
constexpr char GameDisplay[3] = {'.', '*', '+'};

export class TicTacToe : public Generics<GameThings>
{
	public:
		//using Generics<GameThings>::Generics;
		TicTacToe();
		~TicTacToe();
		void StartGame();
		std::string ShowGrid()const;
	private:
		//helper methods
		bool Player_1_turn;
		bool _blnContinue;
		bool CheckWin(GameThings Thing) const;
		bool isDraw()const;
		void HandleTurn();
		void HandleMovement(char cInput);
		void PlaceInGrid(int Row, int Col);
		void callStart();
		//class constants
		static constexpr int DefaultRows = 3;
		static constexpr int DefaultCols = 3;
		static constexpr GameThings DefaultValue = SPACE;
};

TicTacToe::TicTacToe() : Generics<GameThings>(DefaultRows, DefaultCols, DefaultValue)
{
	Player_1_turn = true;
	_blnContinue = true;
}

TicTacToe::~TicTacToe(){}
std::string TicTacToe::ShowGrid()const
{
	std::stringstream ssShow;
	for(int k = 0;k<getRows();k++)
	{
		for(int j = 0;j<getCols();j++)
		{
			ssShow<<GameDisplay[getValue(k, j)]<<' ';
		}
		ssShow<<"\n";
	}
	ssShow<<"For Player "<<(Player_1_turn ? "1 " : "2 ")<<"choose:\n";
	ssShow<<"Q - UP_Left, "<<"W - UP_Mid, "<<"E - UP_Right\n";
	ssShow<<"A - Mid_Left, "<<"S - Mid_Mid, "<<"D - Mid_Right\n";
	ssShow<<"Z - Down_Left, "<<"X - Down_Mid, "<<"C - Down_Right\n";
	ssShow<<"f-Quit\n";
	return ssShow.str();
}
void TicTacToe::StartGame()
{	
	char Chchoice = '\0';
	do{
		system("cls");
		std::cout<<ShowGrid();
		std::cin>>Chchoice;
		HandleMovement(tolower(Chchoice));
	}while(_blnContinue);
	std::cout<<"start game (y/n)? ";
	std::cin>>Chchoice;
	if(std::tolower(Chchoice) == 'y')
	{
		Reset(SPACE);
		_blnContinue = true;
		StartGame();
	}
	
}

void TicTacToe::HandleTurn()
{
	Player_1_turn = !Player_1_turn;
}

bool TicTacToe::CheckWin(GameThings Thing) const
{
	if(getValue(0, 0) == Thing && getValue(1, 1) == Thing && getValue(2, 2) == Thing)
		return true;
	if(getValue(0, 2) == Thing && getValue(1, 1) == Thing && getValue(2, 0) == Thing)
		return true;
	for(int k = 0; k<getRows();k++)
	{
		if(getValue(k, 0) == Thing && getValue(k, 1) == Thing && getValue(k, 2) == Thing)
			return true;
	}
	for(int k = 0;k<getCols();k++)
	{
		if(getValue(0, k) == Thing && getValue(1, k) == Thing && getValue(2, k) == Thing)
			return true;
	}
	//else
	return false;
}

void TicTacToe::PlaceInGrid(int Row, int Col)
{
	if(getValue(Row, Col) == SPACE)
	{
		setValue(Row, Col, Player_1_turn ? STAR : CROSS);
		bool PlayerWon = CheckWin(Player_1_turn ? STAR : CROSS);
		if(PlayerWon)
		{
			system("cls");
			std::cout<<ShowGrid();
			std::cout<<"Player"<<(Player_1_turn ? " 1": " 2")<<" Won the Game!!\n";
			_blnContinue = false;
		}
		HandleTurn();
	}
	else
		std::cout<<"Cannot Place There\n";
	
}

bool TicTacToe::isDraw()const
{
	for(int k = 0;k<getRows();k++)
	{
		for(int j = 0;j<getCols();j++)
		{
			if(getValue(k, j) == SPACE)
				return false;
		}
	}
	return true;
}


void TicTacToe::HandleMovement(char cInput)
{
	switch(std::tolower(cInput))
		{
			case 'q':
				PlaceInGrid(0, 0);
				break;
			case 'w':
				PlaceInGrid(0, 1);
				break;
			case 'e':
				PlaceInGrid(0, 2);
				break;
			case 'a':
				PlaceInGrid(1, 0);
				break;
			case 's':
				PlaceInGrid(1, 1);
				break;
			case 'd':
				PlaceInGrid(1, 2);
				break;
			case 'z':
				PlaceInGrid(2, 0);
				break;
			case 'x':
				PlaceInGrid(2, 1);
				break;
			case 'c':
				PlaceInGrid(2, 2);
				break;
			case 'f':
				_blnContinue = false;
				break;
			default:
			break;
		}
		if(isDraw())
		{
			system("cls");
			std::cout<<ShowGrid();
			std::cout<<"A game played perfect is a draw."<<std::endl;
			_blnContinue = false;
		}
}
