#pragma once
#include <array>
#include <iostream>
#include <iomanip>

enum class GuitarString
{
	E_LOW = 0,
	A = 1,
	D = 2,
	G = 3,
	B = 4,
	E_HIGH = 5
};

enum class FretBoardPrintMode
{
	TAB,
	GRID
};

class FretBoard
{
public:

	void set_fret(GuitarString string, int fret, bool value)
	{
		int string_index = static_cast<int>(string);
		board[fret][string_index] = value;
	}

    void print_board(FretBoardPrintMode mode) const
    {
        if (mode == FretBoardPrintMode::TAB)
        {
            // todo
        }
        else if (mode == FretBoardPrintMode::GRID)
        {
            for (int fret = 0; fret < 24; fret++)
            {
				std::string output;
				output += std::to_string(fret);
                for (int string = 0; string < 6; string++)
				{
					if (board[fret][string])
						output += "x";
					else
						output += ".";
                }


				std::cout << std::setw(10) << output  << "\n";
            }
        }
    }

	void set_board(std::array<std::array<bool, 6>, 24> new_board)
	{
		board = new_board;
	}

	std::array<std::array<bool, 6>, 24> get_board()
	{
		return board;
	}

private:
	std::array<std::array<bool, 6>, 24> board{};
	bool get_fret(GuitarString string, int fret)
	{
		int string_index = static_cast<int>(string);
		return board[fret][string_index];
	}

};