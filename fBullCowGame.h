#pragma once
#include <string>

using FString = std::string;
using int32 = int;
//all values initialized to 0
struct fBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Number,
	Special_Character,
	Wrong_Length,
	Not_Lowercase
};

enum class EResetStatus
{
	No_Hidden_Word,
	OK
};

class FBullCowGame {
public:
	FBullCowGame(); //constructor


	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; 

	void Reset(); //TODO make a richer return value
	
	// counts Bulls and Cows and increases turn number assuming valid guess
	fBullCowCount SubmitValidGuess(FString);



// ^^ Please try and ignore this; focus on above ^^
private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString  MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
