﻿/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include <map>
#define TMap = std::map;
// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays

// the entry point for our application
int main()
{
	bool bPlayAgain = false;
	do {
		BCGame.Reset();
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
		}
	while (bPlayAgain);

	return 0; // exit the application
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << ".=     ,        =. " << std::endl;
	std::cout << " _  _   /'/    )\,/,/(_   \ \ " << std::endl;
	std::cout << "`//-.|  (  ,\\)\//\)\/_  ) |" << std::endl;
	std::cout << "//___\   `\\\/\\/\/\\///'  / " << std::endl;
	std::cout << ",-~`-._ `- - '_   ``  _ \`~-,_ " << std::endl;
	std::cout << "\       `-.  '_`.      .'_` \ ,-'~`/ " << std::endl;
	std::cout << " `.__.-'`/   (-\        /-) |-.__,' " << std::endl;
	std::cout << "   ||   |     \ \O)  /^\ (O/| " << std::endl;
	std::cout << "   `\\  |         /   `\    / " << std::endl;
	std::cout << "     \\  \       /      `\ /    ^ " << std::endl;
	std::cout << "     `\\ `-.   /' .---.--.\ " << std::endl;
	std::cout << "      `\\/`~(,'()      ()'" << std::endl;
	std::cout << "       /(O) \\  _,.-.,_)" << std::endl;
	std::cout << "      //  \\ `\'`      /" << std::endl;
	std::cout << "     / |  || `''''''' " << std::endl;
	std::cout << "    /  |__||" << std::endl;


	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// plays a single game to completion
void PlayGame()
{
	FBullCowGame BullCowGame();
	int32 MaxTries = BCGame.GetMaxTries();
	
	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();
				
		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	ECheckInput Status = ECheckInput::No_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case ECheckInput::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case ECheckInput::Not_Isogram:
			std::cout << "Please enter a word witout repeating letters.\n\n";
			break;
		case ECheckInput::No_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != ECheckInput::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}