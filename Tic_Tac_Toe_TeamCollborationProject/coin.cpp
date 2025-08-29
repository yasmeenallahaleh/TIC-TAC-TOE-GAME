#include <iostream>
#include "coin.h"

int givePlayerCoins(int& totCoins){

    std::cout << "Hello Player, you recived 14 coins for joining . . .\n";
    std::cout << "Have fun ;) . . .\n";
    totCoins = 14;

    return totCoins;
}


int manageCoins(int& totCoins, int winOrLose){
    if(winOrLose == 1){
        return totCoins - 5;//if they lose, they lose 5 coins
        std::cout << "\nYou now have " << totCoins << " coins\n";
    }
    else {
        return totCoins + 5;//if they win, they win 5 coins
        std::cout << "\nYou now have " << totCoins << " coins\n";
    }
}

