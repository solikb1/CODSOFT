#include <iostream>
#include <cstdlib> 
#include <ctime>   

using namespace std;

char board[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };
char player1, player2, currentPlayer;
bool isAI = false; 

void displayBoard() {
    cout << "\nTic-Tac-Toe Game\n";
    cout << "Player 1 (" << player1 << ") - Player 2 (" << (isAI ? "AI" : "Player 2") << " " << player2 << ")\n\n";
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << " " << board[i][j] << " ";
            if (j < 2) cout << "|";
        }
        cout << endl;
        if (i < 2) cout << "---|---|---\n";
    }
    cout << endl;
}

bool winCheck() {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2]) || 
            (board[0][i] == board[1][i] && board[1][i] == board[2][i])) {
            return true;
        }
    }
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0])) {
        return true;
    }
    return false;
}

bool drawCheck() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != player1 && board[i][j] != player2) {
                return false;
            }
        }
    }
    return true;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == player1) ? player2 : player1;
}

bool makeMove(int position) {
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;

    if (board[row][col] != player1 && board[row][col] != player2) {
        board[row][col] = currentPlayer;
        return true;
    } else {
        return false;
    }
}

void aiMove() {
    srand(time(0));
    int move;
    do {
        move = (rand() % 9) + 1; 
    } while (!makeMove(move)); 

    cout << "AI chooses position " << move << endl;
}

int getValidMove() {
    int move;
    while (true) {
        cout << "Player " << currentPlayer << ", enter a number (1-9): ";
        if (cin >> move && move >= 1 && move <= 9 && makeMove(move)) {
            return move;
        }
        cout << "Invalid input. Try again.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

void resetBoard() {
    char num = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = num++;
        }
    }
}

void chooseOpponent() {
    char choice;
    while (true) {
        cout << "Do you want to play against the AI? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            isAI = true;
            break;
        } else if (choice == 'n' || choice == 'N') {
            isAI = false;
            break;
        } else {
            cout << "Invalid choice. Please enter 'y' or 'n'.\n";
        }
    }
}

void chooseSymbol() {
    while (true) {
        cout << "Player 1, choose your symbol (X or O): ";
        cin >> player1;
        player1 = toupper(player1);
        
        if (player1 == 'X' || player1 == 'O') {
            player2 = (player1 == 'X') ? 'O' : 'X';
            currentPlayer = player1;
            break;
        } else {
            cout << "Invalid input. Please choose 'X' or 'O'.\n";
        }
    }
}

int main() {
    int position;
    char playAgain;

    cout << "=================================\n";
    cout << "  Welcome to Tic-Tac-Toe Game!  \n";
    cout << "=================================\n\n";

    do {
        resetBoard();
        chooseOpponent(); 
        chooseSymbol();   
        bool gameRunning = true;

        while (gameRunning) {
            displayBoard();

            if (isAI && currentPlayer == player2) {
                aiMove();
            } else {
                position = getValidMove();
            }

            if (winCheck()) {
                displayBoard();
                cout << "Player " << currentPlayer << " wins!\n";
                gameRunning = false;
            } else if (drawCheck()) {
                displayBoard();
                cout << "It's a draw!\n";
                gameRunning = false;
            } else {
                switchPlayer();
            }
        }

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
        while (playAgain != 'y' && playAgain != 'Y' && playAgain != 'n' && playAgain != 'N') {
            cout << "Invalid input. Please enter 'y' or 'n': ";
            cin >> playAgain;
        }
    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing Tic-Tac-Toe!\n";
    return 0;
}
