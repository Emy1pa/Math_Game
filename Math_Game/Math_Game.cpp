#include <iostream>
#include <cstdlib>
using namespace std;

enum enPassFail {Pass = 1, Fail = 2};

enum enGameLevel {
	Easy = 1,
	Medium = 2,
	Hard = 3,
	MixLevel = 4,
};

enum enOperationType {
	Addition = 1,
	Substraction = 2,
	Multiplication = 3,
	Division = 4,
	Mix = 5,
};

struct stMathGameResults {
	short NumberOfQuestions = 0;
	short UserWinTimes = 0;
	short UserLooseTimes = 0;
	enGameLevel GameLevel;
	enOperationType OperationType;
	enPassFail PassOrFail;
};

enPassFail CheckPassOrFail(short UserWinTimes, short UserLooseTimes){
	if (UserWinTimes > UserLooseTimes)
		return enPassFail::Pass;
	else
		return enPassFail::Fail;
}

struct stQuestionSet {
	short NumberOfQuestions = 0;
	enOperationType OperationType;
	enGameLevel GameLevel;
	int UserAnswer = 0;
	bool CheckQuestion = true;
	int CorrectAnswer = 0;
	int Number1 = 0;
	int Number2 = 0;
};

int generateRandomNumber(int From, int To) {
	int RandomNumber = rand() % (To - From + 1) + From;
	return RandomNumber;
}

void SetAnswerScreenColor(stQuestionSet QuestionSet){
	if (QuestionSet.CheckQuestion)
		system("Color 2F");
	else
		system("Color 4F");
}

int generateNumberBasedOnLevel(stQuestionSet QuestionSet) {
	switch (QuestionSet.GameLevel)
	{
	case enGameLevel::Easy:
		return generateRandomNumber(1, 10);
	case enGameLevel::Medium:
		return generateRandomNumber(10, 50);
	case enGameLevel::Hard:
		return generateRandomNumber(50, 100);
	case enGameLevel::MixLevel:
		return generateRandomNumber(1, 100);
	
	}
}

enOperationType getRandomOperationType() {
	return (enOperationType)generateRandomNumber(1, 4);
}

string getEnumKeyByValue(enOperationType OperationType) {
	switch (OperationType)
	{
	case enOperationType::Addition:
		return "+";
	case enOperationType::Substraction:
		return "-";
	case enOperationType::Multiplication:
		return "*";
	case enOperationType::Division:
		return "/";
	}
}

int performCalculation(stQuestionSet QuestionSet){
	if (QuestionSet.OperationType == enOperationType::Addition) {
		return QuestionSet.Number1 + QuestionSet.Number2;
	}
	else if (QuestionSet.OperationType == enOperationType::Substraction) {
		return QuestionSet.Number1 - QuestionSet.Number2;
	} 
	else if (QuestionSet.OperationType == enOperationType::Multiplication) {
		return QuestionSet.Number1 * QuestionSet.Number2;
	}
	else if (QuestionSet.OperationType == enOperationType::Division) {
		return QuestionSet.Number1 / QuestionSet.Number2;
	}
	
}

short getNumberOfQuestionsToAnswer() {
    short numberOfQuestions;
	do
	{
		cout << "How many questions do you want to answer ? \n";
		cin >> numberOfQuestions;
	} while (numberOfQuestions < 1 || numberOfQuestions > 100);
	return numberOfQuestions;
}

enGameLevel readQuestionLevel() {
	short questionLevelChoice = 0;
	do
	{
		cout << "Enter Questions Level: \n";
		cout << "[1] Easy \n";
		cout << "[2] Medium \n";
		cout << "[3] Hard \n";
		cout << "[4] Mix \n";
		cout << "Your choice: ";
		cin >> questionLevelChoice;
		cout << endl;
	} while (questionLevelChoice < 1 || questionLevelChoice > 4);
	return (enGameLevel) questionLevelChoice;
}

enOperationType readOperationType() {
	short selectedOperationChoice = 0;
	do
	{
		cout << "Enter Operation Type: \n";
		cout << "[1] Addition \n";
		cout << "[2] Subtraction  \n";
		cout << "[3] Multiplication \n";
		cout << "[4] Divison \n";
		cout << "[5] Mix \n";
		cout << "Your choice: ";
		cin >> selectedOperationChoice;
		cout << endl;

	} while (selectedOperationChoice < 1 || selectedOperationChoice > 5);
	return (enOperationType) selectedOperationChoice;
}

stMathGameResults FillMathGameResults(int NumberOfQuestion, short UserWinTimes, short UserLooseTimes, enGameLevel GameLevel, enOperationType OperationType) {
	stMathGameResults MathGameResults;
	MathGameResults.NumberOfQuestions = NumberOfQuestion;
	MathGameResults.UserWinTimes = UserWinTimes;
	MathGameResults.UserLooseTimes = UserLooseTimes;
	MathGameResults.GameLevel = GameLevel;
	MathGameResults.OperationType = OperationType;
	MathGameResults.PassOrFail = CheckPassOrFail(UserWinTimes, UserLooseTimes);
	return MathGameResults;
}

stMathGameResults startQuestions(short HowManyQuestions){

	stQuestionSet QuestionSet;
	QuestionSet.GameLevel = readQuestionLevel();
	QuestionSet.OperationType = readOperationType();

	enOperationType SelectedType = QuestionSet.OperationType;
	
	
	int UserCorrectAnswers = 0, UserFalseAnswers = 0;

	for (short QuestionCounter = 1; QuestionCounter <= HowManyQuestions; QuestionCounter++)
	{
		cout << "Question [" << QuestionCounter << "/" << HowManyQuestions << "] \n";
		QuestionSet.Number1 = generateNumberBasedOnLevel(QuestionSet);
		QuestionSet.Number2 = generateNumberBasedOnLevel(QuestionSet);

		if (SelectedType == enOperationType::Mix) {
			QuestionSet.OperationType = getRandomOperationType();
		}
		else {
			QuestionSet.OperationType = SelectedType;
		}
		
		cout << QuestionSet.Number1 << endl;
		cout << QuestionSet.Number2 << " " << getEnumKeyByValue(QuestionSet.OperationType) << endl;
		cout << "---------------------\n";
		cin >> QuestionSet.UserAnswer;
		cout << endl;

		int CorrectAnswer = performCalculation(QuestionSet);

		if (QuestionSet.UserAnswer == CorrectAnswer) {
			QuestionSet.CheckQuestion = true;
			UserCorrectAnswers++;
			cout << "Right answer :-)\n\n";
			SetAnswerScreenColor(QuestionSet);
		}
		else {
			QuestionSet.CheckQuestion = false;
			UserFalseAnswers++;
			SetAnswerScreenColor(QuestionSet);
			QuestionSet.CorrectAnswer = CorrectAnswer;
			cout << "Wrong answer :-(\n";
			cout << "The right answer is: " << QuestionSet.CorrectAnswer << endl;
			cout << endl;
		}
	}
	return FillMathGameResults(HowManyQuestions, UserCorrectAnswers, UserFalseAnswers, QuestionSet.GameLevel, SelectedType);
}

string Tabs(short NumberOfTabs){
	string t = "";
	for (int i = 1; i < NumberOfTabs; i++)
	{
		t = t + "\t";
		cout << t;
	}
	return t;
}

void ShowMathGameOverScreen() {
	cout << Tabs(2) << "--------------------------------------------------\n\n";
	cout << Tabs(2) << "                     Final Results " << endl;
	cout << Tabs(2) << "--------------------------------------------------\n\n";
}

void resetMathGame() {
	system("cls");
	system("color 0F");
}

string DisplayFinalResult(enPassFail PassOrFail){
	switch (PassOrFail)
	{
	case Pass:
		return "PASS";
	case Fail:
		return "FAIL";
	}
}

void SetGameScreenColor(enPassFail PassOrFail) {
	switch (PassOrFail)
	{
	case Pass:
		system("color 2F");
		break;
	case Fail:
		system("color 4F");
		break;
	
	}
}

string DisplayGameLevel(enGameLevel GameLevel){
	switch (GameLevel)
	{
	case Easy:
		return "Easy";
	case Medium:
		return "Medium";
	case Hard:
		return "Hard";
	case MixLevel:
		return "Mix";
	
	}
}

string DisplayOperationType(enOperationType OperationType){
	switch (OperationType)
	{
	case Mix:
		return "Mix";
	case Addition:
		return "Addition";
	case Substraction:
		return "Substraction";
	case Multiplication:
		return "Multiplication";
	case Division:
		return "Divison";
	
	}
}

void showFinalResults(stMathGameResults GameResults){
	cout << endl;
	cout << Tabs(2) << "-------------[Math Game Results]: " << DisplayFinalResult(GameResults.PassOrFail) << "------------\n";
	cout << Tabs(2) << "Number of Questions         :" << GameResults.NumberOfQuestions << endl;
	cout << Tabs(2) << "Questions Level             :" << DisplayGameLevel(GameResults.GameLevel) << endl;
	cout << Tabs(2) << "Operation Type              :" << DisplayOperationType(GameResults.OperationType) << endl;
	cout << Tabs(2) << "Number of Right Answers     :" << GameResults.UserWinTimes << endl;
	cout << Tabs(2) << "Number of Wrong Answers     :" << GameResults.UserLooseTimes << endl;
	cout << Tabs(2) << "--------------------------------------------------\n";
	SetGameScreenColor(GameResults.PassOrFail);
}

void startMathGame() {
	char PlayAgain = 'Y';
	do
	{
		resetMathGame();
		short numberOfQuestions = getNumberOfQuestionsToAnswer();
		stMathGameResults GameResults = startQuestions(numberOfQuestions);
		ShowMathGameOverScreen();
		showFinalResults(GameResults);
		cout << endl << "Do you want to play again ? (Y/N)\n";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	startMathGame();
    return 0;
}


