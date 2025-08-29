#include "gtest/gtest.h"
#include "coin.cpp"

TEST(coinTest, manageCoins){
    int totCoins = 10;
    int winLose = 0;

    EXECT_EQ(manageCoins(totCoins,winLose),15);
}

TEST(coinTest, givePlayerCoins){
    int totCoins = 14;
    EXECT_EQ(givePlayerCoins(totCoins),14);
}