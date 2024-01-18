#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class game_world
{
private:
	char world_grid[5][5];
	char player_grid[5][5];
	int px, py;
	int game_state;
	char player_state;
	int score;

public:
	game_world() //Constructor
	{
		game_state = 0;
		player_state = 'A';
		score = 0;
	}
	void intialize_game_world(); //Initializes the game board
	void disp_entire_world(); //Displays the entire game world
	void disp_visible_world(); //Displays and reveals the game world within the player's range (one square)
	void disp_player_world(); //Displays the game world that the player can see initially and throughout.
	void disp_score(); //Displays the player's final score
	void find_player(); //Determines the location of the player on the board.
	void m_up(); //Move up
	void m_down(); //Move down
	void m_left(); //Move left
	void m_right(); //Move right
	bool win_or_lose(); //Determines if the player has won or not
	bool DoA(); //Determines if the playe is dead or alive

	friend ostream& operator << (ostream& outfile, const game_world&); //Overloaded operator
};

void err_msg(); //Displays an error message for invalid input
void disp_game(); //Displays the starting menu.
void disp_rules(); //Displays the rules.


#endif