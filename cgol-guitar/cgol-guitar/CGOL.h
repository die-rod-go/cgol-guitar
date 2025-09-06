#pragma once
#include <array>

class CGOL {
public:
    template<int Rows, int Cols>
    static std::array<std::array<bool, Cols>, Rows> calc_step(const std::array<std::array<bool, Cols>, Rows>& board)
    {
        // make new board
        std::array<std::array<bool, Cols>, Rows> next{};

        // loop over every cell
        for (int y = 0; y < Rows; y++) {
            for (int x = 0; x < Cols; x++) {
                int neighbors = get_num_neighbors<Rows, Cols>(x, y, board);
                bool alive = board[y][x];

                // survive on 2/3, born on 3
                if ((board[y][x] && neighbors == 2) || neighbors == 3)
                    next[y][x] = true;
                else
                    next[y][x] = false;
            }
        }
        return next;
    }
private:
    template<int Rows, int Cols>
    static int get_num_neighbors(int x, int y, const std::array<std::array<bool, Cols>, Rows>& board)
    {
        int num_neighbors = 0;
        // loop over 3x3 and count live neighbors (excluding self)
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                // skip self
                if (dx == 0 && dy == 0) continue; 

                int ny = y + dy;
                int nx = x + dx;

                // loop if out of bounds (touroidal wrapping) idk how to spell it
                if (ny < 0)
                    ny = Rows - 1;
                if (ny >= Rows)
                    ny = 0;
                    
                if (nx < 0)
                    nx = Cols - 1;
                if (nx >= Cols)
                    nx = 0;

                if (board[ny][nx]) num_neighbors++;
            }
        }
        return num_neighbors;
    }
};
