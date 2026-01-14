

#include<iostream>
#include <chrono>
#include <cstring>
#include"help.h"
#include<cwchar>
const int MIN_X = 595;  // top-left x of grid
const int MIN_Y = 180;  // top-left y of grid
const int STEP = 90;   // size of each cell
const int ROWS = 8;
const int COLS = 8;
int score = 0;
constexpr int V_BERRY = 31, H_BERRY = 41, V_EOE = 35, H_EOE = 45,
H_EOR = 47, V_EOR = 37, V_OVAL = 33, H_OVAL = 43,
H_DROPLET = 46, V_DROPLET = 36, DISCO = 17;
using namespace std;
void berry(int x1, int y1, int x2, int y2)          //This code will print a berry. Imagine u see a square and u know the x and y coordinates of its upper left corner and lower right corner. Berry will be printed in its center.
{
    int d = (x2 - x1) / 5, h = (y2 - y1) / 5;      //These variables decide the scale of ellipses in the berry
    x1 += d + d / 2;
    y1 += h;
    int i1 = x1, i2 = x1 + d, j1 = y1, j2 = y1 + h;
    for (int i = 1; i <= 2; i++)                 //This loop is for making first two circles of the berry
    {
        for (i1, i1, j1, j2; i1 <= i2 && j1 <= j2; i1++, i2--, j1++, j2--)  //This loop is for colouring the berry
            myEllipse(i1, j1, i2, j2, 190, 40, 255);
        i1 = x1 + d;
        i2 = x1 + 2 * d;
        j1 = y1;
        j2 = y1 + h;
    }
    i1 = x1 - (d / 2);
    i2 = i1 + d;
    j1 = y1 + h;
    j2 = y1 + h + h;                    //These calculations are for the variable reset
    for (int i = 1; i <= 3; i++)         //This loop is for making the next three circles of the berry in the next row
    {
        for (i1, i2, j1, j2; i1 <= i1 && j1 <= j2; i1++, i2--, j1++, j2--)
            myEllipse(i1, j1, i2, j2, 190, 40, 255);
        i1 = x1 - (d / 2);
        i2 = i1 + d;
        j1 = y1 + h;
        j2 = y1 + h + h;
        i1 += i * d;
        i2 += i * d;
    }
    i1 = x1;
    i2 = x1 + d;
    j1 = y1 + 2 * h;
    j2 = j1 + h;
    for (int i = 1; i <= 2; i++)       //This loop is for making last two circles of the berry
    {
        for (i1, i1, j1, j2; i1 <= i2 && j1 <= j2; i1++, i2--, j1++, j2--)  //This loop is for colouring the circles
            myEllipse(i1, j1, i2, j2, 190, 40, 255);
        i1 = x1 + d;
        i2 = x1 + d + d;
        j1 = y1 + 2 * h;
        j2 = j1 + h;
    }
}
void vertical_berry(int x1, int y1, int x2, int y2)   //This is the special vertically stripped berry which occurs when theres a match of four berry in a column
{
    berry(x1, y1, x2, y2);
    int d = (x2 - x1) / 10, h = (y2 - y1) / 10;
    int i1 = x1 + 3 * d - (d / 2), i2 = i1, j1 = y1 + 4 * h, j2 = j1 + (3 * h / 2);
    myLine(i1, j1, i2, j2, 255, 255, 255);
    i1 = x1 + 4 * d;
    i2 = i1;
    j1 = y1 + 2 * h;
    j2 = j1 + 6 * h;
    myLine(i1, j1, i2, j2, 255, 255, 255);
    i1 += 2 * d;
    i2 = i1;
    myLine(i1, j1, i2, j2, 255, 255, 255);
    i1 += 7 * d / 6;
    i2 = i1;
    j1 = y1 + 4 * h;
    j2 = j1 + (3 * h / 2);
    myLine(i1, j1, i2, j2, 255, 255, 255);
}
void horizontal_berry(int x1, int y1, int x2, int y2)     //This is the special horizontally stripped berry which occurs when theres a match of four berry in a row
{
    int d = (x2 - x1) / 20, h = (y2 - y1) / 20;
    berry(x1, y1, x2, y2);
    y1 += 7 * h;
    y2 = y1;
    x1 += 6 * d;
    x2 -= 6 * d;
    myLine(x1, y1, x2, y2, 255, 255, 255);
    y1 += 4 * h;
    y2 = y1;
    x1 -= 2 * d;
    x2 += 2 * d;
    myLine(x1, y1, x2, y2, 255, 255, 255);
    y1 += 4 * h;
    y2 = y1;
    x1 += 2 * d;
    x2 -= 2 * d;
    myLine(x1, y1, x2, y2, 255, 255, 255);
}
void ellipseOverRectangle(int x1, int y1, int x2, int y2)                      //This is a candy having a cirlce over a square(EOR)
{
    int d = (x2 - x1) / 5, h = (y2 - y1) / 5;
    int i1 = x1 + d, i2 = x1 + 4 * d, j1 = y1 + h, j2 = y1 + 4 * h;
    for (i1, i2, j1, j2; i1 <= i1 && j1 <= j2; i1++, i2--, j1++, j2--)
        myRect(i1, j1, i2, j2, 255, 0, 0);
    i1 = x1 + d; i2 = x1 + 4 * d; j1 = y1 + h; j2 = y1 + 4 * h;
    for (i1, i2, j1, j2; i1 <= i1 && j1 <= j2; i1++, i2--, j1++, j2--)
        myEllipse(i1, j1, i2, j2, 0, 255, 0);
}
void horizontal_eor(int x1, int y1, int x2, int y2)                  //This is the special horizontally stripped EOR which occurs when theres a match of four EOR in a row
{
    int d = (x2 - x1) / 20, h = (y2 - y1) / 20;
    ellipseOverRectangle(x1, y1, x2, y2);
    x1 += 4 * d;
    y1 += 7 * h;
    y2 = y1;
    x2 -= 4 * d;
    myLine(x1, y1, x2, y2, 255, 255, 255);
    y1 += 4 * h;
    y2 = y1;
    myLine(x1, y1, x2, y2, 255, 255, 255);
    y1 += 4 * h;
    y2 = y1;
    myLine(x1, y1, x2, y2, 255, 255, 255);
}
void vertical_eor(int x1, int y1, int x2, int y2)                  //This is the special vertically stripped EOR which occurs when theres a match of four EOR in a column
{
    int d = (x2 - x1) / 20, h = (y2 - y1) / 20;
    ellipseOverRectangle(x1, y1, x2, y2);
    y1 += 4 * d;
    x1 += 7 * h;
    x2 = x1;
    y2 -= 4 * d;
    myLine(x1, y1, x2, y2, 255, 255, 255);
    x1 += 4 * h;
    x2 = x1;
    myLine(x1, y1, x2, y2, 255, 255, 255);
    x1 += 4 * h;
    x2 = x1;
    myLine(x1, y1, x2, y2, 255, 255, 255);
}
void EllipseoverEllipse(int x1, int y1, int x2, int y2)                 //this function forms a star type candy using two ellipses over one another.
{
    myEllipse(x1, y1, x1 + 70, y1 - 20, 255, 0, 0);
    myEllipse(x1 + 25, y1 - 40, (x1 + 25) + 20, (y1 - 40) + 70, 255, 0, 0);
}
void vertical_eoe(int x1, int y1, int x2, int y2)                       //This is the special vertically stripped EOE which occurs when theres a match of four EOE in a column
{
    EllipseoverEllipse(x1, y1, x2, y2);
    int d = (x2 - x1) / 20, h = (y2 - y1) / 20;
    //y1 -= 4 * d;
    x1 += 4 * d;
    x2 = x1;
    y2 = y1 + 3 * d;
    myLine(x1, y1, x2, y2, 255, 255, 255);
    x1 += 4 * d;
    x2 = x1;
    y1 -= 4 * d;
    y2 += 6 * d;
    myLine(x1, y1, x2, y2, 255, 255, 255);
    x1 += 4 * h;
    x2 = x1;
    y1 += 4 * d;
    y2 -= 6 * d;
    myLine(x1, y1, x2, y2, 255, 255, 255);
}
void horizontal_eoe(int x1, int y1, int x2, int y2)                    //This is the special horizontally stripped EOE which occurs when theres a match of four EOE in a row
{
    EllipseoverEllipse(x1, y1, x2, y2);
    int d = (x2 - x1) / 20, h = (y2 - y1) / 20;
    y1 -= 2 * h;
    y2 = y1;
    x2 = x1 + 16 * d;
    myLine(x1, y1, x2, y2, 255, 255, 255);
    x1 += 7 * d;
    x2 -= 6 * d;
    y1 -= 4 * h;
    y2 = y1;
    myLine(x1, y1, x2, y2, 255, 255, 255);
    y1 += 8 * h;
    y2 = y1;
    myLine(x1, y1, x2, y2, 255, 255, 255);
}
void droplet(int x1, int y1, int x2, int y2)                    //this function is for forming a droplet shaped candy
{
    int d = (x2 - x1) / 5, h = (y2 - y1) / 5;
    int i1 = x1 + d, i2 = i1 + 2 * d, j1 = y1 + h, j2 = j1 + 2 * h + (h / 2);
    for (i1, j1, i2, j2; i1 <= i2 && j1 <= j2; i1++, j1++, i2--, j2--)
        myTriangle(i1, j1, i2, j2, 0, 0, 255);
    i1 = x1 + d;
    i2 = i1 + 2 * d;
    j1 = y1 + h;
    j2 = j1 + 2 * h;
    j1 += (2) * h;
    j2 = j1 + h;
    for (i1, j1, i2, j2; i1 <= i2 && j1 <= j2; i1++, j1++, i2--, j2--)
        myEllipse(i1, j1, i2, j2, 0, 0, 255);
}

void vertical_droplet(int x1, int y1, int x2, int y2)                    //This is the special vertically stripped droplet which occurs when theres a match of four droplets in a column
{
    int d = (x2 - x1) / 5, h = (y2 - y1) / 5;
    int i1 = x1 + d, i2 = i1 + 2 * d, j1 = y1 + h, j2 = j1 + 2 * h + (h / 2);
    for (i1, j1, i2, j2; i1 <= i2 && j1 <= j2; i1++, j1++, i2--, j2--)
        myTriangle(i1, j1, i2, j2, 0, 0, 255);
    i1 = x1 + d;
    i2 = i1 + 2 * d;
    j1 = y1 + h;
    j2 = j1 + 2 * h;
    j1 += (2) * h;
    j2 = j1 + h;
    myEllipse(i1, j1, i2, j2, 0, 0, 255);
    myLineEdited(i1 + 20, j1 - 32, i1 + 20, j2, 255, 255, 255, 2);
    myLineEdited(i1 + 12, j1 - 22, i1 + 12, j2, 255, 255, 255, 2);
    myLineEdited(i1 + 4, j1 - 5, i1 + 4, j2, 255, 255, 255, 2);
    myLineEdited(i1 + 28, j1 - 7, i1 + 28, j2, 255, 255, 255, 2);
}
void horizontal_droplet(int x1, int y1, int x2, int y2)                    //This is the special horizontally stripped droplet which occurs when theres a match of four droplets in a row
{
    int d = (x2 - x1) / 5, h = (y2 - y1) / 5;
    int i1 = x1 + d, i2 = i1 + 2 * d, j1 = y1 + h, j2 = j1 + 2 * h + (h / 2);
    for (i1, j1, i2, j2; i1 <= i2 && j1 <= j2; i1++, j1++, i2--, j2--)
        myTriangle(i1, j1, i2, j2, 0, 0, 255);
    i1 = x1 + d;
    i2 = i1 + 2 * d;
    j1 = y1 + h;
    j2 = j1 + 2 * h;
    j1 += (2) * h;
    j2 = j1 + h;
    myEllipse(i1, j1, i2, j2, 0, 0, 255);
    myLineEdited(i1, j1, i2 - 3, j1, 255, 255, 255, 2);
    myLineEdited(i1 - 3, j1 + 10, i1 + 35, j1 + 10, 255, 255, 255, 2);
    myLineEdited(i1 + 4, j1 - 10, i2 - 7, j1 - 10, 255, 255, 255, 2);
    myLineEdited(i1 + 10, j1 - 20, i2 - 12, j1 - 20, 255, 255, 255, 2);
}
void oval(int x1, int y1, int x2, int y2)                               //this forms an oval shaped candy
{
    int d = (x2 - x1) / 10, h = (y2 - y1) / 10;
    int i1 = x1 + 3 * d, i2 = i1 + 4 * d, j1 = y1 + 2 * h, j2 = y2 - 2 * h;
    for (i1, i2, j1, j2; i1 <= i1 && j1 <= j2; i1++, i2--, j1++, j2--)
        myEllipse(i1, j1, i2, j2, 255, 120, 0);
}
void vertical_oval(int x1, int y1, int x2, int y2)                         // the vertically stripped oveal
{
    int d = (x2 - x1) / 10, h = (y2 - y1) / 10;
    int i1 = x1 + 3 * d, i2 = i1 + 4 * d, j1 = y1 + 2 * h, j2 = y2 - 2 * h;
    myEllipse(i1, j1, i2, j2, 255, 120, 0);
    myLineEdited(i1 + 15, j1 - 2, i1 + 15, j2, 255, 255, 255, 2);
    myLineEdited(i1 + 5, j1 + 4, i1 + 5, j2 - 7, 255, 255, 255, 2);
    myLineEdited(i1 + 25, j1 + 2, i1 + 25, j2 - 3, 255, 255, 255, 2);
}
void horizontal_oval(int x1, int y1, int x2, int y2)                      // the horizontally stripped oval
{

    int d = (x2 - x1) / 10, h = (y2 - y1) / 10;
    int i1 = x1 + 3 * d, i2 = i1 + 4 * d, j1 = y1 + 2 * h, j2 = y2 - 2 * h;
    myEllipse(i1, j1, i2, j2, 255, 120, 0);
    myLineEdited(i1 + 3, j1 + 5, i2 - 5, j1 + 5, 255, 255, 255, 2);
    myLineEdited(i1 - 2, j1 + 28, i2, j1 + 28, 255, 255, 255, 2);
    myLineEdited(i1 - 2, j1 + 15, i2 - 2, j1 + 15, 255, 255, 255, 2);
    myLineEdited(i1 - 1, j1 + 41, i2 - 1, j1 + 41, 255, 255, 255, 2);
    myLineEdited(i1 + 4, j1 + 49, i2 - 6, j1 + 49, 255, 255, 255, 2);
}
void crystalBerry(int x1, int y1, int x2, int y2)       //the destroyer berry occuring at a L match
{
    int d = (x2 - x1) / 5, h = (y2 - y1) / 5;      //These variables decide the scale of ellipses in the berry
    int i1 = x1 + 2 * d;
    int j1 = y1 + h;
    int i2 = x1 - d;
    int j2 = y2 - h;
    myRect(i1, j1 - 2, i2, j2 + 2, 231, 162, 255);
    berry(x1 - 2 * d, y1, x2 - 2 * d, y2);
}
void crystalOval(int x1, int y1, int x2, int y2)               //a destroyer oval occuring at a L match
{
    int d = (x2 - x1) / 5, h = (y2 - y1) / 5;
    int i1 = x1 + 2 * d;
    int j1 = y1 + h;
    int i2 = x1 - d;
    int j2 = y2 - h;
    myRect(i1, j1 - 2, i2, j2 + 2, 231, 209, 182);
    oval(x1 - 2 * d, y1, x2 - 2 * d, y2);
}
void crystalEllipseOverRectangle(int x1, int y1, int x2, int y2)      // destroyer EOR
{
    int d = (x2 - x1) / 5, h = (y2 - y1) / 5;
    int i1 = x1 + 2 * d;
    int j1 = y1 + h;
    int i2 = x1 - d;
    int j2 = y2 - h;
    myEllipse(i1 - 3 * d, j1 - d / 2, i2 + 3 * d, j2 + d / 2, 187, 252, 255);
    ellipseOverRectangle(x1 - 2 * d - 5, y1, x2 - 2 * d - 5, y2);
}
void crystalDroplet(int x1, int y1, int x2, int y2)         //Destroyer droplet
{
    int d = (x2 - x1) / 5, h = (y2 - y1) / 5;
    int i1 = x1 + 2 * d;
    int j1 = y1 + h;
    int i2 = x1 - d;
    int j2 = y2 - h;
    myRect(i1, j1, i2, j2, 165, 253, 255);
    droplet(x1 - 2 * d + 10, y1, x2 - 2 * d, y2);
}
void crystalEoe(int x1, int y1, int x2, int y2)            //Destroyer EOE
{
    int d = (x2 - x1) / 5, h = (y2 - y1) / 5;
    int i1 = x1 + 2 * d - 10;
    int j1 = y1 + h - 8;
    int i2 = x1 - d - 20;
    int j2 = y2 - h + 10;
    myRect(i1 + (d / 2), j1, i2, j2, 255, 186, 140);
    EllipseoverEllipse(x1 - 2 * d, y1 + 50, x2 - 2 * d, y2);
}
void disco_ball(int x1, int y1, int x2, int y2)                      // the special disco ball which occurs at a match of 5 in a row or a column
{
    int d = (x2 - x1) / 20, h = (y2 - y1) / 20;
    x1 += 4 * d;
    y1 += 4 * d;
    x2 -= 4 * d;
    y2 -= 4 * d;
    int i1 = x1, i2 = x2, j1 = y1, j2 = y2;
    for (i1, i2, j1, j2; i1 < i2 && j1 < j2; i1++, i2--, j1++, j2--)
    {
        myEllipse(i1, j1, i2, j2, 0, 0, 0);
    }
    y1 += 2 * d;
    x2 = x1 + 2 * d;
    y2 = y1 + 2 * d;
    i1 = x1;
    i2 = x2;
    j1 = y1;
    j2 = y2;
    for (i1, i2, j1, j2; i1 < i2 && j1 < j2; i1++, i2--, j1++, j2--)
    {
        myEllipse(i1, j1, i2, j2, 255, 0, 0);
    }
    x1 += 4 * d;
    x2 = x1 + 2 * d;
    y1 -= d;
    y2 = y1 + 2 * d;
    i1 = x1;
    i2 = x2;
    j1 = y1;
    j2 = y2;
    for (i1, i2, j1, j2; i1 < i2 && j1 < j2; i1++, i2--, j1++, j2--)
    {
        myEllipse(i1, j1, i2, j2, 0, 255, 0);
    }
    x1 += 4 * d;
    x2 = x1 + 2 * d;
    y1 += 3 * d;
    y2 = y1 + 2 * d;
    i1 = x1;
    i2 = x2;
    j1 = y1;
    j2 = y2;
    for (i1, i2, j1, j2; i1 < i2 && j1 < j2; i1++, i2--, j1++, j2--)
    {
        myEllipse(i1, j1, i2, j2, 0, 0, 255);
    }
    x1 += 3 * d;
    x2 = x1 + 2 * d;
    y1 -= 3 * d;
    y2 = y1 + 2 * d;
    i1 = x1;
    i2 = x2;
    j1 = y1;
    j2 = y2;
    for (i1, i2, j1, j2; i1 < i2 && j1 < j2; i1++, i2--, j1++, j2--)
    {
        myEllipse(i1, j1, i2, j2, 0, 255, 0);
    }
    x1 -= 7 * d;
    x2 = x1 + 2 * d;
    y1 += 5 * d;
    y2 = y1 + 2 * d;
    i1 = x1;
    i2 = x2;
    j1 = y1;
    j2 = y2;
    for (i1, i2, j1, j2; i1 < i2 && j1 < j2; i1++, i2--, j1++, j2--)
    {
        myEllipse(i1, j1, i2, j2, 255, 0, 0);
    }
    x1 -= 2 * d;
    x2 = x1 + 2 * d;
    y1 += 5 * d;
    y2 = y1 + 2 * d;
    i1 = x1;
    i2 = x2;
    j1 = y1;
    j2 = y2;
    for (i1, i2, j1, j2; i1 < i2 && j1 < j2; i1++, i2--, j1++, j2--)
    {
        myEllipse(i1, j1, i2, j2, 0, 255, 0);
    }
    x1 += 5 * d;
    x2 = x1 + 2 * d;
    y1 += d;
    y2 = y1 + 2 * d;
    i1 = x1;
    i2 = x2;
    j1 = y1;
    j2 = y2;
    for (i1, i2, j1, j2; i1 < i2 && j1 < j2; i1++, i2--, j1++, j2--)
    {
        myEllipse(i1, j1, i2, j2, 255, 0, 0);
    }
    x1 += 3 * d;
    x2 = x1 + 2 * d;
    y1 -= 3 * d;
    y2 = y1 + 2 * d;
    i1 = x1;
    i2 = x2;
    j1 = y1;
    j2 = y2;
    for (i1, i2, j1, j2; i1 < i2 && j1 < j2; i1++, i2--, j1++, j2--)
    {
        myEllipse(i1, j1, i2, j2, 255, 0, 0);
    }
}
bool down(int arr[][8], int& r, int i, int j)                           //THIS FUNCTION WILL CHECK IF THERE ARE VERTCIALLY MATCHING ITEMS AND ALSO GIVE THEIR LENGTH(3,4,5).
{
    if (arr[i][j] == 0)
    {
        return false;
    }
    r = 1;
    int value = arr[i][j];
    for (int k = i + 1; k < 8; k++)
    {
        if (arr[k][j] == value)
            r++;
        else
            break;
    }
    return (r >= 3);
}
bool right(int arr[][8], int& r, int i, int j)             //THIS FUNCTION WILL CHECK IF THERE ARE HORIZONTALLY MATCHING ITEMS AND ALSO GIVE THEIR LENGTH(3,4,5).
{
    if (arr[i][j] == 0)
    {
        return false;
    }
    r = 1;
    int value = arr[i][j];
    for (int k = j + 1; k < 8; k++)
    {
        if (arr[i][k] == value)
            r++;
        else
            break;
    }
    return (r >= 3);
}
void graphic_grid()                                               //this function forms a grid for the candies
{
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color, 6);
    SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
    int x_left = MIN_X, y_top = MIN_Y;
    int cell = STEP;
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            int x1 = MIN_X + col * cell;
            int y1 = MIN_Y + row * cell;
            int x2 = x1 + cell;
            int y2 = y1 + cell;
            myRect(x1, y1, x2, y2, 150, 75, 0);
        }
    }
    int x_left2 = MIN_X;
    int y_top2 = MIN_Y;
    for (int i = 0; i <= ROWS; i++)
    {
        myLineEdited(MIN_X, y_top2, MIN_X + COLS * STEP, y_top2, 88, 0, 219, 7);
        y_top2 += STEP;
    }
    for (int i = 0; i <= COLS; i++)
    {
        myLineEdited(x_left2, MIN_Y, x_left2, MIN_Y + ROWS * STEP, 88, 0, 219, 7);
        x_left2 += STEP;
    }
}
void grid_gen(int arr[][8], int r)                     //generates random values for the 5 candies and makes sure that there is no match initially
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            arr[i][j] = rand() % 5 + 1;
        }
    }
    bool changed = true;
    while (changed)
    {
        changed = false;
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                if (arr[i][j] == arr[i][j + 1] && arr[i][j] == arr[i][j + 2])
                {
                    do
                    {
                        arr[i][j + 2] = rand() % 5 + 1;
                    } while (arr[i][j] == arr[i][j + 2]);
                    changed = true;
                }
            }
        }
        for (int j = 0; j < 8; j++)
        {
            for (int i = 0; i < r - 2; i++)
            {
                if (arr[i][j] == arr[i + 1][j] && arr[i][j] == arr[i + 2][j])
                {
                    do
                    {
                        arr[i + 2][j] = rand() % 5 + 1;
                    } while (arr[i][j] == arr[i + 2][j]);
                    changed = true;
                }
            }
        }
    }
}
void grid_display(int arr[][8], int r)                       //this function places the candies in the grid, each candy has been assigned a unique number as generated by the grid_gen function
{
    graphic_grid();
    int x = 595;
    int y = 190;
    for (int j = 0; j < r; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            if (arr[i][j] == 1)
            {
                berry(x, y, x + 90, y + 90);
            }
            else if (arr[i][j] == 2)
            {
                oval(x, y, x + 90, y + 90);
            }
            else if (arr[i][j] == 3)
            {
                EllipseoverEllipse(x + 7, y + 45, x + 7 + 90, y + 45 + 90);
            }
            else if (arr[i][j] == 4)
            {
                droplet(x, y, x + 90, y + 90);
            }
            else if (arr[i][j] == 5)
            {
                ellipseOverRectangle(x, y, x + 90, y + 90);
            }
            else if (arr[i][j] == 41)
            {
                vertical_berry(x, y, x + 90, y + 90);
            }
            else if (arr[i][j] == 31)
            {
                horizontal_berry(x, y, x + 90, y + 90);
            }
            else if (arr[i][j] == 43)
            {
                vertical_eoe(x + 10, y + 40, x + 90 + 10, y + 90 + 40);
            }
            else if (arr[i][j] == 33)
            {
                horizontal_eoe(x + 10, y + 40, x + 90 + 10, y + 90 + 40);
            }
            else if (arr[i][j] == 35)
            {
                horizontal_eor(x, y, x + 90, y + 90);
            }
            else if (arr[i][j] == 45)
            {
                vertical_eor(x, y, x + 90, y + 90);
            }
            else if (arr[i][j] == 44)
            {
                vertical_oval(x, y, x + 90, y + 90);
            }
            else if (arr[i][j] == 32)
            {
                horizontal_oval(x, y, x + 90, y + 90);
            }
            else if (arr[i][j] == 34)
            {
                horizontal_droplet(x, y, x + 90, y + 90);
            }
            else if (arr[i][j] == 42)
            {
                vertical_droplet(x, y, x + 90, y + 90);
            }
            else if (arr[i][j] == 17)
            {
                disco_ball(x, y, x + 90, y + 90);
            }
            else if (arr[i][j] == 21)
            {
                crystalBerry(x + 45, y, x + 90 + 45, y + 90);
            }
            else if (arr[i][j] == 22)
            {
                crystalOval(x + 45, y, x + 90 + 45, y + 90);
            }
            else if (arr[i][j] == 23)
            {
                crystalEoe(x + 45, y, x + 90 + 45, y + 90);
            }
            else if (arr[i][j] == 24)
            {
                crystalDroplet(x + 45, y, x + 90 + 45, y + 90);
            }
            else if (arr[i][j] == 25)
            {
                crystalEllipseOverRectangle(x + 45, y, x + 90 + 45, y + 90);
            }
            else if (arr[i][j] == 0)
            {
                myRect(x, y - 10, x + 90, y + 80, 99, 99, 99);
            }
            x += 90;
        }
        y += 90;
        x = 595;
    }
}
bool findMatches(int arr[][8])                    // this function find if there are any matches being formed, whether in a row column or L, it also then assigns a number
// zero to those cells
{
    int r;
    bool comp = false;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (arr[i][j] != 0)
            {
                if (down(arr, r, i, j))
                {
                    if (r == 3)
                    {
                        if (right(arr, r, i, j) && r == 3)
                        {
                            arr[i][j] = arr[i][j] + 20;            //crystal L shape (orignal L)
                            arr[i][j + 1] = 0;
                            arr[i][j + 2] = 0;
                            arr[i + 1][j] = 0;
                            arr[i + 2][j] = 0;
                            grid_display(arr, 8);
                            Sleep(100);
                            for (int i1 = 0; i1 < 3; i1++)
                            {
                                for (int j1 = 0; j1 < 3; j1++)
                                {
                                    arr[i - i1][j + j1] = 0;
                                }
                            }
                            score += 90;
                            comp = true;
                        }
                        else if (j >= 2 && right(arr, r, i - 2, j - 2) && r == 3)
                        {
                            arr[i][j] = arr[i][j] + 20;             //crystal  L shapes
                            arr[i][j + 1] = 0;
                            arr[i][j + 2] = 0;
                            arr[i - 1][j] = 0;
                            arr[i - 2][j] = 0;
                            Sleep(100);
                            for (int i1 = 0; i1 < 3; i1++)          //to destroy 3 by 3
                            {
                                for (int j1 = 0; j1 < 3; j1++)
                                {
                                    arr[i - i1][j - j1] = 0;
                                }
                            }
                            grid_display(arr, 8);
                            score += 90;
                            comp = true;
                        }
                        else
                        {
                            arr[i][j] = 0;
                            arr[i + 1][j] = 0;
                            arr[i + 2][j] = 0;
                            grid_display(arr, 8);
                            score += 30;
                            comp = true;
                        }
                    }
                    else if (r == 4)
                    {
                        arr[i][j] = arr[i][j] + 30;                //vertical striped
                        score += 40;
                        grid_display(arr, 8);
                        Sleep(200);
                        for (int k = 0; k < 8; k++)
                        {
                            arr[k][j] = 0;
                        }
                        grid_display(arr, 8);
                        score += 70;
                        comp = true;
                    }
                    else if (r == 5)
                    {
                        arr[i][j] = 17;                              //disco ball
                        arr[i][j + 1] = 0;
                        arr[i][j + 2] = 0;
                        arr[i][j + 3] = 0;
                        arr[i][j + 4] = 0;
                        grid_display(arr, 8);
                        score += 200;
                        comp = true;
                    }
                }
                else if (right(arr, r, i, j))
                {
                    if (r == 3)
                    {
                        if (down(arr, r, i - 2, j) && r == 3)
                        {
                            arr[i][j] = pow(arr[i][j], 3) + 20;        //crystal    L shape
                            arr[i - 1][j] = 0;
                            arr[i - 2][j] = 0;
                            arr[i][j + 1] = 0;
                            arr[i][j + 2] = 0;
                            Sleep(100);
                            for (int i1 = 0; i1 < 3; i1++)            //to destroy 3 by 3
                            {
                                for (int j1 = 0; j1 < 3; j1++)
                                {
                                    arr[i + i1][j - j1] = 0;
                                }
                            }
                            grid_display(arr, 8);
                            score += 90;
                            comp = true;
                        }
                        else if (j >= 2 && down(arr, r, i - 2, j + 2))
                        {
                            arr[i][j] = pow(arr[i][j], 3) + 20;       //crystal  L shape
                            arr[i - 2][j] = 0;
                            arr[i - 1][j] = 0;
                            arr[i][j + 1] = 0;
                            arr[i][j + 2] = 0;
                            Sleep(100);
                            for (int i1 = 0; i1 < 3; i1++)
                            {
                                for (int j1 = 0; j1 < 3; j1++)
                                {
                                    arr[i + i1][j + j1] = 0;           //to destroy 3 by 3
                                }
                            }
                            grid_display(arr, 8);
                            score += 90;
                            comp = true;
                        }
                        else
                        {
                            arr[i][j] = 0;
                            arr[i][j + 1] = 0;
                            arr[i][j + 2] = 0;
                            grid_display(arr, 8);
                            score += 30;
                            comp = true;
                        }
                    }
                    else if (r == 4)
                    {
                        arr[i][j] = pow(arr[i][j], 2) + 40;            //horizontal striped
                        score += 40;
                        grid_display(arr, 8);
                        Sleep(200);
                        for (int k = 0; k < 8; k++)
                        {
                            arr[i][k] = 0;
                        }
                        grid_display(arr, 8);
                        score += 100;
                        comp = true;
                    }
                    else if (r == 5)
                    {
                        arr[i][j] = 17;                           //disco ball
                        arr[i][j + 1] = 0;
                        arr[i][j + 2] = 0;
                        arr[i][j + 3] = 0;
                        arr[i][j + 4] = 0;
                        grid_display(arr, 8);
                        score += 100;
                        comp = true;
                    }
                }
            }
        }
    }
    return comp;
}
void activateDisco(int arr[][8], int swapped)                 // this function stores the number of the candy with which the disco ball is swapped then
// it removes all those candies of that one type from the grid.
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (arr[i][j] == swapped)
            {
                arr[i][j] = 0;
            }
        }
    }
}
bool isLegalMove(int arr[][8], int r, int c)                    // this function is specifically made to check if the move made by the user is legal or not, as in if he moves his candy anywhere then this tells if theres
// a match being formed after that move or not
{
    int candy = arr[r][c];
    if (candy == 0)
    {
        return false;
    }
    if (candy == 17)
    {
        return true;
    }
    int count = 1;

    count = 1;
    for (int j = c - 1; j >= 0 && arr[r][j] == candy; j--)
    {
        count++;
    }
    for (int j = c + 1; j < 8 && arr[r][j] == candy; j++)
    {
        count++;
    }
    if (count >= 3) return true;

    count = 1;
    for (int i = r - 1; i >= 0 && arr[i][c] == candy; i--)
    {
        count++;
    }
    for (int i = r + 1; i < 8 && arr[i][c] == candy; i++)
    {
        count++;
    }
    if (count >= 3)
    {
        return true;
    }
    return false;
}
void applyGravity(int arr[][8])                      // this function makes candies fall from above and the fills the candies at the top
{
    for (int c = 0; c < 8; ++c)
    {
        int write = 7; // destination row (from bottom)
        for (int r = 7; r >= 0; --r)
        {
            if (arr[r][c] != 0)
            {
                arr[write][c] = arr[r][c];
                if (write != r)
                    arr[r][c] = 0;
                write--;
            }
        }
    }
    for (int c = 0; c < 8; ++c)
    {
        for (int r = 0; r < 8; ++r)
        {

            if (arr[r][c] == 0)
                arr[r][c] = rand() % 5 + 1;
        }
    }
}
bool moving_positions(int arr[][8], int& i, int& j, int& x, int& y)              // this function keeps track of user movement, it also ensures that the cursor doesnt go beyond the bound of the grid
{                                                                                // it calls the legal move function if the swap is legal, it intitally swaps then if the legal move functions tells that theres
                                                                                 // no match then this function reswaps the candy to their orignal positions
    int key;
    isCursorKeyPressed(key);
    bool shift = (GetAsyncKeyState(VK_SHIFT) & 0x8000);
    int row = (x - MIN_X) / STEP;
    int col = (y - MIN_Y) / STEP;
    int dr = 0, dc = 0;
    if (GetAsyncKeyState(VK_UP) && col > 0)
    {
        dc = -1;
    }
    else if (GetAsyncKeyState(VK_DOWN) && col < COLS - 1)
    {
        dc = +1;
    }
    else if (GetAsyncKeyState(VK_LEFT) && row > 0)
    {
        dr = -1;
    }
    else if (GetAsyncKeyState(VK_RIGHT) && row < ROWS - 1)
    {
        dr = +1;
    }
    else
    {
        myRectOutline(x, y, x + STEP, y + STEP, 0, 0, 0, 7);
        return false;
    }
    if (!shift)
    {
        myRectOutline(x, y, x + STEP, y + STEP, 88, 0, 219, 7);
        row += dr;
        col += dc;
        i = row;
        j = col;
        x = MIN_X + row * STEP;
        y = MIN_Y + col * STEP;
        myRectOutline(x, y, x + STEP, y + STEP, 0, 0, 0, 7);
        return true;
    }
    int r2 = i + dr;
    int c2 = j + dc;
    swap(arr[i][j], arr[r2][c2]);
    Sleep(100);
    if (!isLegalMove(arr, i, j) && !isLegalMove(arr, r2, c2))
    {
        system("color DF");
        grid_display(arr, 8);
        swap(arr[i][j], arr[r2][c2]);
        system("color DF");
        grid_display(arr, 8);
        return false;
    }
    i = r2;
    j = c2;
    x = MIN_X + i * STEP;
    y = MIN_Y + j * STEP;
    myRectOutline(x, y, x + STEP, y + STEP, 0, 0, 0, 7);
    if (arr[i][j] == 17)
    {
        activateDisco(arr, arr[i + dr][j + dr]);
        arr[i][j] = 0;
        grid_display(arr, 8);
        Sleep(100);
        applyGravity(arr);
    }
    return true;
}
void zero(int x1, int y1, int x2, int y2)                             // these are all the graphic functions below for various numbers and alphabets
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    myRect(x1, y1, x2, y2, 0, 0, 255);
    x1 += 4 * d;
    x2 -= 4 * d;
    y1 += 3 * d;
    y2 -= 3 * d;
    myEllipseEdited(x1, y1, x2, y2, 255, 255, 255);
}
void one(int x1, int y1, int x2, int y2)
{
    myRect(x1, y1, x2, y2, 0, 0, 255);
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    x1 += 7 * d;
    y1 += 4 * d;
    x2 = x1;
    y2 -= 3 * d;
    myLineEdited(x1, y1, x2, y2, 255, 255, 255, 5);
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1, y1, x2, y2, 255, 255, 255, 5);
}
void two(int x1, int y1, int x2, int y2)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    myRect(x1, y1, x2, y2, 0, 0, 255);
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 8, y1 + 3, x2 - 10, y1 + 3, 255, 255, 255, 5);
    myLineEdited(x1 - 8, y1 + 26, x2 - 10, y1 + 26, 255, 255, 255, 5);
    myLineEdited(x1 - 8, y1 + 50, x2 - 10, y1 + 50, 255, 255, 255, 5);
    myLineEdited(x1 - 8, y1 + 27, x1 - 8, y1 + 50, 255, 255, 255, 5);
    myLineEdited(x1 + 40, y1 + 3, x1 + 40, y1 + 26, 255, 255, 255, 5);
}
void three(int x1, int y1, int x2, int y2)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    myRect(x1, y1, x2, y2, 0, 0, 255);
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 8, y1 + 3, x2 - 10, y1 + 3, 255, 255, 255, 5);
    myLineEdited(x1 - 8, y1 + 26, x2 - 10, y1 + 26, 255, 255, 255, 5);
    myLineEdited(x1 - 8, y1 + 50, x2 - 10, y1 + 50, 255, 255, 255, 5);
    myLineEdited(x1 + 40, y1 + 3, x1 + 40, y1 + 26, 255, 255, 255, 5);
    myLineEdited(x1 + 40, y1 + 27, x1 + 40, y1 + 50, 255, 255, 255, 5);
}
void four(int x1, int y1, int x2, int y2)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    myRect(x1, y1, x2, y2, 0, 0, 255);
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 8, y1 + 3, x1 - 8, y1 + 26, 255, 255, 255, 5);
    myLineEdited(x1 - 8, y1 + 25, x2 - 10, y1 + 25, 255, 255, 255, 5);
    myLineEdited(x1 + 40, y1 + 3, x1 + 40, y1 + 50, 255, 255, 255, 5);
}
void five(int x1, int y1, int x2, int y2)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    myRect(x1, y1, x2, y2, 0, 0, 255);
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 8, y1 + 3, x2 - 10, y1 + 3, 255, 255, 255, 5);
    myLineEdited(x1 - 8, y1 + 26, x2 - 10, y1 + 26, 255, 255, 255, 5);
    myLineEdited(x1 - 8, y1 + 50, x2 - 10, y1 + 50, 255, 255, 255, 5);
    myLineEdited(x1 - 8, y1 + 3, x1 - 8, y1 + 26, 255, 255, 255, 5);
    myLineEdited(x1 + 40, y1 + 27, x1 + 40, y1 + 50, 255, 255, 255, 5);
}
void seven(int x1, int y1, int x2, int y2)
{
    myRect(x1, y1, x2, y2, 0, 0, 255);
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 8, y1 + 3, x2 - 10, y1 + 3, 255, 255, 255, 5);
    myLineEdited(x2 - 10, y1 + 3, x2 - 40, y1 + 60, 255, 255, 255, 5);
}
void eight(int x1, int y1, int x2, int y2)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    myRect(x1, y1, x2, y2, 0, 0, 255);
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 8, y1 + 3, x2 - 10, y1 + 3, 255, 255, 255, 5);
    myLineEdited(x1 - 8, y1 + 26, x2 - 10, y1 + 26, 255, 255, 255, 5);
    myLineEdited(x1 - 8, y1 + 50, x2 - 10, y1 + 50, 255, 255, 255, 5);
    myLineEdited(x1 + 40, y1 + 3, x1 + 40, y1 + 26, 255, 255, 255, 5);
    myLineEdited(x1 + 40, y1 + 27, x1 + 40, y1 + 50, 255, 255, 255, 5);
    myLineEdited(x1 - 8, y1 + 3, x1 - 8, y1 + 26, 255, 255, 255, 5);
    myLineEdited(x1 - 8, y1 + 27, x1 - 8, y1 + 50, 255, 255, 255, 5);
}
void six(int x1, int y1, int x2, int y2)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    myRect(x1, y1, x2, y2, 0, 0, 255);
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 8, y1 + 3, x2 - 10, y1 + 3, 255, 255, 255, 5);
    myLineEdited(x1 - 8, y1 + 26, x2 - 10, y1 + 26, 255, 255, 255, 5);
    myLineEdited(x1 - 8, y1 + 50, x2 - 10, y1 + 50, 255, 255, 255, 5);
    myLineEdited(x1 - 8, y1 + 3, x1 - 8, y1 + 50, 255, 255, 255, 5);
    myLineEdited(x1 + 40, y1 + 27, x1 + 40, y1 + 50, 255, 255, 255, 5);
}
void nine(int x1, int y1, int x2, int y2)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    myRect(x1, y1, x2, y2, 0, 0, 255);
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 8, y1 + 3, x2 - 10, y1 + 3, 255, 255, 255, 5);
    myLineEdited(x1 - 8, y1 + 26, x2 - 10, y1 + 26, 255, 255, 255, 5);
    myLineEdited(x1 - 8, y1 + 50, x2 - 10, y1 + 50, 255, 255, 255, 5);
    myLineEdited(x1 + 40, y1 + 3, x1 + 40, y1 + 26, 255, 255, 255, 5);
    myLineEdited(x1 + 40, y1 + 27, x1 + 40, y1 + 50, 255, 255, 255, 5);
    myLineEdited(x1 - 8, y1 + 3, x1 - 8, y1 + 26, 255, 255, 255, 5);
}
void S(int x1, int y1, int x2, int y2, int w)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 8, y1 + 3, x2 - 10, y1 + 3, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 26, x2 - 10, y1 + 26, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 50, x2 - 10, y1 + 50, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 3, x1 - 8, y1 + 26, 255, 255, 255, w);
    myLineEdited(x1 + 20, y1 + 27, x1 + 20, y1 + 50, 255, 255, 255, w);
}
void C(int x1, int y1, int x2, int y2, int w)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 8, y1 + 3, x2 - 10, y1 + 3, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 50, x2 - 10, y1 + 50, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 3, x1 - 8, y1 + 26, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 26, x1 - 8, y1 + 49, 255, 255, 255, w);
}
void O(int x1, int y1, int x2, int y2, int w)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 8, y1 + 3, x2 - 10, y1 + 3, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 50, x2 - 10, y1 + 50, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 3, x1 - 8, y1 + 26, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 26, x1 - 8, y1 + 49, 255, 255, 255, w);
    myLineEdited(x2 - 10, y1 + 3, x2 - 10, y1 + 49, 255, 255, 255, w);
}
void R(int x1, int y1, int x2, int y2, int w)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 8, y1 + 3, x2 - 10, y1 + 3, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 3, x1 - 8, y1 + 50, 255, 255, 255, w);
    myLineEdited(x2 - 10, y1 + 3, x2 - 10, y1 + 24, 255, 255, 255, w);
    myLineEdited(x2 - 10, y1 + 24, x1 - 8, y1 + 24, 255, 255, 255, w);
    myLineEdited(x2 - 20, y1 + 24, x2 - 10, y1 + 50, 255, 255, 255, w);
}
void E(int x1, int y1, int x2, int y2, int width)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 8, y1 + 3, x2 - 10, y1 + 3, 255, 255, 255, width);
    myLineEdited(x1 - 8, y1 + 3, x1 - 8, y1 + 50, 255, 255, 255, width);
    myLineEdited(x2 - 10, y1 + 24, x1 - 8, y1 + 24, 255, 255, 255, width);
    myLineEdited(x1 - 8, y1 + 50, x2 - 10, y1 + 50, 255, 255, 255, width);
}
void T(int x1, int y1, int x2, int y2)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    int a1 = x1, b1 = y1, a2 = x2, b2 = y2;
    a1 += 4 * d;
    b1 += 3 * d;
    b2 -= 4 * d;
    a2 -= 2 * d;
    myLineEdited(a1, b1, a2 + 2, b1, 255, 255, 255, 5);
    myLineEdited(a1 + 16, b1, a1 + 16, b2 + 25, 255, 255, 255, 5);
}
void I(int x1, int y1, int x2, int y2)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    int a1 = x1, b1 = y1, a2 = x2, b2 = y2;
    a1 += 4 * d;
    b1 += 3 * d;
    b2 -= 4 * d;
    a2 -= 2 * d;
    myLineEdited(a1, b1, a1, b2 - 30 + 12, 255, 255, 255, 5);
}
void M(int x1, int y1, int x2, int y2, int width)
{
    int d = (x2 - x1) / 20, h = (y2 - y1) / 5;
    x1 += 4 * d;
    y1 += 4 * h;
    x2 -= 4 * d;
    y2 -= 4 * h;
    myLineEdited(x1, y1 + 10, x1, y2 - 12 + 10, 255, 255, 255, width);
    myLineEdited(x2, y1 + 10, x2, y2 - 12 + 10, 255, 255, 255, width);
    x1 += 7 * d;
    y1 -= h;
    myLineEdited(x1, y1, x2, y2, 255, 255, 255, width);
    x2 -= 14 * d;
    myLineEdited(x2, y2, x1, y1, 255, 255, 255, width);
}
void Sedited(int x1, int y1, int x2, int y2, int w)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 8, y1 + 3, x2 - 10, y1 + 3, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 46, x2 - 10, y1 + 46, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 90, x2 - 10, y1 + 90, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 3, x1 - 8, y1 + 46, 255, 255, 255, w);
    myLineEdited(x1 + 70, y1 + 46, x1 + 70, y1 + 90, 255, 255, 255, w);
}
void Cedited(int x1, int y1, int x2, int y2, int w)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 8, y1 + 3, x2 - 10, y1 + 3, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 90, x2 - 10, y1 + 90, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 3, x1 - 8, y1 + 90, 255, 255, 255, w);
}
void Oedited(int x1, int y1, int x2, int y2, int w)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 8, y1 + 3, x2 - 10, y1 + 3, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 100, x2 - 10, y1 + 100, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 3, x1 - 8, y1 + 100, 255, 255, 255, w);
    myLineEdited(x2 - 10, y1 + 3, x2 - 10, y1 + 100, 255, 255, 255, w);
}
void Redited(int x1, int y1, int x2, int y2, int w)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 8, y1 + 3, x2 - 10, y1 + 3, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 60, x2 - 10, y1 + 60, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 3, x1 - 8, y1 + 102, 255, 255, 255, w);
    myLineEdited(x2 - 10, y1 + 3, x2 - 10, y1 + 60, 255, 255, 255, w);
    myLineEdited(x2 - 20, y1 + 75, x2 - 10, y1 + 102, 255, 255, 255, w);
}
void P(int x1, int y1, int x2, int y2, int w)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 8, y1 + 3, x2 - 10, y1 + 3, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 60, x2 - 10, y1 + 60, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 3, x1 - 8, y1 + 102, 255, 255, 255, w);
    myLineEdited(x2 - 10, y1 + 3, x2 - 10, y1 + 60, 255, 255, 255, w);
}
void L(int x1, int y1, int x2, int y2, int w)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 8, y1 + 3, x1 - 8, y1 + 102, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 102, x2 - 10, y1 + 102, 255, 255, 255, w);
}
void A(int x1, int y1, int x2, int y2, int w)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 8, y1 + 3, x2 - 10, y1 + 3, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 50, x2 - 10, y1 + 50, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 3, x1 - 8, y1 + 100, 255, 255, 255, w);
    myLineEdited(x2 - 10, y1 + 3, x2 - 10, y1 + 100, 255, 255, 255, w);
}
void Y(int x1, int y1, int x2, int y2, int w)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 8, y1 + 50, x2 - 10, y1 + 50, 255, 255, 255, w);
    myLineEdited(x1 - 8, y1 + 3, x1 - 8, y1 + 50, 255, 255, 255, w);
    myLineEdited(x2 - 10, y1 + 3, x2 - 10, y1 + 50, 255, 255, 255, w);
    myLineEdited(x1 + 34, y1 + 60, x1 + 34, y1 + 110, 255, 255, 255, w);

}
void Eedited(int x1, int y1, int x2, int y2, int width)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 8, y1 + 3, x2 - 6, y1 + 3, 255, 255, 255, width);
    myLineEdited(x1 - 8, y1 + 3, x1 - 4, y2 - 50, 255, 255, 255, width);
    myLineEdited(x1 - 8, y1 + 60, x2 - 6, y1 + 60, 255, 255, 255, width);
    myLineEdited(x1 - 8, y2 - 50, x2 - 6, y2 - 50, 255, 255, 255, width);
}
void X(int x1, int y1, int x2, int y2, int width)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    x1 += 4 * d;
    y1 += 3 * d;
    y2 -= 4 * d;
    x2 -= 2 * d;
    myLineEdited(x1 - 4, y1 + 13, x1 + 45, y2 - 60, 255, 255, 255, width);
    myLineEdited(x1 + 45, y1 + 13, x1 - 4, y2 - 60, 255, 255, 255, width);

}
void Iedited(int x1, int y1, int x2, int y2, int w)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    int a1 = x1, b1 = y1, a2 = x2, b2 = y2;
    a1 += 4 * d;
    b1 += 3 * d;
    b2 -= 4 * d;
    a2 -= 2 * d;
    myLineEdited(a1, b1, a1, b2 - 30 + 12, 255, 255, 255, w);
}
void Tedited(int x1, int y1, int x2, int y2, int w)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    int a1 = x1, b1 = y1, a2 = x2, b2 = y2;
    a1 += 4 * d;
    b1 += 3 * d;
    b2 -= 4 * d;
    a2 -= 2 * d;
    myLineEdited(a1 - 90, b1 + 10, a2 - 90, b1 + 10, 255, 255, 255, w);
    myLineEdited(a1 + 15 - 70, b1 + 10, a1 + 15 - 70, b2 - 30, 255, 255, 255, w);
}
void N(int x1, int y1, int x2, int y2, int width)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    x1 += 4 * d;
    y1 += 2 * h;
    y2 -= 2 * h;
    x2 -= 2 * d;
    myLineEdited(x1, y1, x1, y2, 255, 255, 255, width);
    myLineEdited(x2, y1, x2, y2, 255, 255, 255, width);
    myLineEdited(x1, y1, x2, y2, 255, 255, 255, width);
}
void U(int x1, int y1, int x2, int y2, int width)
{
    int d = (x2 - x1) / 12, h = (y2 - y1) / 12;
    x1 += 4 * d;
    y1 += 2 * h;
    y2 -= 2 * h;
    x2 -= 2 * d;
    myLineEdited(x1, y1, x1, y2, 255, 255, 255, width);
    myLineEdited(x2, y1, x2, y2, 255, 255, 255, width);
    myLineEdited(x1, y2, x2, y2, 255, 255, 255, width);
}
void curtains()                           // this function is to display curtains at the menu and exit
{
    int xstart = -968, xmid = 968, xend = 2904, ystart = -700, ymid = 540;
    for (int i = 0; i < 3; i++)
    {
        myEllipse((xmid / 2) - 2904, 180, xmid / 2, 2900 - 180, 0, 0, 0);
        myEllipse((xmid / 2) - 2904 - 10, 180, (xmid / 2) - 10, 2900 - 180 - 10, 255, 190, 200);
        myEllipse((xmid / 2) + xmid + 50, 180 + 100, xend + (xend * (75 / 100)) + 200 + 50, 2900 - 180 + 100, 0, 0, 0);
        myEllipse((xmid / 2) + xmid + 7 + 50, 180 + 100, xend + (xend * (75 / 100)) + 7 + 200 + 50, 2900 - 180 + 7 + 100, 255, 190, 200);
        myEllipse(xstart, ystart, xmid, ymid, 0, 0, 0);
        myEllipse(xmid - 17, ystart + 10, xend, ymid + 5, 0, 0, 0);
        myEllipse(xstart - 5, ystart - 5, xmid - 5, ymid - 5, 255, 190, 200);
        myEllipse(xmid - 15, ystart - 5, xend - 15, ymid - 5, 255, 190, 200);
        myEllipse(0 - 20, ymid, 0 + 20, ymid + 40, 0, 0, 0);
        myEllipse(1936 - 40, ymid, 1936 + 10, ymid + 40, 0, 0, 0);
        myLineEdited(180, 480, 868, 100, 0, 0, 0, 5);
        myLineEdited(210, 370, 678, 130, 0, 0, 0, 5);
        myLineEdited(210 + 60, 370 - 90, 678 - 190, 130 + 30, 0, 0, 0, 5);
        myLineEdited(1936 - 180, 480, 1936 - 868, 100, 0, 0, 0, 5);
        myLineEdited(1936 - 210, 370, 1936 - 678, 130, 0, 0, 0, 5);
        myLineEdited(1936 - 270, 370 - 90, 1936 - (678 - 190), 130 + 30, 0, 0, 0, 5);
        myLineEdited(60, 590, 340, 1000, 0, 0, 0, 5);
        myLineEdited(70, 680, 250, 960, 0, 0, 0, 5);
        myLineEdited(1936 - 60, 590, 1936 - 330, 1000, 0, 0, 0, 5);
        myLineEdited(1936 - 70, 680, 1936 - 240, 960, 0, 0, 0, 5);
    }
}
void menu()                            //The word menu on the cover page
{
    M(675, 300, 825, 450, 25);
    Eedited(800, 290, 945, 530, 25);
    N(900, 300, 1070, 465, 25);
    U(1025, 300, 1195, 465, 25);
}
void scoreExit(int Score)                         //this is to display score at the exit page
{
    int x1 = 162.5 + 600, x2 = x1 + 90, y1 = 470, y2 = y1 + 90;
    if (Score / 1000 == 1)
        one(x1, y1, x2, y2);
    else if (Score / 1000 == 2)
        two(x1, y1, x2, y2);
    else if (Score / 1000 == 3)
        three(x1, y1, x2, y2);
    else if (Score / 1000 == 4)
        four(x1, y1, x2, y2);
    else if (Score / 1000 == 5)
        five(x1, y1, x2, y2);
    else if (Score / 1000 == 6)
        six(x1, y1, x2, y2);
    else if (Score / 1000 == 7)
        seven(x1, y1, x2, y2);
    else if (Score / 1000 == 8)
        eight(x1, y1, x2, y2);
    else if (Score / 1000 == 9)
        nine(x1, y1, x2, y2);
    x1 += 100;
    x2 = x1 + 90;
    if (Score / 1000 != 0 && (Score % 1000) / 100 == 0)
        zero(x1, y1, x2, y2);
    Score = Score % 1000;
    if (Score / 100 == 1)
        one(x1, y1, x2, y2);
    else if (Score / 100 == 2)
        two(x1, y1, x2, y2);
    else if (Score / 100 == 3)
        three(x1, y1, x2, y2);
    else if (Score / 100 == 4)
        four(x1, y1, x2, y2);
    else if (Score / 100 == 5)
        five(x1, y1, x2, y2);
    else if (Score / 100 == 6)
        six(x1, y1, x2, y2);
    else if (Score / 100 == 7)
        seven(x1, y1, x2, y2);
    else if (Score / 100 == 8)
        eight(x1, y1, x2, y2);
    else if (Score / 100 == 9)
        nine(x1, y1, x2, y2);
    Score = Score % 100;
    x1 += 100;
    x2 = x1 + 90;
    if (Score / 10 == 1)
        one(x1, y1, x2, y2);
    else if (Score / 10 == 2)
        two(x1, y1, x2, y2);
    else if (Score / 10 == 3)
        three(x1, y1, x2, y2);
    else if (Score / 10 == 4)
        four(x1, y1, x2, y2);
    else if (Score / 10 == 5)
        five(x1, y1, x2, y2);
    else if (Score / 10 == 6)
        six(x1, y1, x2, y2);
    else if (Score / 10 == 7)
        seven(x1, y1, x2, y2);
    else if (Score / 10 == 8)
        eight(x1, y1, x2, y2);
    else if (Score / 10 == 9)
        nine(x1, y1, x2, y2);
    else if (Score / 10 == 0)
        zero(x1, y1, x2, y2);
    x1 += 100;
    x2 = x1 + 90;
    if (Score % 10 == 0)
        zero(x1, y1, x2, y2);
    else if (Score % 10 == 1)
        one(x1, y1, x2, y2);
    else if (Score % 10 == 2)
        two(x1, y1, x2, y2);
    else if (Score % 10 == 3)
        three(x1, y1, x2, y2);
    else if (Score % 10 == 4)
        four(x1, y1, x2, y2);
    else if (Score % 10 == 5)
        five(x1, y1, x2, y2);
    else if (Score % 10 == 6)
        six(x1, y1, x2, y2);
    else if (Score % 10 == 7)
        seven(x1, y1, x2, y2);
    else if (Score % 10 == 8)
        eight(x1, y1, x2, y2);
    else if (Score % 10 == 9)
        nine(x1, y1, x2, y2);
}
void Exit(int& i)                        // the exit page display and programming
{
    i = 6;
    system("color D5");
    curtains();
    Sedited(675 - 50, 300, 825 - 50, 450, 25);
    Cedited(825 - 70, 300, 975 - 70, 450, 25);
    Oedited(975 - 80, 300, 1125 - 80, 450, 25);
    Redited(1125 - 90, 300, 1280 - 90, 450, 25);
    Eedited(1280 - 100, 300, 1435 - 100, 540, 25);
    scoreExit(score);
    Eedited(700, 550, 855, 790, 25);
    X(855, 550, 955, 790, 25);
    Iedited(940, 545, 1120, 780, 25);
    Tedited(1100, 545, 1240, 780, 25);
    P(670, 720, 825, 955, 25);
    L(825, 730, 925, 945, 25);
    A(920, 720, 1070, 955, 25);
    Y(1070, 720, 1220, 955, 25);

    int x1 = 660, y1 = 570, x2 = 1250, y2 = 730, key;
    myRectOutline(x1, y1, x2, y2, 255, 255, 255, 4);
    while (1)
    {
        if (isCursorKeyPressed(key))
        {
            if (key == 5)
                break;
            else if (GetAsyncKeyState(VK_UP) && i != 6)
            {


                myRectOutline(x1, y1, x2, y2, 255, 103, 180, 4);
                y1 -= 160, y2 -= 160;
                myRectOutline(x1, y1, x2, y2, 255, 255, 255, 4);
                i = 0;
            }
            else if (GetAsyncKeyState(VK_DOWN) && i < 7)
            {
                i = 1;
                myRectOutline(x1, y1, x2, y2, 255, 103, 180, 4);
                y1 += 160, y2 += 160;
                myRectOutline(x1, y1, x2, y2, 255, 255, 255, 4);
            }
        }
    }
}
void remaining_time(int remainingTime)                         //this shows how much time is left for the user
{
    int x1 = 352.5, x2 = x1 + 90, y1 = 180, y2 = y1 + 90;
    T(x1, y1, x2 - 45, y2 - 45);
    x1 += 45;
    x2 = x1 + 45;
    I(x1, y1, x2, y2);
    x1 += 20;
    x2 = x1 + 45;
    M(x1, y1 - 8, x2, y2 - 25, 5);
    x1 += 45;
    x2 = x1 + 45;
    E(x1, y1 - 2, x2, y2 - 25, 5);
    x1 = 352.5;
    x2 = x1 + 90;
    y1 += 90;
    y2 = y1 + 90;
    if (remainingTime / 10 == 1)
        one(x1, y1, x2, y2);
    else if (remainingTime / 10 == 2)
        two(x1, y1, x2, y2);
    else if (remainingTime / 10 == 3)
        three(x1, y1, x2, y2);
    else if (remainingTime / 10 == 4)
        four(x1, y1, x2, y2);
    else if (remainingTime / 10 == 5)
        five(x1, y1, x2, y2);
    else if (remainingTime / 10 == 6)
        six(x1, y1, x2, y2);
    else if (remainingTime / 10 == 0)
        zero(x1, y1, x2, y2);
    x1 += 100;
    x2 = x1 + 90;
    if (remainingTime % 10 == 0)
        zero(x1, y1, x2, y2);
    else if (remainingTime % 10 == 1)
        one(x1, y1, x2, y2);
    else if (remainingTime % 10 == 2)
        two(x1, y1, x2, y2);
    else if (remainingTime % 10 == 3)
        three(x1, y1, x2, y2);
    else if (remainingTime % 10 == 4)
        four(x1, y1, x2, y2);
    else if (remainingTime % 10 == 5)
        five(x1, y1, x2, y2);
    else if (remainingTime % 10 == 6)
        six(x1, y1, x2, y2);
    else if (remainingTime % 10 == 7)
        seven(x1, y1, x2, y2);
    else if (remainingTime % 10 == 8)
        eight(x1, y1, x2, y2);
    else if (remainingTime % 10 == 9)
        nine(x1, y1, x2, y2);
}
void scoreee(int Score)                           // this shows the score of the user while playing the game
{
    int x1 = 102.5 + 135, x2 = x1 + 45, y1 = 480 + 18, y2 = y1 + 45;
    S(x1, y1, x2, y2, 5);
    x1 += 45;
    x2 = x1 + 45;
    C(x1, y1, x2, y2, 5);
    x1 += 45;
    x2 = x1 + 45;
    O(x1, y1, x2, y2, 5);
    x1 += 45;
    x2 = x1 + 45;
    R(x1, y1, x2, y2, 5);
    x1 += 45;
    x2 = x1 + 45;
    E(x1, y1, x2, y2, 5);
    x1 = 162.5;
    x2 = x1 + 90;
    y1 = 570;
    y2 = y1 + 90;
    if (Score / 1000 == 1)
        one(x1, y1, x2, y2);
    else if (Score / 1000 == 2)
        two(x1, y1, x2, y2);
    else if (Score / 1000 == 3)
        three(x1, y1, x2, y2);
    else if (Score / 1000 == 4)
        four(x1, y1, x2, y2);
    else if (Score / 1000 == 5)
        five(x1, y1, x2, y2);
    else if (Score / 1000 == 6)
        six(x1, y1, x2, y2);
    else if (Score / 1000 == 7)
        seven(x1, y1, x2, y2);
    else if (Score / 1000 == 8)
        eight(x1, y1, x2, y2);
    else if (Score / 1000 == 9)
        nine(x1, y1, x2, y2);
    x1 += 100;
    x2 = x1 + 90;
    if (Score / 1000 != 0 && (Score % 1000) / 100 == 0)
        zero(x1, y1, x2, y2);
    Score = Score % 1000;
    if (Score / 100 == 1)
        one(x1, y1, x2, y2);
    else if (Score / 100 == 2)
        two(x1, y1, x2, y2);
    else if (Score / 100 == 3)
        three(x1, y1, x2, y2);
    else if (Score / 100 == 4)
        four(x1, y1, x2, y2);
    else if (Score / 100 == 5)
        five(x1, y1, x2, y2);
    else if (Score / 100 == 6)
        six(x1, y1, x2, y2);
    else if (Score / 100 == 7)
        seven(x1, y1, x2, y2);
    else if (Score / 100 == 8)
        eight(x1, y1, x2, y2);
    else if (Score / 100 == 9)
        nine(x1, y1, x2, y2);
    Score = Score % 100;
    x1 += 100;
    x2 = x1 + 90;
    if (Score / 10 == 1)
        one(x1, y1, x2, y2);
    else if (Score / 10 == 2)
        two(x1, y1, x2, y2);
    else if (Score / 10 == 3)
        three(x1, y1, x2, y2);
    else if (Score / 10 == 4)
        four(x1, y1, x2, y2);
    else if (Score / 10 == 5)
        five(x1, y1, x2, y2);
    else if (Score / 10 == 6)
        six(x1, y1, x2, y2);
    else if (Score / 10 == 7)
        seven(x1, y1, x2, y2);
    else if (Score / 10 == 8)
        eight(x1, y1, x2, y2);
    else if (Score / 10 == 9)
        nine(x1, y1, x2, y2);
    else if (Score / 10 == 0)
        zero(x1, y1, x2, y2);
    x1 += 100;
    x2 = x1 + 90;
    if (Score % 10 == 0)
        zero(x1, y1, x2, y2);
    else if (Score % 10 == 1)
        one(x1, y1, x2, y2);
    else if (Score % 10 == 2)
        two(x1, y1, x2, y2);
    else if (Score % 10 == 3)
        three(x1, y1, x2, y2);
    else if (Score % 10 == 4)
        four(x1, y1, x2, y2);
    else if (Score % 10 == 5)
        five(x1, y1, x2, y2);
    else if (Score % 10 == 6)
        six(x1, y1, x2, y2);
    else if (Score % 10 == 7)
        seven(x1, y1, x2, y2);
    else if (Score % 10 == 8)
        eight(x1, y1, x2, y2);
    else if (Score % 10 == 9)
        nine(x1, y1, x2, y2);
}
void candyCrush(int& i)                         // this is the main game loop, where evrything is called in a specific manner to ensure smooth running of the game.
{

    int grid[8][8];
    int i1 = 1, j1 = 1;
    int x = 685, y = 270;
    bool mark[8][8];
    int special[8][8];
    cout << "                                               *****       *       *   *     ****     *   *                        *****      ****       *   *       ****       *   *" << endl;
    cout << "                                               *          * *      **  *     *   *     * *                         *          *   *      *   *      *           *   *" << endl;
    cout << "                                               *         *****     * * *     *   *      *                          *          ****       *   *       ***        *****" << endl;
    cout << "                                               *         *   *     *  **     *   *      *                          *          *  *       *   *          *       *   *" << endl;
    cout << "                                               *****     *   *     *   *     ****       *                          *****      *   *       ***       ****        *   *" << endl;
    graphic_grid();
    Sleep(100);
    grid_gen(grid, 8);
    grid_display(grid, 8);
    myRectOutline(x, y, x + STEP, y + STEP, 0, 0, 0, 7);
    //--- START TIMER ---
    auto startTime = std::chrono::steady_clock::now();
    const int GAME_DURATION = 60; // 60 seconds = 1 minute
    cout << "                                                                             Welcome to the game, each round is of one minute                                                                                      ";
    graphic_grid();
    grid_display(grid, 8);
    while (true)
    {
        //--- CHECK TIME ---
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
        int remainingTime = GAME_DURATION - elapsed;
        // --- DISPLAY TIMER ---
        COORD timerPos = { 0, 0 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), timerPos);
        remaining_time(remainingTime);
        scoreee(score);
        if (elapsed >= GAME_DURATION)
        {
            break;
        }
        // --- SAVE GRID BEFORE MOVE ---
        int before[8][8];
        for (int rr = 0; rr < 8; ++rr)
            for (int cc = 0; cc < 8; ++cc)
                before[rr][cc] = grid[rr][cc];
        // --- HANDLE PLAYER INPUT / MOVEMENT / SWAP ---
        bool moved = moving_positions(grid, i1, j1, x, y);
        if (moved)
        {
            Sleep(100);
        }
        // --- CHECK IF A SWAP OCCURRED ---
        bool swapped = false;
        for (int rr = 0; rr < 8 && !swapped; ++rr)
        {
            for (int cc = 0; cc < 8 && !swapped; ++cc)
            {
                if (before[rr][cc] != grid[rr][cc])
                {
                    swapped = true;
                }
            }
        }
        if (swapped)
        {
            while (true)
            {
                bool any = findMatches(grid);
                if (!any)
                {
                    break;
                }
                applyGravity(grid);
                system("color DF");
                grid_display(grid, 8);
                Sleep(120);
            }
        }
        Sleep(20);
    }
    Exit(i);
}


void Rules(int& i)                   // rules on the cover page
{
    i = 3;
    int key;
    curtains();
    myRectOutline(700, 350, 1220, 900, 184, 0, 3, 4);
    myRect(850, 290, 1075, 390, 255, 103, 180);
    myText(850, 290, "Rules", 184, 0, 3, 100, "Times New Roman");
    myText(715, 380, "1. There will be 5 different ", 255, 255, 255, 45, "Calibri");
    myText(715, 420, "candies on the board.", 255, 255, 255, 45, "Calibri");
    myText(715, 470, "2. Match of 3->Cadies explosion", 255, 255, 255, 45, "Calibri");
    myText(715, 520, "3. Match of 4 Vertically->Vertical", 255, 255, 255, 45, "Calibri");
    myText(715, 560, "Striped Candy", 255, 255, 255, 45, "Calibri");
    myText(715, 610, "4. Match of 4 Horizontally->", 255, 255, 255, 45, "Calibri");
    myText(715, 650, "Horizontal Striped Candy", 255, 255, 255, 45, "Calibri");
    myText(715, 700, "5. Match of 5->Disco ball", 255, 255, 255, 45, "Calibri");
    myText(715, 750, "6. Use arrow keys for cursor ", 255, 255, 255, 45, "Calibri");
    myText(715, 790, "movement", 255, 255, 255, 45, "Calibri");
    myText(715, 830, "7. Use shift+arrow key for swap", 255, 255, 255, 45, "Calibri");

    myText(700, 910, " Menu             Game              Exit", 255, 255, 255, 50, "Calibri");
    int x1 = 700, x2 = x1 + 120;
    myRectOutline(x1, 905, x2, 965, 184, 0, 3, 4);
    while (1)
    {
        if (isCursorKeyPressed(key) && key == 5)
            break;
        else if (GetAsyncKeyState(VK_LEFT) && i != 3)
        {
            myRectOutline(x1, 905, x2, 965, 255, 103, 180, 4);
            Sleep(100);
            x2 -= 220, x1 -= 220;
            myRectOutline(x1, 905, x2, 965, 184, 0, 3, 4);
            i--;
        }
        else if (GetAsyncKeyState(VK_RIGHT) && i < 5)
        {
            myRectOutline(x1, 905, x2, 965, 255, 103, 180, 4);
            Sleep(100);
            x2 += 220, x1 += 220;
            myRectOutline(x1, 905, x2, 965, 184, 0, 3, 4);
            i += 1;
        }
    }
}
void MENU(int& i)                          // the menu page, its display and all loop logic
{
    curtains();
    M(675, 300, 825, 450, 25);
    Eedited(800, 290, 945, 530, 25);
    N(900, 300, 1070, 465, 25);
    U(1025, 300, 1195, 465, 25);
    myText(830, 450, "Rules", 255, 255, 255, 100, "Calibri");
    myText(850, 530, "Play", 255, 255, 255, 100, "Calibri");
    myText(850, 610, "Exit", 255, 255, 255, 100, "Calibri");
    int x1 = 800, y1 = 460, x2 = 1040, y2 = 545;
    myRectOutline(x1, y1, x2, y2, 184, 0, 3, 4);
    i = 0;
    int key;
    while (1)
    {
        if (isCursorKeyPressed(key))
        {
            if (key == 5)
                break;
            else if (GetAsyncKeyState(VK_UP) && i != 0)
            {
                myRectOutline(x1, y1, x2, y2, 255, 103, 180, 4);
                y1 -= 80, y2 -= 80;
                myRectOutline(x1, y1, x2, y2, 184, 0, 3, 4);
                i--;
            }
            else if (GetAsyncKeyState(VK_DOWN) && i != 2)
            {
                myRectOutline(x1, y1, x2, y2, 255, 103, 180, 4);
                y1 += 80, y2 += 80;
                myRectOutline(x1, y1, x2, y2, 184, 0, 3, 4);
                i++;
            }
        }
    }
}
int main()
{
    int whatToDoNext;
    SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
    MENU(whatToDoNext);
    while (1)
    {
        system("cls");
        score = 0;
        if (whatToDoNext == 0)
            Rules(whatToDoNext);
        else if (whatToDoNext == 3)
            MENU(whatToDoNext);
        else if (whatToDoNext == 1 || whatToDoNext == 4 || whatToDoNext == 7)
            candyCrush(whatToDoNext);
        else if (whatToDoNext == 2 || whatToDoNext == 5 || whatToDoNext == 6)
            return 0;

    }

    return 0;
}
//end of game
//Khadija Imran   (25L-2521)
//Nigarish Naseem (25L-2019)

