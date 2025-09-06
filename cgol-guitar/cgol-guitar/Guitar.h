#pragma once
#include <array>
#include <iostream>
#include <iomanip>
#include "miniaudio.h"
#include <chrono>
#include <thread>
#include <cstdlib> 
#include <ctime>

const int NUM_FRETS = 24;

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

	FretBoard() {
		srand(time(0));
		// init audio engine
		if (ma_engine_init(nullptr, &engine) != MA_SUCCESS) {
			std::cout << "Failed to initialize audio engine.\n";
		}

		//	should probably move these as instance data cause i repeat it later
		std::string string_names[6] = { "E_LOW", "A", "D", "G", "B", "E_HIGH" };

		for (int s = 0; s < 6; s++) {

			// build path
			std::string path = "sounds\\";
			path += string_names[s] + ".wav";

			// init audio stuff
			if (ma_sound_init_from_file(&engine, path.c_str(),
				MA_SOUND_FLAG_NO_SPATIALIZATION,
				nullptr, nullptr, &voices[s]) == MA_SUCCESS) {
				voices_loaded[s] = true;
			}
			else {
				voices_loaded[s] = false;
				std::cout << "Failed to load " << path << "\n";
			}
		}
	}

	~FretBoard() {
		for (int i = 0; i < 6; ++i) {
			if (voices_loaded[i]) {
				ma_sound_uninit(&voices[i]);
				voices_loaded[i] = false;
			}
		}
		ma_engine_uninit(&engine);
	}

	void set_fret(GuitarString string, int fret, bool value)
	{
		if (fret <= 0 || fret >= NUM_FRETS)
		{
			std::cout << "Attempted to set Invalid Fret\n";
			return;
		}

		int string_index = static_cast<int>(string);
		board[fret - 1][string_index] = value;
	}

	void bar_fret(int fret, bool value)
	{
		if (fret <= 0 || fret >= NUM_FRETS)
		{
			std::cout << "Attempted to set Invalid Fret\n";
			return;
		}

		for (int string = 0; string < 6; string++)
			board[fret - 1][string] = value;
	}

    void print_board(FretBoardPrintMode mode) const
    {
		std::cout << "    EADGBE\n";
        if (mode == FretBoardPrintMode::TAB)
        {
            // todo
        }
        else if (mode == FretBoardPrintMode::GRID)
        {
            for (int fret = 0; fret < NUM_FRETS; fret++)
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

	void set_board(std::array<std::array<bool, 6>, NUM_FRETS> new_board)
	{
		board = new_board;
	}

	std::array<std::array<bool, 6>, NUM_FRETS> get_board()
	{
		return board;
	}

	void play_notes()
	{
		// keeps track of the highest fretted not on each string 
		// (0=low_e through 6=high_e)
		std::array<int, 6> highest_notes{};

		for(int fret = NUM_FRETS - 1; fret > 0; fret--)
		{
			for (int string = 0; string < 6; string++)
			{
				if (board[fret][string])
				{
					// if nothing has been fretted on that string yet then update it
					if (highest_notes[string] == 0)
						highest_notes[string] = fret + 1;
				}
			}
		}
		
		// go through each string and play the corresponding wav file
		// pitched up according to highest_note value

		// string sample names
		std::string string_names[6] = { "E_LOW", "A", "D", "G", "B", "E_HIGH" };

		for (int s = 0; s < 6; s++) {
			// check if that wav was loaded
			if (!voices_loaded[s]) continue;

			int semitones = highest_notes[s];
			float ratio = std::pow(2.0f, semitones / 12.0f);

			ma_sound_stop(&voices[s]);
			ma_sound_set_pitch(&voices[s], ratio);
			ma_sound_seek_to_pcm_frame(&voices[s], 0);
			ma_sound_start(&voices[s]);
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			//std::getchar();
		}

	}

	void fill_random()
	{
		for (int fret = 0; fret < NUM_FRETS; fret++)
		{
			for (int string = 0; string < 6; string++)
			{
				board[fret][string] = static_cast<bool>(rand() % 2);
			}
		}
	}


private:
	std::array<std::array<bool, 6>, NUM_FRETS> board{};
	ma_engine engine;

	ma_sound voices[6]{};
	bool voices_loaded[6]{};

	bool get_fret(GuitarString string, int fret)
	{
		int string_index = static_cast<int>(string);
		return board[fret][string_index];
	}

};