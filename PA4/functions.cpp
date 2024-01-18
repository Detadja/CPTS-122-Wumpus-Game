#include "header.h"

//Displays an error message for invalid input
void err_msg()
{
	system("cls");
	cout << "[That is invalid. Please enter a valid input.]\n\n";
}

//Displays the starting menu.
void disp_game()
{
	cout << "[Hunt The Wumpus]" << endl;
	cout << endl << "[1.) Play Game]\n" << "[2.) Rules]\n" << "[3.) Exit]\n\n";
}

//Displays the rules.
void disp_rules()
{
	cout << "[The objective of this game is for you, the player (U), to ]\n";
	cout << "[explore and find gold (G). Watch out however, as you are  ]\n";
	cout << "[also being chased by the Wumpus (W), and you must be wary ]\n";
	cout << "[of pitfalls (P) along the way.                            ]\n\n";
	cout << "[You are able to see the surroundings of where you         ]\n";
	cout << "[start, but everything else is unknown. You are able to    ]\n";
	cout << "[slightly see ahead of your new location if you input 'V'. ]\n";
	cout << "[Additionally, if you are curious, you may be able to cheat]\n";
	cout << "[using 'C', to be able to see the entire game.             ]\n\n";
	cout << "[If you find yourself to be in a deadend, you could restart]\n";
	cout << "[using 'R', or if you would like a second player to play,  ]\n";
	cout << "[you can use 'N' to make an entirely new game. Finally, if ]\n";
	cout << "[you feel like you had enough to play, 'Q' will end the    ]\n";
	cout << "[game and quit.                                            ]\n\n";
} 

//Initializes the game board
void game_world::intialize_game_world()
{
	for (int y_ind = 0; y_ind < 5; y_ind++) //Initializes the board
	{
		for (int x_ind = 0; x_ind < 5; x_ind++)
		{
			world_grid[x_ind][y_ind] = '-';
		}
	}

	for (int y_ind = 0; y_ind < 5; y_ind++) //Initializes the player's board
	{
		for (int x_ind = 0; x_ind < 5; x_ind++)
		{
			player_grid[x_ind][y_ind] = '-';
		}
	}

	int x = 0, y = 0, px = 0, py = 0;
	x = px = (rand() % 5);
	y = py = (rand() % 5);
	//Randomly places the player on the grid.
	world_grid[x][y] = 'U'; 
	player_grid[x][y] = 'U';

	x = (rand() % 5);
	y = (rand() % 5);
	//Checks if there is already an object in that location
	while (world_grid[x][y] == 'U')
	{
		x = (rand() % 5);
		y = (rand() % 5);
	}
	world_grid[x][y] = 'W'; //Randomly places the Wumpus on the grid.

	x = (rand() % 5);
	y = (rand() % 5);
	//Checks if there is already an object in that location
	while (world_grid[x][y] == 'U' || world_grid[x][y] == 'W')
	{
		x = (rand() % 5);
		y = (rand() % 5);
	}
	world_grid[x][y] = 'G'; //Randomly places the Gold on the grid.

	int num = 0;
	num = (rand() % 6) + 1; //Randomly decides how many pitfalls there are going to be (min 1)
	for (int index = 0; index < num; index++)
	{
		x = (rand() % 5);
		y = (rand() % 5);
		//Checks if there is already an object in that location
		while (world_grid[x][y] == 'U' || world_grid[x][y] == 'G' || world_grid[x][y] == 'W' || world_grid[x][y] == 'P')
		{
			x = (rand() % 5);
			y = (rand() % 5);
		}
		world_grid[x][y] = 'P'; //Randomly places the Gold on the grid.
	}

	//Reveals the player's surroundings when they start
	if (px == 0) //If the player's location is at the left vertical edge
	{
		if (py == 0) //Top left
		{
			player_grid[px + 1][py] = world_grid[px + 1][py]; //Right
			player_grid[px][py + 1] = world_grid[px][py + 1]; //Down
			player_grid[px + 1][py + 1] = world_grid[px + 1][py + 1]; //Lower right
		}
		else if (py == 4) //Bottom left
		{
			player_grid[px][py - 1] = world_grid[px][py - 1]; //Up
			player_grid[px + 1][py - 1] = world_grid[px + 1][py - 1]; //Upper right
			player_grid[px + 1][py] = world_grid[px + 1][py]; //Right
		}
		else //Middle left
		{
			player_grid[px][py - 1] = world_grid[px][py - 1]; //Up
			player_grid[px + 1][py - 1] = world_grid[px + 1][py - 1]; //Upper right
			player_grid[px + 1][py] = world_grid[px + 1][py]; //Right
			player_grid[px][py + 1] = world_grid[px][py + 1]; //Down
			player_grid[px + 1][py + 1] = world_grid[px + 1][py + 1]; //Lower right
		}
	}
	else if (px == 4) //If the player's location is at the right vertical edge
	{
		if (py == 0) //Top right
		{
			player_grid[px - 1][py] = world_grid[px - 1][py]; //Left
			player_grid[px - 1][py + 1] = world_grid[px - 1][py + 1]; //Lower left
			player_grid[px][py + 1] = world_grid[px][py + 1]; //Down
		}
		else if (py == 4) //Bottom right
		{
			player_grid[px - 1][py - 1] = world_grid[px - 1][py - 1]; //Upper left
			player_grid[px][py - 1] = world_grid[px][py - 1]; //Up
			player_grid[px - 1][py] = world_grid[px - 1][py]; //Left
		}
		else //Middle right
		{
			player_grid[px - 1][py - 1] = world_grid[px - 1][py - 1]; //Upper left
			player_grid[px][py - 1] = world_grid[px][py - 1]; //Up
			player_grid[px - 1][py] = world_grid[px - 1][py]; //Left
			player_grid[px - 1][py + 1] = world_grid[px - 1][py + 1]; //Lower left
			player_grid[px][py + 1] = world_grid[px][py + 1]; //Down
		}
	}
	else if (py == 0) //If the player's location is somewhere in the top middle
	{
		if (px == 0)
		{
			player_grid[px + 1][py] = world_grid[px + 1][py]; //Right
			player_grid[px][py + 1] = world_grid[px][py + 1]; //Down
			player_grid[px + 1][py + 1] = world_grid[px + 1][py + 1]; //Lower right
		}
		else if (px == 4)
		{
			player_grid[px - 1][py] = world_grid[px - 1][py]; //Left
			player_grid[px - 1][py + 1] = world_grid[px - 1][py + 1]; //Lower left
			player_grid[px][py + 1] = world_grid[px][py + 1]; //Down
		}
		else
		{
			player_grid[px - 1][py] = world_grid[px - 1][py]; //Left
			player_grid[px + 1][py] = world_grid[px + 1][py]; //Right
			player_grid[px - 1][py + 1] = world_grid[px - 1][py + 1]; //Lower left
			player_grid[px][py + 1] = world_grid[px][py + 1]; //Down
			player_grid[px + 1][py + 1] = world_grid[px + 1][py + 1]; //Lower right
		}
	}
	else if (py == 4) //If the player's location is somewhere in the bottom middle
	{
		if (px == 0)
		{
			player_grid[px][py - 1] = world_grid[px][py - 1]; //Up
			player_grid[px + 1][py - 1] = world_grid[px + 1][py - 1]; //Upper right
			player_grid[px + 1][py] = world_grid[px + 1][py]; //Right
		}
		else if (px == 4)
		{
			player_grid[px - 1][py - 1] = world_grid[px - 1][py - 1]; //Upper left
			player_grid[px][py - 1] = world_grid[px][py - 1]; //Up
			player_grid[px - 1][py] = world_grid[px - 1][py]; //Left
		}
		else
		{
			player_grid[px - 1][py - 1] = world_grid[px - 1][py - 1]; //Upper left
			player_grid[px][py - 1] = world_grid[px][py - 1]; //Up
			player_grid[px + 1][py - 1] = world_grid[px + 1][py - 1]; //Upper right
			player_grid[px - 1][py] = world_grid[px - 1][py]; //Left
			player_grid[px + 1][py] = world_grid[px + 1][py]; //Right
		}
	}
	else
	{
		player_grid[px - 1][py - 1] = world_grid[px - 1][py - 1]; //Upper left
		player_grid[px][py - 1] = world_grid[px][py - 1]; //Up
		player_grid[px + 1][py - 1] = world_grid[px + 1][py - 1]; //Upper right
		player_grid[px - 1][py] = world_grid[px - 1][py]; //Left
		player_grid[px + 1][py] = world_grid[px + 1][py]; //Right
		player_grid[px - 1][py + 1] = world_grid[px - 1][py + 1]; //Lower left
		player_grid[px][py + 1] = world_grid[px][py + 1]; //Down
		player_grid[px + 1][py + 1] = world_grid[px + 1][py + 1]; //Lower right
	}
}

//Displays the entire game world
void game_world::disp_entire_world()
{
	for (int y_ind = 0; y_ind < 5; y_ind++) //Makes the player's board display the entire world
	{
		for (int x_ind = 0; x_ind < 5; x_ind++)
		{
			player_grid[x_ind][y_ind] = world_grid[x_ind][y_ind];
		}
	}
	
	cout << "____________________" << endl;
	for (int y_ind = 0; y_ind < 5; y_ind++)
	{
		cout << "| ";
		for (int x_ind = 0; x_ind < 5; x_ind++)
		{
			cout << player_grid[x_ind][y_ind] << " | ";
		}
		cout << endl;
		cout << "---------------------" << endl;
	}

	score -= 5;
}

//Displays and reveals the game world within the player's range (one square)
void game_world::disp_visible_world()
{
	//Determines the location of the player on the board.
	for (int y_ind = 0; y_ind < 5; y_ind++)
	{
		for (int x_ind = 0; x_ind < 5; x_ind++)
		{
			if (world_grid[x_ind][y_ind] == 'U')
			{
				px = x_ind;
				py = y_ind;
			}
		}
	}
	
	if (px == 0) //If the player's location is at the left vertical edge
	{
		if (py == 0) //Top left
		{
			player_grid[px + 1][py] = world_grid[px + 1][py]; //Right
			player_grid[px][py + 1] = world_grid[px][py + 1]; //Down
			player_grid[px + 1][py + 1] = world_grid[px + 1][py + 1]; //Lower right
		}
		else if (py == 4) //Bottom left
		{
			player_grid[px][py - 1] = world_grid[px][py - 1]; //Up
			player_grid[px + 1][py - 1] = world_grid[px + 1][py - 1]; //Upper right
			player_grid[px + 1][py] = world_grid[px + 1][py]; //Right
		}
		else //Middle left
		{
			player_grid[px][py - 1] = world_grid[px][py - 1]; //Up
			player_grid[px + 1][py - 1] = world_grid[px + 1][py - 1]; //Upper right
			player_grid[px + 1][py] = world_grid[px + 1][py]; //Right
			player_grid[px][py + 1] = world_grid[px][py + 1]; //Down
			player_grid[px + 1][py + 1] = world_grid[px + 1][py + 1]; //Lower right
		}
	}
	else if (px == 4) //If the player's location is at the right vertical edge
	{
		if (py == 0) //Top right
		{
			player_grid[px - 1][py] = world_grid[px - 1][py]; //Left
			player_grid[px - 1][py + 1] = world_grid[px - 1][py + 1]; //Lower left
			player_grid[px][py + 1] = world_grid[px][py + 1]; //Down
		}
		else if (py == 4) //Bottom right
		{
			player_grid[px - 1][py - 1] = world_grid[px - 1][py - 1]; //Upper left
			player_grid[px][py - 1] = world_grid[px][py - 1]; //Up
			player_grid[px - 1][py] = world_grid[px - 1][py]; //Left
		}
		else //Middle right
		{
			player_grid[px - 1][py - 1] = world_grid[px - 1][py - 1]; //Upper left
			player_grid[px][py - 1] = world_grid[px][py - 1]; //Up
			player_grid[px - 1][py] = world_grid[px - 1][py]; //Left
			player_grid[px - 1][py + 1] = world_grid[px - 1][py + 1]; //Lower left
			player_grid[px][py + 1] = world_grid[px][py + 1]; //Down
		}
	}
	else if (py == 0) //If the player's location is somewhere in the top middle
	{
		if (px == 0)
		{
			player_grid[px + 1][py] = world_grid[px + 1][py]; //Right
			player_grid[px][py + 1] = world_grid[px][py + 1]; //Down
			player_grid[px + 1][py + 1] = world_grid[px + 1][py + 1]; //Lower right
		}
		else if (px == 4)
		{
			player_grid[px - 1][py] = world_grid[px - 1][py]; //Left
			player_grid[px - 1][py + 1] = world_grid[px - 1][py + 1]; //Lower left
			player_grid[px][py + 1] = world_grid[px][py + 1]; //Down
		}
		else
		{
			player_grid[px - 1][py] = world_grid[px - 1][py]; //Left
			player_grid[px + 1][py] = world_grid[px + 1][py]; //Right
			player_grid[px - 1][py + 1] = world_grid[px - 1][py + 1]; //Lower left
			player_grid[px][py + 1] = world_grid[px][py + 1]; //Down
			player_grid[px + 1][py + 1] = world_grid[px + 1][py + 1]; //Lower right
		}
	}
	else if (py == 4) //If the player's location is somewhere in the bottom middle
	{
		if (px == 0)
		{
			player_grid[px][py - 1] = world_grid[px][py - 1]; //Up
			player_grid[px + 1][py - 1] = world_grid[px + 1][py - 1]; //Upper right
			player_grid[px + 1][py] = world_grid[px + 1][py]; //Right
		}
		else if (px == 4)
		{
			player_grid[px - 1][py - 1] = world_grid[px - 1][py - 1]; //Upper left
			player_grid[px][py - 1] = world_grid[px][py - 1]; //Up
			player_grid[px - 1][py] = world_grid[px - 1][py]; //Left
		}
		else
		{
			player_grid[px - 1][py - 1] = world_grid[px - 1][py - 1]; //Upper left
			player_grid[px][py - 1] = world_grid[px][py - 1]; //Up
			player_grid[px + 1][py - 1] = world_grid[px + 1][py - 1]; //Upper right
			player_grid[px - 1][py] = world_grid[px - 1][py]; //Left
			player_grid[px + 1][py] = world_grid[px + 1][py]; //Right
		}
	}
	else
	{
		player_grid[px - 1][py - 1] = world_grid[px - 1][py - 1]; //Upper left
		player_grid[px][py - 1] = world_grid[px][py - 1]; //Up
		player_grid[px + 1][py - 1] = world_grid[px + 1][py - 1]; //Upper right
		player_grid[px - 1][py] = world_grid[px - 1][py]; //Left
		player_grid[px + 1][py] = world_grid[px + 1][py]; //Right
		player_grid[px - 1][py + 1] = world_grid[px - 1][py + 1]; //Lower left
		player_grid[px][py + 1] = world_grid[px][py + 1]; //Down
		player_grid[px + 1][py + 1] = world_grid[px + 1][py + 1]; //Lower right
	}

	score -= 2;
}

//Displays the game world that the player can see initially and throughout.
void game_world::disp_player_world()
{
	cout << "____________________" << endl;
	for (int y_ind = 0; y_ind < 5; y_ind++)
	{
		cout << "| ";
		for (int x_ind = 0; x_ind < 5; x_ind++)
		{
			cout << player_grid[x_ind][y_ind] << " | ";
		}
		cout << endl;
		cout << "---------------------" << endl;
	}
}

//Displays the player's final score
void game_world::disp_score()
{
	cout << "[Your score is: " << score << "]" << endl;
}

//Determines the location of the player on the board.
void game_world::find_player()
{
	for (int y_ind = 0; y_ind < 5; y_ind++)
	{
		for (int x_ind = 0; x_ind < 5; x_ind++)
		{
			if (world_grid[x_ind][y_ind] == 'U')
			{
				px = x_ind;
				py = y_ind;
			}
		}
	}
}

//Move up
void game_world::m_up()
{	
	if (py == 0) //Checks if the player is at an edge and stops their movement.
	{
		system("cls");
		disp_player_world();
		cout << endl << "[You are at an edge, you cannot move further.]" << endl;
		system("pause");
		return;
	}
	
	//Checks whether the location the player moved has a pitfall or Wumpus.
	if (world_grid[px][py - 1] == 'W' || world_grid[px][py - 1] == 'P') //If the player walks into a Pitfall or the Wumpus
	{
		world_grid[px][py - 1] = 'X';
		world_grid[px][py] = '-';
		player_state = 'X';
		score += 5;
	}
	else if (world_grid[px][py - 1] == 'G') //If the player walks into the Gold
	{
		world_grid[px][py - 1] = '!';
		world_grid[px][py] = '-';
		game_state = 1;
		score += 5;
	}
	else //If they run into nothing
	{
		world_grid[px][py - 1] = 'U';
		world_grid[px][py] = '-';
		player_grid[px][py - 1] = 'U';
		player_grid[px][py] = '-';
		score += 5;
	}
}

//Move down
void game_world::m_down()
{
	if (py == 4) //Checks if the player is at an edge and stops their movement.
	{
		system("cls");
		disp_player_world();
		cout << endl << "[You are at an edge, you cannot move further.]" << endl;
		system("pause");
		return;
	}
	
	//Checks whether the location the player moved has a pitfall or Wumpus.
	if (world_grid[px][py + 1] == 'W' || world_grid[px][py + 1] == 'P') //If the player walks into a Pitfall or the Wumpus
	{
		world_grid[px][py + 1] = 'X';
		world_grid[px][py] = '-';
		player_state = 'X';
		score += 5;
	}
	else if (world_grid[px][py + 1] == 'G') //If the player walks into the Gold
	{
		world_grid[px][py + 1] = '!';
		world_grid[px][py] = '-';
		game_state = 1;
		score += 5;
	}
	else //If they run into nothing
	{
		world_grid[px][py + 1] = 'U';
		world_grid[px][py] = '-';
		player_grid[px][py + 1] = 'U';
		player_grid[px][py] = '-';
		score += 5;
	}
}

//Move left
void game_world::m_left()
{
	if (px == 0) //Checks if the player is at an edge and stops their movement.
	{
		system("cls");
		disp_player_world();
		cout << endl << "[You are at an edge, you cannot move further.]" << endl;
		system("pause");
		return;
	}
	
	//Checks whether the location the player moved has a pitfall or Wumpus.
	if (world_grid[px - 1][py] == 'W' || world_grid[px - 1][py] == 'P') //If the player walks into a Pitfall or the Wumpus
	{
		world_grid[px - 1][py] = 'X';
		world_grid[px][py] = '-';
		player_state = 'X';
		score += 5;
	}
	else if (world_grid[px - 1][py] == 'G') //If the player walks into the Gold
	{
		world_grid[px - 1][py] = '!';
		world_grid[px][py] = '-';
		game_state = 1;
		score += 5;
	}
	else //If they run into nothing
	{
		world_grid[px - 1][py] = 'U';
		world_grid[px][py] = '-';
		player_grid[px - 1][py] = 'U';
		player_grid[px][py] = '-';
		score += 5;
	}
}

//Move right
void game_world::m_right()
{
	if (px == 4) //Checks if the player is at an edge and stops their movement.
	{
		system("cls");
		disp_player_world();
		cout << endl << "[You are at an edge, you cannot move further.]" << endl;
		system("pause");
		return;
	}
	
	//Checks whether the location the player moved has a pitfall or Wumpus.
	if (world_grid[px + 1][py] == 'W' || world_grid[px + 1][py] == 'P') //If the player walks into a Pitfall or the Wumpus
	{
		world_grid[px + 1][py] = 'X';
		world_grid[px][py] = '-';
		player_state = 'X';
		score += 5;
	}
	else if (world_grid[px + 1][py] == 'G') //If the player walks into the Gold
	{
		world_grid[px + 1][py] = '!';
		world_grid[px][py] = '-';
		game_state = 1;
		score += 5;
	}
	else //If they run into nothing
	{
		world_grid[px + 1][py] = 'U';
		world_grid[px][py] = '-';
		player_grid[px + 1][py] = 'U';
		player_grid[px][py] = '-';
		score += 5;
	}
}

//Determines if the player has won or not
bool game_world::win_or_lose()
{
	if (game_state == 1) //If game is won
		return true;
	else //If game is lost/havent been won
		return false;
}

//Determines if the player is dead or still alive
bool game_world::DoA()
{
	if (player_state == 'X') // If player is dead
		return false;
	else //If player is alive
		return true;
}

//Overloaded operator
ostream& operator << (ostream& outfile, const game_world& G)
{
	outfile << "The Player's score was: " << G.score;

	return outfile;
}
