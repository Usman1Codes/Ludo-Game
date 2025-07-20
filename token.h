

							/*  _     _    _ _____   ____     _____ _______       _____  
							| |   | |  | |  __ \ / __ \   / ____|__   __|/\   |  __ \ 
							| |   | |  | | |  | | |  | | | (___    | |  /  \  | |__) |
							| |   | |  | | |  | | |  | |  \___ \   | | / /\ \ |  _  / 
							| |___| |__| | |__| | |__| |  ____) |  | |/ ____ \| | \ \ 
							|______\____/|_____/ \____/  |_____/   |_/_/    \_\_|  \_\
																					
																					*/

#include <iostream>
#include <string>

class Token
{
public:
	int position;
	bool free;
	bool stacked;
	int iterator;
	bool insideSafeHouse;
	int xCoordinates, yCoordinates;
	bool ended;

	Token();

	bool getFree();

	bool getStacked();

	int getPosition();

	void setPosition(int x);

	void setFree(bool val);
};