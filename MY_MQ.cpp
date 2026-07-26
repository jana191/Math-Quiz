#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//====================
// Enums
//====================
enum enLevel
{
    Easy = 1,
    Med = 2,
    Hard = 3,
    Mix = 4
};

enum enOpType
{
    Add = 1,
    Sub = 2,
    Mul = 3,
    Div = 4,
    OMix = 5
};

//====================
// Structs
//====================
struct stQuizQues
{
    short QuesNum = 0;
    enLevel UserLevelChoice;
    enOpType UserOpTypeChoice;
    short Num1 = 0;
    short Num2 = 0;
    char OP;
    short UserAnswer = 0;
    short RightAnswer = 0;
};
struct stQuizResults
{
    short NumberOfQues = 0;
    enLevel QuesLevel;
    enOpType OPType;
    short RightAnswersNum = 0;
    short WrongAnswersNum = 0;
};
//====================
// Function Prototypes
//====================
short GetQuestionsNum();
enLevel GetQuestionsLevel();
enOpType GetOperationType();
int GetUserAnswer();
int RandNum(int from, int to);
string Tabs(int NumsOfTabs);
char GetRandomOP();
stQuizResults PlayQuiz(short NumOfQues);
stQuizQues GenerateQuestion(enLevel Level, enOpType OpType);
void StartQuiz();
bool PassOrFail(stQuizResults QuizResults);
void PrintResultsScreen(stQuizResults QuizResults);
void PrintFinalResults(stQuizResults QuizResults, stQuizQues Quizques);
string LevelName(enLevel Level);
string OPName(enOpType OpType);
void ResetScreen();
//====================
// Utility Functions
//====================
int RandNum(int from, int to)
{
    int RandNum = rand() % (to - from + 1) + from;
    return RandNum;
}

string Tabs(int NumsOfTabs)
{
    string t = "";
    for (int i = 0; i < NumsOfTabs; i++)
    {
        t += "\t";
    }
    return t;
}

void ResetScreen()
{
    system("cls");
    system("color 0F"); // Black
}
//====================
// Input Functions
//====================
short GetQuestionsNum()
{
    short QN = 0;
    do
    {
        cout << "How Many Questions Do you want ? 1:10  ";
        cin >> QN;
    } while ((QN < 1) || (QN > 10));
    return QN;
}

enLevel GetQuestionsLevel()
{
    short QL = 0;
    do
    {
        cout << "Enter Question Level [1]:Easy [2]:Med [3]:Hard [4]:Mix  ";
        cin >> QL;
    } while ((QL < 1) || (QL > 4));
    return (enLevel)QL;
}

enOpType GetOperationType()
{
    short OP = 0;
    do
    {
        cout << "Enter Operation Type [1]:Add [2]:Sub [3]:Mul [4]:Div [5]:Mix  ";
        cin >> OP;
    } while ((OP < 1) || (OP > 5));
    return (enOpType)OP;
}

int GetUserAnswer()
{
    int UserAnswer;
    cout << "Your Answer: ";
    cin >> UserAnswer;
    return UserAnswer;
}
//====================
// Quiz Logic
//====================
stQuizQues GenerateQuestion(enLevel Level, enOpType OpType)
{
    stQuizQues QuizQues;
    int From, To, N1, N2;

    if (OpType == enOpType::OMix)
    {
        QuizQues.OP = GetRandomOP();
    }
    else
    {
        switch (OpType)
        {
        case enOpType::Add:
            QuizQues.OP = '+';
            break;

        case enOpType::Sub:
            QuizQues.OP = '-';
            break;

        case enOpType::Mul:
            QuizQues.OP = '*';
            break;

        case enOpType::Div:
            QuizQues.OP = '/';
            break;
        }
    }
    if (Level == enLevel::Mix)
    {
        Level = (enLevel)RandNum(1, 3);
    }
    switch (Level)
    {
    case enLevel::Easy:
        From = 1;
        To = 20;
        break;

    case enLevel::Med:
        From = 20;
        To = 40;
        break;

    case enLevel::Hard:
        From = 60;
        To = 80;
        break;
    }
    QuizQues.Num1 = RandNum(From, To);
    QuizQues.Num2 = RandNum(From, To);

    switch (QuizQues.OP)
    {
    case '+':
        QuizQues.RightAnswer = QuizQues.Num1 + QuizQues.Num2;
        break;

    case '-':
        QuizQues.RightAnswer = QuizQues.Num1 - QuizQues.Num2;
        break;

    case '*':
        QuizQues.RightAnswer = QuizQues.Num1 * QuizQues.Num2;
        break;

    case '/':
        QuizQues.RightAnswer = QuizQues.Num1 / QuizQues.Num2;
        break;
    }

    return QuizQues;
}

stQuizResults PlayQuiz(short NumOfQues)
{
    stQuizQues QuizQues;
    stQuizResults QuizResults;
    QuizResults.NumberOfQues = NumOfQues;
    QuizQues.UserLevelChoice = GetQuestionsLevel();
    QuizQues.UserOpTypeChoice = GetOperationType();
    QuizResults.QuesLevel = QuizQues.UserLevelChoice;
    QuizResults.OPType = QuizQues.UserOpTypeChoice;
    for (int i = 1; i <= NumOfQues; i++)
    {
        cout << "\nQuestion [" << i << "/" << NumOfQues << "] \n\n";
        QuizQues = GenerateQuestion(QuizResults.QuesLevel, QuizResults.OPType);

        cout << QuizQues.Num1 << Tabs(1) << "\n"
             << QuizQues.Num2 << " " << QuizQues.OP << Tabs(1) << "\n"
             << "_________________\n";

        QuizQues.UserAnswer = GetUserAnswer();

        if (QuizQues.UserAnswer == QuizQues.RightAnswer)
        {
            system("color 2F");
            cout << "Right Answer!\n";
            QuizResults.RightAnswersNum++;
        }
        else
        {
            system("color 4F");
            cout << "\a";
            cout << "Wrong Answer \n";
            cout << "Right Answer is: " << QuizQues.RightAnswer << endl;
            QuizResults.WrongAnswersNum++;
        }
    }
    return QuizResults;
}

bool PassOrFail(stQuizResults QuizResults)
{
    return QuizResults.RightAnswersNum >= QuizResults.WrongAnswersNum;
}
//====================
// Output Functions
//====================
char GetRandomOP()
{
    enOpType RandOP = (enOpType)RandNum(1, 4);
    switch (RandOP)
    {
    case enOpType::Add:
        return '+';

    case enOpType::Sub:
        return '-';

    case enOpType::Mul:
        return '*';

    case enOpType::Div:
        return '/';
    }
}
string LevelName(enLevel Level)
{
    string LevelArr[4] = {"Easy", "Med", "Hard", "Mix"};
    return LevelArr[Level - 1];
}

string OPName(enOpType OpType)
{
    string OPArr[5] = {"Add", "Sub", "Mul", "Div", "Mix"};
    return OPArr[OpType - 1];
}
void PrintResultsScreen(stQuizResults QuizResults)
{
    if (PassOrFail(QuizResults))
    {
        system("color 2F");
        cout << "____________________________________\n\n";
        cout << "     FINAL RESULT IS PASS !! \n";
        cout << "____________________________________\n";
    }
    else
    {
        system("color 4F");
        cout << "\a";
        cout << "____________________________________\n\n";
        cout << "     FINAL RESULT IS FAIL :(\n";
        cout << "____________________________________\n";
    }
}
void PrintFinalResults(stQuizResults QuizResults)
{
    cout << "Number Of Questions      : " << QuizResults.NumberOfQues;
    cout << "\nQuestions Level          : " << LevelName(QuizResults.QuesLevel);
    cout << "\nOP Type                  : " << OPName(QuizResults.OPType);
    cout << "\nNumber of Right Answers  : " << QuizResults.RightAnswersNum;
    cout << "\nNumber of Wrong Answers  : " << QuizResults.WrongAnswersNum;
}
//====================
// Main Game
//====================
void StartQuiz()
{
    char again;
    do
    {
        ResetScreen();
        stQuizResults QuizResults;
        QuizResults.NumberOfQues = GetQuestionsNum();
        QuizResults = PlayQuiz(QuizResults.NumberOfQues);
        PrintResultsScreen(QuizResults);
        PrintFinalResults(QuizResults);
        cout << endl
             << Tabs(3) << "Do you want to play again ? Y/N ";
        cin >> again;
    } while (again == 'Y' || again == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartQuiz();
    return 0;
}