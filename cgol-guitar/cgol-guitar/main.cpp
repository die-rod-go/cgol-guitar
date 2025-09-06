#include <iostream>
#include <string>
#include "Guitar.h"
#include "CGOL.h"
#include <cstdlib>


int main()
{
	FretBoard board;
	// Glider
	board.set_fret(GuitarString::D, 2, true);
	board.set_fret(GuitarString::G, 3, true);
	board.set_fret(GuitarString::D, 1, true);
	board.set_fret(GuitarString::G, 1, true);
	board.set_fret(GuitarString::B, 1, true);

	// E Major
	board.set_fret(GuitarString::A, 2, true);
	board.set_fret(GuitarString::D, 2, true);
	board.set_fret(GuitarString::G, 1, true);


	// C Major
	board.set_fret(GuitarString::A, 6, true);
	board.set_fret(GuitarString::D, 5, true);
	board.set_fret(GuitarString::B, 4, true);

	// E minor
	board.set_fret(GuitarString::A, 2, true);
	board.set_fret(GuitarString::D, 2, true);
	board.set_fret(GuitarString::B, 3, true);

	// G Open
	board.set_fret(GuitarString::E_LOW, 3, true);
	board.set_fret(GuitarString::A, 2, true);
	board.set_fret(GuitarString::E_HIGH, 3, true);

	//board.fill_random();

	while (true)
	{
		board.print_board(FretBoardPrintMode::GRID);
		std::getchar();
		system("cls");
		board.play_notes();
		board.set_board(CGOL::calc_step<24, 6>(board.get_board()));
	}

	board.print_board(FretBoardPrintMode::GRID);
	return EXIT_SUCCESS;
}