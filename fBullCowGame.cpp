#include "stdafx.h"
#include "fBullCowGame.h"
#include <map>
#define TMap std::map

#pragma once

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor


int FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ { 3, 5 }, { 4, 7 }, { 5, 9 }, { 6, 11 } };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram; //TODO write function
	}
	else if (!IsLowercase(Guess)) //if the guess isn't all lowerccase 
	{
		return EGuessStatus::Not_Lowercase; // TODO write method
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	} 
	else // otherwise
	{
		return EGuessStatus::OK;
	}
		
}


//recieves a VALID guess, increments turn, and returns count
fBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	fBullCowCount BullCowCount;

	//loop through all leters in the hidden word
	int32 WordLength = MyHiddenWord.length(); // assuming the same length as guess
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{	//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{	//if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{ //if they are in the same place
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}

			}
		}

		
				//increment bulls 
		//else
				//increment cows if not
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{

	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // setup the map
	for (auto Letter : Word)
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) { return false; }
		else { LetterSeen[Letter] = true; }
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{

	for (auto Letter : Word)
	{
		if (!islower(Letter)) //if not a lowercase item
		{
			return false;
		}
	}

	return true;


}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "plant";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}
