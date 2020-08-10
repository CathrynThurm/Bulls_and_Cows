#include "FBullCowGame.h"
#include <map>
#include <string>
#include <iostream>

#define TMap std::map



using FString = std:: string;
using int32 = int;

void FBullCowGame::Reset(){

	if (UserWordLength == 3) {
		const FString HIDDEN_WORD = "ant";
		MyHiddenWord = HIDDEN_WORD;
	}
	else if (UserWordLength == 4)
	{
		const FString HIDDEN_WORD = "talk";
		MyHiddenWord = HIDDEN_WORD;
	}
	else if (UserWordLength == 5)
	{
		const FString HIDDEN_WORD = "bacon";
		MyHiddenWord = HIDDEN_WORD;
	}
	else if (UserWordLength == 6)
	{
		const FString HIDDEN_WORD = "rabies";
		MyHiddenWord = HIDDEN_WORD;
	}
	bGameWon = false;
	CurrentTry = 1;
	return;
}
// TODO make a give hint function that prompts somebody for if they would like a hint or not.
FString FBullCowGame::GiveHint()
{
	FString message = "";
	if (UserWordLength == 3)
	{
		if (CurrentTry == 1) {
			message = "It is an animal.";
		}
		else if (CurrentTry == 2) {
			message = "It is smaller than a baseball.";
		}
		else if (CurrentTry == 3) {
			message = "It is an insect.";
		}
		else if (CurrentTry == 4) {
			message = "It lives in a colony.";
		}
		else if (CurrentTry == 5) {
			message = "It can life 10-50 times its body weight.";
		}
	}
	if (UserWordLength == 4) {
		if (CurrentTry == 1) {
			message = "Its something that almost all humans can do.";
		}
		else if (CurrentTry == 2) {
			message = "Some birds can also do it.";
		}
		else if (CurrentTry == 3) {
			message = "You learn to do it when you are a baby.";
		}
		else if (CurrentTry == 4) {
			message = "Its not 'sing.'";
		}
		else if (CurrentTry == 5) {
			message = "Your tongue helps.";
		}
		else if (CurrentTry == 6) {
			message = "You use your voice box too.";
		}
		else if (CurrentTry == 7) {
			message = "Its how you communicate.";
		}
	}
	if (UserWordLength == 5) {
		if (CurrentTry == 1) {
			message = "Its a part of an animal.";
		}
		else if (CurrentTry == 2) {
			message = "It is food.";
		}
		else if (CurrentTry == 3) {
			message = "You eat it for breakfast.";
		}
		else if (CurrentTry == 4) {
			message = "It splatters grease everywhere.";
		}
		else if (CurrentTry == 5) {
			message = "You can use this greese to cook other things.";
		}
		else if (CurrentTry == 6) {
			message = "It comes from a pig.";
		}
		else if (CurrentTry == 7) {
			message = "Its the fatty meat on a pig that you eat with eggs.";
		}
	}
	if (UserWordLength == 6) {
		if (CurrentTry == 1) {
			message = "A common disease to get vaccinated against.";
		}
		else if (CurrentTry == 2) {
			message = "You get it if you are bitten.";
		}
		else if (CurrentTry == 3) {
			message = "The disease can come from bats, raccons, or even dogs.";
		}
		else if (CurrentTry == 4) {
			message = "This disease is why Old Yeller had to be put down.";
		}
		else if (CurrentTry == 5) {
			message = "It makes animals froth at the mouth.";
		}
		else if (CurrentTry == 6) {
			message = "It rhymes with 'babies.'";
		}
		else if (CurrentTry == 7) {
			message = "I really hope you got it!.";
		}
	}
	return message;
}

int32 FBullCowGame::GetUserWordLength()
{
	std::cout << "How long of a word would you like? 3 to 6 letters.\n";
	std::cin >> UserWordLength;
	return UserWordLength;
}


bool FBullCowGame::bIsogram(FString Guess) const
{
	if (Guess.length() <= 1) {return true;}

	//for each letter in FString Guess add a count to that letter
	TMap<char, bool> LettersSeen;
	for (char Letter : Guess)
	{
		Letter = tolower(Letter);
		if (LettersSeen[Letter])
		{
			return false;
		}
		else
		{
			LettersSeen[Letter] = true;
		}
	}
}

bool FBullCowGame::IsLower(FString Guess) const
{
	for (char Letter : Guess){
		if (Letter != tolower(Letter)) {
			return false;
		}
		else {
			return true;
		}
	}
}

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetCurrentTry()
{
	return CurrentTry;
}

int32 FBullCowGame::GetMaxTries()
{
	int32 MyUserWordLength = UserWordLength;
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,7}, {5,7}, {6,20} };
	return WordLengthToMaxTries[MyUserWordLength];
}

// receives a VALID guess and returns BULL or COW, increments try number by one, and returns count.

FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	CurrentTry++;
	FBullCowCount BullCowCount;
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++)
	{
		// compare letters against hidden letter
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++)
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{
					BullCowCount.bulls++;
				}
				else
				{
					BullCowCount.cows++;
				}
			}
		}
	}
	if (BullCowCount.bulls == HiddenWordLength)
	{
		bGameWon = true;
	}
	else {
		bGameWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsGameWon() const
{
	return bGameWon;
}

int32 FBullCowGame::GetHiddenWordLength()
{
	int32 HiddenWordLength = MyHiddenWord.length();
	return HiddenWordLength;
}


EGuessValidation FBullCowGame::CheckGuessValidity(FString Guess) // TODO write functions for different error messages
{

	if (!bIsogram(Guess))
	{
		return EGuessValidation::not_isogram;
	}
	else if (false) {	// if the guess is a special character
		return EGuessValidation::numbers_or_special_characters;
	}
	else if (Guess.length() != GetHiddenWordLength()) {	// if the guess is the wrong length
			return EGuessValidation::wrong_length;
	}
	else if (false) {	// if the user already tested that word
		return EGuessValidation::already_tested;
	}
	else if (!IsLower(Guess)) {	// if the word is not lowercase
		return EGuessValidation::not_lowercase;
	}
	else {
		return EGuessValidation::okay;
	}
}

