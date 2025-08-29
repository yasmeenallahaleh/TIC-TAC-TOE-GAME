#include "PvCPU.h"

//Unit testing: RNG
#include <iostream>
static bool DEBUG = false; //changed from true
#define LOG(cat, msg) do{ if (DEBUG) std::cerr << "[PvCPU][" << cat << "] " << msg << "\n"; }while(0)


#include <algorithm>
#include <limits>
#include <random>
#include <string>
#include <vector>
#include <cassert>
#include <cctype>

namespace pvcpu{

    //--------- RNG ---------


    static std::mt19937& rng() {
        static std::random_device rd;
        static std::mt19937 gen(rd()); //call setRandomSeed(...) to override
        return gen;
    }

    void setRandomSeed(unsigned seed) {
        rng().seed(seed);
    }

    static int randomChoiceIndex(int size) {
        if (size <= 0) return -1;
        std::uniform_int_distribution<int> d(0, size - 1);
        return d(rng());
    }

    static bool coinFlip(double p) {
        std::uniform_real_distribution<double> d(0.0, 1.0);
        return d(rng()) < p;
    }

    //RNG done. Continue later...
    // TODO[Board]: isMark, labelForIdx, N_from_boardSize/K_from_boardSize, legalMoves, opponentOf
    
    //----------- Board helpers --------------
    static inline bool isMark(const std::string& s) noexcept { return s=="X" || s=="O"; }
    static inline std::string labelForIdx(int idx){ return std::to_string(idx+1); }
    
    static inline int N_from_boardSize(const std::string& boardSize, std::size_t len=0) noexcept {
        if (boardSize=="3x3") return 3;
        if (boardSize=="4x4") return 4;
        
        if (len==9) return 3;
        if (len==16) return 4;
        
        return 3; //safe default
    }
    // static inline int K_from_boardSize(const std::string& boardSize, std::size_t len=0) noexcept {
    //     return N_from_boardSize(boardSize, len);
    // }
    
    static std::vector<int> legalMoves(const std::vector<std::string>& board){
        std::vector<int> m;
        m.reserve(board.size());
        for (int i=0;i<(int)board.size();++i) if (!isMark(board[i])) m.push_back(i);
        return m;
    }
    static inline std::string opponentOf(const std::string& me){ return (me=="X")?"O":"X"; }

    static inline std::string normalizeXO(const std::string& s) noexcept {
        if (s.empty()) return "X";
        char c = static_cast<char>(std::toupper(static_cast<unsigned char>(s[0])));
        return (c == 'O') ? "O" : "X"; // default to X for anything else
    }

    static std::vector<int> cornersForN(int N) {
        return {0, N - 1, N * (N - 1), N * N - 1};
    }

    static int preferCenterCorner(const std::vector<int>& candidates, int N,
                              const std::vector<std::string>& board) {
    // Prefer center on odd N (3x3)
    if (N % 2 == 1) {
        int center = (N/2) * N + (N/2);
        if (!isMark(board[center])) {
            for (int m : candidates) if (m == center) return center;
        }
    }
    // Then prefer any corner
    auto cs = cornersForN(N);
    for (int m : candidates) {
        if (std::find(cs.begin(), cs.end(), m) != cs.end()) return m;
    }
    // Otherwise random among candidates
    return candidates[randomChoiceIndex((int)candidates.size())];
}

    //Done: Board Helpers

    // TODO[Terminal]: hasWin (rows/cols/diags), isDraw
    
    // ------------- Terminal checks ---------------
    static bool hasWin(const std::vector<std::string>& b, int N, const std::string& mark){
        
        //rows
        for (int r = 0; r < N; ++r){
            bool ok = true;
            
            for (int c = 0; c < N; ++c) if (b[r*N + c] != mark) { ok = false; break; }
            if (ok) return true;
        }

        //cols
        for (int c = 0; c < N; ++c) {
            bool ok = true;
            for (int r = 0; r < N; ++r) if (b[r*N + c] != mark) { ok = false; break; }
            if (ok) return true;
        }
        
        // main diagonal
        {
            bool ok = true;
            for (int i = 0; i < N; ++i) if (b[i*N + i] != mark) {ok = false; break;}
            if (ok) return true;
        }

        // anti diagonal
        {
            bool ok = true;
            for (int i = 0; i < N; ++i) if (b[i*N + (N-1-i)] != mark) {ok = false; break;}
            if (ok) return true;
        }
        return false;

    } //hasWin()

    // True if no empty cells remain
    static bool isDraw(const std::vector<std::string>& b) {
        for (const auto& v : b) if (!isMark(v)) return false;
        return true;
    }

    //Optional (used soon by Easy/Medium/Hard): return a move that wins immediately, or -1
    static int findImmediateWin(const std::vector<std::string>& b, int N, const std::string& whoIn) {
        const std::string who = normalizeXO(whoIn);
        auto moves = legalMoves(b);
        for (int idx : moves) {
            auto tmp = b;
            tmp[idx] = who;
            if (hasWin(tmp, N, who)) return idx;
        }
        return -1;
    }

    // --------- Heuristic (K = N) ---------
    // Positive is good for `me`, negative is good for opponent.
    static int evaluate(const std::vector<std::string>& b, int N, const std::string& me) {
        const std::string opp = (me == "X" ? "O" : "X");
        // weights: index = count of marks in a line (K=N)
        // K=3 → {0,1,10,100000}, K=4 → {0,1,5,50,100000}
        static const int W3[] = {0, 1, 10, 100000};
        static const int W4[] = {0, 1, 5, 50, 100000};
        const int* W = (N == 3) ? W3 : W4;

        auto scoreLine = [&](auto idxAt) {
            int my = 0, op = 0;
            for (int i = 0; i < N; ++i) {
                const auto& v = b[idxAt(i)];
                if (v == me) ++my;
                else if (v == opp) ++op;
            }
            if (my && op) return 0;          // blocked line
            if (my) return W[my];
            if (op) return -W[op];
            return 0;
        };

        int S = 0;
        // rows
        for (int r = 0; r < N; ++r)
            S += scoreLine([&](int i){ return r * N + i; });
        // cols
        for (int c = 0; c < N; ++c)
            S += scoreLine([&](int i){ return i * N + c; });
        // diags
        S += scoreLine([&](int i){ return i * N + i; });
        S += scoreLine([&](int i){ return i * N + (N - 1 - i); });
        return S;
    }

    //Done: Terminal checks

    // ----------- Easy strategy -----------
    // Mostly random; with a small chance, take an immediate win or block.
    // Allow tests to override Easy's smart probability at compile time.
    // Default is 0.10 unless -DPVCU_EASY_SMART_P=... is passed to the compiler.
   #ifndef PVCU_EASY_SMART_P
    #define PVCU_EASY_SMART_P 0.10
    #endif
    static constexpr double EASY_SMART_P = PVCU_EASY_SMART_P;

    static int moveEasy(const std::vector<std::string>& board, int N, const std::string& me) {
        auto moves = legalMoves(board);
        if (moves.empty()) return -1;

        const std::string opp = (me[0] == 'X') ? "O" : "X"; // me is normalized, so this is safe

        // optional debug
        LOG("Easy", "me=" << me << " opp=" << opp);

        if (coinFlip(EASY_SMART_P)) {
            int w = findImmediateWin(board, N, me);
            if (w != -1) return w;

            int b = findImmediateWin(board, N, opp);  // now correctly checks the opponent
            if (b != -1) return b;
        }
        return moves[randomChoiceIndex(static_cast<int>(moves.size()))];
    }

    // --------- Medium strategy ---------
    static int moveMedium(const std::vector<std::string>& board, int N, const std::string& me) {
        auto moves = legalMoves(board);
        if (moves.empty()) return -1;
        const std::string opp = (me == "X" ? "O" : "X");

        // 1) Win now
        if (int w = findImmediateWin(board, N, me); w != -1) return w;
        // 2) Block now
        if (int b = findImmediateWin(board, N, opp); b != -1) return b;

        // 3) Center (only exists for odd N, i.e., 3x3)
        if (N % 2 == 1) {
            int center = (N / 2) * N + (N / 2);
            if (!isMark(board[center])) return center;
        }

        // 4) Corners
        {
            auto cs = cornersForN(N);
            std::vector<int> open;
            for (int c : cs) if (!isMark(board[c])) open.push_back(c);
            if (!open.empty()) return open[randomChoiceIndex((int)open.size())];
        }

        // 5) Heuristic: pick randomly among top-3 simulated moves
        struct Scored { int s; int m; };
        std::vector<Scored> scored; scored.reserve(moves.size());
        for (int m : moves) { auto tmp = board; tmp[m] = me; scored.push_back({ evaluate(tmp, N, me), m }); }
        std::sort(scored.begin(), scored.end(), [](const Scored& a, const Scored& b){ return a.s > b.s; });
        int keep = std::min(3, (int)scored.size());
        return scored[randomChoiceIndex(keep)].m;
    }
        //Done: sliding-window heuristic (K=N)

    // --------- Hard strategy: alpha–beta minimax ---------

    // Order moves to speed up alpha–beta (wins/blocks first, then by heuristic)
    static std::vector<int> orderedMoves(const std::vector<std::string>& board, int N, const std::string& me) {
        const std::string opp = (me == "X" ? "O" : "X");
        auto moves = legalMoves(board);
        if (moves.empty()) return moves;

        // wins & blocks to front
        int w = findImmediateWin(board, N, me);
        int b = findImmediateWin(board, N, opp);

        std::vector<int> front;
        std::vector<int> rest;
        for (int m : moves) {
            if (m == w || m == b) front.push_back(m);
            else rest.push_back(m);
        }

        // score remaining by heuristic (descending)
        std::vector<std::pair<int,int>> scored;
        scored.reserve(rest.size());
        for (int m : rest) { auto tmp = board; tmp[m] = me; scored.push_back({ evaluate(tmp, N, me), m }); }
        std::sort(scored.begin(), scored.end(), [](auto& a, auto& b){ return a.first > b.first; });
        for (auto& p : scored) front.push_back(p.second);
        return front;
    }

    // Depth-scaled terminal scores (prefer faster wins / slower losses)
    static inline int winScore(int remainingDepth) { return 100000 + remainingDepth; }
    static inline int lossScore(int remainingDepth){ return -100000 - remainingDepth; }

    // Alpha–beta search. `toMove` is "X" or "O". Returns score from `me`'s perspective.
    static int minimaxScore(std::vector<std::string>& b, int N,
                            const std::string& me, const std::string& toMove,
                            int depth, int alpha, int beta, int& nodes)
    {
        ++nodes;

        const std::string opp = (me == "X" ? "O" : "X");
        // terminal checks
        if (hasWin(b, N, me))  return winScore(depth);
        if (hasWin(b, N, opp)) return lossScore(depth);
        auto moves = legalMoves(b);
        if (moves.empty()) return 0;           // draw
        if (depth == 0)   return evaluate(b, N, me);

        const bool maximizing = (toMove == me);
        if (maximizing) {
            int best = std::numeric_limits<int>::min();
            // order from 'me' perspective
            auto order = orderedMoves(b, N, me);
            for (int m : order) {
                std::string old = b[m];
                b[m] = me;
                int val = minimaxScore(b, N, me, opp, depth - 1, alpha, beta, nodes);
                b[m] = old;

                if (val > best) best = val;
                if (val > alpha) alpha = val;
                if (beta <= alpha) break; // prune
            }
            return best;
        } else {
            int best = std::numeric_limits<int>::max();
            // order from opponent’s perspective (so it finds its wins/blocks first)
            auto order = orderedMoves(b, N, opp);
            for (int m : order) {
                std::string old = b[m];
                b[m] = opp;
                int val = minimaxScore(b, N, me, me, depth - 1, alpha, beta, nodes);
                b[m] = old;

                if (val < best) best = val;
                if (val < beta) beta = val;
                if (beta <= alpha) break; // prune
            }
            return best;
        }
    } //minimaxScore()

    static int moveHard(const std::vector<std::string>& board, int N, const std::string& me) {
        const std::string opp = (me == "X" ? "O" : "X");

        // Fast path: win or block immediately
        if (int w = findImmediateWin(board, N, me); w != -1) return w;
        if (int b = findImmediateWin(board, N, opp); b != -1) return b;

        // Depth: full search on 3×3, capped on 4×4
        int depthLimit = (N == 3) ? 9 : 6;

        // Evaluate each root move; tie-break randomly among best
        auto order = orderedMoves(board, N, me);
        int bestScore = std::numeric_limits<int>::min();
        std::vector<int> bestMoves;
        bestMoves.reserve(order.size());

        int nodes = 0;
        for (int m : order) {
            auto tmp = board;
            tmp[m] = me;
            int score = minimaxScore(tmp, N, me, opp, depthLimit - 1,
                                    std::numeric_limits<int>::min()/2,
                                    std::numeric_limits<int>::max()/2,
                                    nodes);
            if (score > bestScore) {
                bestScore = score;
                bestMoves.clear();
                bestMoves.push_back(m);
            } else if (score == bestScore) {
                bestMoves.push_back(m);
            }
        }

        // optional: LOG on DEBUG
        LOG("Hard", "N=" << N << " depth=" << depthLimit << " nodes=" << nodes
            << " best=" << bestScore << " choices=" << bestMoves.size());

        if (bestMoves.empty()) {
        auto moves = legalMoves(board);
        if (moves.empty()) return -1;
        return moves[randomChoiceIndex((int)moves.size())];
    }
    // Previously: return bestMoves[randomChoiceIndex((int)bestMoves.size())];
    return preferCenterCorner(bestMoves, N, board);
    } //moveHard()

    //Done: Easy/Medium/Hard

    int chooseCpuMove(const std::vector<std::string>& board,
                    const std::string& boardSize,
                    const std::string& cpuSide,
                    Difficulty difficulty)
    {
        int N = N_from_boardSize(boardSize, board.size());

        // If the game is already over, no move.
        if (hasWin(board, N, "X") || hasWin(board, N, "O") || isDraw(board)) return -1;

        // Optional: defensive early exit
        if (legalMoves(board).empty()) return -1;

        const std::string me = normalizeXO(cpuSide);

        switch (difficulty) {
            case Difficulty::Easy:   return moveEasy(board, N, me);
            case Difficulty::Medium: return moveMedium(board, N, me);
            case Difficulty::Hard:   return moveHard(board, N, me);
            default:                 return moveMedium(board, N, me);
        }
    }  // chooseCpuMove

} //namespace pvcpu