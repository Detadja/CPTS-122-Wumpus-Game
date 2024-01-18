#include "header.h"

int main()
{
	game_world game;
	ofstream score("game_scores.txt", ios::out);

	int choice = 0;

	do
	{
		disp_game();
		cin >> choice;

		while (choice > 3 || choice < 1) //Checks for invallid input
		{
			system("cls");
			err_msg();
			disp_game();
			cin >> choice;
		}
		
		switch (choice)
		{
		case 1: //Play the game
		{
			system("cls");
			srand((unsigned int)time(nullptr));
			cout << "[Generating world...]\n";
			game.intialize_game_world();
			cout << "[World generated.]\n\n";
			system("pause");

			char move = '\0';
			while (game.DoA()) //As long as the player is still alive.
			{
				system("cls");
				game.find_player();
				game.disp_player_world();
				cout << endl << "[Which direction do you want to move?]" << endl;
				cout << "[I - Up]\n" << "[K - Down]\n" << "[J - Left]\n" << "[L - Right]\n\n";
				cout << "[Alternatively, enter 'O' for additional options.]" << endl;
				cin >> move;

				//Checks for invalid input
				while (move != 'i' && move != 'I' && move != 'k' && move != 'K' && move != 'j' && move != 'J' && move != 'l' && move != 'L' 
					&& move != 'o' && move != 'O')
				{
					system("cls");
					err_msg();
					char move = '\0';
					game.find_player();
					game.disp_player_world();
					cout << endl << "[Which direction do you want to move?]" << endl;
					cout << "[I - Up]\n" << "[K - Down]\n" << "[J - Left]\n" << "[L - Right]\n\n";
					cout << "[Alternatively, enter 'O' for additional options.]" << endl;
					cin >> move;
				}

				if (move == 'o' || move == 'O')
				{
					system("cls");
					game.disp_player_world();
					cout << endl << "[V - See one square past yours]\n" << "[C - See the entire game world (cheat)]\n";
					cout << "[R - Restart the game with a different board (use when stuck)]\n" << "[N - Restart the whole game for a new player]\n";
					cout << "[Q - End current game]\n\n";
					cin >> move;

					//Checks for invalid input
					while (move != 'v' && move != 'V' && move != 'c' && move != 'C' && move != 'r' && move != 'R' && move != 'n' && move != 'N' 
						&& move != 'q' && move != 'Q')
					{
						system("cls");
						err_msg();
						game.disp_player_world();
						cout << endl << "[V - See one square past yours]\n" << "[C - See the entire game world (cheat)]\n";
						cout << "[R - Restart the game with a different board (use when stuck)]\n" << "[N - Restart the whole game for a new player]\n";
						cout << "[Q - End current game]\n\n";
						cin >> move;
					}

					if (move == 'v') //View one square past
					{
						game.disp_visible_world();
					}
					else if (move == 'c') //Cheat/display world
					{
						game.disp_entire_world();
					}
					else if (move == 'r') //Reset game with same player, different board
					{
						game.intialize_game_world();
					}
					else if (move == 'n') //Reset entire game with different player
					{
						system("cls");
						cout << "[Are you sure? (Y/N)]" << endl;
						cin >> move;
						while (move != 'y' && move != 'Y' && move != 'n' && move != 'N') //Checks for invalid input
						{
							system("cls");
							err_msg();
							cout << "[I ask again, are you sure? (Y/N)]" << endl;
							cin >> move;
						}

						if (move == 'y' || move == 'Y') //If the new player is sure
						{
							system("cls");
							game.disp_score();
							cout << endl;
							score << game;
							system("pause");
							system("cls");
							
							cout << "[Preparing for new player...]" << endl;
							system("pause");
							system("cls");
							game = game_world();
							break;
						}

						system("cls");
						cout << "[Game continuing...]" << endl;
						system("pause");
						system("cls");
					}
					else //Quit game
					{
						system("cls");
						cout << "[Are you sure? (Y/N)]" << endl;
						cin >> move;
						while (move != 'y' && move != 'Y' && move != 'n' && move != 'N') //Checks for invalid input
						{
							system("cls");
							err_msg();
							cout << "[I ask again, are you sure? (Y/N)]" << endl;
							cin >> move;
						}

						if (move == 'y' || move == 'Y') //If the player is sure
						{
							system("cls");
							game.disp_score();
							cout << endl;
							score << game;
							system("pause");
							
							choice = 4;
							break;
						}

						system("cls");
						cout << "[Game continuing...]" << endl;
						system("pause");
						system("cls");
					}
				}
				else if (move == 'i' || move == 'I') //Move up
				{
					game.m_up();
				}
				else if (move == 'k' || move == 'K') //Move down
				{
					game.m_down();
				}
				else if (move == 'j' || move == 'J') //Move left
				{
					game.m_left();
				}
				else //Move right
				{
					game.m_right();
				}

				if (game.win_or_lose()) //If player wins by getting the gold.
				{
					system("cls");
					cout << "[Congratulations! You have won!]" << endl; 
					game.disp_score();
					score << game;
					cout << "[This is what the world looked like:]" << endl;
					game.disp_entire_world();
					system("pause");
					system("cls");
					cout << "[Would you like to play again? (Y/N)]" << endl;
					cin >> move;

					while (move != 'y' && move != 'Y' && move != 'n' && move != 'N') //Checks for invalid input
					{
						system("cls");
						err_msg();
						cout << "[Would you like to play again? (Y/N)]" << endl;
						cin >> move;
					}

					if (move == 'y' || move == 'Y')
					{
						system("cls");
						game = game_world();
					}
					else
					{
						choice = 4;
					}
					break;
				}
				else if (!game.win_or_lose() && !game.DoA()) //If the player loses by dying.
				{
					system("cls");
					cout << "[Unfortunately, you have lost the game.]" << endl;
					game.disp_score();
					score << game;
					cout << "[This is what the world looked like:]" << endl;
					game.disp_entire_world();
					system("pause");
					system("cls");
					cout << "[Would you like to play again? (Y/N)]" << endl;
					cin >> move;

					while (move != 'y' && move != 'Y' && move != 'n' && move != 'N') //Checks for invalid input
					{
						system("cls");
						err_msg();
						cout << "[Would you like to play again? (Y/N)]" << endl;
						cin >> move;
					}

					if (move == 'y' || move == 'Y')
					{
						system("cls");
						game = game_world();
					}
					else
					{
						choice = 4;
					}
					break;
				}
			}	
		}
		break;
		case 2: //Display the rules
		{
			system("cls");
			disp_rules();
			system("pause");
			system("cls");
		}
		break;
		case 3: //Exit
		{
			choice = 4;
		}
		break;
		}
	} while (choice > 0 && choice < 4);

	score.close();
	system("cls");
	cout << "[Thank you for playing!]" << endl;

	return 0;
}