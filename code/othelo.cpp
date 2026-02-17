#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
const int BOARD_SIZE =8;
#include <ctime>
#include "othelo.h"
#include <vector>
#include <utility>

/* constructor */
othelo::othelo() {
	for (int i = 0; i <BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			array[i][j] = '-';
		}
	}
	array[(BOARD_SIZE/2) -1 ][(BOARD_SIZE/2)-1]='1';
	array[BOARD_SIZE/2][BOARD_SIZE/2]='1';
	array[(BOARD_SIZE/2) -1 ][BOARD_SIZE/2]='0';
	array[BOARD_SIZE/2][(BOARD_SIZE/2)-1]='0';
}
/*copy constructor*/
othelo :: othelo(const othelo& ob)
{	this->player = ob.player;
	for(int i = 0; i<BOARD_SIZE; i++)
		for(int j=0; j<BOARD_SIZE; j++)
			this->array[i][j] = ob.array[i][j];

}

/* Yperfortwsh << : gia ektipwsh */
ostream& operator<<(ostream& left, othelo& right) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			left << right.array[i][j] << " ";
		}
		left << endl;
	}
	return left;
}
/* next_player*/
void othelo :: next_player()
{
	if (player=='0')
		player='1';
	else
		player = '0';
}
/*set_player*/
void othelo :: set_player(char c) {
	player = c;
}
/*get_player*/
char othelo:: get_player() const {
	return player;
}
/*play()*/
bool othelo :: play(int choice_i,int choice_j)
{
	if(choice_i<0 || choice_i>BOARD_SIZE || choice_j <0 || choice_j>BOARD_SIZE || array[choice_i][choice_j]!='-')

	{	cout<<"Error,Dwse swstew sintetagmenes!"<<endl;

		return false;/*has not valid move*/
	}

	if(flip(choice_i,choice_j,player))
	{	array[choice_i][choice_j]=player;
		return true;
	}
	return false;


}
/*has valid moves*/
bool othelo :: has_valid_move()
{
	int directions[8][2] = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1},{1,0}, {1,1}};/* 8 kateythinseis ksekinwntas apo panw aristera,ews katw deksia*/
	int dx,dy;
	for(int i=0; i<BOARD_SIZE; i++)
		for(int j=0; j<BOARD_SIZE; j++)
		{	if(array[i][j]=='-')
			{
				/*gia authn thn thesi,elegxoume kai tis 8 kateuthinseis*/
				for(int k=0; k<8; k++)
				{
					dx = directions[k][0];
					dy = directions[k][1];

					if (is_valid_direction(i, j, dx, dy, player))
						/*vrethike egkiri kinhsh den xreiazetai na psaksoyme allo*/
						return true;
				}
			}
		}
	return false;
}

/*is_valid_directions*/
bool othelo :: is_valid_direction(int x, int y, int dx, int dy, char current_player)
{
	char opponent;
	int kateuthinsi_i=x+dx;
	int kateuthinsi_j=y+dy;
	if(current_player=='1')
		opponent = '0';
	else
		opponent = '1';

	/*prepei na iparxei toulaxiston ena antipalo pouli kata thn kinhsh*/
	if (kateuthinsi_i>=0 && kateuthinsi_i<BOARD_SIZE && kateuthinsi_j>=0 && kateuthinsi_j<BOARD_SIZE && array[kateuthinsi_i][kateuthinsi_j]==opponent)
	{	kateuthinsi_i += dx;/*synexizoume sthn grammh i pros ta panw h pros ta katw antistoixa*/
		kateuthinsi_j+= dy; /*omoiws sinexizoume to psaksimo kaata mikos ths sthlhs,omws pros
                              ta ekei pou mas leei to y(px y=-1) mporei na phgainoume aristera dld*/
		while (kateuthinsi_i >= 0 && kateuthinsi_i< BOARD_SIZE && kateuthinsi_j >= 0 && kateuthinsi_j < BOARD_SIZE) {
			if(array[kateuthinsi_i][kateuthinsi_j]== current_player) {
				return true;
			}
			if(array[kateuthinsi_i][kateuthinsi_j]== '-')
			{
				return false;
			}
			kateuthinsi_i += dx;
			kateuthinsi_j+= dy;

		}

	}
	return false;
}
/*flip*/
bool othelo ::  flip(int x,int y,char current_player)
{
	bool flipped = false;
	int directions[8][2] = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1},{1,0}, {1,1}};
	for(int i=0; i<8; i++)
	{
		int dx = directions [i][0];
		int dy = directions [i][1];
		if(is_valid_direction(x,y,dx,dy,current_player)) {
			int kateuthinsi_i = x+ dx;
			int kateuthinsi_j = y+dy;
			char opponent = (current_player == '0') ? '1' : '0';

			while(kateuthinsi_i>=0 && kateuthinsi_i<BOARD_SIZE && kateuthinsi_j>=0 && kateuthinsi_j<BOARD_SIZE && array[kateuthinsi_i][kateuthinsi_j]==opponent)
			{
				array[kateuthinsi_i][kateuthinsi_j] = current_player;
				kateuthinsi_i +=dx;
				kateuthinsi_j+=dy;
				flipped = true;
			}
		}

	}
	return flipped;
}

/*minimax*/
int othelo ::minimax(int current_depth,int depth, bool isMax,char maximizing_player,int alpha,int beta)
{	/*opponent player*/
	char minimizing_player;
	if (maximizing_player=='0')
		minimizing_player ='1';
	else
		minimizing_player = '0';
	/*current player*/
	char current_player;
	if(isMax)
		current_player = maximizing_player;
	else
		current_player = minimizing_player;

	std::vector<std::pair<int, int>> valid_moves = this->get_all_valid_moves_for_player(current_player);



	if (valid_moves.empty())/*o trexwn paikths den exei egkiri kinhsh,opote theloume eite pass,eite game over*/
	{

		/*elegxoume an o antipalos mporei na kinithei*/
		if (this->get_all_valid_moves_for_player(minimizing_player).empty()) {
			return this->evaluate(maximizing_player);
		}


		return this->minimax(current_depth, depth, !isMax, maximizing_player,alpha,beta);/*pass*/
	}
	if(current_depth==depth)
	{
		return this->evaluate(maximizing_player);
	}

	if(isMax)
	{
		int max_evaluation = -10000;
		for(const auto& move : valid_moves)
		{

			othelo new_board(*this);
			new_board.play(move.first, move.second);
			int eval = new_board.minimax(current_depth + 1, depth, false, maximizing_player,alpha,beta);
			max_evaluation = std::max(eval,max_evaluation);

			alpha = std::max(alpha, max_evaluation);
			if (alpha >= beta) {
				break;
			}

		}

		return max_evaluation;
	}
	else
	{
		int min_evaluation = 10000;
		for(const auto& move : valid_moves)
		{
			othelo new_board(*this);
			new_board.play(move.first, move.second);
			int eval = new_board.minimax(current_depth +1,depth,true,maximizing_player,alpha,beta);
			min_evaluation = std :: min(eval,min_evaluation);
			beta = std::min(beta, min_evaluation);
			if (alpha >= beta) {
				break;
			}

		}
		return min_evaluation;
	}

}

/* get_all_valid_moves_for_player*/
std::vector<std::pair<int, int>> othelo :: get_all_valid_moves_for_player(char player)
{
	std::vector<std::pair<int, int>> moves; /* moves = lista poy periexei ta zeugaria twn egkirvn kinisewn*/
	int directions[8][2] = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1},{1,0}, {1,1}};/* 8 kateythinseis ksekinwntas apo panw aristera,ews katw deksia*/
	int dx,dy;
	for(int i=0; i<BOARD_SIZE; i++)
		for(int j=0; j<BOARD_SIZE; j++)
		{	if(array[i][j]=='-')
			{
				/*gia authn thn thesi,elegxoume kai tis 8 kateuthinseis*/
				for(int k=0; k<8; k++)
				{
					dx = directions[k][0];
					dy = directions[k][1];

					if (is_valid_direction(i, j, dx, dy, player))/*vrethike egkiri kinhsh */
					{	moves.push_back({i,j});/*topothetei to stoixeio sth lista kai auksanei to megethos kata 1*/
						break;
					}
				}
			}
		}
	return moves;
}

int othelo :: evaluate(char maximizing_player)/*euretikh diaforas pouliwn kai barh*/
{


	static const int weights[BOARD_SIZE][BOARD_SIZE] = {
		{120, -20, 20,  5,  5, 20, -20, 120},
		{-20, -40, -5, -5, -5, -5, -40, -20},
		{ 20,  -5, 15,  3,  3, 15,  -5,  20},
		{  5,  -5,  3,  3,  3,  3,  -5,   5},
		{  5,  -5,  3,  3,  3,  3,  -5,   5},
		{ 20,  -5, 15,  3,  3, 15,  -5,  20},
		{-20, -40, -5, -5, -5, -5, -40, -20},
		{120, -20, 20,  5,  5, 20, -20, 120}
	};
	

	int total_score = 0;
	int count_pc=0;
	int count_opponent=0;
	char opponent_player; 

	if (maximizing_player == '0') {
		opponent_player = '1';
	} else {
		opponent_player = '0';
	}
	


	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{

			if (array[i][j] == maximizing_player)
			{
				total_score += weights[i][j];//An vroyme poyli toy 'maximizing_player' (AI), prosthetoyme to varos
				count_pc++;/*metavlith pou krataei posa poulia exei o pc sto desk*/
			}

			else if (array[i][j] == opponent_player)
			{
				total_score -= weights[i][j];// An vroyme to pouli toy antipaloy, afairovme to varos
				count_opponent++;/*metavliti poy krataei posa poulia exei o player sto desk*/
			}
		}
	}
	double Heuristic_count = double(count_pc-count_opponent);

	const double W_Position = 1.0;
	const double W_Count    = 0.8;
	double final_score = (total_score*W_Position) + (Heuristic_count*W_Count);/*athroisma ginomenwn twn 2 euretikwn gia to kalitero apotelesma*/
	return (int)final_score;


}

std :: pair<int, int> othelo ::find_best_move(char pc,int depth)

{	/*arxikopoiw row,column se periptwsh pou den mpei pote ston vrogxo for*/
	int row=-1;
	int column=-1;

	/*arxikopoihsh alpha,beta*/
	int alpha = -100000;
	int beta = 100000;

	int best_total = -1000;
	std::vector<std::pair<int, int>> valid_moves = this->get_all_valid_moves_for_player(pc);
	if(valid_moves.empty()) {
		return {-1,-1};
	}
	for(const auto& move : valid_moves) {
		othelo new_board(*this);/*dhmiourgia antigrafou tamplo*/
		new_board.play(move.first,move.second);
		int score = new_board.minimax(1,depth,false,pc,alpha,beta);
		if(score>best_total)
		{
			best_total = score;
			row = move.first;
			column=move.second;
			/*best_move = move;*/
			alpha = std::max(alpha,best_total);
		}
	}
	return {row, column};

}
int othelo :: count_checkers()
{
	int player_checkers=0;
	int pc_checkers=0;
	for (int i=0; i<BOARD_SIZE; i++)
		for (int j=0; j<BOARD_SIZE; j++)
			if (array[i][j] == '1')
				player_checkers+=1;
			else if(array[i][j]=='0')
				pc_checkers+=1;


	if (player_checkers>pc_checkers)
	{	cout<<"You won"<<endl;
		return 1;
	}
	else if(player_checkers==pc_checkers)
	{	cout<<"Isopalia";
		return 0;
	}
	else/*(player_checkers<pc_checkers)*/
	{	
	    cout<<"Pc won";
	    return -1;
		
	}

}
