#include <iostream>   
#include <string>  
#include <ctime>
#include <cstdlib>


using namespace std;


int RandNumber(int From, int To)
{
    int RandNum = rand() % (To - From + 1) + From;
    return RandNum;
}
enum enGameChoice{stone = 1, paper = 2, scissor = 3};
string GetChoiceName(enGameChoice choic)
{
    string ChoicNam[3] = { "Stone", "Paper", "Scissor" };
    return ChoicNam[choic - 1];
}
enum enWinner {player = 1, computer = 2, Draw = 3};
string WinnerName(enWinner winner)
{
    string WinnerName[3] = { "Player", "Computer", "Draw" };
    return WinnerName[winner - 1];
}
struct strRoundResult
{
    short RoundNumber = 0;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;

};
struct strGameResult
{
    short GameRounds = 0;
    short PlayerWinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName;

};
short ReadHowManyRounds(string msg)
{
    short NumberOfRounds;
    do
    {
        cout << msg;
        cin >> NumberOfRounds;

    } while (NumberOfRounds < 1 || NumberOfRounds > 10);
    cout << endl;
        return NumberOfRounds;
}
enGameChoice GetPlayerChoice()
{
    
    short ChoiceNum;
    do
    {
        cout << "Enter your choice Stone[1], Paper[2], Scissor[3]: ";
        cin >> ChoiceNum;

    } while (ChoiceNum < 1 || ChoiceNum > 3);

    return (enGameChoice)ChoiceNum;
}
enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandNumber(1, 3);
}
enWinner WhoWonTheRound(strRoundResult GameRound)
{
    if (GameRound.PlayerChoice == GameRound.ComputerChoice)
        return enWinner::Draw;



    switch (GameRound.PlayerChoice)
    {
    case enGameChoice::stone:
        if (GameRound.ComputerChoice == enGameChoice::paper)
            return enWinner::computer;

    case enGameChoice::paper:
        if (GameRound.ComputerChoice == enGameChoice::scissor)
            return enWinner::computer;

    case enGameChoice::scissor:
        if (GameRound.ComputerChoice == enGameChoice::stone)
            return enWinner::computer;

    }
    // if you are her then player is winer
    return enWinner::player;
}
enWinner WhoWonTheGame(short PlayerTimesWin, short ComputerTimesWin)
{
    if (PlayerTimesWin > ComputerTimesWin)
        return  enWinner::player;

    else if (PlayerTimesWin < ComputerTimesWin)
        return enWinner::computer;
    else
        return enWinner::Draw;
}
void SetScreenWinner(enWinner winer)
{
    switch (winer)
    {
    case enWinner::player: system("color 2F");
        break;

    case enWinner::computer: system("color 4F");
        cout << "\a";
        break;

    default: system("color 6F");

    }
}
strGameResult FillGameResult(int HowManyRounds, short PlayerTimesWin, short ComputerTimesWin, short DrawTimes)
{
    strGameResult GameResults;

    GameResults.GameRounds = HowManyRounds;
    GameResults.PlayerWinTimes = PlayerTimesWin;
    GameResults.ComputerWinTimes = ComputerTimesWin;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(PlayerTimesWin, ComputerTimesWin);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}
void ShowGameOverScreen()
{
    cout << "___________________________________________\n";
    cout << "_____________+++[Game Over]+++_____________\n\n";
}
void PrintFinalGameResult(strGameResult GameResult)
{
    cout << "\n\n\n___________________________________________\n\n";
    cout << "Game        Rounds:" << GameResult.GameRounds << endl;
    cout << "Player   won Times: " << GameResult.PlayerWinTimes << endl;
    cout << "Computer won Times: " << GameResult.ComputerWinTimes << endl;
    cout << "Draw         Times: " << GameResult.DrawTimes << endl;
    cout << "Game        Winner: [" <<GameResult.WinnerName<< "]" << endl;
    cout << "\n___________________________________________\n"<<endl;

    SetScreenWinner(GameResult.GameWinner);
}
void PrintRoundResult(strRoundResult RoundResult)
{
    cout << "\n\n_________________Round["<<RoundResult.RoundNumber<<"]__________________\n\n";
    cout << "Player   choice: " << GetChoiceName(RoundResult.PlayerChoice) << endl;
    cout << "Computer choice: " << GetChoiceName(RoundResult.ComputerChoice) << endl;
    cout << "Round    Winner: [" << RoundResult.WinnerName << "]" <<  endl;
    cout << "___________________________________________\n\n\n" << endl;

    SetScreenWinner(RoundResult.Winner);
}
strGameResult PlayGame(short HowManyRounds)
{
    
    short PlayerTimesWin = 0, ComputerTimesWin = 0, DrawTimes = 0;
    strRoundResult RoundR;
    strGameResult GameResult;

    for (int GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
       
        RoundR.RoundNumber = GameRound;
        RoundR.PlayerChoice = GetPlayerChoice();
        RoundR.ComputerChoice = GetComputerChoice();
        RoundR.Winner = WhoWonTheRound(RoundR);
        RoundR.WinnerName = WinnerName(RoundR.Winner);


        if (RoundR.Winner == enWinner::player)
            PlayerTimesWin++;
      
        else if (RoundR.Winner == enWinner::computer)
                    ComputerTimesWin++;
        
        else
            DrawTimes++;

            PrintRoundResult(RoundR);
    }

    return FillGameResult(HowManyRounds, PlayerTimesWin, ComputerTimesWin, DrawTimes);

    
}
void StartGame()
{
    char PlayAgain = 'Y';
    
    do
    {
        system("cls");
        system("color 0F");
       strGameResult  GameResults =  PlayGame(ReadHowManyRounds("Please enter number of Rounds 1 to 10: "));
       ShowGameOverScreen();
       PrintFinalGameResult(GameResults);
       cout << "\n\nDo you want to play again Y / N ? ";
       cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');

}



int main()
{
    srand((unsigned)time(NULL));

    StartGame();
    
    return 0;
}