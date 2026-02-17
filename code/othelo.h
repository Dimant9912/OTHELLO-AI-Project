#ifndef OTHELO_H
#define OTHELO_H
#include <iostream>
#include <vector>
#include <utility>

class othelo {
public:
	othelo();
	othelo(const othelo& ob);
	friend ostream& operator<<(ostream& left, othelo& right);
	void set_player(char c);
	char get_player() const;
	void next_player();
	bool play(int choice_i,int choice_j);
	bool has_valid_move() ;/*elegxei kai tis 64 theseis toy pinaka,kai gia kathe kenh thesi
	tha elegksei an topothetwntas to poyli se ekeinh thn thesi tha ginotan estw kai mia anstrofi*/
	bool is_valid_direction(int x, int y, int dx, int dy, char current_player);/*elegxei an iparxei alisida kommatiwn toy antipaloy pou
	teleiwnei se pouli tou paikth se sygkekrimenh thesi*/
	int evaluate(char pl);/* euretikh sinarthsh : molis ftasoume sta leaves tou dentrou,epistrefei mia timh sth riza,anadromika*/
    int count_checkers();

// Returns the optimal value a maximizer can obtain.
// current_depth is current depth in game tree.
// isMax is true if current move is of maximizer, else false
// depth is maximum height of Game tree
	int minimax(int current_depth,int depth, bool isMax,char maximizing_player,int alpha,int beta);
	std::vector<std::pair<int, int>> get_all_valid_moves_for_player(char player);/*mia lista (vector) apo ta zeugaria  ! OLWN !  twn egkirwn kinhsevn */
	std::pair<int,int> find_best_move(char pc,int depth);
	

private:
	bool flip(int x,int y,char current_player);
	char array[BOARD_SIZE][BOARD_SIZE];
	char player;
	char pc;
	int depth;

};
#endif