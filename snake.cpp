#include <iostream>
#include <cstdlib>
#include <windows.h>  
using namespace std;

bool gameOver;
const int width = 20, height = 20;
int x, y, fruitX, fruitY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
int tailX[100], tailY[100];
int nTail;

void setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    score = 0;
    fruitX = rand() % width;
    fruitY = rand() % height;
}

void draw() {
    system("cls");

    for (int i = 0; i < width + 2; i++) {
        cout << "#";
    }
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#"; 
            if (i == y && j == x)
                cout << "O";  
            else if (i == fruitY && j == fruitX)
                cout << "F";  
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; 
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";  
            }

            if (j == width - 1)
                cout << "#"; 
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++) {
        cout << "#";
    }
    cout << endl;

    cout << "Score: " << score << endl;
}

void input() {
    if (GetAsyncKeyState(VK_UP) & 0x8000)
        dir = UP;
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
        dir = DOWN;
    else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        dir = LEFT;
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        dir = RIGHT;
    else if (GetAsyncKeyState('X') & 0x8000)
        gameOver = true;
}

void logic() {
    int previousX = tailX[0];
    int previousY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = previousX;
        tailY[i] = previousY;
        previousX = prev2X;
        previousY = prev2Y;
    }

    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }

    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }

    if (x == fruitX && y == fruitY) {
        nTail++;
        score++;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}

int main() {
    setup();

    while (!gameOver) {
        draw();
        input();
        logic();
    }

    return 0;
}
