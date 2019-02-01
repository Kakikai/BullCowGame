/*This project was practicce for learning the Unreal Engine's C++ syntax. Certain
data types are renamed within the engine and its coding standards call for a 
particular manner of organiztion, so I used this game to get acquainted with them.*/

#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>
#include "fBullCowGame.h"

// practicing Unreal Engine Syntax
using FText = std::string;
using int32 = int;

//function prototypes outside of classes
void PrintIntro(); //prints the introduction to the game
void PlayGame();
FText GetValidGuess(); //aquires the first word guess of the player
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game


//entry point32of program
int main()
{
	do
	{
		system("CLS");
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain() == true);
    return 0; //exit the application
}




void PrintIntro()
{
	std::cout << "   }....{                            L....L\n";
	std::cout << "   ( o o)                            (O O  )\n";
	std::cout << "   \\   /                              \\   /\n";
	std::cout << "    ^__^                              ('_')\n";


	//introduce the game
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word based game!" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram that I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// loop continually until the user gives valid guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		//get a guess from the player
		
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " <<BCGame.GetMaxTries() << ". ";
		std::cout << "Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a word with all lowercase letters.\n\n";
			break;
		default:
			break;
		}

	} while (Status != EGuessStatus::OK); //keeps looping untile we get no errors
	return Guess;
} //TODO change to get valid guess

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);

	
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while 
	//is NOT won and if there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess(); 
		
		
		 
		fBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ", Cows = " << BullCowCount.Cows << "\n\n";


		std::cout << "Your guess was: " << Guess << std::endl;
		std::cout << std::endl;
	}
	PrintGameSummary();
	return;
}

void PrintGameSummary() 
{
	if (BCGame.IsGameWon()) 
	{
		std::cout << "You win! Would you like to play again with the same word?\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}
