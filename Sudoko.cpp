#include <iostream>
#include <cstdlib>
using namespace std;

const int N = 9;
bool isSolvedCompletely(int grid[N][N]) {
    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++)
            if (grid[row][col] == 0)
                return false;

    return true;
}

bool isSafe(int board[N][N], int row, int col, int num) {
    for (int i = 0; i < N; ++i)
        if (board[row][i] == num || board[i][col] == num || board[row - row % 3 + i / 3][col - col % 3 + i % 3] == num)
            return false;
    return true;
}

void printBoard(int grid[N][N]) {
    system("cls");
    cout << "\t\t\t<================================================================================>" << endl
         << "\t\t\t|                        WELCOME IN MY SUDOKO GAME                               |" << endl
         << "\t\t\t|                       Fill in the missing numbers                              |" << endl
         << "\t\t\t<================================================================================>" << endl;
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col)
            cout << (col == 3 || col == 6 ? " | " : " ") << grid[row][col];
        cout << (row == 2 || row == 5 ? "\n---------------------" : "") << endl;
    }
}

bool solveSudoku(int board[N][N], int row, int col) {
    if (row == N - 1 && col == N)
        return true;
    if (col == N) {
        row++;
        col = 0;
    }
    if (board[row][col] != 0)
        return solveSudoku(board, row, col + 1);

    for (int num = 1; num <= 9; ++num) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;
            if (solveSudoku(board, row, col + 1))
                return true;
            board[row][col] = 0;
        }
    }
    return false;
}

void playGame(int board[N][N]) {
    int row, col, num;
    while (true) {
        printBoard(board);
        cout << "\n\nUnable to solve? Enter -1 as row, col, and num to view the solved sudoku.\n"
             << "Enter row: ";
        cin >> row;
        cout << "Enter column: ";
        cin >> col;
        cout << "Enter number: ";
        cin >> num;

        if (row == -1 || col == -1 || num == -1) {
            solveSudoku(board, 0, 0);
            printBoard(board);
            cout << "\nBetter luck next time!!!\n";
            return;
        }

        if (isSolvedCompletely(board))
            break;

        row--;
        col--;

        if (!isSafe(board, row, col, num)) {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        board[row][col] = num;
    }

    bool solved = isSolvedCompletely(board);

    cout << (solved ? "Congratulations! You have solved the puzzle.\n" : "Puzzle not solved. Better luck next time.\n");
    printBoard(board);
}


int main() {
    system("title Sudoku Game @copyassignment");
    system("color B0");

    int board[N][N] = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

    cout << "\t\t\t<================================================================================>" << endl
         << "\t\t\t|                        WELCOME TO SUDOKU Game!                                 |" << endl
         << "\t\t\t|       Fill in the missing numbers(represented by 0) to solve the puzzle.       |" << endl
         << "\t\t\t<================================================================================>" << endl;

    while (true) {
        int choice;
        cout << "\n\n\t\t[1] Solve the Sudoku\n"
             << "\t\t[2] Unable to solve? View the solved Sudoku\n"
             << "\t\t[3] Exit\n"
             << "\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                playGame(board);
                break;
            case 2:
                if (solveSudoku(board, 0, 0)) {
                    cout << "Completely Solved Sudoku is:\n";
                    printBoard(board);
                    cout << "\nBetter luck next time!!!\n";
                } else {
                    cout << "No solution found\n";
                }
                break;
            case 3:
                exit(0);
            default:
                cout << "Invalid choice\n";
        }
    }

    return 0;
}
