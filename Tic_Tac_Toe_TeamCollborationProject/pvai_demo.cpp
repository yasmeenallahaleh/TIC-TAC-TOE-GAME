#include "PvCPU.h"
#include <iostream>
#include <vector>
#include <string>

static void show3x3(const std::vector<std::string>& b) {
  for (int i=0;i<9;i++){ std::cout << b[i] << ((i%3==2)?"\n":" "); }
}
static bool isMark(const std::string& s){ return s=="X"||s=="O"; }
static bool terminal(const std::vector<std::string>& b){
  // quick check using your public API: ask CPU for a move; -1 means terminal
  return pvcpu::chooseCpuMove(b,"3x3","X",pvcpu::Difficulty::Easy) == -1 &&
         pvcpu::chooseCpuMove(b,"3x3","O",pvcpu::Difficulty::Easy) == -1;
}

int main(){
  using namespace pvcpu;
  std::vector<std::string> board = {"1","2","3","4","5","6","7","8","9"};
  std::string human = "X";
  std::string cpu   = "O";
  setRandomSeed(123);

  while (true) {
    show3x3(board);
    // human move
    int n; std::cout << "Your move (1-9): "; if(!(std::cin>>n)) break;
    for (int i=0;i<9;i++) if (board[i]==std::to_string(n)) { board[i]=human; break; }
    if (chooseCpuMove(board,"3x3",cpu,Difficulty::Medium)==-1){ show3x3(board); break; }

    // cpu move
    int m = chooseCpuMove(board,"3x3",cpu,Difficulty::Medium);
    if (m==-1){ show3x3(board); break; }
    board[m]=cpu;
    if (chooseCpuMove(board,"3x3",cpu,Difficulty::Medium)==-1){ show3x3(board); break; }
  }
}
