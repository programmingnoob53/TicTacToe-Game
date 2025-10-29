module;
#include <iostream>
#include <cstdlib>
export module GameHandler;

import TicTacToe;



using namespace std;

export class GameHandler
{
	public:
		GameHandler();
		~GameHandler();

		void Start();//game loop
	private:
		TicTacToe* _obj;
		GameTurn _turn;
		bool _BlnContinue;
		void HandleTurn();
		void PlaceInGrd(int r, int c);
};


GameHandler::GameHandler(){
	_obj = new TicTacToe;
	_turn = PLAYER_1;
	_BlnContinue = true;
}
GameHandler::~GameHandler(){delete _obj; _obj = nullptr;}

void GameHandler::Start()
{
	do
		{
			system("cls");
			cout<<_obj->ShowGrid();
			char Choice = '\0';
			switch(_turn)
			{
			case PLAYER_1:
				cout<<"For player 1, choose a move: "<<endl;
				cout<<"q - Top Left,  w - Top Center,  e - Top Right"<<endl;
				cout<<"a - Mid Left,  s - Mid Center,  d - Mid Right"<<endl;
				cout<<"z - Bot Left,  x - Bot Center,  c - Bot Right"<<endl;
				cout<<"f-QUIT"<<endl;
				cin>>Choice;

				break;
			case PLAYER_2:
				cout<<"For player 2, choose a move: "<<endl;
				cout<<"q - Top Left,  w - Top Center,  e - Top Right"<<endl;
				cout<<"a - Mid Left,  s - Mid Center,  d - Mid Right"<<endl;
				cout<<"z - Bot Left,  x - Bot Center,  c - Bot Right"<<endl;
				cout<<"f-QUIT"<<endl;
				cin>>Choice;
				break;
			}

			switch(tolower(Choice))
			{
			case 'q':
				
				PlaceInGrd(0, 0);
				break;
			case 'w':
				PlaceInGrd(0, 1);
				break;
			case 'e':
				PlaceInGrd(0, 2);
				break;
			case 'a':
				PlaceInGrd(1, 0);
				break;
			case 's':
				PlaceInGrd(1, 1);
				break;
			case 'd':
				PlaceInGrd(1, 2);
				break;
			case 'z':
				PlaceInGrd(2, 0);
				break;
			case 'x':
				PlaceInGrd(2, 1);
				break;
			case 'c':
				PlaceInGrd(2, 2);
				break;
			case 'f':
				cout<<"Quiting..."<<endl;
				_BlnContinue = false;//stop the loop
				break;
			default:
				break;

			}
			HandleTurn();
		}while(_BlnContinue);
}

void GameHandler::PlaceInGrd(int r, int c)
{
	if (_turn == PLAYER_1)
	{
		_obj->setCharAt(r, c, STAR);
	}
	else
		_obj->setCharAt(r, c, CROSS);
}

void GameHandler::HandleTurn()
{
	if(_turn == PLAYER_1)
		_turn = PLAYER_2;
	else
		_turn = PLAYER_1;
}


