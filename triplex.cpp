#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

void PrintMessage(std::string TextFlagStart, std::string TextFlagEnd);
void PrintNewline(int NumOfLines);

std::vector<bool> PlayGame(int LevelDifficulty);
void GameIntro(int LevelDifficulty);
std::vector<int> GiveGameCodes(int LevelDifficulty);
std::vector<int> AskForPlayerGuesses();
bool CheckWinOrLose(std::vector<int> GameCodes, std::vector<int> PlayerGuesses);
bool AskForPlayAgain(bool WinOrLoseFlag);
void BufferCleanUp();

int main()
{
    srand(time(NULL)); // Create new random sequence based on time of the day

    std::vector<bool> GameResult;
    const int MaxDifficulty = 5;
    int LevelDifficulty = 1;
    do
    {
        // Start playing game
        GameResult = PlayGame(LevelDifficulty);

        BufferCleanUp();

        if (GameResult[0])
        {
            LevelDifficulty++;
        }
    } 
    while (GameResult[1] && LevelDifficulty <= MaxDifficulty);

    std::cout << "Congratulations! You've reached the final secure server room! You won this battle!" << std::endl;
    
    return 0;
}


std::vector<bool> PlayGame(int LevelDifficulty) 
{
    // Print Introduction
    GameIntro(LevelDifficulty);

    // Get game codes
    std::vector<int> GameCodes = GiveGameCodes(LevelDifficulty);

    // Get player guess
    std::vector<int> PlayerGuesses = AskForPlayerGuesses();

    // Check result
    bool WinOrLoseFlag = CheckWinOrLose(GameCodes, PlayerGuesses);

    // Ask if player wants to play again
    bool PlayAgainFlag = AskForPlayAgain(WinOrLoseFlag);

    std::vector<bool> GameResult(2);
    GameResult[0] = WinOrLoseFlag;
    GameResult[1] = PlayAgainFlag;
    return GameResult;
}

void GameIntro(int LevelDifficulty)
{
    // Print game intro
    PrintNewline(2);
    std::cout << "You are a secret agent breaking into a LEVEL " << LevelDifficulty << " secure server room." << std::endl;
    PrintMessage("--Game Intro Start", "--Game Intro End");
}

std::vector<int> GiveGameCodes(int LevelDifficulty) 
{
    // Print game level info
    const int CodeA = rand() % (3 + LevelDifficulty) + 1;
    const int CodeB = rand() % (3 + LevelDifficulty) + 1;
    const int CodeC = rand() % (3 + LevelDifficulty) + 1;

    const int CodeSum = CodeA + CodeB + CodeC;
    const int CodeProduct = CodeA * CodeB * CodeC;
    PrintNewline(1);
    PrintMessage("--Game Level Info Start", "--Game Level Info End");
    std::cout << "+ The codes add-up to: " << CodeSum << std::endl;
    std::cout << "+ The codes multiply to give: " << CodeProduct << std::endl;
    PrintNewline(1);
    std::vector<int> GameCodes(2);
    GameCodes[0] = CodeSum;
    GameCodes[1] = CodeProduct;
    return GameCodes;
}

std::vector<int> AskForPlayerGuesses()
{
    // Store player guess
    int GuessA, GuessB, GuessC;
    std::cin >> GuessA >> GuessB >> GuessC;
    std::cout << "You entered: " << GuessA << " " << GuessB << " " << GuessC << std::endl;
    PrintNewline(1);

    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;
    std::vector<int> PlayerGuesses(2);
    PlayerGuesses[0] = GuessSum;
    PlayerGuesses[1] = GuessProduct;
    return PlayerGuesses;
}

bool CheckWinOrLose(std::vector<int> GameCodes, std::vector<int> PlayerGuesses) 
{
    bool WinOrLoseFlag;

    // Check if the player's guess is correct
    if(PlayerGuesses[0] == GameCodes[0] && PlayerGuesses[1] == GameCodes[1])
    {
        PrintMessage("--Game Win Start", "--Game Win End");
        PrintNewline(1);
        WinOrLoseFlag = true;
    }
    else 
    {
        PrintMessage("--Game Lose Start", "--Game Lose End");
        PrintNewline(1);
        WinOrLoseFlag = false;
    }

    return WinOrLoseFlag;
}

bool AskForPlayAgain(bool WinOrLoseFlag) 
{
    bool PlayAgainFlag = false;
    char PlayerChoice;

    if(WinOrLoseFlag) 
    {
        PrintMessage("--Game Win Play Again Start", "--Game Win Play Again End");
    }
    else 
    {
        PrintMessage("--Game Lose Play Again Start", "--Game Lose Play Again End");
    }

    std::cin >> PlayerChoice;

    if(PlayerChoice == 'y' || PlayerChoice == 'Y')
    {
        PlayAgainFlag = true;
    }
    else 
    {
        PlayAgainFlag = false;
    }
    return PlayAgainFlag;
}

void BufferCleanUp() 
{
    std::cin.clear();
    std::cin.ignore();
}


void PrintMessage(std::string TextFlagStart, std::string TextFlagEnd) 
{
    // Loading game texts
    std::ifstream Infile(".\\game_texts.txt");
    std::string Line;
    bool PrintStartFlag = false;
    while(std::getline(Infile, Line)) 
    {
        if(!PrintStartFlag && Line.substr(0, Line.size()) == TextFlagStart) 
        {
            PrintStartFlag = true;
        }
        else if(PrintStartFlag && Line.substr(0, Line.size()) == TextFlagEnd) 
        {
            PrintStartFlag = false;
            break;
        }
        else if(PrintStartFlag)
        {
            std::cout << Line << std::endl;
        }
    }
}

void PrintNewline(int NumOfLines)
{
    for(int i = 0; i < NumOfLines; i++) 
    {
        std::cout << std::endl;
    }
}

