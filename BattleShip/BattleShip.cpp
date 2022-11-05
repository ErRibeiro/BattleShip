// BattleShip.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string> // for string and to_string()
#include "BattleShip.h"
#include <list>
using namespace std;
class Vector2 {
public:
    int x, y;
};
class BattleShip {
public:
    int nearCount = 0;
    int o = 0;
    int hiddenBoard[16][16]; // this is the board with the answer
    int board[16][16];       // this is the board with all the answers hidden as 0s
    vector<Vector2> spotsShot; // Sttores positions of spots I have shot at.
    vector<Vector2> nearSpots; // Sttores positions of spots I have shot at and are near.
    bool firstHit = false;
    int shipsSunk = 0;
    int moves = 0;
    public:
    void MakeBoard()
    {
        for (int i = 0; i < 16; i++)
        {
            for (o = 0; o < 16; o++)
            {
                hiddenBoard[i][o] = 0;
                board[i][o] = 0;
            }
        }
    }
    void placeShips()
    {
        srand(time(NULL));
        int count = 0;
        while (count != 10)
        {
            int r1 = (rand() % 16);
            int r2 = (rand() % 16);
            //std::cout << r1, r2;
            if (hiddenBoard[r1][r2] == 0)
            {
                hiddenBoard[r1][r2] = 1;
                count++;
            }
        }
    }
    void Logic() {
        //Shoot middle first, then check for HIT, MISS, NEAR. 
        //If hit, shoot positions divisible by 2 so you can hit the most area with the NEAR mechanic
            for (int n = 1; n <= 16; n++)
            {
                for (int m = 1; m <= 16; m++)
                {

                    Shoot(n, m);
                    moves++;

                    m++;
                    m++;
                }
                n++;
                n++;
            }
            for (int index = 0; index < nearSpots.size(); index++)
            {
                if (shipsSunk < 10)
                {
                    ShootNear(nearSpots.at(index).x, nearSpots.at(index).y);
                }
            }
           
        
        
    }
    int Shoot(int x, int y) {
      
        Vector2 v; //variable which changes every loop
        v.x = x;
        v.y = y;
        spotsShot.push_back(v);
        // 2 = hit, 1 = near, 0 = miss
        if (CheckOnTarget(x, y) == 2)
        {
            shipsSunk++;
            board[x][y] ++;
            return 2;
        }
        else if (CheckOnTarget(x, y) == 1)
        {
                nearSpots.push_back(v);
                return 1;
        }
        else if (CheckOnTarget(x, y) == 0)
        {
            //do nothing
            return 0;
        }
        
        
        spotsShot.push_back(v);

       // system("clear");
        
    }
    bool NoRepeatShots(int x, int y) {
            bool alreadyshotthere = false;
            for (int index2 = 0; index2 < spotsShot.size(); index2++)
            {
                if (spotsShot.at(index2).x == x && spotsShot.at(index2).y == y)
                {
                    alreadyshotthere = true;
                    return true;
                }
            }
            if (alreadyshotthere == false)
            {
                return false;
            }
        
    }
    int ShootEnding(int x, int y) {

        Vector2 v; //variable which changes every loop
        v.x = x;
        v.y = y;
        moves++;
        spotsShot.push_back(v);
        // 2 = hit, 1 = near, 0 = miss
        if (CheckOnTarget(x, y) == 2)
        {
            if (board[x][y] !=1)
            {
                shipsSunk++;
                board[x][y] ++;
            }
            
            return 2;
        }
        else if (CheckOnTarget(x, y) == 1 )
        {
            nearSpots.push_back(v);
            return 1;
        }
        else if (CheckOnTarget(x, y) == 0)
        {
            //do nothing
            return 0;
        }


        spotsShot.push_back(v);

        // system("clear");

    }
    int CheckOnTarget(int x, int y) {
        if (hiddenBoard[x][y] == 1)
        {
            return 2;
        }
        else if (hiddenBoard[x][y] == 0)
        {
            return CheckAround(x,y);
        }
    }
    bool ShootNear(int x, int y) {
            //right
            if (ShootEnding(x + 1, y) == 2 && NoRepeatShots(x + 1, y) == false)
            {
                
                return true;
            }
            //left
            if (ShootEnding(x - 1, y) == 2 && NoRepeatShots(x - 1, y) == false)
            {
                return true;
            }
            //up
            if (ShootEnding(x, y + 1) == 2 && NoRepeatShots(x, y + 1) == false)
            {
                
                return true;
            }
            //down
            if (ShootEnding(x + 1, y - 1) == 2 && NoRepeatShots(x + 1, y - 1) == false)
            {
                
                return true;
            }
            //up+right
            if (ShootEnding(x + 1, y + 1) == 2 && NoRepeatShots(x + 1, y + 1) == false)
            {
               
                return true;
            }
            //down right
            if (ShootEnding(x + 1, y - 1) == 2 && NoRepeatShots(x + 1, y - 1) == false)
            {
               
                return true;
            }
            //up + left
            if (ShootEnding(x - 1, y + 1) == 2 && NoRepeatShots(x - 1, y + 1) == false)
            {
               
                return true;
            }
            //down + left
            if (ShootEnding(x - 1, y - 1) == 2 && NoRepeatShots(x - 1, y - 1) == false)
            {
                
                return true;
            }
    }
    int CheckAround(int x, int y) {
        if (hiddenBoard[x+1][y] == 1)
        {
            return 1;
        }
        else if (hiddenBoard[x - 1][y] == 1)
        {
            return 1;
        }
        else if (hiddenBoard[x+1][y+1] == 1)
        {
            return 1;
        }
        else if (hiddenBoard[x + 1][y-1] == 1)
        {
            return 1;
        }
        else if (hiddenBoard[x - 1][y+1] == 1)
        {
            return 1;
        }
        else if (hiddenBoard[x - 1][y-1] == 1)
        {
            return 1;
        }
        else if (hiddenBoard[x][y+1] == 1)
        {
            return 1;
        }
        else if (hiddenBoard[x][y-1] == 1)
        {
            return 1;
        }
        else {
            return 0;
        }
    }
    void PrintBoard()
    {
        for (int i = 0; i < 16; i++)
        {
            for (o = 0; o < 16; o++)
            {
                std::cout << board[i][o];
            }
            std::cout << endl;
        }
        std::cout << endl;
        std::cout << endl;
        std::cout << "Moves :";
        std::cout << moves;
        std::cout << endl;
        std::cout << endl;
        std::cout << "Answer Key";
        std::cout << endl;
        for (int i = 0; i < 16; i++)
        {
            for (o = 0; o < 16; o++)
            {
                std::cout << hiddenBoard[i][o];
            }
            std::cout << endl;
        }

        std::cout << endl;
        std::cout << endl;
        std::cout << "Ships Destroyed :";
        std::cout << shipsSunk;
    }
};
int main()
{
    BattleShip bs;
    bs.MakeBoard();
    bs.placeShips();
    bs.Logic();
    bs.PrintBoard();
   
}
// run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
