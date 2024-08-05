#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

// Game variables
bool gameOver;
const int width = 20; // board width
const int height = 20; // height
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100]; // snake tail position arrays
int nTail; // length of the snake tail
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
bool wallsWithCollision = true; // game mode variable


void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2; // Snake starting position
    y = height / 2;
    fruitX = rand() % width; // Random fruit position
    fruitY = rand() % height;
    score = 0;
}

// Function to draw the game board
void Draw() {
    system("cls"); // Clear screen

    // top border
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    // Draw game area
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#"; // Left border
            if (i == y && j == x)
                cout << "O"; // Snake head
            else if (i == fruitY && j == fruitX)
                cout << "F"; // Fruit
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // tail
                        print = true;
                    }
                }
                if (!print)
                    cout << " "; // Empty space
            }

            if (j == width - 1)
                cout << "#"; // Right border
        }
        cout << endl;
    }

    // Draw bottom border
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    // Display score
    cout << "Your Score:" << score << endl;
}

// user input
void Input() {
    if (_kbhit()) { 
        switch (_getch()) {
        case 'a':
            dir = LEFT; 
            break;
        case 'd':
            dir = RIGHT; 
            break;
        case 'w':
            dir = UP; 
            break;
        case 's':
            dir = DOWN; 
            break;
        case 'x':
            gameOver = true; 
            break;
        }
    }
}

// game logic
void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
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

    // wall collision if mode is selected
    if (wallsWithCollision) {
        if (x >= width || x < 0 || y >= height || y < 0) {
            gameOver = true; // end game if collision mode
        }
    } else {
        // if mode is not collision --> allow passing through walls
        if (x >= width) x = 0; 
        else if (x < 0) x = width - 1;
        if (y >= height) y = 0;
        else if (y < 0) y = height - 1;
    }

    // check collision with itself
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    // check if snake ate the fruit (same coordinates)
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

// game mode menu
void DisplayMenu() {
    int choice;
    cout << "Welcome to Snake++!" << endl;
    cout << "Select Game Mode:" << endl;
    cout << "1. Wall Collision" << endl;
    cout << "2. Pass-Through Walls" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    // game mode
    if (choice == 1) {
        wallsWithCollision = true;
    } else if (choice == 2) {
        wallsWithCollision = false;
    } 
}
int main() {
    DisplayMenu(); // display game mode menu
    Setup(); // set up initial game state (with snake in the middle)
    while (!gameOver) {
        Draw(); // draw the game board
        Input(); // handle user input
        Logic(); // update game logic
        Sleep(100); // slow down the game (was too fast)
    }
    return 0;
}
