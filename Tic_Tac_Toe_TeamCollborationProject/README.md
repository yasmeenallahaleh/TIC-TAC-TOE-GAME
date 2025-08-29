[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/DM7iZNjj)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=20043153)

# Tic-Tac Toe
 
## Authors:
* [Yasmeen Allahaleh]((https://github.com/yasmeenallahaleh05)) 
* [Nicky Shih]((https://github.com/Shadow090)) 
* Ali Syed 
* Angel Cesma


# Project Description

 * Why is it important or interesting to you?
   
>  This project is interesting becuase we will implement all the skills we learned in C++ and implement it in a fun game everyone is familiar with, Tic-Tac-Toe. We've also chose this game because there are many different combonation of boards and winning strategies that make the players think

 * What languages/tools/technologies do you plan to use? (This list may change over the course of the project)
   
>  The language we will use throughout the entire project will be C++ as we will run the game in the terminal of Visual Studio Code.

 * What will be the input/output of your project?

>  Some inputs of this project would be the choosing which spaces the player would want to put there mark on the tic-tac-toe board, if they want to play with an actaul player or AI, and if they want a 3x3 board or a 4x4 board. The terminal will then output the board and the option of where the player can place their shape. At the end of the game, the output would be which ever player won the game.

* What are the features that the project provides?
 
>  Some feature that this project will provide is player against another person or an AI bot. Another feature this project will include is the ability to choose between 3x3 and 4x4 boards. The player can also gain coins if he wins a game or lose coins if he loses a game. The players loses and wins is also kept track of through the multiple games played. The coins collected can be used to buy at the game shop such as mini arcade toys.

# Description Detail:
This project is a Tic-Tac-Toe game where the user is brought to a menu screen. There it can choose if they want to play on a 3x3 board or a 4x4 board. When they pick which board they want. The player is then asked if they want to play against another player, player 2, or an AI bot, which isn't that smart. Through the games played, they can either earn or loose coins based on their winning status, where they collect and save to spend at the arcade prize station. The player starts with a set of coins to give them a boost. The players # of loses and wins can also be tracked and can be pulled up after each game and is announced. 


 > ## Phase II
## User Interface Specification

### Navigation Diagram
> The diagram shows how users move step by step through menus, decisions, gameplay, and post game options in a clear, structured path.
> <img width="1110" height="839" alt="image" src="https://github.com/user-attachments/assets/dd3190e1-cc81-4f24-87af-799fa9cceeaf" />

### Screen Layouts
> As we are using the terminal as the interface for the Tic Tac Toe, all of the screens will be on the terminal and will be mostly text based, and the screens are the main menu, the play menu, and the actual game itself. The differences between the screens are the options the user has, like for the main menu there's the options of Play, Arcade, or Quit, for the play menu there's the options of choosing between the 3x3 and 4x4 boards, choosing the game mode, either PVP or Player verses AI, and choosing whether one wants to play as the X or the O, finally for the actual game, it displays the board that is chosen during the earlier play menu and displays an updated board after the player chose a spot to place the X/O, with the selected spot having a X/O.
> The below is a visual of what has been described above.
> <img width="722" height="746" alt="image" src="https://github.com/user-attachments/assets/cc7bccfb-2ba6-44d8-8195-002f955ae9c8" />


## Class Diagram
>Description:
* Our class is dedicated for the user to navigate the menu easier. Our class is called MenuOption and consists of one public string variable called 'userMainMenuInput'. It default set is nothing and just set as a " " since this varaible will store where the user input in where the user wants to go within the tic-tac-toe board such as the aracade or the main game. This class also contains two void public functions. The function called menu displays all the options where the user can go whether it be the arcade, the main game where the user can choose the board size and player mode, or just completely exit and quit. The function called outputPicker, just helps navigiate and lead the player saying please pick what option as you see printed by the menu function.
>
> 
![Image 8-22-25 at 2 24 PM](https://github.com/user-attachments/assets/26ecc817-465b-4e6d-9f46-c5b4d8cccf2b)

## SOLID Principles:
* 1.) S - Single-responsibility principle (SRP):
* > We applied the single repsonisblity principle to out class. We applied it in both out menu and option picker functions in the class and it helps us write better code by our functions in the class has a specfic and single task to handle to make things more readable and organized
* 2.) O - Open-closed principle (OCP):
  > We applied our open closed principle to our class. We applied it by it by allowing the class to be extended but not modfied. With this class, it easy to extend the class into a subclass. It helps us write better code because it allows us to utilize the class without having to go back and change the content of the orginal class.
* 3.) L - Liskov substitution principles (LSP):
  > We applied the Liskov subsitution to our class as if we were to have subclasses, its parent class without any unexpected error and could be replaceable with its instances. This allows the code to be assured that no error could occur within the classes if we were to replace any object  with instances of their subtypes.
* 4.) I - I - Interface Segregation Principle (ISP):
  > We applied the interface segregation principle in our menu option class as none of our function are forced upon the user. All of our functions are necessary to navigate around the menu. Our class doesnt contant methods the user doesn't need and this helps us keep everything condense and organize, having the necessities and leaving out unnecessary code.
* 5.) D - Dependency Inversion Principle (DIP):
  >  We applied the dependency inversion principle by having our class depnd on the abstractions and not every minut detail in the class. This helps us with allowing us to focus and simplify the program when working on it.


 ## Screenshots
 > Screenshots of the input/output after running your application
> * This is an example of the user joing the menu and being asked where they would like to go. They input the arcade and is Lead there
> * After that they are asked what they want to buy, they choose the sticky hand and recieved it.
> * Then they asked if they want to go back to the menu and they inputed yes, which lead them back
> <img width="505" height="495" alt="Screenshot 2025-08-29 at 10 26 12 AM" src="https://github.com/user-attachments/assets/0bfe99fd-7636-4d62-9dc7-2f6a35781b61" />

> * When the user goes back to the menu, they input 'Play' and is taken the the game mode option.
> * The user inputed these option for each catorgory: 3x3, PVP, and being player 'X'
> * It spit out there option to make sure they want to play
>   <img width="580" height="381" alt="Screenshot 2025-08-29 at 10 34 10 AM" src="https://github.com/user-attachments/assets/08799e1f-a4a0-4978-9284-20a6f487a0fe" />

> * After the user clicked yes, the game was outputed
> * The player then proceed to player with a second player, and managed to win
> * The winner was outputted at the very end
>   * <img width="430" height="371" alt="Screenshot 2025-08-29 at 10 34 20 AM" src="https://github.com/user-attachments/assets/e17cc3e1-f168-4032-8428-bbcbe1b8768a" />

> *If the user decides he doesn't want to play after first joing the game, then they type quit and the program exits
> *  <img width="425" height="129" alt="Screenshot 2025-08-29 at 10 42 55 AM" src="https://github.com/user-attachments/assets/cfbe8522-4b63-4530-a4c0-068e25321f04" />


 ## Installation/Usage
 > The steps are quiet simple in order to make the game work.
> Steps:
> * 1.) First download all the files found in the master branch
> * 2.) After that run the exectuble file in the terminal in order to allow the main.cpp to run
> * 3.) After the exectutable is ran, the game should appear in your terminal and enjoy!
 # Testing:
> We tested our code by unit tests and making sure valgrind also passed:
> ## Valgrind
> <img width="898" height="273" alt="image" src="https://github.com/user-attachments/assets/613f7e11-fcb4-4649-8ed5-1fdb9021b0ab" />


> ## Unit Tests
> <img width="1054" height="589" alt="Screenshot 2025-08-28 at 9 18 57 PM" src="https://github.com/user-attachments/assets/52c893c0-c6a7-413a-bd02-3fe1693fe379" />
<img width="888" height="247" alt="Screenshot 2025-08-29 at 11 20 34 AM" src="https://github.com/user-attachments/assets/ca163bc5-bfb2-4c59-bc4f-f0d4c17d13bc" />


