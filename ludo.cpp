#include "raylib.h"
#include <iostream>
#include <math.h>
#include <time.h>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <cstdint>

#include "token.cpp"

using namespace std;

// global variables
string currentTurn[4] = {"Red", "Green", "Yellow", "Blue"};
int currentTurnIndex = -1;
bool newTurn = true;
int totalTokens = 0;
int keypressed;
int absolutePosCoordinates[52][2];
bool player_done[4] = {false};
string names[4];
int dice;
int dice2 = 0;
int dice3 = 0;

void killGoti(string, int);

struct House
{
	string color;
	int tokensRemaining; // gootiyan jo rehti hain
	int endHousePosition[5][2];
	int tokensStuck; // Those stuck inside house
	Token *tokens;
	int startHouseCoordinates[4][2];
	int hitrate;
	int position;

	House() // constructor sceenezz
	{
		hitrate = 0;
		tokensRemaining = totalTokens;
		tokensStuck = totalTokens;
		position = 0;
	}

	void setColor(string c)
	{
		tokensRemaining = totalTokens;
		tokensStuck = totalTokens;
		tokens = new Token[totalTokens];
		color = c;

		if (color == "Green")
		{
			for (int i = 0; i < totalTokens; i++)
			{
				tokens[i].setPosition(0);
			}

			startHouseCoordinates[0][0] = 125; // first 0 = 0th piece, 2nd 0 = x coordinate
			startHouseCoordinates[0][1] = 125; // 1 here = y coordinate

			startHouseCoordinates[1][0] = 225;
			startHouseCoordinates[1][1] = 125;

			startHouseCoordinates[2][0] = 125;
			startHouseCoordinates[2][1] = 225;

			startHouseCoordinates[3][0] = 225;
			startHouseCoordinates[3][1] = 225;

			// Setting the x and y coordinates of the tokens
			tokens[0].xCoordinates = startHouseCoordinates[0][0];
			tokens[0].yCoordinates = startHouseCoordinates[0][1];

			if (totalTokens > 1)
			{
				tokens[1].xCoordinates = startHouseCoordinates[1][0];
				tokens[1].yCoordinates = startHouseCoordinates[1][1];
			}

			if (totalTokens > 2)
			{
				tokens[2].xCoordinates = startHouseCoordinates[2][0];
				tokens[2].yCoordinates = startHouseCoordinates[2][1];
			}

			if (totalTokens > 3)
			{
				tokens[3].xCoordinates = startHouseCoordinates[3][0];
				tokens[3].yCoordinates = startHouseCoordinates[3][1];
			}
		}
		else if (color == "Red")
		{

			for (int i = 0; i < totalTokens; i++)
			{

				tokens[i].setPosition(13);
			}

			startHouseCoordinates[0][0] = 575; // first 0 = 0th piece, 2nd 0 = x coordinate
			startHouseCoordinates[0][1] = 125; // 1 here = y coordinate

			startHouseCoordinates[1][0] = 675;
			startHouseCoordinates[1][1] = 125;

			startHouseCoordinates[2][0] = 575;
			startHouseCoordinates[2][1] = 225;

			startHouseCoordinates[3][0] = 675;
			startHouseCoordinates[3][1] = 225;

			tokens[0].xCoordinates = startHouseCoordinates[0][0];
			tokens[0].yCoordinates = startHouseCoordinates[0][1];

			if (totalTokens > 1)
			{
				tokens[1].xCoordinates = startHouseCoordinates[1][0];
				tokens[1].yCoordinates = startHouseCoordinates[1][1];
			}

			if (totalTokens > 2)
			{
				tokens[2].xCoordinates = startHouseCoordinates[2][0];
				tokens[2].yCoordinates = startHouseCoordinates[2][1];
			}

			if (totalTokens > 3)
			{
				tokens[3].xCoordinates = startHouseCoordinates[3][0];
				tokens[3].yCoordinates = startHouseCoordinates[3][1];
			}
		}
		else if (color == "Blue")
		{

			for (int i = 0; i < totalTokens; i++)
			{

				tokens[i].setPosition(26);
			}

			startHouseCoordinates[0][0] = 575; // first 0 = 0th piece, 2nd 0 = x coordinate
			startHouseCoordinates[0][1] = 575; // 1 here = y coordinate

			startHouseCoordinates[1][0] = 675;
			startHouseCoordinates[1][1] = 575;

			startHouseCoordinates[2][0] = 575;
			startHouseCoordinates[2][1] = 675;

			startHouseCoordinates[3][0] = 675;
			startHouseCoordinates[3][1] = 675;

			tokens[0].xCoordinates = startHouseCoordinates[0][0];
			tokens[0].yCoordinates = startHouseCoordinates[0][1];

			if (totalTokens > 1)
			{
				tokens[1].xCoordinates = startHouseCoordinates[1][0];
				tokens[1].yCoordinates = startHouseCoordinates[1][1];
			}

			if (totalTokens > 2)
			{
				tokens[2].xCoordinates = startHouseCoordinates[2][0];
				tokens[2].yCoordinates = startHouseCoordinates[2][1];
			}

			if (totalTokens > 3)
			{
				tokens[3].xCoordinates = startHouseCoordinates[3][0];
				tokens[3].yCoordinates = startHouseCoordinates[3][1];
			}
		}
		else if (color == "Yellow")
		{

			for (int i = 0; i < totalTokens; i++)
			{

				tokens[i].setPosition(39);
			}

			startHouseCoordinates[0][0] = 125; // first 0 = 0th piece, 2nd 0 = x coordinate
			startHouseCoordinates[0][1] = 575; // 1 here = y coordinate

			startHouseCoordinates[1][0] = 225;
			startHouseCoordinates[1][1] = 575;

			startHouseCoordinates[2][0] = 125;
			startHouseCoordinates[2][1] = 675;

			startHouseCoordinates[3][0] = 225;
			startHouseCoordinates[3][1] = 675;

			tokens[0].xCoordinates = startHouseCoordinates[0][0];
			tokens[0].yCoordinates = startHouseCoordinates[0][1];

			if (totalTokens > 1)
			{
				tokens[1].xCoordinates = startHouseCoordinates[1][0];
				tokens[1].yCoordinates = startHouseCoordinates[1][1];
			}

			if (totalTokens > 2)
			{
				tokens[2].xCoordinates = startHouseCoordinates[2][0];
				tokens[2].yCoordinates = startHouseCoordinates[2][1];
			}

			if (totalTokens > 3)
			{
				tokens[3].xCoordinates = startHouseCoordinates[3][0];
				tokens[3].yCoordinates = startHouseCoordinates[3][1];
			}
		}
	}

	string getColor()
	{
		return color;
	}

	void moveGoti(int key)
	{
		if (dice == 6 && dice2 == 6 && dice3 == 6) // three times the player got 6
		{
			dice = 0;
			dice2 = 0;
			dice3 = 0;
			newTurn = true;
			return;
		}

		if (dice)
		{
			if (tokens[key].free == false && dice == 6 && tokens[key].ended == false) // goti in home + 6 + not ended
			{

				tokensStuck--;
				tokens[key].setFree(true);

				//0 for green house 13 for red house 26 for blue house 39 for yellow house
				if (color == "Green")
				{ // 50
					tokens[key].position = 0;
					tokens[key].xCoordinates = absolutePosCoordinates[0][0] + 25;
					tokens[key].yCoordinates = absolutePosCoordinates[0][1] + 25;
				}
				else if (color == "Red")
				{ // 11
					tokens[key].position = 13;
					tokens[key].xCoordinates = absolutePosCoordinates[13][0] + 25;
					tokens[key].yCoordinates = absolutePosCoordinates[13][1] + 25;
				}
				else if (color == "Blue")
				{ // 24
					tokens[key].position = 26;
					tokens[key].xCoordinates = absolutePosCoordinates[26][0] + 25;
					tokens[key].yCoordinates = absolutePosCoordinates[26][1] + 25;
				}
				else if (color == "Yellow")
				{ // 37
					tokens[key].position = 39;
					tokens[key].xCoordinates = absolutePosCoordinates[39][0] + 25;
					tokens[key].yCoordinates = absolutePosCoordinates[39][1] + 25;
				}
				dice = 0;
			}


			else if (tokens[key].free && tokens[key].ended == false) // goti can move
			{

				tokens[key].position += dice;
				tokens[key].iterator += dice;

				// goti inside the safe house
				if (tokens[key].iterator > 50 && this->hitrate > 0)
				{
					tokens[key].insideSafeHouse = true;
				}

				// go back if no kill
				else if (this->hitrate == 0 && tokens[key].iterator > 51)
				{

					tokens[key].iterator = tokens[key].iterator % 52;
				}

				killGoti(color, key);

				// gooti goes to house
				if (tokens[key].iterator >= 51 && this->hitrate > 0)
				{

					if (tokens[key].iterator == 56)
					{
						tokens[key].free = false;
						tokens[key].ended = true;
						tokensRemaining--;
						tokens[key].xCoordinates = 3000;
						tokens[key].yCoordinates = 3000;
					}
					else if (tokens[key].iterator > 56) // move back the gooti cuz u didnt get the right number	
					{
						tokens[key].iterator -= dice;
					}
					else
					{
						// set the cords
						tokens[key].xCoordinates = endHousePosition[tokens[key].iterator % 51][0] + 25;
						tokens[key].yCoordinates = endHousePosition[tokens[key].iterator % 51][1] + 25;
					}
				}

				// normal move the gooti 
				else
				{
					// set the cords
					tokens[key].xCoordinates = absolutePosCoordinates[tokens[key].position % 52][0] + 25;
					tokens[key].yCoordinates = absolutePosCoordinates[tokens[key].position % 52][1] + 25;
				}
				dice = 0;
			}
		}

		// same thing what happened to dice
		else if (dice2)
		{
			if (tokens[key].free == false && dice2 == 6 && tokens[key].ended == false)
			{
				tokensStuck--;
				tokens[key].setFree(true);

				if (color == "Green")
				{ // 50
					tokens[key].position = 0;
					tokens[key].xCoordinates = absolutePosCoordinates[0][0] + 25;
					tokens[key].yCoordinates = absolutePosCoordinates[0][1] + 25;
				}
				else if (color == "Red")
				{ // 11
					tokens[key].position = 13;
					tokens[key].xCoordinates = absolutePosCoordinates[13][0] + 25;
					tokens[key].yCoordinates = absolutePosCoordinates[13][1] + 25;
				}
				else if (color == "Blue")
				{ // 24
					tokens[key].position = 26;
					tokens[key].xCoordinates = absolutePosCoordinates[26][0] + 25;
					tokens[key].yCoordinates = absolutePosCoordinates[26][1] + 25;
				}
				else if (color == "Yellow")
				{ // 37
					tokens[key].position = 39;
					tokens[key].xCoordinates = absolutePosCoordinates[39][0] + 25;
					tokens[key].yCoordinates = absolutePosCoordinates[39][1] + 25;
				}
				dice2 = 0;
			}
			else if (tokens[key].free && tokens[key].ended == false)
			{
				tokens[key].position += dice2;
				tokens[key].iterator += dice2;

				if (tokens[key].iterator > 50 && this->hitrate > 0)
				{
					tokens[key].insideSafeHouse = true;
				}

				else if (this->hitrate == 0 && tokens[key].iterator > 51)
				{
					tokens[key].iterator = tokens[key].iterator % 52;
				}

				killGoti(color, key);

				if (tokens[key].iterator >= 51 && this->hitrate > 0)
				{
					if (tokens[key].iterator == 56)
					{
						tokens[key].ended = true;
						tokensRemaining--;

						tokens[key].xCoordinates = 3000;
						tokens[key].yCoordinates = 3000;
					}

					else if (tokens[key].iterator > 56)
					{
						tokens[key].iterator -= dice2;
					}

					else
					{
						tokens[key].xCoordinates = endHousePosition[tokens[key].iterator % 51][0] + 25;
						tokens[key].yCoordinates = endHousePosition[tokens[key].iterator % 51][1] + 25;
					}
				}

				else
				{
					tokens[key].xCoordinates = absolutePosCoordinates[tokens[key].position % 52][0] + 25;
					tokens[key].yCoordinates = absolutePosCoordinates[tokens[key].position % 52][1] + 25;
				}
				dice2 = 0;
			}
		}

		// same thing as dice2
		else if (dice3)
		{
			if (dice3 == 6)
			{
				return;
			}

			if (tokens[key].free && tokens[key].ended == false && tokens[key].ended == false)
			{
				tokens[key].position += dice3;
				tokens[key].iterator += dice3;

				if (tokens[key].iterator > 50 && this->hitrate > 0)
				{
					tokens[key].insideSafeHouse = true;
				}

				else if (this->hitrate == 0 && tokens[key].iterator > 51)
				{
					tokens[key].iterator = tokens[key].iterator % 52;
				}

				killGoti(color, key);

				if (tokens[key].iterator >= 51 && this->hitrate > 0)
				{
					tokens[key].insideSafeHouse = true;

					if (tokens[key].iterator == 56) // goti is done and dusted
					{
						tokens[key].free = false;
						tokens[key].ended = true;
						tokensRemaining--;
						tokens[key].xCoordinates = 3000;
						tokens[key].yCoordinates = 3000;
					}
					
					else if (tokens[key].iterator > 56)
					{
						tokens[key].iterator -= dice3;
					}
					
					else
					{
						tokens[key].xCoordinates = endHousePosition[tokens[key].iterator % 51][0] + 25;
						tokens[key].yCoordinates = endHousePosition[tokens[key].iterator % 51][1] + 25;
					}
				}

				else
				{
					tokens[key].xCoordinates = absolutePosCoordinates[tokens[key].position % 52][0] + 25;
					tokens[key].yCoordinates = absolutePosCoordinates[tokens[key].position % 52][1] + 25;
				}
				dice3 = 0;
			}
		}
	}
};

// all of the hosues global e
House allHouses[4];

void absolutePosition_init()
{
	// Absolute Pos 0 = Start of Green

	// 0 - 5 of green path
	for (int i = 0, j = 75; i < 5; i++, j += 50)
	{
		absolutePosCoordinates[i][0] = j;
		absolutePosCoordinates[i][1] = 325;
	}

	// 5-10 of red path
	for (int i = 5, j = 275; i < 11; i++, j -= 50)
	{
		absolutePosCoordinates[i][0] = 325;
		absolutePosCoordinates[i][1] = j;
	}

	// 11 in red
	absolutePosCoordinates[11][0] = 375;
	absolutePosCoordinates[11][1] = 25;

	// 12-17 in red
	for (int i = 12, j = 25; i < 18; i++, j += 50)
	{
		absolutePosCoordinates[i][0] = 425;
		absolutePosCoordinates[i][1] = j;
	}

	// 18-23 in blue
	for (int i = 18, j = 475; i < 24; i++, j += 50)
	{
		absolutePosCoordinates[i][0] = j;
		absolutePosCoordinates[i][1] = 325;
	}

	// 24 in blue
	absolutePosCoordinates[24][0] = 725;
	absolutePosCoordinates[24][1] = 375;

	// 25 - 30 in blue
	for (int i = 25, j = 725; i < 31; i++, j -= 50)
	{
		absolutePosCoordinates[i][0] = j;
		absolutePosCoordinates[i][1] = 425;
	}

	// 31 - 36 in yellow
	for (int i = 31, j = 475; i < 37; i++, j += 50)
	{
		absolutePosCoordinates[i][0] = 425;
		absolutePosCoordinates[i][1] = j;
	}

	// 37 in yellow
	absolutePosCoordinates[37][0] = 375;
	absolutePosCoordinates[37][1] = 725;

	// 38-43 in yellow
	for (int i = 38, j = 725; i < 44; i++, j -= 50)
	{
		absolutePosCoordinates[i][0] = 325;
		absolutePosCoordinates[i][1] = j;
	}

	// 44 - 49 in green
	for (int i = 44, j = 275; i < 50; i++, j -= 50)
	{
		absolutePosCoordinates[i][0] = j;
		absolutePosCoordinates[i][1] = 425;
	}

	// 50 in green
	absolutePosCoordinates[50][0] = 25;
	absolutePosCoordinates[50][1] = 375;

	// 51 in green
	absolutePosCoordinates[51][0] = 25;
	absolutePosCoordinates[51][1] = 325;

	// relative coordinates of green house
	for (int i = 0, j = 75; i < 5; i++, j += 50)
	{

		// x=75 constant height = 375
		allHouses[1].endHousePosition[i][0] = j;
		allHouses[1].endHousePosition[i][1] = 375;
	}

	// relative coordinates of red house
	for (int i = 0, j = 75; i < 5; i++, j += 50)
	{

		// constant width = 375 height = 75
		allHouses[0].endHousePosition[i][0] = 375;
		allHouses[0].endHousePosition[i][1] = j;
	}

	// relative coordinates of blue house
	for (int i = 0, j = 675; i < 5; i++, j -= 50)
	{

		// x = 675 constant height = 375
		allHouses[3].endHousePosition[i][0] = j;
		allHouses[3].endHousePosition[i][1] = 375;
	}

	// relative coordinates of yellow house
	for (int i = 0, j = 675; i < 5; i++, j -= 50)
	{

		// constant width = 375 constant height = 375
		allHouses[2].endHousePosition[i][0] = 375;
		allHouses[2].endHousePosition[i][1] = j;
	}
}

void drawBoard()
{

	// Houses
	DrawRectangle(25, 25, 300, 300, GREEN);
	DrawRectangle(475, 25, 300, 300, RED);
	DrawRectangle(25, 475, 300, 300, YELLOW);
	DrawRectangle(475, 475, 300, 300, BLUE);

	// Center
	// Center
	Vector2 x1, y1, z1;
	x1.x = 325;
	x1.y = 325;
	y1.x = 400;
	y1.y = 400;
	z1.x = 325;
	z1.y = 475;
	DrawTriangle(z1, y1, x1, GREEN);
	x1.x = 325;
	x1.y = 325;
	y1.x = 400;
	y1.y = 400;
	z1.x = 475;
	z1.y = 325;
	DrawTriangle(x1, y1, z1, RED);
	x1.x = 475;
	x1.y = 325;
	y1.x = 400;
	y1.y = 400;
	z1.x = 475;
	z1.y = 475;
	DrawTriangle(x1, y1, z1, BLUE);
	x1.x = 325;
	x1.y = 475;
	y1.x = 400;
	y1.y = 400;
	z1.x = 475;
	z1.y = 475;
	DrawTriangle(z1, y1, x1, YELLOW);

	// House Special Tiles
	// Red House
				//safe house
	for (int i = 75; i < 325; i += 50)
	{
		DrawRectangle(375, i, 50, 50, RED);
	}

	//safe spot
	DrawRectangle(325, 125, 50, 50, RED);
	DrawRectangle(425, 75, 50, 50, RED);

	// Blue House
				//safe house
	for (int i = 475; i < 725; i += 50)
	{
		DrawRectangle(i, 375, 50, 50, BLUE);
	}

	//safe spot
	DrawRectangle(625, 325, 50, 50, BLUE);
	DrawRectangle(675, 425, 50, 50, BLUE);

	// Yellow House
					//safe house
	for (int i = 475; i < 725; i += 50)
	{
		DrawRectangle(375, i, 50, 50, YELLOW);
	}

	//safe spot
	DrawRectangle(425, 625, 50, 50, YELLOW);
	DrawRectangle(325, 675, 50, 50, YELLOW);

	// Green House
				//safe house
	for (int i = 75; i < 300; i += 50)
	{
		DrawRectangle(i, 375, 50, 50, GREEN);
	}

	//safe spot
	DrawRectangle(125, 425, 50, 50, GREEN);
	DrawRectangle(75, 325, 50, 50, GREEN);

	// Grid
	// Red House
	for (int i = 25; i < 350; i += 50)
	{
		DrawLine(325, i, 475, i, BLACK); // Horizontal Lines
	}
	for (int i = 325; i < 480; i += 50)
	{
		DrawLine(i, 25, i, 325, BLACK); // Vertical Lines`
	}

	// Blue House
	for (int i = 325; i < 480; i += 50)
	{
		DrawLine(25, i, 325, i, BLACK); // Horizontal Lines
	}
	for (int i = 25; i < 330; i += 50)
	{
		DrawLine(i, 325, i, 475, BLACK); // Vertical Lines
	}

	// Yellow House
	for (int i = 475; i < 780; i += 50)
	{
		DrawLine(325, i, 475, i, BLACK); // Horizontal Lines
	}
	for (int i = 325; i < 480; i += 50)
	{
		DrawLine(i, 475, i, 775, BLACK); // Vertical Lines
	}

	// Green house
	for (int i = 325; i < 480; i += 50)
	{
		DrawLine(475, i, 775, i, BLACK); // Horizontal Lines
	}
	for (int i = 475; i < 780; i += 50)
	{
		DrawLine(i, 325, i, 475, BLACK); // Vertical Lines
	}
}

void drawPieces()
{

	int outline = 22;
	int inner = 18;
	
	// Draw the pieces in the house
	DrawCircle(allHouses[1].tokens[0].xCoordinates, allHouses[1].tokens[0].yCoordinates, outline, RAYWHITE); // Background (White)
	DrawCircle(allHouses[1].tokens[0].xCoordinates, allHouses[1].tokens[0].yCoordinates, inner, GREEN);		 // Actual Color
	DrawText("1", allHouses[1].tokens[0].xCoordinates - 3, allHouses[1].tokens[0].yCoordinates - 8, 20, BLACK);

	DrawCircle(allHouses[0].tokens[0].xCoordinates, allHouses[0].tokens[0].yCoordinates, outline, RAYWHITE); // Background (White)
	DrawCircle(allHouses[0].tokens[0].xCoordinates, allHouses[0].tokens[0].yCoordinates, inner, RED);		 // Actual Color
	DrawText("1", allHouses[0].tokens[0].xCoordinates - 3, allHouses[0].tokens[0].yCoordinates - 8, 20, BLACK);

	DrawCircle(allHouses[2].tokens[0].xCoordinates, allHouses[2].tokens[0].yCoordinates, outline, RAYWHITE); // Background (White)
	DrawCircle(allHouses[2].tokens[0].xCoordinates, allHouses[2].tokens[0].yCoordinates, inner, YELLOW);	 // Actual Color
	DrawText("1", allHouses[2].tokens[0].xCoordinates - 3, allHouses[2].tokens[0].yCoordinates - 8, 20, BLACK);

	DrawCircle(allHouses[3].tokens[0].xCoordinates, allHouses[3].tokens[0].yCoordinates, outline, RAYWHITE); // Background (White)
	DrawCircle(allHouses[3].tokens[0].xCoordinates, allHouses[3].tokens[0].yCoordinates, inner, BLUE);		 // Actual Color
	DrawText("1", allHouses[3].tokens[0].xCoordinates - 3, allHouses[3].tokens[0].yCoordinates - 8, 20, BLACK);

	if (totalTokens > 1)
	{
		DrawCircle(allHouses[1].tokens[1].xCoordinates, allHouses[1].tokens[1].yCoordinates, outline, RAYWHITE);    // Background (White)
		DrawCircle(allHouses[1].tokens[1].xCoordinates, allHouses[1].tokens[1].yCoordinates, inner, GREEN);         // Actual Color
		DrawText("2", allHouses[1].tokens[1].xCoordinates - 3, allHouses[1].tokens[1].yCoordinates - 8, 20, BLACK);

		DrawCircle(allHouses[0].tokens[1].xCoordinates, allHouses[0].tokens[1].yCoordinates, outline, RAYWHITE);   // Background (White)
		DrawCircle(allHouses[0].tokens[1].xCoordinates, allHouses[0].tokens[1].yCoordinates, inner, RED);         // Actual Color
		DrawText("2", allHouses[0].tokens[1].xCoordinates - 3, allHouses[0].tokens[1].yCoordinates - 8, 20, BLACK);

		DrawCircle(allHouses[2].tokens[1].xCoordinates, allHouses[2].tokens[1].yCoordinates, outline, RAYWHITE);  // Background (White)
		DrawCircle(allHouses[2].tokens[1].xCoordinates, allHouses[2].tokens[1].yCoordinates, inner, YELLOW);      // Actual Color
		DrawText("2", allHouses[2].tokens[1].xCoordinates - 3, allHouses[2].tokens[1].yCoordinates - 8, 20, BLACK);

		DrawCircle(allHouses[3].tokens[1].xCoordinates, allHouses[3].tokens[1].yCoordinates, outline, RAYWHITE);   // Background (White)
		DrawCircle(allHouses[3].tokens[1].xCoordinates, allHouses[3].tokens[1].yCoordinates, inner, BLUE);         // Actual Color
		DrawText("2", allHouses[3].tokens[1].xCoordinates - 3, allHouses[3].tokens[1].yCoordinates - 8, 20, BLACK);
	}

	if (totalTokens > 2)
	{
		DrawCircle(allHouses[1].tokens[2].xCoordinates, allHouses[1].tokens[2].yCoordinates, outline, RAYWHITE); // Background (White)
		DrawCircle(allHouses[1].tokens[2].xCoordinates, allHouses[1].tokens[2].yCoordinates, inner, GREEN);		 // Actual Color
		DrawText("3", allHouses[1].tokens[2].xCoordinates - 3, allHouses[1].tokens[2].yCoordinates - 8, 20, BLACK);

		DrawCircle(allHouses[0].tokens[2].xCoordinates, allHouses[0].tokens[2].yCoordinates, outline, RAYWHITE); // Background (White)
		DrawCircle(allHouses[0].tokens[2].xCoordinates, allHouses[0].tokens[2].yCoordinates, inner, RED);		 // Actual Color
		DrawText("3", allHouses[0].tokens[2].xCoordinates - 3, allHouses[0].tokens[2].yCoordinates - 8, 20, BLACK);

		DrawCircle(allHouses[2].tokens[2].xCoordinates, allHouses[2].tokens[2].yCoordinates, outline, RAYWHITE); // Background (White)
		DrawCircle(allHouses[2].tokens[2].xCoordinates, allHouses[2].tokens[2].yCoordinates, inner, YELLOW);	 // Actual Color
		DrawText("3", allHouses[2].tokens[2].xCoordinates - 3, allHouses[2].tokens[2].yCoordinates - 8, 20, BLACK);

		DrawCircle(allHouses[3].tokens[2].xCoordinates, allHouses[3].tokens[2].yCoordinates, outline, RAYWHITE); // Background (White)
		DrawCircle(allHouses[3].tokens[2].xCoordinates, allHouses[3].tokens[2].yCoordinates, inner, BLUE);		 // Actual Color
		DrawText("3", allHouses[3].tokens[2].xCoordinates - 3, allHouses[3].tokens[2].yCoordinates - 8, 20, BLACK);
	}

	if (totalTokens > 3)
	{
		DrawCircle(allHouses[1].tokens[3].xCoordinates, allHouses[1].tokens[3].yCoordinates, outline, RAYWHITE);   // Background (White)
		DrawCircle(allHouses[1].tokens[3].xCoordinates, allHouses[1].tokens[3].yCoordinates, inner, GREEN);        // Actual Color
		DrawText("4", allHouses[1].tokens[3].xCoordinates - 3, allHouses[1].tokens[3].yCoordinates - 8, 20, BLACK);

		DrawCircle(allHouses[0].tokens[3].xCoordinates, allHouses[0].tokens[3].yCoordinates, outline, RAYWHITE);   // Background (White)
		DrawCircle(allHouses[0].tokens[3].xCoordinates, allHouses[0].tokens[3].yCoordinates, inner, RED);          // Actual Color
		DrawText("4", allHouses[0].tokens[3].xCoordinates - 3, allHouses[0].tokens[3].yCoordinates - 8, 20, BLACK);

		DrawCircle(allHouses[2].tokens[3].xCoordinates, allHouses[2].tokens[3].yCoordinates, outline, RAYWHITE);   // Background (White)
		DrawCircle(allHouses[2].tokens[3].xCoordinates, allHouses[2].tokens[3].yCoordinates, inner, YELLOW);       // Actual Color
		DrawText("4", allHouses[2].tokens[3].xCoordinates - 3, allHouses[2].tokens[3].yCoordinates - 8, 20, BLACK);

		DrawCircle(allHouses[3].tokens[3].xCoordinates, allHouses[3].tokens[3].yCoordinates, outline, RAYWHITE);    // Background (White)
		DrawCircle(allHouses[3].tokens[3].xCoordinates, allHouses[3].tokens[3].yCoordinates, inner, BLUE);          // Actual Color
		DrawText("4", allHouses[3].tokens[3].xCoordinates - 3, allHouses[3].tokens[3].yCoordinates - 8, 20, BLACK);
	}
}

void drawDice()
{
	if (currentTurnIndex != -1)
	{
		DrawText("Current", 800, 40, 30, BLACK);    // Current Turn Text, X, Y, Font Size, Color
		DrawText("Turn:", 820, 80, 30, BLACK);
		string turn = currentTurn[currentTurnIndex];


		if (turn == "Green"){
			DrawText(turn.c_str(), 820, 120, 30, GREEN);
		}

		else if (turn == "Red"){
			DrawText(turn.c_str(), 820, 120, 30, RED);
		}

		else if (turn == "Yellow"){
			DrawText(turn.c_str(), 820, 120, 30, YELLOW);
		}

		else if (turn == "Blue"){
			DrawText(turn.c_str(), 820, 120, 30, BLUE);
		}


		// DrawText(turn.c_str(), 820, 120, 30, BLACK);

		for (int i = 0, j = 160; i < 4; i++, j += 40)
		{
			string n = names[i] + ": " + to_string(allHouses[i].hitrate);

			DrawText(n.c_str(), 800, j, 30, BLACK);
		}

		// Draw the dice
		if (dice2)
		{
			DrawRectangle(800, 460, 75, 75, LIGHTGRAY);
			string s2 = to_string(dice2);
			DrawText(s2.c_str(), 830, 475, 40, BLACK);
		}

		if (dice3)
		{
			DrawRectangle(800, 560, 75, 75, LIGHTGRAY);
			string s3 = to_string(dice3);
			DrawText(s3.c_str(), 830, 575, 40, BLACK);
		}

		DrawRectangle(800, 360, 75, 75, LIGHTGRAY);
		string s1 = to_string(dice);
		DrawText(s1.c_str(), 830, 375, 40, BLACK);
	}
}

void rollDice()
{
	if (newTurn)
	{
		dice = GetRandomValue(1, 6);
		newTurn = false;

		// if chakha then do another roll
		if (dice == 6)
		{
			dice2 = GetRandomValue(1, 6);

			// if another chakha then do another rol
			if (dice2 == 6)
			{
				dice3 = GetRandomValue(1, 6);
			}
		}
	}
}

void killGoti(string color, int key)
{

	for (int i = 0; i < 4; i++) // checking all houses
	{
		if (color == allHouses[i].color) // if the color is same
		{
			for (int j = 0; j < 4; j++)
			{ 
				if (j == i)
				{
					continue; // same house then just ignore 
				}

				for (int k = 0; k < totalTokens; k++) // going through all tokens
				{
					if (allHouses[i].tokens[k].insideSafeHouse == true) // if token safe then ignore
					{
						continue;
					}

					if (allHouses[j].tokens[k].insideSafeHouse == true)
					{
						continue; // If killing gotti inside its own safe house, it can't kill
					}

					// if gotti in safe spot which are 0,8,13,21,26,34,39,47
					if (allHouses[i].tokens[key].position % 52 == 0 || allHouses[i].tokens[key].position % 52 == 8 ||
						allHouses[i].tokens[key].position % 52 == 13 || allHouses[i].tokens[key].position % 52 == 21 ||
						allHouses[i].tokens[key].position % 52 == 26 || allHouses[i].tokens[key].position % 52 == 34 ||
						allHouses[i].tokens[key].position % 52 == 39 || allHouses[i].tokens[key].position % 52 == 47)
					{
						continue;
					}

					if (allHouses[i].tokens[key].position % 52 == allHouses[j].tokens[k].position % 52) // same position difference houses
					{
						allHouses[j].tokens[k].position = -1;
						allHouses[j].tokens[k].iterator = 0;
						allHouses[j].tokens[k].xCoordinates = allHouses[j].startHouseCoordinates[k][0];
						allHouses[j].tokens[k].yCoordinates = allHouses[j].startHouseCoordinates[k][1];
						allHouses[j].tokens[k].free = false;
						allHouses[j].tokensStuck++;
						allHouses[i].hitrate++; // maar di gotti
						cout << allHouses[i].color << ":" << allHouses[i].hitrate << endl;
						break;
					}
				}
			}
			break;
		}
	}
}


// semaphores
sem_t tokensem;
sem_t dicesem;

void *player(void *args)
{
	int p_no = *(int *)args;
	while (true)
	{
		sem_wait(&dicesem); // semapahore for dice
		rollDice();

		sem_post(&dicesem);
		sleep(1);
		sem_wait(&tokensem); // semaphore for goti
		currentTurnIndex = p_no;
		int count = 0;
		if (dice == 6 && dice2 == 6 && dice3 == 6)
		{
			count = 3;
		}

		while (count != 3)
		{
			// dont change it ffs
			if (keypressed)
			{
				usleep(1000);
			}
			if (keypressed >= 49 && keypressed < 49 + totalTokens)
			{

				allHouses[p_no].moveGoti(keypressed - 49);
				keypressed = 0;
				if (dice2)
				{
					count++;
				}
				else if (dice3)
				{
					count++;
				}
				else
				{
					count = 3;
				}
			}
		}
		newTurn = true;
		sem_post(&tokensem);
		sleep(1);
	}
	pthread_exit(NULL);
}

void *masterthread(void *args)
{
	//creating threads for players
	pthread_t players[4];
	for (int i = 0; i < 4; i++)
	{
		int *p_no = new int;
		p_no[0] = i;
		pthread_create(&players[i], NULL, &player, p_no);
	}

	for (int i = 0; i < 4; i++)
	{
		pthread_detach(players[i]);
	}

	int temp_position = 1;
	int counter = 0;
	while (true)
	{

		for (int i = 0; i < 4; i++)
		{

			if (allHouses[i].tokensRemaining == 0)
			{
				// setting the position of the player
				allHouses[i].position = temp_position;
				temp_position++;
				player_done[i] = true;
				allHouses[i].tokensRemaining = 4;
				cout << endl;
				cout << names[i] << endl;
				cout << "pid:" << (uint64_t)players[i] << endl;
				cout << "Color:" << allHouses[i].getColor() << endl;
				cout << "Cancelled Thread" << endl;
				cout << endl;
				pthread_cancel(players[i]);
				newTurn = true;
				rollDice();
			}
		}
		
		for (int i = 0; i < 4; i++) // how many players done with the game
		{
			if (player_done[i])
			{
				counter++;
			}
		}
		// if 3 players are done 
		if (counter == 3)
		{
			cout << "Exiting Master Thread" << endl;
			for (int i = 0; i < 4; i++)
			{
				cout << "Position of " << names[i] << " " << allHouses[i].position << endl; // printing position
			}
			exit(0);
			pthread_exit(NULL);
		}
		else
		{
			counter = 0;
		}
	}
}

int main()
{
	cout << "Enter number of tokens:";
	cin >> totalTokens;
	while (totalTokens < 1 || totalTokens > 4)
	{
		cout << "Tokens must be between 1 and 4, Re-enter.\n";
		cin >> totalTokens;
	}
	cout << "Enter Red's name: ";
	cin >> names[0];
	cout << "Enter Green's name: ";
	cin >> names[1];
	cout << "Enter Yellow's name: ";
	cin >> names[2];
	cout << "Enter Blue's name: ";
	cin >> names[3];

	// initializating the hosues
	allHouses[0].setColor("Red");
	allHouses[1].setColor("Green");
	allHouses[2].setColor("Yellow");
	allHouses[3].setColor("Blue");

	// the rayliub windwo
	const int windowWidth = 1000;
	const int windowHeight = 1000;

	InitWindow(windowWidth, windowHeight, "OS Project");
	SetTargetFPS(60);

	// semaphore initiliazation
	sem_init(&dicesem, 0, 1);  
	sem_init(&tokensem, 0, 1); 
	

	pthread_t master;
	pthread_create(&master, NULL, &masterthread, NULL);
	pthread_detach(master);

	// initializing all of the paths
	absolutePosition_init();

	//raylib loop
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		drawBoard();
		drawPieces();
		drawDice();
		keypressed = GetCharPressed();

		EndDrawing();
	}
}
