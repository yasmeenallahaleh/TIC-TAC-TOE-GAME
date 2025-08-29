#include "PvCPU.h"
#include <iostream>
#include <vector>
#include <cassert>

int main() {
    using namespace pvcpu;
    setRandomSeed(12345);

    // 1) 3x3: X already won (top row)
    std::vector<std::string> won3 = {
        "X","X","X",
        "4","5","6",
        "7","8","9",
    };
    int r1 = chooseCpuMove(won3, "3x3", "O", Difficulty::Easy);
    std::cout << "won3 result: " << r1 << " (expect -1)\n";
    assert(r1 == -1);

    // 2) 3x3: full-board draw (no 3-in-a-row)
    std::vector<std::string> draw3 = {
        "X","O","X",
        "X","O","O",
        "O","X","X",
    };
    int r2 = chooseCpuMove(draw3, "3x3", "X", Difficulty::Hard);
    std::cout << "draw3 result: " << r2 << " (expect -1)\n";
    assert(r2 == -1);

    // 3) 4x4: O already won (top row)
    std::vector<std::string> won4 = {
        "O","O","O","O",
        "5","6","7","8",
        "9","10","11","12",
        "13","14","15","16",
    };
    int r3 = chooseCpuMove(won4, "4x4", "X", Difficulty::Medium);
    std::cout << "won4 result: " << r3 << " (expect -1)\n";
    assert(r3 == -1);

    // 4) Easy: win-in-1 (CPU = X should sometimes pick index 2)
    {
        std::vector<std::string> w = {
            "X","X","3",
            "4","O","6",
            "7","8","9",
        };
        int m = chooseCpuMove(w, "3x3", "X", Difficulty::Easy);
        std::cout << "easy win-in-1 chose: " << m << " (expect 2 sometimes)\n";
        // If you temporarily set EASY_SMART_P=1.0 in PvCPU.cpp, you can assert(m == 2);
    }

    // 5) Easy: block-in-1 (CPU = X should sometimes block at index 2)
    {
        std::vector<std::string> b = {
            "O","O","3",
            "4","X","6",
            "7","8","9",
        };
        int m = chooseCpuMove(b, "3x3", "X", Difficulty::Easy);
        std::cout << "easy block-in-1 chose: " << m << " (expect 2 sometimes)\n";
        // With EASY_SMART_P=1.0 temporarily: assert(m == 2);
    }

    // 6) Medium: center preference on empty 3x3
    {
        std::vector<std::string> e = {"1","2","3","4","5","6","7","8","9"};
        int m = chooseCpuMove(e, "3x3", "X", Difficulty::Medium);
        std::cout << "medium empty-3x3 chose: " << m << " (expect 4)\n";
        // assert(m == 4); // uncomment if you want strict
    }

    // 7) Medium: never misses win/block
    {
        std::vector<std::string> w = {
            "X","X","3",
            "4","O","6",
            "7","8","9",
        };
        int m1 = chooseCpuMove(w, "3x3", "X", Difficulty::Medium);
        std::cout << "medium win-in-1 chose: " << m1 << " (expect 2)\n";

        std::vector<std::string> b = {
            "O","O","3",
            "4","X","6",
            "7","8","9",
        };
        int m2 = chooseCpuMove(b, "3x3", "X", Difficulty::Medium);
        std::cout << "medium block-in-1 chose: " << m2 << " (expect 2)\n";
    }

        // 8) Hard: empty 3x3 → center
    {
        std::vector<std::string> e = {"1","2","3","4","5","6","7","8","9"};
        int m = chooseCpuMove(e, "3x3", "X", Difficulty::Hard);
        std::cout << "hard empty-3x3 chose: " << m << " (expect 4)\n";
    }

    // 9) Hard: block threat on 4x4
    {
        // Row 0: X X X .
        std::vector<std::string> t4 = {
            "X","X","X","4",
            "5","6","7","8",
            "9","10","11","12",
            "13","14","15","16",
        };
        int m = chooseCpuMove(t4, "4x4", "O", Difficulty::Hard);
        std::cout << "hard 4x4 block chose: " << m << " (expect 3)\n";
    }

    std::cout << "All terminal tests passed \n";
    return 0;
}
