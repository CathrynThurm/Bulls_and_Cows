/*
This is the console executeble that makes use of the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all user interatin
To see game logic go to FBullCowGame class.
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include <map>

#define TMap std::map

// to make sytax Unreal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCgame; // new game instantiation "BCgame"

int32 HiddenWordLength = BCgame.GetUserWordLength(); //global variable

int main() {

	do {
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain() == 1);

	return 0;
}

// TODO  explain what bulls and cows mean
// TODO give more hints
void PrintIntro() {
	std::cout << "\n\nWelcome to Bulls and Cows\n";
	std::cout << "Can you guess the " << HiddenWordLength << " letter isogram that I am thinking of?\n";
	std::cout << "An isogram is a word with no repeating letters.\n";
	std::cout << "For each guess you'll see how many BULLS and COWS you got.\n";
	std::cout << "BULLS are the correct letters in the correct places, COWS are the correct letters in the wrong places." << std::endl;
	std::cout << "\n";
	std::cout << "  /                      \\" << std::endl;
	std::cout << " /X/      _______        \\X\\" << std::endl;
	std::cout << "|XXX\   _/       \\_    /XXX|___________" << std::endl;
	std::cout << "\\XXXXXXX           XXXXXXX/          \\\\\\" << std::endl;
	std::cout << " \\XXXX    /    \\  XXXXX/               \\\\\\" << std::endl;
	std::cout << "      |   0     0   |                         \\" << std::endl;
	std::cout << "       |           |     BULLS                 \\" << std::endl;
	std::cout << "       \\         /           &                 |______//" << std::endl;
	std::cout << "        \\       /              COWS            |" << std::endl;
	std::cout << "         | O_O | \                            |" << std::endl;
	std::cout << "          \\ _ /   \________________           |" << std::endl;
	std::cout << "                      | |  | |     \\         /" << std::endl;
	std::cout << "                      / |  / |      \\______/" << std::endl;
	std::cout << "                   __| |__| |      __| |__| |" << std::endl;
	std::cout << "                   |___||___|      |___||___|" << std::endl;

	std::cout << std::endl;
	return;
}

// loops continually until the user provides a valid guess
FText GetValidGuess() {
	EGuessValidation validation = invalid_validation;
	do
	{
		int32 CurrentTry = BCgame.GetCurrentTry();
		FText Guess = "";
		std::cout << "                 HINT: " << BCgame.GiveHint() << std::endl;
		std::cout << "Try " << CurrentTry << " of " << BCgame.GetMaxTries() << std::endl;
		std::cout << "Please enter your guess:" << std::endl;
		getline(std::cin, Guess);
		EGuessValidation validation = BCgame.CheckGuessValidity(Guess);
		switch (validation)
		{
		case (EGuessValidation::wrong_length):
			std::cout << "Please enter a word with " << HiddenWordLength << " letters for a valid guess\n";
			break;
		case EGuessValidation::already_tested:
			std::cout << "You have already tested that word, please enter a new word.\n";
			break;
		case EGuessValidation::not_isogram:
			std::cout << "The word you are trying to test is not an isogram. An isogram is a word with no repeating letters.\n";
			break;
		case EGuessValidation::not_lowercase:
			std::cout << "Please enter a word that is all lowercases.\n";
			break;
		case EGuessValidation::numbers_or_special_characters:
			std::cout << "Please enter a word with no special characters or numbers.\n";
			break;
		default:
			return Guess;
		}
	} while (validation != okay);
	
}

void PlayGame()
{
	BCgame.Reset();
	//BCgame.GetMaxTries();


	// loop while the game is NOT won
	// and there are tries remaining
	while (!BCgame.IsGameWon() && BCgame.GetCurrentTry() <= BCgame.GetMaxTries())
	{
			FText Guess = GetValidGuess();
			FBullCowCount BullCowCount = BCgame.SubmitGuess(Guess);
			
			std::cout << "Bulls: " << BullCowCount.bulls;
			std::cout << " Cows: " << BullCowCount.cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again? (y/n) "; //TODO MAKE THIS ASK TO GET ANOTHER USER WORD LENGTH
	FText Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}


void PrintGameSummary()
{
	if (BCgame.IsGameWon())
	{
		std::cout << "\nYOU WIN!!\n";
	}
	else {
		std::cout << "\nHA FUCKING LOSER\n";
	}
}
