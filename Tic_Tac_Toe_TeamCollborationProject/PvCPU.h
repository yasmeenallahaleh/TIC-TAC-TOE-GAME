#pragma once

#include <string>
#include <vector>

/*
Public interface for the Tic-Tac-Toe CPU opponent.

Board encoding:
- Empty cells are numeric strings ("1".."9" or "1".."16").
- Occupied cells are exactly "X" or "O" (uppercase).

Difficulty behavior (summary):
- Easy   : mostly random; occasionally takes an obvious win/block.
- Medium : rules first (win/block/center/corners), then a simple heuristic.
- Hard   : alpha–beta search (perfect on 3x3, depth-capped on 4x4).

Return contract:
- Returns a 0-based index into `board` where the CPU should play.
- Returns -1 if the game is already over (win/draw) or no legal moves exist.
*/

namespace pvcpu {

/// Difficulty levels
enum class Difficulty { Easy, Medium, Hard };

/**
 * Decide the CPU's next move.
 *
 * @param board       Current board state (numbers for empty cells, "X"/"O" for occupied).
 * @param boardSize   "3x3" or "4x4".
 * @param cpuSide     "X" or "O" indicating which mark the CPU plays (case-insensitive).
 * @param difficulty  Difficulty level for this decision.
 *
 * @return Index in [0, board.size()) where the CPU should play,
 *         or -1 if the position is terminal (win/draw) or has no legal moves.
 *
 * Notes:
 * - This function does NOT mutate `board`; it only chooses a move.
 * - Inputs are normalized where sensible (e.g., cpuSide case). See .cpp for details.
 */
int chooseCpuMove(const std::vector<std::string>& board,
                  const std::string& boardSize,
                  const std::string& cpuSide,
                  Difficulty difficulty);

/**
 * Set a fixed RNG seed for deterministic behavior (useful in tests/demos).
 * Affects Easy/Medium randomness and Hard's tie-breakers.
 */
void setRandomSeed(unsigned seed);

} // namespace pvcpu
