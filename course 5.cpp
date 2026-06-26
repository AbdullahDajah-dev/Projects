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
	enGameChoice ComputerChoice;
	enGameChoice Player1Choice;
	enWinner Winner;
	string WinnerName;
	bool PlayerWon = false;
};

struct stGameResult
{
	
	int TotalRounds = 0;
	int Player1Wins = 0;
	int ComputerWins = 0;
	int DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName;
};

string Tabs(short HowManyTabs)
{
	string t = "";

	for (int i = 0;i < HowManyTabs;i++)
	{
		t += "\t";
	}
	return t;
}

int RandomNumber(int from, int to)
{
	int random_number = rand() % (to - from + 1) + from;
	return random_number;
}

int ReadHowManyRounds()
{
	int NumberOfRounds = 0;
	do
	{
		cout << "How many rounds 1 to 10 ? ";
		cin >> NumberOfRounds;

	} while (NumberOfRounds < 1 || NumberOfRounds > 10);

	return NumberOfRounds;
}

enGameChoice GetPlayerChoice()
{
	int Player1Choice = 1;
	do
	{
		cout << "Your Choice -> [1]Rock  [2]Paper  [3]Scissor ?\n";
		cin >> Player1Choice;

	} while (Player1Choice < 1 || Player1Choice > 3);

	return (enGameChoice)Player1Choice;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}

string GetChoiceName(enGameChoice Choice)
{
	string arrPlayerChoice[3] = { "Rock", "Paper", "Scissor" };
	return arrPlayerChoice[Choice - 1];
}

string GetWinnerName(enWinner Winner)
{
	string arrWinner[3] = { "Player1", "Computer", "Draw" };
	return arrWinner[Winner - 1];
}

enWinner WhoWonTheRound(stRoundInfo);

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
	else 
	{
		return enWinner::Draw;
	}
}

void ShowRoundResult(stRoundInfo RoundInfo)
{
	cout << "\n__________ Round [" << RoundInfo.RoundNumber << "] __________\n\n";
	cout << "Player1 Choice  : " << GetChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer Choice : " << GetChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round winner    : " << RoundInfo.WinnerName << endl;
	cout << "_______________________________\n" << endl;
}

stGameResult FillGameResult(short TotalRounds, short Player1Wins, short ComputerWins, short DrawTimes)
{
	stGameResult GameResult;

	GameResult.TotalRounds = TotalRounds;
	GameResult.Player1Wins = Player1Wins;
	GameResult.ComputerWins = ComputerWins;
	GameResult.DrawTimes = DrawTimes;
	GameResult.GameWinner = WhoWonTheGame(Player1Wins, ComputerWins);
	GameResult.WinnerName = GetWinnerName(GameResult.GameWinner);

	return GameResult;
}

stGameResult PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;

	short PLayerWins = 0, ComputerWins = 0, DrawTimes = 0;

	for (short round = 1;round <= HowManyRounds;round++)
	{
		cout << "\nRound [" << round << "] Begins\n";
		RoundInfo.RoundNumber = round;
		RoundInfo.Player1Choice = GetPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = GetWinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player1)
		{
			RoundInfo.PlayerWon = true;
			PLayerWins++;
		}
		else if (RoundInfo.Winner == enWinner::Computer)
		{
			RoundInfo.PlayerWon = false;
			ComputerWins++;
		}
		else {
			RoundInfo.PlayerWon = false;
			DrawTimes++;
		}

		ShowRoundResult(RoundInfo);
	}

	return FillGameResult(HowManyRounds, PLayerWins, ComputerWins, DrawTimes);
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
	case enWinner::Player1:
		system("color 2f");
		break;
	case enWinner::Computer:
		cout << "\a";
		system("color 4f");
		break;
	default:
		system("color 6f");
	}
}

void ShowGameResult(stGameResult GameResult)
{
	cout << Tabs(4) << "_____________ Game Result _____________\n\n";
	cout << Tabs(4) << "Game Rounds   : " << GameResult.TotalRounds << endl;
	cout << Tabs(4) << "Player1 Wins  : " << GameResult.Player1Wins << endl;
	cout << Tabs(4) << "Computer Wins : " << GameResult.ComputerWins << endl;
	cout << Tabs(4) << "Draw Times    : " << GameResult.DrawTimes << endl;
	cout << Tabs(4) << "Final Winner  : " << GameResult.WinnerName << endl;
	cout << Tabs(4) << "______________________________________" << endl;

	SetWinnerScreenColor(GameResult);
}

void ResetScreen()
{
	system("cls");
	system("Color 0f");
}

void StartGame()
{
	string PlayAgain = "y";

	do
	{

		ResetScreen();
		stGameResult GameResult = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowGameResult(GameResult);

		cout << Tabs(4)<< "Do you want to play again? y/n: ";
		cin >> PlayAgain;

	} while (PlayAgain == "y" || PlayAgain == "Y");

	system("color 0f");
	cout << endl;
	cout << Tabs(4)<< "Thank you for playin with us :-)" << endl;
}






int main() {

	srand((unsigned)time(NULL));

	StartGame();




	return 0;
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
	}

	return enWinner::Player1;
}