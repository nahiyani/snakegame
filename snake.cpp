#include <iostream>
#include <cstdlib>
#include <conio.h>
using namespace std;

bool gameOver;
const int width = 20, height = 20;
int x, y, fruitX, fruitY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
int tailX[100], tailY[100];
int nTail;

void setup(){

    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    score = 0;
    fruitX = rand() % width;
    fruitY= rand() % height;

}

void draw(){

    system("cls");
    for (int i = 0; i < width + 2; i++){
        cout << "#";
    }
    cout << endl;
    
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "🍉";
            else{
                bool print = false;
                for (int k = 0; k < nTail; k++){
                    if (tailX[k] == j && tailY[k] == i){
                        cout << "o";
                        print = true;
                    }
                }
                if (!print){
                    cout << " ";
                }
            }    
                
            
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++){
        cout << "#";
    }
    cout << endl;
     cout << endl;
    cout << "Score: " << score << endl;
   
}

void input() {
    if (_kbhit()) {
        int key = _getch();
        
        if (key == 224) { 
            switch (_getch()) {
                case 72: 
                    dir = UP;
                    break;
                case 80: 
                    dir = DOWN;
                    break;
                case 75: 
                    dir = LEFT;
                    break;
                case 77: 
                    dir = RIGHT;
                    break;
            }
        } else {
            switch (key) {
                case 'x':
                    gameOver = true;
                    break;
            }
        }
    }
}

void logic(){

    int previousX = tailX[0];
    int previousY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for(int i = 1; i < nTail; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = previousX;
        tailY[i] = previousY;
        previousX = prev2X;
        previousY = prev2Y;
    }
    
    switch(dir){
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

    if (x > width || x < 0 || y > height || y < 0){
        gameOver = true;
    }

    for (int i = 0; i < nTail; i++){
        if (tailX[i] == x && tailY[i] == y){
            gameOver = true;
        }
    }


    if (x == fruitX && y == fruitY){
        nTail++;
        score++;
        fruitX = rand() % width;
        fruitY= rand() % height;
    }

}

int main(){

    setup();
    draw();
   
    while (!gameOver){
        draw();
        input();
        logic();
    }

    return 0;
}