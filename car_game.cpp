#include<bits/stdc++.h>


#include <conio.h>
#include <windows.h>
#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];
char car[4][4] = { 
    ' ', 'O', 'O', ' ', 
    'O', '=', '=', 'O', 
    ' ', 'O', 'O', ' ', 
    'O', '=', '=', 'O' 
};


int carPos = WIN_WIDTH / 2;
int score = 0;

// Function declarations
void gotoxy(int x, int y);
void setcursor(bool visible, DWORD size);
void drawBorder();
void genEnemy(int ind);
void drawEnemy(int ind);
void eraseEnemy(int ind);
void resetEnemy(int ind);
void drawCar();
void eraseCar();
int collision();
void gameover();
void updateScore();
void instructions();
void play();

void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) {
    if (size == 0) size = 20;

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void drawBorder() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(0, i);
        cout << "|";
        gotoxy(WIN_WIDTH, i);
        cout << "|";
    }
}

void genEnemy(int ind) {
    enemyX[ind] = 17 + rand() % (33);
}

void drawEnemy(int ind) {
    if (enemyFlag[ind]) {
        gotoxy(enemyX[ind], enemyY[ind]);
        cout << "****";
        gotoxy(enemyX[ind], enemyY[ind] + 1);
        cout << " ** ";
        gotoxy(enemyX[ind], enemyY[ind] + 2);
        cout << "****";
        gotoxy(enemyX[ind], enemyY[ind] + 3);
        cout << " ** ";
    }
}

void eraseEnemy(int ind) {
    if (enemyFlag[ind]) {
        gotoxy(enemyX[ind], enemyY[ind]);
        cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 1);
        cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 2);
        cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 3);
        cout << "    ";
    }
}

void resetEnemy(int ind) {
    eraseEnemy(ind);
    enemyY[ind] = 1;
    genEnemy(ind);
}

void drawCar() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gotoxy(j + carPos, i + 22);
            cout << car[i][j];
        }
    }
}

void eraseCar() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gotoxy(j + carPos, i + 22);
            cout << " ";
        }
    }
}

int collision() {
    for (int i = 0; i < 3; i++) {
        if (enemyFlag[i] && enemyY[i] + 4 >= 22) {
            if (enemyX[i] + 4 > carPos && enemyX[i] < carPos + 4) {
                return 1;
            }
        }
    }
    return 0;
}

void gameover() {
    system("cls");
    cout << "\n\tGame Over\n";
    cout << "\nPress any key to return to the main menu.";
    getch();
}

void updateScore() {
    gotoxy(WIN_WIDTH + 7, 5);
    cout << "Score: " << score;
}

void instructions() {
    system("cls");
    cout << "Instructions\n";
    cout << "----------------\n";
    cout << "Avoid Cars by moving left or right.\n";
    cout << "Press 'a' to move left\n";
    cout << "Press 'd' to move right\n";
    cout << "Press 'Escape' to exit\n";
    cout << "\nPress any key to return to the menu.";
    getch();
}

void play() {
    carPos = WIN_WIDTH / 2;
    score = 0;
    enemyFlag[0] = enemyFlag[1] = enemyFlag[2] = 0;
    enemyY[0] = enemyY[1] = enemyY[2] = 1;

    system("cls");
    drawBorder();
    updateScore();

    genEnemy(0);
    enemyFlag[0] = 1;

    while (1) {
        if (kbhit()) {
            char ch = getch();
            if (ch == 'a' || ch == 'A') {
                if (carPos > 18) carPos -= 4;
            } else if (ch == 'd' || ch == 'D') {
                if (carPos < 50) carPos += 4;
            } else if (ch == 27) {
                break;
            }
        }

        drawCar();
        drawEnemy(0);

        if (collision()) {
            gameover();
            return;
        }

        Sleep(50);
        eraseCar();
        eraseEnemy(0);

        if (enemyFlag[0]) enemyY[0]++;

        if (enemyY[0] > SCREEN_HEIGHT - 4) {
            resetEnemy(0);
            score++;
            updateScore();
        }
    }
}

int main() {
    setcursor(0, 0);
    srand((unsigned)time(NULL));

    do {
        system("cls");
        gotoxy(10, 5);
        cout << "--------------------------";
        gotoxy(10, 6);
        cout << "|        Car Game        |";
        gotoxy(10, 7);
        cout << "--------------------------";
        gotoxy(10, 9);
        cout << "1. Start Game";
        gotoxy(10, 10);
        cout << "2. Instructions";
        gotoxy(10, 11);
        cout << "3. Quit";
        gotoxy(10, 13);
        cout << "Select option: ";
        char op = getche();

        if (op == '1') play();
        else if (op == '2') instructions();
        else if (op == '3') exit(0);

    } while (1);

    return 0;
}
