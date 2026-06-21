#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enGameChoice {Rock = 1, Paper, Scissor};
enum enWinner {Player1 = 1, Computer, Draw};

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputeChoice;
	enWinner Winner;
	string WinnerName;
};

struct stGameResult
{
	short GameRounds = 0;
	short Player1Wins = 0;
	short ComputerWins = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName;
};

short ReadHowManyRounds()
{
	short rounds = 1;
	do
	{
		cout << "How Many Rounds 1 to 10 ? \n";
		cin >> rounds;

	} while (rounds < 1 || rounds > 10);

	return rounds;
}

int RandomNumber(int from, int to)
{
	int random_number = rand() % (to - from + 1) + from;
	return random_number;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}

enGameChoice ReadPlayerChoice()
{
	short Choice = 1;
	do
	{
		cout << "Your Choice: [1]:Rock, [2]:Paper, [3]:Scissor?\n";
		cin >> Choice;

	} while (Choice < 1 || Choice > 3);

	return (enGameChoice)Choice;
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputeChoice)
	{
		return enWinner::Draw;
	}
	switch (RoundInfo.Player1Choice)
	{
	case enGameChoice::Rock:
		if (RoundInfo.ComputeChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Paper:
		if (RoundInfo.ComputeChoice == enGameChoice::Scissor)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Scissor:
		if (RoundInfo.ComputeChoice == enGameChoice::Rock)
		{
			return enWinner::Computer;
		}
		break;
	}

	return enWinner::Player1;
}

string ChoiceName(enGameChoice choice)
{
	string arrGameChoices[3] = { "Rock", "Paper", "Scissor" };
	return arrGameChoices[choice - 1];
}

string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player1", "Computer", "Draw" };
	return arrWinnerName[Winner - 1];
}

enWinner WhoWonTheGame(short Player1Wins, short ComputerWins)
{
	if (Player1Wins > ComputerWins)
	{
		return enWinner::Player1;
	}
	else if (ComputerWins > Player1Wins)
	{
		return enWinner::Computer;
	}
	else {
		return enWinner::Draw;
	}
}

void PrintRoundInfo(stRoundInfo RoundInfo)
{
	cout << "\n__________ Round [" << RoundInfo.RoundNumber << "] __________\n\n";
	cout << "Player1 Choice  : " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer Choice : " << ChoiceName(RoundInfo.ComputeChoice) << "\n";
	cout << "Round Winner    : [" << RoundInfo.WinnerName << "] \n";
	cout << "_____________________________\n" << endl;
}

stGameResult FillGameResult(short GameRounds, short Player1Wins, short ComputerWins, short DrawTimes)
{
	stGameResult GameResult;
	GameResult.GameRounds = GameRounds;
	GameResult.Player1Wins = Player1Wins;
	GameResult.ComputerWins = ComputerWins;
	GameResult.DrawTimes = DrawTimes;
	GameResult.GameWinner = WhoWonTheGame(Player1Wins, ComputerWins);
	GameResult.WinnerName = WinnerName(GameResult.GameWinner);

	return GameResult;
}

string Tabs(short HowManyTabs)
{
	string t = "";
	
	for (int i = 0;i < HowManyTabs;i++)
	{
		t += "\t";
	}
	return t;
}

stGameResult PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;

	short Player1Wins = 0, ComputerWins = 0, DrawTimes = 0;

	for (short GameRounds = 1; GameRounds <= HowManyRounds;GameRounds++)
	{
		cout << "\nRound [" << GameRounds << "] Begins\n";
		RoundInfo.RoundNumber = GameRounds;
		RoundInfo.Player1Choice = ReadPlayerChoice();
		RoundInfo.ComputeChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);
		
		if (RoundInfo.Winner == enWinner::Player1)
		{
			Player1Wins++;
		}
		else if (RoundInfo.Winner == enWinner::Computer)
		{
			ComputerWins++;
		}
		else {
			DrawTimes++;
		}
		PrintRoundInfo(RoundInfo);
	}
	return FillGameResult(HowManyRounds, Player1Wins, ComputerWins, DrawTimes);
}

void ShowGameOverScreen()
{
	cout << Tabs(3) << "  _________________________________________________\n\n";
	cout << Tabs(3) << "                  +++ Game Over +++\n";
	cout << Tabs(3) << "  _________________________________________________\n\n";
}

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player1:
		system("color 2F");
		break;
	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;
	default:
		system("color 6F");
		break;
	}
}

void ShowFinalGameResults(stGameResult GameResult)
{
	cout << Tabs(4) << "_____________ Game Result _____________\n\n";
	cout << Tabs(4) << "Game Rounds        : " << GameResult.GameRounds << endl;
	cout << Tabs(4) << "Player1 Won Times  : " << GameResult.Player1Wins << endl;
	cout << Tabs(4) << "Computer Won Times : " << GameResult.ComputerWins << endl;
	cout << Tabs(4) << "Draw Times         : " << GameResult.DrawTimes << endl;
	cout << Tabs(4) << "Final Winner       : " << GameResult.WinnerName << endl;
	cout << Tabs(4) << "_______________________________________";

	SetWinnerScreenColor(GameResult.GameWinner);
}

void ResestScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResestScreen();
		stGameResult GameResult = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResult);

		cout << endl << Tabs(4) << " Do you want to play again? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
	
	system("color 0F");
	cout << "\n" << Tabs(4) << " Thank you for playing with us :) " << endl;
}


int main()
{
	
	srand((unsigned)time(NULL));
	
	StartGame();
	

	return 0;
}
