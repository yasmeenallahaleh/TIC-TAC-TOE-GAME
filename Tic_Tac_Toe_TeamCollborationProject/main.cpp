#include <string>
#include <vector>
#include <iostream>
#include "PvCPU.h"
#include "coin.h"
#include "arcade.h"
#include "pvp.cpp"

void runPVP(const std::string& boardSize, int& totCoins);
int givePlayerCoins(int& totCoins);
int manageCoins(int& totCoins, int winOrLose);
int enterArcade(int& totCoins);


class MenuOptions{
     public:
        std::string userMainMenuInput = " ";
    
        void menu(){ //Can be changed to add more features 
             std::cout << "Play" << std::endl;
             std::cout << "Arcade" << std::endl; 
             std::cout << "Quit" << std::endl;
       }
        void outputPicker(){
              std::cout << "What would you like to do ?" << std::endl;
              std::cout << "Please enter the options as they are shown above: ";
       }

       
};

void displayBoard(std::string boardSize, std::vector<std::string> board) {
    int outputCounter = 1;
    if (boardSize == "3x3") {
        for (std::string spot : board) {
            if (outputCounter%3 == 0) {
                std::cout << spot << std::endl;
                outputCounter += 1;
            }
            else {
                std::cout << spot << " ";
                outputCounter += 1;
            }
        }
        outputCounter = 1;
    }
    else { //Can change to add more board sizes
        outputCounter = 1;
        for (std::string spot : board) {
            if (outputCounter%4 == 0) {
                std::cout << spot << std::endl;
                outputCounter += 1;
            }
            else {
                std::cout << spot << " ";
                outputCounter += 1;
            }
        }
        outputCounter = 1;
    }
} //displayBoard(boardsize, board)

// --- ADDED (local helpers for PVAI result announcements) ---
static int N_from_boardSize_local(const std::string& boardSize, std::size_t len) {
    if (boardSize == "3x3" || len == 9) return 3;
    if (boardSize == "4x4" || len == 16) return 4;
    return 3;
}

static bool hasWin_local(const std::vector<std::string>& b, int N, const std::string& mark) {
    // rows
    for (int r = 0; r < N; ++r) {
        bool ok = true;
        for (int c = 0; c < N; ++c) if (b[r*N + c] != mark) { ok = false; break; }
        if (ok) return true;
    }
    // cols
    for (int c = 0; c < N; ++c) {
        bool ok = true;
        for (int r = 0; r < N; ++r) if (b[r*N + c] != mark) { ok = false; break; }
        if (ok) return true;
    }
    // main diag
    {
        bool ok = true;
        for (int i = 0; i < N; ++i) if (b[i*N + i] != mark) { ok = false; break; }
        if (ok) return true;
    }
    // anti diag
    {
        bool ok = true;
        for(int i = 0; i < N; ++i) if (b[i*N + (N-1-i)] != mark) { ok = false; break; }
        if (ok) return true;
    }
    return false;
}

static bool isDraw_local(const std::vector<std::string>& b) {
    for (const auto& cell : b) if (cell != "X" && cell != "O") return false;
    return true;
}
// --- END ADDED ---


int main() {

    MenuOptions menu;
    int totCoins = 0;
    totCoins = givePlayerCoins(totCoins);

    std::string backToMenu = " "; 
do{
         std::cout << "Welcome to Tic Tac Toe" << std::endl;
         menu.menu();
         menu.outputPicker();
         std::getline(std::cin, menu.userMainMenuInput);
     
         if (menu.userMainMenuInput == "Play") {
             std::cout << std::endl;
             std::cout << "Board Size: None Selected" << std::endl;
             std::cout << "Game Mode: None Selected" << std::endl;
             std::cout << "Side: None Selected" << std::endl;
     
             std::cout << "What would you like to select first ?" << std::endl;
             std::string playMenuInput = " ";
             std::cout << "Please enter Board for Board Size, Side for Side, and Mode for Game Mode ";
             std::cin >> playMenuInput;
     
             std::string boardSize = " ";
             std::string gameMode = " ";
             std::string side = " ";
             std::vector<std::string> board = {};
             if (playMenuInput == "Board") {
                 std::cout << std::endl;
                 std::cout << "What board size would you like to play on ?" << std::endl;
                 std::cout << "The size options are 3x3 or 4x4, please enter 3x3 or 4x4 ";
                 std::cin >> boardSize;
                 if (boardSize == "3x3") {
                     board = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
                 }
                 else { //Change this to an else if add more board sizes
                     board = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"};
                 }
     
                 std::cout << "What game mode would you like to play on ?" << std::endl;
                 std::cout << "The options are PVP or PVAI, please enter PVP or PVAI ";
                 std::cin >> gameMode;
     
                 std::cout << "Which side would you like to play as ?" << std::endl;
                 std::cout << "Please select X or O, please enter either X or O ";
                 std::cin >> side;
             }
             else if (playMenuInput == "Mode") {
                 std::cout << "What game mode would you like to play on ?" << std::endl;
                 std::cout << "The options are PVP or PVAI, please enter PVP or PVAI ";
                 std::cin >> gameMode;
     
                 std::cout << std::endl;
                 std::cout << "What board size would you like to play on ?" << std::endl;
                 std::cout << "The size options are 3x3 or 4x4, please enter 3x3 or 4x4 ";
                 std::cin >> boardSize;
                 if (boardSize == "3x3") {
                     board = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
                 }
                 else { //Change this to an else if to add more board sizes
                     board = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"};
                 }
     
                 std::cout << std::endl;
                 std::cout << "Which side would you like to play as ?" << std::endl;
                 std::cout << "Please select X or O, please enter either X or O ";
                 std::cin >> side;
             }
             else if (playMenuInput == "Side") {
                 std::cout << std::endl;
                 std::cout << "Which side would you like to play as ?" << std::endl;
                 std::cout << "Please select X or O, please enter either X or O ";
                 std::cin >> side;
     
                 std::cout << "What board size would you like to play on ?" << std::endl;
                 std::cout << "The size options are 3x3 or 4x4, please enter 3x3 or 4x4 ";
                 std::cin >> boardSize;
                 if (boardSize == "3x3") {
                     board = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
                 }
                 else { //Change this to an else if add more board sizes
                     board = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"};
                 }
     
                 std::cout << "What game mode would you like to play on ?" << std::endl;
                 std::cout << "The options are PVP or PVAI, please enter PVP or PVAI ";
                 std::cin >> gameMode;
             }
     
             else {
                 std::cout << "This is not an option";
             }
             std::cout << "You have selected" << std::endl;
             std::cout << "Board Size: " << boardSize << std::endl;
             std::cout << "Game Mode: " << gameMode << std::endl;
             std::cout << "Side: " << side << std::endl;
             std::string userPlayInput = " ";
             std::cout << "Would you like to play now ? " << std::endl;
             std::cout << "Please enter y for yes and n for no ";
             std::cin >> userPlayInput;
     
             if (userPlayInput == "y") {
                  if (gameMode == "PVP"){
                         runPVP(boardSize, totCoins);
                         std::cout << "Would you like to go back to the menu? (Yes or No)" << std::endl;
                         std::cin >> backToMenu;
                         if(backToMenu[0] == 'n'){
                            return 0;
                         }
                  }    
                       
                 if (gameMode == "PVAI") {
                     // --- PVCPU loop (only runs for PVAI) ---
                     const std::string humanSide = side;
                     const std::string cpuSide   = (side == "X" ? "O" : "X");
     
                     // Pick difficulty (default: Medium)
                     pvcpu::Difficulty diff = pvcpu::Difficulty::Medium;
                     std::string diffInput;
                     std::cout << "Select difficulty (Easy/Medium/Hard) [Medium]: ";
                     if (std::cin >> diffInput) {
                         if (diffInput == "Easy" || diffInput == "easy" || diffInput == "E" || diffInput == "e") {
                             diff = pvcpu::Difficulty::Easy;
                         } else if (diffInput == "Hard" || diffInput == "hard" || diffInput == "H" || diffInput == "h") {
                             diff = pvcpu::Difficulty::Hard;
                         } else {
                             diff = pvcpu::Difficulty::Medium;
                         }
                     }
                     std::cout << "Difficulty set to "
                               << (diff == pvcpu::Difficulty::Easy ? "Easy"
                                   : diff == pvcpu::Difficulty::Hard ? "Hard" : "Medium")
                               << std::endl;
     
                     // pvcpu::setRandomSeed(12345); // <- optional: deterministic CPU for demos
     
                     while (true) {
                         // Show board
                         std::cout << "\nCurrent board:\n";
                         displayBoard(boardSize, board);
     
                         // ----- Human turn -----
                         int spotInput = 0;
                         bool placed = false;
                         while (!placed) {
                             std::cout << "Your move (" << humanSide << "). Enter the spot number: ";
                             if (!(std::cin >> spotInput)) { std::cout << "Input ended.\n"; return 0; }
                             for (std::size_t i = 0; i < board.size(); ++i) {
                                 if (board[i] == std::to_string(spotInput)) {
                                     board[i] = humanSide;
                                     placed = true;
                                     break;
                                 }
                             }
                             if (!placed) std::cout << "Invalid spot. Try an empty numbered cell.\n";
                         }
     
                         // Check terminal after human move → ANNOUNCE RESULT
                         {
                             int N = N_from_boardSize_local(boardSize, board.size());
                             if (hasWin_local(board, N, humanSide)) {
                                 std::cout << "\nFinal board:\n";
                                 displayBoard(boardSize, board);
                                 std::cout << "You (" << humanSide << ") win!\n";
                                 manageCoins(totCoins, 0);
                                 break;
                             }
                             if (isDraw_local(board)) {
                                 std::cout << "\nFinal board:\n";
                                 displayBoard(boardSize, board);
                                 std::cout << "Draw.\n";
                                 break;
                             }
                         }
     
                         // ----- CPU turn -----
                         int cpuIdx = pvcpu::chooseCpuMove(board, boardSize, cpuSide, diff);
                         if (cpuIdx == -1) {
                             // If CPU returns -1 here, it means terminal (but we still announce properly)
                             int N = N_from_boardSize_local(boardSize, board.size());
                             std::cout << "\nFinal board:\n";
                             displayBoard(boardSize, board);
                             if (hasWin_local(board, N, humanSide)) {
                                 std::cout << "You (" << humanSide << ") win!\n";
                                  manageCoins(totCoins, 0);
                                  std::cout << "You now have " << totCoins << " coins\n";
                             } else if (hasWin_local(board, N, cpuSide)) {
                                 std::cout << "CPU (" << cpuSide << ") wins!\n";
                                  manageCoins(totCoins, 1);
                                  std::cout << "You now have " << totCoins << " coins\n";
                             } else {
                                 std::cout << "Draw.\n";
                             }
                             break;
                         }
                         board[cpuIdx] = cpuSide;
                         std::cout << "CPU (" << cpuSide << ") played at " << (cpuIdx + 1) << std::endl;
     
                         // Check terminal after CPU move → ANNOUNCE RESULT
                         {
                             int N = N_from_boardSize_local(boardSize, board.size());
                             if (hasWin_local(board, N, cpuSide)) {
                                 std::cout << "\nFinal board:\n";
                                 displayBoard(boardSize, board);
                                 std::cout << "CPU (" << cpuSide << ") wins!\n";
                                 manageCoins(totCoins, 0);
                                 std::cout << "You now have " << totCoins << " coins\n";
                                 break;
                             }
                             if (isDraw_local(board)) {
                                 std::cout << "\nFinal board:\n";
                                 displayBoard(boardSize, board);
                                 std::cout << "Draw.\n";
                                 break;
                             }
                         }

                         
                     }
                     // --- end PVCPU loop ---
     
                 } else {
                     // keep your original one-move behavior for non-PVAI modes
                     if (boardSize == "3x3") {
                         displayBoard(boardSize, board);
     
                         int spotInput = 0;
                         std::cout << "Where would you like to place ?" << std::endl;
                         std::cout << "Please enter the number of the spot ";
                         std::cin >> spotInput;
     
                         for (std::size_t i = 0; i < board.size(); ++i) {
                             if (board[i] == std::to_string(spotInput)) {
                                 board[i] = side;
                             }
                         }
     
                         std::cout << "The Board Is Now:" << std::endl;
                         displayBoard(boardSize, board);
                     } else { // 4x4 and others
                         displayBoard(boardSize, board);
     
                         int spotInput = 0;
                         std::cout << "Where would you like to place ?" << std::endl;
                         std::cout << "Please enter the number of the spot ";
                         std::cin >> spotInput;
     
                         for (std::size_t i = 0; i < board.size(); ++i) {
                             if (board[i] == std::to_string(spotInput)) {
                                 board[i] = side;
                             }
                         }
     
                         std::cout << "The Board Is Now:" << std::endl;
                         displayBoard(boardSize, board);
                     }
                 }
     
             } else {
                 std::cout << "Goodbye";
                 std::cout << "Would you like to go back to the menu? (Yes or No)" << std::endl;
                 std::cin >> backToMenu;
                 if(backToMenu[0] == 'n'){
                    return 0;
                  }
             }
     
         }
         else if (menu.userMainMenuInput == "Arcade") {
             totCoins = enterArcade(totCoins);
             std::cout << "Would you like to go back to the menu? (Yes or No)" << std::endl;
             std::cin >> backToMenu;
             if(backToMenu[0] == 'n')
             {
                return 0;
             }
         }
         else if (menu.userMainMenuInput == "Quit") {
             std::cout << "Thank you for Playing" << std::endl;
             return 0;

         }
     
   }while(tolower(backToMenu[0]) == 'y');   

    std::cout << "G O O D B Y E !!" << std::endl; 
    return 0;
}
