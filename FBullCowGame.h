#pragma once
#include <string>
#include <map>

#define TMap std::map
 
using FString = std::string;
using int32 = int;

enum EGuessValidation
{
	invalid_validation,
	okay,
	not_isogram,
	numbers_or_special_characters,
	wrong_length,
	already_tested,
	not_lowercase,

};

struct FBullCowCount
{
	int32 bulls = 0;
	int32 cows = 0;
};

class FBullCowGame {
public:
	FBullCowGame(); // constructor
	int32 GetCurrentTry(); //counts the number of tries
	int32 GetMaxTries();
	bool IsGameWon() const; //checks to see if the game is won
	int32 GetHiddenWordLength();
	EGuessValidation CheckGuessValidity(FString); //checks user input to make sure that it is a word not number
	//counts bulls and cows,increments the try number
	FBullCowCount SubmitGuess(FString);
	void Reset(); // resets the game
	FString GiveHint();
	int32 GetUserWordLength();


private:
	// see contructor for initialization
	int32 MaxTries;
	int32 CurrentTry;
	FString MyHiddenWord;
	bool bGameWon;
	int32 UserWordLength;

	bool bIsogram(FString) const; // checks to see if something is an isogram
	bool IsLower(FString) const; // checks to see if every letter in guess is lowercase
};