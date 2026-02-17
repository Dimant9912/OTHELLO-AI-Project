
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
#include <ctime>
const int BOARD_SIZE =8;
#include "othelo.h"





int main() {
	othelo o1;
	char player = '1';
	char ai = '0';
	int depth ;
	char choice;
	int choice_i;
	int choice_j;
	cout<<"Poios tha paiksei prwtos? : (0 for pc , 1 for user)"<<endl;
	cin>>choice;
	o1.set_player(choice);

	cout<<"Dialekse to vathos(depth) toy minimax: "<<endl;
	cin>>depth;

	while(true)
	{

		char current_player = o1.get_player();
		cout<<"----------"<<endl;
		cout<<"Board: " <<endl;
		cout<<o1;
		cout<<"player : "<< current_player << " is playing"<<endl;

		vector<pair<int,int>>  current_valid_moves = o1.get_all_valid_moves_for_player(current_player);
		if(current_valid_moves.empty())
		{
			o1.next_player();
			bool next_player_has_valid_moves=!o1.get_all_valid_moves_for_player(o1.get_player()).empty();
			o1.next_player();
			if(!next_player_has_valid_moves) {
				cout<<"Game is over";
				break;
			}
			cout << "O paikths " << current_player << " den exei egkyrh kinhsh kai paramenei h seira " << endl;
			o1.next_player();
			continue;
		}
		int row=-2;
		int column=-2;
		if(current_player=='0')
		{
			pair<int,int> best_move = o1.find_best_move(current_player,depth);
			int row = best_move.first;
			int column = best_move.second;
			if(row!=-1 && column != -1)
			{
				o1.play(row,column);
			}
			else
			{
				cout<<"No move found for pc"<<endl;
				o1.next_player();
			}
		}

		else
		{	bool valid_move=true;
			int row,column;
			cout<<"Dwse grammh , sthlh : "<<endl;
			while(true)
			{
				if(!(cin>>row>>column))/*prospathei na diavasei 2 arithmouw,kai na ts apothikeusei st row,column*/
					/*h roh eisodou leitourgei ws logikh sinthiki*/
					/*an o xrhsths dwsei kati ektos apo arithmous,epistrefetai false,opote prepei na ksanadwsei*/
				{
					cout<<"Error,Dwse swstew sintetagmenes!"<<endl;
					cin.clear();/*epanaferei thn roh*/
					cin.ignore(10000,'\n');/*afairountai ta lathos dedomena*/
					continue;
				}
				if((row<0 || row>BOARD_SIZE-1) || (column<0 || column>BOARD_SIZE-1))
				{
					cout<<"Error,dwse swstes sintetagmenes"<<endl;
					cin.clear();
					cin.ignore(10000,'\n');
					continue;
				}


				if(o1.play(row,column))
				{
					cout<<"Kinhsh  egkyrh"<<endl;
					break;
				}
				else {
					"kinhsh oxi egkiri";

				}
			}
		}
		o1.next_player();
	}
	o1.count_checkers();
	return 0;
}



