#include <iostream>
#include "arcade.h"

int enterArcade(int& totCoins){

    std::cout << "Welcome to the\n\n";
    std::cout << "===============\n";
    std::cout << "| A R C A D E |\n";
    std::cout << "===============\n\n";

    std::cout << "You have " << totCoins << " coins.\n";
    std::cout << "Here are the prize choices: \n\n";
    std::cout << "1.) Toostie POP: 4 coins\n";
    std::cout << "2.) Sticky Hand: 8 coins\n";
    std::cout << "3.) Glow In The Dark Slime: 15 coins\n";
    std::cout << "4.) Small Plushie: 25 coins\n";
    std::cout << "5.) Light Up Sword: 35 coins\n";
    std::cout << "6.) Giant Plushie: 40 coins\n\n";

    std::cout << "Please enter the number of the Prize you want to buy: \n";

    int prizeChoice = 0;
    std::cin >> prizeChoice;


    switch(prizeChoice){
        case 1:
            if(totCoins < 4){
                std::cout << "You dont have enough coins for this item, sorry . . .";
            }
            else{
                std::cout << "Yay! You've bought the prize: Toostie POP!\n";
                totCoins = totCoins-4;
                std::cout << "You now have " << totCoins << " coins\n";
                return totCoins;
            }

            break;
        case 2:
             if(totCoins < 8){
                std::cout << "You dont have enough coins for this item, sorry . . .\n";
            }
            else{
                std::cout << "Yay! You've bought the prize: Sticky Hand!\n";
                totCoins = totCoins-8;
                std::cout << "You now have " << totCoins << " coins\n";
                return totCoins;
            }
            break;
        case 3:
             if(totCoins < 15){
                std::cout << "You dont have enough coins for this item, sorry . . .\n";
            }
            else{
                std::cout << "Yay! You've bought the prize: Glow in the Dark Slime!\n";
                totCoins = totCoins-15;
                std::cout << "You now have " << totCoins << " coins\n";
                return totCoins;
            }
            break;
        case 4:
             if(totCoins < 25){
                std::cout << "You dont have enough coins for this item, sorry . . .\n";
            }
            else{
                std::cout << "Yay! You've bought the prize: Small Plushie!\n";
                totCoins = totCoins-25;
                std::cout << "You now have " << totCoins << " coins\n";
                return totCoins;
            }
            break;
        case 5:
             if(totCoins < 35){
                std::cout << "You dont have enough coins for this item, sorry . . .\n";
            }
            else{
                std::cout << "Yay! You've bought the prize: Light Up Sword!\n";
                totCoins = totCoins-35;
                std::cout << "You now have " << totCoins << " coins\n";
                return totCoins;
            }
            break;
        case 6:
             if(totCoins < 40){
                std::cout << "You dont have enough coins for this item, sorry . . .\n";
            }
            else{
                std::cout << "Yay! You've bought the prize: Giant plushie!\n";
                totCoins = totCoins-40;
                std::cout << "You now have " << totCoins << " coins\n";
                return totCoins;
            }
            break;
        default:
            std::cout << "Invalid Entry For Prize\n";
    }

}
