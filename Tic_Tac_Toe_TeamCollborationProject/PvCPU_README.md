PvCPU — Tic-Tac-Toe CPU Opponent (3×3 & 4×4)

This module implements the computer player for our CS100 final project.
It exposes a small public API for choosing the CPU’s next move and supports three difficulty levels: Easy, Medium, and Hard.

Scope: This branch contains only the PvCPU logic. The course-provided main.cpp is unchanged and currently performs a single user move (no game loop). Use the included sanity runner to demonstrate PvCPU behavior.

Quick Start
Build the PvCPU sanity tests (recommended for demo)
g++ -std=c++17 -O0 -g -Wall -Wextra PvCPU.cpp PvCPU_sanity.cpp -o pvcpu_test
./pvcpu_test

Build full game with main.cpp
g++ -std=c++17 -O2 -Wall -Wextra -Wpedantic -Wno-sign-compare main.cpp PvCPU.cpp -o tictactoe
./tictactoe

---------main.cpp currently accepts one user move then exits--------
However, the pvai_demo.cpp file exits to prove the branch works

Testing:
Sanity runner (PvCPU_sanity.cpp)
g++ -std=c++17 -O2 -Wall -Wextra -Wpedantic -Wno-sign-compare main.cpp PvCPU.cpp -o tictactoe
./tictactoe


---------------- File map ----------------
PvCPU.h            // Public API (chooseCpuMove, setRandomSeed, Difficulty)
PvCPU.cpp          // Implementation: helpers, terminal checks, Easy/Medium/Hard
PvCPU_sanity.cpp   // Standalone sanity tests (+ demo runner for the module)
main.cpp           // Course-provided app (unchanged; single user move for now)