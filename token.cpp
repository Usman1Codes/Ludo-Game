
							/*  _     _    _ _____   ____     _____ _______       _____  
							| |   | |  | |  __ \ / __ \   / ____|__   __|/\   |  __ \ 
							| |   | |  | | |  | | |  | | | (___    | |  /  \  | |__) |
							| |   | |  | | |  | | |  | |  \___ \   | | / /\ \ |  _  / 
							| |___| |__| | |__| | |__| |  ____) |  | |/ ____ \| | \ \ 
							|______\____/|_____/ \____/  |_____/   |_/_/    \_\_|  \_\
																					
																					*/

									/

#include "token.h"
Token::Token()
{
    ended = false;
    insideSafeHouse = false;
    iterator = 0;
    position = -1;
    free = false;
    stacked = false;
}

bool Token::getFree()
{
    return free;
}

bool Token::getStacked()
{
    return stacked;
}

int Token::getPosition()
{
    return position;
}

void Token::setPosition(int x)
{
    position = x;
}

void Token::setFree(bool val)
{
    free = val;
}



