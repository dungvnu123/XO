#include <bits/stdc++.h>
using namespace std;

void drawboard(char *space) {
    cout << '\n';
    cout << "     |     |     " << '\n';
    cout << "  " << space[0] << "  |  " << space[1] << "  |  " << space[2] << "  " << '\n';
    cout << "-----|-----|------" << '\n';
    cout << "  " << space[3] << "  |  " << space[4] << "  |  " << space[5] << "  " << '\n';
    cout << "-----|-----|------" << '\n';
    cout << "  " << space[6] << "  |  " << space[7] << "  |  " << space[8] << "  " << '\n';
    cout << "     |     |     " << '\n';
}

void playerMove(char *space, char player) {
    int number;
    do {
        cout << "Moi ban chon mot so tu 1 den 9: ";
        cin >> number;
        number--; 
        if (number >= 0 && number < 9 && space[number] == ' ') {
            space[number] = player;
            break;
        } else {
            cout << "Vi tri khong hop le hoac da duoc danh dau. Vui long chon lai!\n";
        }
    } while (true);
}

void computerMove(char *space, char computer) {
    int number;
    srand(time(NULL));
    while (true) {
        number = rand() % 9;
        if (space[number] == ' ') {
            space[number] = computer;
            break;
        }
    }
}

bool checkWinner(char *space, char marker) {
    for (int i = 0; i < 9; i += 3) {
        if (space[i] != ' ' && space[i] == space[i + 1] && space[i] == space[i + 2]) {
            return true;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (space[i] != ' ' && space[i] == space[i + 3] && space[i] == space[i + 6]) {
            return true;
        }
    }
    if (space[0] != ' ' && space[0] == space[4] && space[0] == space[8]) {
        return true;
    }
    if (space[2] != ' ' && space[2] == space[4] && space[2] == space[6]) {
        return true;
    }
    return false;
}

bool checkTie(char *space) {
    for (int i = 0; i <= 8; i++) {
        if (space[i] == ' ') {
            return false;
        }
    }
    cout << "Great!\n";
    return true;
}

int main() {
    char space[9] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
    char player = 'X';
    char computer = 'O';
    bool running = true;

    while (running) {
        drawboard(space);
        playerMove(space, player);
        if (checkWinner(space, player)) {
            drawboard(space);
            cout << "You win!\n";
            running = false;
            break;
        } else if (checkTie(space)) {
            drawboard(space);
            cout << " Great! ";
            running = false;
            break;
        }

        computerMove(space, computer);
        if (checkWinner(space, computer)) {
            drawboard(space);
            cout << "You lost!\n";
            running = false;
            break;
        } else if (checkTie(space)) {
            drawboard(space);
            cout << " Great! ";
            running = false;
            break;
        }
    }

    cout << "Cam on ban da tham gia tro choi!\n";
    return 0;
}

