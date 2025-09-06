#include <iostream>
#include <string>
#include "Guitar.h"
#include "CGOL.h"
#include <cstdlib>


int main()
{
	FretBoard board;
	board.set_fret(GuitarString::D, 1, true);
	board.set_fret(GuitarString::G, 2, true);
	board.set_fret(GuitarString::D, 0, true);
	board.set_fret(GuitarString::G, 0, true);
	board.set_fret(GuitarString::B, 0, true);

	while (true)
	{
		board.set_board(CGOL::calc_step<24, 6>(board.get_board()));
		board.print_board(FretBoardPrintMode::GRID);
		std::getchar();
		system("cls");
	}

	board.print_board(FretBoardPrintMode::GRID);
	return EXIT_SUCCESS;
}