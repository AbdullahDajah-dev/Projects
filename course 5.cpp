#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <ctime>
using namespace std;

enum enGameChoice { Rock = 1, Paper, Scissor };

enum enWinner { Player1 = 1, Computer, Draw };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner RoundWinner;
	string WinnerName;
};

struct stGameResult
{
	short GameRounds = 0;
	short player1Wins = 0;
	short ComputerWins = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName;
};

int RandomNumber(int from, int to)
{
	int random_number = rand() % (to - from + 1) + from;
	return random_number;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}
	switch (RoundInfo.Player1Choice)
	{
	case enGameChoice::Rock:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissor)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Scissor:
		if (RoundInfo.ComputerChoice == enGameChoice::Rock)
		{
			return enWinner::Computer;
		}
		break;
	}
	return enWinner::Player1;
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

string ChoiceName(enGameChoice Choice)
{
	string arrChoiceName[3] = { "Rock", "Paper", "Scissor" };
	return arrChoiceName[Choice - 1];
}

string WinnerName(enWinner winner)
{
	string arrWinnerName[3] = { "Player1", "Computer", "Draw" };
	return arrWinnerName[winner - 1];
}

enGameChoice ReadPlayerChoice()
{
	int Choice;
	do
	{
		cout << "Your Choice --> [1]: Rock  [2]: Paper  [3]: Scissors ?\n";
		cin >> Choice;

	} while (Choice < 1 || Choice > 3);

	return (enGameChoice)Choice;
}

short HowManyRounds()
{
	short Rounds;
	do
	{
		cout << "How Many Rounds 1 to 10 ?\n";
		cin >> Rounds;
	} while (Rounds < 1 || Rounds > 10);

	return Rounds;
}

void ShowRoundResult(stRoundInfo RoundInfo)
{
	cout << "\n__________ Round [" << RoundInfo.RoundNumber << "] __________\n\n";
	cout << "Player1 Choice  : " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << "\n";
	cout << "Round Winner    : [" << RoundInfo.WinnerName << "] \n";
	cout << "_______________________________\n" << endl;
}

stGameResult FillGameResult(short GameRounds, short Player1Wins, short ComputerWins, short DrawTimes)
{
	stGameResult GameResult;

	GameResult.GameRounds = GameRounds;
	GameResult.player1Wins = Player1Wins;
	GameResult.ComputerWins = ComputerWins;
	GameResult.DrawTimes = DrawTimes;
	GameResult.GameWinner = WhoWonTheGame(Player1Wins, ComputerWins);
	GameResult.WinnerName = WinnerName(GameResult.GameWinner);

	return GameResult;
}

stGameResult PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short Player1Wins = 0, ComputerWins = 0, DrawTimes = 0;

	for (short GameRounds = 1;GameRounds <= HowManyRounds;GameRounds++)
	{
		cout << "Round [" << GameRounds << "] Begins\n";
		RoundInfo.RoundNumber = GameRounds;
		RoundInfo.Player1Choice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.RoundWinner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.RoundWinner);

		if (RoundInfo.RoundWinner == enWinner::Player1)
		{
			Player1Wins++;

		}
		else if (RoundInfo.RoundWinner == enWinner::Computer) {

			ComputerWins++;
		}
		else {
			DrawTimes++;
		}

		ShowRoundResult(RoundInfo);
	}

	return FillGameResult(HowManyRounds, Player1Wins, ComputerWins, DrawTimes);
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

void ShowGameOverScreen()
{
	cout << Tabs(4) << "________________________________________________\n\n";
	cout << Tabs(4) << "               +++ G A M E  O V E R +++\n";
	cout << Tabs(4) << "________________________________________________\n\n";
}

void SetWinnerScreenColor(stGameResult GameResult)
{
	switch (GameResult.GameWinner)
	{
	case enWinner::Computer:
		system("color 4f");
		cout << "\a";
		break;
	case enWinner::Player1:
		system("color 2f");
		break;
	default:
		system("Color 6f");
	}
}

void ShowFinalGameResult(stGameResult GameResult)
{
	cout << Tabs(4) << "_____________ Game Result _____________\n\n";
	cout << Tabs(4) << "Game Rounds   : " << GameResult.GameRounds << endl;
	cout << Tabs(4) << "Player1 Wins  : " << GameResult.player1Wins << endl;
	cout << Tabs(4) << "Computer Wins : " << GameResult.ComputerWins << endl;
	cout << Tabs(4) << "Draw Times    : " << GameResult.DrawTimes << endl;
	cout << Tabs(4) << "Final Winner  : " << GameResult.WinnerName << endl;
	cout << Tabs(4) << "______________________________________" << endl;

	SetWinnerScreenColor(GameResult);
}

void ResestScreen()
{
	system("cls");
	system("color 0f");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResestScreen();
		stGameResult GameResult = PlayGame(HowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResult(GameResult);

		cout << Tabs(4) << "Do you want to play again? Y/N ?";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');

	system("color 0f");
	cout << "\n" << Tabs(4) << "Thank you for playing with us :-)" << endl;
	cout << "\n" << Tabs(4) << "Credits : Abdullah Al-Dajah" << endl;
}


int main() {

	srand((unsigned)time(NULL));

	StartGame();




	return 0;
}