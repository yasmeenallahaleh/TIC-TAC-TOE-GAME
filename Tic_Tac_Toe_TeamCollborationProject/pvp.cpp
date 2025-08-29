#include <string>
#include <vector>
#include <iostream>
#include "coin.h"
using namespace std;

void displayBoard(string boardSize, vector<string> board);
int manageCoins(int& totCoins, int winOrLose);

bool isWin(const vector<string>& b, char player, int N) {
    string P(1, player);

    for (int r = 0; r < N; ++r) {
        bool ok = true;
        for (int c = 0; c < N; ++c) {
            if (b[r * N + c] != P) { ok = false; break; }
        }
        if (ok) return true;
    }

    for (int c = 0; c < N; ++c) {
        bool ok = true;
        for (int r = 0; r < N; ++r) {
            if (b[r * N + c] != P) { ok = false; break; }
        }
        if (ok) return true;
    }

    bool okMain = true;
    for (int i = 0; i < N; ++i) if (b[i * N + i] != P) { okMain = false; break; }
    if (okMain) return true;

    bool okAnti = true;
    for (int i = 0; i < N; ++i) if (b[i * N + (N - 1 - i)] != P) { okAnti = false; break; }
    if (okAnti) return true;

    return false;
}

bool isDraw(const vector<string>& b) {
    for (size_t i = 0; i < b.size(); ++i) {
        if (b[i] != "X" && b[i] != "O") return false;
    }
    return true;
}

bool isFree(const vector<string>& b, int idx) {
    return b[idx] != "X" && b[idx] != "O";
}

void runPVP(const string& boardSize, int& totCoins) {
    int N = (boardSize == "3x3") ? 3 : 4;
    int len = N * N;

    vector<string> board;
    for (int i = 1; i <= len; ++i) board.push_back(to_string(i));

    cout << "\nTic-Tac-Toe PvP (" << boardSize << ")\n";
    cout << "Player X goes first. ";
    if (N == 3) cout << "Get 3 in a row.\n";
    else        cout << "Get 4 in a row.\n";

    displayBoard(boardSize, board);

    char player = 'X';
    while (true) {
        int spot;
        cout << "Player " << player << ", choose a spot (1-" << len << "): ";
        if (!(cin >> spot)) { cout << "\nInput error. Ending match.\n"; return; }

        if (spot < 1 || spot > len) {
            cout << "  Out of range. Please Try again.\n";
            continue;
        }
        int idx = spot - 1;
        if (!isFree(board, idx)) {
            cout << "  That spot is taken. Please Try again.\n";
            continue;
        }

        board[idx] = string(1, player);
        displayBoard(boardSize, board);

        if (isWin(board, player, N)) {
            cout << "Player " << player << " wins!\n";
            if(player = 'X'){
                totCoins = manageCoins(totCoins, 0);// from coins.cpp
            }
            else{
                totCoins = manageCoins(totCoins, 1);//from coins.cpp
            }
            break;
        }
        if (isDraw(board)) {
            cout << "It's a draw!\n";
            break;
        }

        player = (player == 'X') ? 'O' : 'X';
    }
}
