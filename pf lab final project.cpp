// My project works on 4D arrays, whole of quesiton file out of 5 is loaded at a time in the array.
// First dimension represents difficulty level that is also taken as input by user.
// 2nd dimension represents 20 questions for each difficulty and thsese are randomized by an int array
// 3rd represents option type like answer and opiton and statement 
// 4th represents each char 
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<conio.h>
#include<string>
using namespace std;
void menu(); 
void subject();   //for selecting subj,taken from user
void file_open(); //for opening repective file
void difficulty(); //for asking difficulty level
void selection(); //for selection of random questions;
void question_display();//shows ques to user
void que_load(); //reads all questions from file 1-60 and stores in 4D array
bool verify(int, int);  //checks that whether answer is correect or not
bool time_check(double, int); //checks time for each question
void lifeline_show();  //shows all powerups left
void lifeline_use(int, int);  //uses any powerup
void option_remove(int i); //50/50 powerup
void replace_function(int i); //to show a completely new function
void extra_time_function(); //to give user 10 more seconds for question
void neg_marking(); //for negative marking
void bonus();   //bonus points for correct answers
void highscore(); // for opening highscore file
void highscore_update(char nam[], int scor, char name[][30], int scores[], int n);//for updating the highscore file
void loging(char name[], int score, int cc, int ic); //for logging player data in a file
void review(); //for reviewing incorrect questions
void replay(); //for replayig the same questions

ifstream fin("science.txt");

int questions[10] = { 0 };//random questions nos srored in array and randomixed in void selection
//2 char in int questions (range=00-19)
//randomize it by 1-19 and use it in place of m

int file[6];
int wrong_ques[10] = { 0 }; // stores all quesion index in array which are attempted wrong by user 
const int n = 3, m = 20, o = 6, p = 100;//dimensions of 4D array
int x = 0, y = 0, j = 0, k = 0;   // These are variables that will be used inplace of n,m,o,p
char ques[n][m][o][p] = { 0 };          // 4D array for selction of question
//n is for selecting portion (easy,medium,hard)
//m for selecting random question //used an element of array questions[m] later in place of m
//o indictes type
//for exapmle o=0 for question statement
//o=1 to 0=4 for 4 options
//o=5 for  answer
//p is max size of array i.e 100
int file_arr[6];
int menu_ = 0;
int sub = 0;
int diff = 0; //variable for taking value of dificulty level
int answer;
int correct;
int incorrect;
int score = 0;//total score of the player
char N[30];  //name of player that is playing the game
int bonus_ = 0; //for calculating bonus streak;
int t = 15; //time for each question
//variables for lifeline

int h_score[10];  //for loading high scores
char names[10][30];  //for loading high scores names
time_t TIME;

bool skip = false;
bool wrong_r = false;
bool replace = false;
bool e_time = false;
bool bonus_bool = true;
bool replace_used = false;
bool high_true = false;

int main()
{
	srand(time(0));
	char l = 'C';
	do
	{
		score = 0;
		system("cls");
		char c;
		menu();
		switch (menu_)
		{
		case 1:
		{

			do
			{
				system("cls");
				subject(); //it furter leads to difficulty() before coming back to main()
				file_open();
				que_load();
				selection();
				question_display();
				if (incorrect > 0)
				{
					cout << "Do you want to review incorrected answers?(1 for Yes and 0 for No)\n";
					int n;
					cin >> n;
					if (n == 1)
					{
						while (n < 0 || n>1)
						{
							cout << "incorrect input!\n";
						}
						review();
					}
				}
				if (score > h_score[9])
				{
					cout << "You set a new highscore!\n";
					highscore_update(N, score, names, h_score, 10);
					cout << "Enter \"H\" to view high score ";
					char h;
					cin >> h;
					if (h == 'H' || h == 'h')
					{
						highscore();
					}
				}
				loging(N, score, correct, incorrect);//store information of login
				cout << "Do you want to play again?(Y/N):";
				cin >> c;
				while (c != 'Y' && c != 'y' && c != 'N' && c != 'n')
				{
					cout << "Invalid input!enter again: ";
					cin >> c;
				}
			} while (c == 'Y' || c == 'y');
			cout << "=======Program Terminating=======\n";
			cout << "=============Thank You============\n";
			l = 'a';
			break;
		}
		case 2:
		{
			highscore();
			l = 'C';
			break;
		}
		case 3:
		{
			cout << "=======Program Terminating=======\n";
			cout << "=============Thank You============\n";
			l = 'a';
			break;
		}
		}
	} while (l == 'C');//we have kept l==c as a key for breaking the loop 
	//the loop will continue till its value is 
}
void menu() //for selecting menu option.
{
	cout << "-------------------------------------\n";
	cout << "===============Quiz Game=============\n";
	cout << "-------------------------------------\n";
	cout << "Choose one:\n\n1- Quiz Now\n2- View Highscore\n3- Exit Game\n";
	cout << "---------------------------------\n";
	cout << "Enter: ";
	cin >> menu_;
	while (menu_ > 3 || menu_ < 1)
	{
		cout << "-------------------------------------\n";
		cout << "Invalid choice! Enter again\n";
		cin >> menu_;
	}
}
void subject() //for selecting subject
{
	system("cls");
	cout << "-------------------------------------\n";
	cout << "===============Quiz Game=============\n";
	cout << "-------------------------------------\n";
	cout << "Choose subject:\n\n";
	cout << "1- Science\n2- Computer\n3- Sports\n4- History\n5- Logic\n";
	cout << "---------------------------------\n";
	cout << "Enter: ";
	cin >> sub;
	while (sub > 5 || sub < 1)
	{
		cout << "Invalid choice! Enter again\n";
		cin >> sub;
	}

	difficulty();
}
void highscore()
{
	system("cls");
	cout << "-------------------------------------\n";
	cout << "===============Quiz Game=============\n";
	cout << "-------------------------------------\n";
	cout << "          <- Leaderboard ->         \n";
	cout << "-------------------------------------\n";
	ifstream ffin("high.txt");
	if (!ffin.is_open())
	{
		cout << "Highscore file is not open!";
	}
	for (int i = 0; i < 10; ++i)
	{
		ffin >> h_score[i];
		ffin.getline(names[i], 100);
	}
	for (int i = 0; i < 10; ++i)
	{
		cout << h_score[i] << " \t";
		cout << names[i];
		cout << endl;
	}
	cout << "-------------------------------------\n";
	char f;
	cout << "Enter B to go to main nenu or R to review answers: \n";
	do
	{
		cin >> f;
	} while (f != 'B' && f != 'b' && f != 'R' && f != 'r');
	if (f == 'r' || f == 'R')
	{
		review();
	}
	ffin.close();
}
void file_open() // for opening the file//futher leads to loads all questions from file in 4D array
{
	fin.close();
	switch (sub)
	{
	case 1:
		fin.open("science.txt");
		if (!fin.is_open())
		{
			cout << "file is closed";
		}
		break;
	case 2:
	{
		fin.open("computer.txt");
		if (!fin.is_open())
		{
			cout << "file is closed";
		}
		break;
	}
	case 3:
	{
		fin.open("sports.txt");
		if (!fin.is_open())
		{
			cout << "file is closed";
		}
		break;
	}
	case 4:
	{
		fin.open("history.txt");
		if (!fin.is_open())
		{
			cout << "file is closed";
		}
		break;
	}
	case 5:
	{
		fin.open("logic.txt");
		if (!fin.is_open())
		{
			cout << "file is closed";
		}
		break;
	}
	que_load();
	}
}
void selection() //for selecting random nos of questions
{
	for (int a = 0; a < 10; ++a)
	{
		questions[a] = rand() % 20;
		for (int s = 0; s < a; ++s)
		{
			if (questions[a] == questions[s] && a != s)
			{
				questions[a] = rand() % 20;
				s = -1;
				continue;
			}
		}
	}
	return;
}
void question_display()
{ //most imp part for displaying question 
	//even controls a large no of functions 
	skip = false;
	wrong_r = false;
	replace = false;
	e_time = false;
	replace_used = false;
	score = 0;
	correct = 0;
	incorrect = 0;
	bonus_ = 0;
	for (int i = 0; i < 10; ++i)
	{
		t = 10;
		system("cls");

		cout << "===============Quiz Game=============\n";
		lifeline_show();
		cout << "---------------------------------\n";
		cout << "Current score: " << score << endl;
		cout << "---------------------------------\n";
		cout << "Question " << i + 1 << " :" << endl;
		cout << "---------------------------------\n";
		for (int j = 0; j < 1; ++j)
		{
			for (int k = 0; k < p - 1 && ques[x - 1][questions[i]][j][k] != '#'; ++k)
			{
				cout << ques[x - 1][questions[i]][j][k];
			}
			cout << endl;
		}
		for (int j = 1; j < 5; ++j)
		{
			cout << setw(3) << setfill(' ') << left << j;
			cout << setw(5) << setfill(' ') << left << ques[x - 1][questions[i]][j];

			cout << endl;
		}
		cout << "---------------------------------\n";
		cout << "Enter your answer(1-4): ";
		time_t que_time = time(0);
		TIME = que_time;
		cin >> answer;
		while ((answer > 8 || answer < 1))
		{
			cout << "Invalid answer,Enter again: ";
			cin >> answer;
		}

		if (answer == 5)
		{
			if (!skip)
			{
				skip = true;
				continue;
			}
			else
			{
				cout << "Skip is aready used!";
			}
		}
		replace_used = false; //here it is made false so that it does not continue the question loop 
		do
		{
			if (answer == 6 || answer == 7 || answer == 8)
			{
				lifeline_use(x, i);
				continue;
			}
			else
				if ((answer > 4 || answer < 1))
				{
					cout << "Invalid answer,Enter again: ";
					cin >> answer;
				}
		} while (answer > 8 && answer < 1);
		if (replace_used)
		{
			continue;
		}
		int f = ques[x - 1][questions[i]][5][0] - '0';
		bool check = verify((int)answer, f);
		if (check)
		{
			system("cls");
			cout << "===============Quiz Game=============\n";
			cout << setw(25) << setfill(' ') << right << "Correct Answer" << endl;
			cout << "=================================\n";
			correct++;
			score += 10;
			bonus_++;
			bonus();
		}
		else
		{
			system("cls");
			cout << "===============Quiz Game=============\n";
			cout << setw(25) << setfill(' ') << right << "Wrong Answer" << endl;
			cout << "---------------------------------\n";
			cout << "  Correct answer was " << ques[x - 1][questions[i]][f] << endl;
			cout << "=================================\n";
			incorrect++;
			if (incorrect > 0)
			{
				wrong_ques[incorrect - 1] = questions[i];
			}
			neg_marking();
			bonus_ = 0;
		}
		time_t que_time_end = time(0);
		double time_used = difftime(que_time_end, que_time);
		time_check(time_used, t);
		system("pause");
	}
	system("pause");
	cout << "Total score was: " << score << endl;
}
void que_load()   //stores whole file into 4D char array
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			for (int k = 0; k < 6; ++k)
			{
				fin.getline(ques[i][j][k], 100);
				int len = strlen(ques[i][j][k]);
				if (len > 0 && ques[i][j][k][len - 1] == '\r')
					ques[i][j][k][len - 1] = '\0';
			}
		}
	}
	fin.close();
}
void difficulty()
{
	cout << "===============Quiz Game=============\n\n";
	cout << "Choose difficulty level\n1- Easy\n2- Intermediate\n3- Advanced\n";
	cout << "-------------------------------------\n";
	cout << "Enter: ";
	cin >> diff;
	while (diff > 3 || diff < 1)
	{
		cout << "-------------------------------------\n";
		cout << "invalid difficulty!Enter again\n";
		cin >> diff;
	}
	cout << "-------------------------------------\n";
	cout << "Enter your name: ";
	cin.ignore();
	cin.getline(N, 30);
	cout << "=====================================\n";
	x = diff;
	system("pause");
}
bool verify(int select, int key)
{
	if (select == key)
	{
		return true;
	}
	else
		return false;
}
bool time_check(double x, int y)
{
	if (x > y)
	{
		cout << "Penality!Time exceeds limit of " << t << " sec!(negative 2 points)\n";
		score -= 2;
		return false;
	}
	else
	{
		cout << "Well in time\n";
		return true;
	}

}
void lifeline_show()
{
	cout << setw(15) << setfill(' ') << right << "Power-UPs:" << endl;
	cout << setw(15) << setfill(' ') << left << "Skip-up: ";
	cout << (!skip) ? 1 : 0;
	cout << " (enter '5')" << endl;
	cout << setw(15) << setfill(' ') << left << "Replace: ";
	cout << (!replace) ? 1 : 0;
	cout << " (enter '6')" << endl;
	cout << setw(15) << setfill(' ') << left << "Extra time: ";
	cout << (!e_time) ? 1 : 0;
	cout << " (enter '7')" << endl;
	cout << setw(15) << setfill(' ') << left << "50/50: ";
	cout << (!wrong_r) ? 1 : 0;
	cout << " (enter '8')" << endl;
}
void lifeline_use(int x, int y)
{
	if (answer == 8)
	{
		if (!wrong_r)
		{
			option_remove(y);


		}
		else
		{
			cout << "Remove(50/50) is already used!\n";
			cout << "Enter Answer: ";
			cin >> answer;
			while (answer > 4 || answer < 1)
			{
				cout << "Invalid answer: ";
				cin >> answer;
			}
		}
	}
	else if (answer == 7)
	{
		if (!e_time)
		{
			extra_time_function();
		}
		else
		{
			cout << "Extra time is already used!\n";
			cout << "Enter Answer: ";
			cin >> answer;
			while (answer > 4 || answer < 1)
			{
				cout << "Invalid answer: ";
				cin >> answer;
			}
		}
	}
	else if (answer == 6)
	{
		if (!replace)
		{
			replace_function(x);
		}
		else
		{
			cout << "Replace is already used!\n";
			cout << "Enter Answer: ";
			cin >> answer;
			while (answer > 4 || answer < 1)
			{
				cout << "Invalid answer: ";
				cin >> answer;
			}
		}
	}
}
void option_remove(int i)
{
	system("cls");
	cout << "===============Quiz Game=============\n";
	cout << "           50/50 ACTIVATED           \n";
	cout << "---------------------------------\n";
	cout << "Question " << i + 1 << " :" << endl;
	cout << ques[x - 1][questions[i]][0] << endl;
	int index = ques[x - 1][questions[i]][5][0] - '0';
	int wrong_idx;
	do
	{
		wrong_idx = (rand() % 4) + 1;
	} while (wrong_idx == index);

	cout << "---------------------------------\n";
	for (int j = 1; j <= 4; ++j)
	{
		if (j == index || j == wrong_idx)
		{
			cout << setw(3) << left << j << " " << ques[x - 1][questions[i]][j] << endl;
		}
		else
		{
			cout << setw(3) << left << j << " " << endl;
		}
	}
	wrong_r = true;
	cout << "---------------------------------\n";
	cout << "Enter Answer (" << ((index < wrong_idx) ? index : wrong_idx) << " or " << ((index > wrong_idx) ? index : wrong_idx) << "): ";
	cin >> answer;
}
void replace_function(int i)
{
	int new_que;
	bool exists;

	do
	{
		new_que = rand() % 20;
		exists = false;
		for (int k = 0; k < 10; ++k)
		{
			if (questions[k] == new_que)
			{
				exists = true;
				break;
			}
		}
	} while (exists);

	replace = true;
	system("cls");
	cout << "===============Quiz Game=============\n";
	cout << "         Question Replaced          \n";
	cout << "---------------------------------\n";
	cout << "Question " << i << " :" << endl;
	for (int k = 0; k < 100 && ques[x - 1][new_que][0][k] != '#'; ++k)
	{
		cout << ques[x - 1][new_que][0][k];
	}
	cout << endl;
	for (int j = 1; j <= 4; ++j)
	{
		cout << setw(3) << left << j << " " << ques[x - 1][new_que][j] << endl;
	}
	cout << "---------------------------------\n";
	cout << "Enter Answer (1-4): ";
	do
	{
		cin >> answer;
	} while (answer > 4 || answer < 1);
	int val = ques[x - 1][new_que][5][0] - '0';
	bool check;
	check = verify((int)answer, val);
	if (check)
	{
		system("cls");
		cout << "===============Quiz Game=============\n";
		cout << "         Question Replaced          \n";
		cout << setw(25) << setfill(' ') << right << "Correct Answer" << endl;
		cout << "=================================\n";
		correct++;
		score += 10;
		bonus_++;
		bonus();
	}
	else
	{
		system("cls");
		cout << "===============Quiz Game=============\n";
		cout << "         Question Replaced          \n";
		cout << setw(25) << setfill(' ') << right << "Wrong Answer" << endl;
		cout << "=================================\n";
		incorrect++;
		neg_marking();
		bonus_ = 0;
	}
	replace_used = true;
	system("pause");
}
void extra_time_function()
{
	t += 15;
	cout << "Extra time granted!\n";
	e_time = true;
	cout << "Enter Answer: ";
	cin >> answer;
	while (answer > 4 || answer < 1)
	{
		cout << "Invalid answer: ";
		cin >> answer;
	}
}
void neg_marking()
{
	switch (x)
	{
	case 1:
	{
		cout << "Negative marking!(easy)\n";
		score -= 2;
		break;
	}
	case 2:
	{
		cout << "Negative marking!(medium)\n";
		score -= 3;
		break;
	}
	case 3:
	{
		cout << "Negative marking!(hard)\n";
		score -= 5;
		break;
	}
	}
}
void bonus()
{
	if (bonus_ == 3)
	{
		cout << "Bonus awarded!(+5 points)\n";
		score += 5;
		bonus_ = 0;
	}
	if (correct >= 5 && bonus_bool)
	{
		cout << "bonus awarded!(+15 points)\n";
		score += 15;
		bonus_bool = false;
	}
}
void highscore_update(char nam[], int scor, char name[][30], int scores[], int n)
{

	ifstream ffin("high.txt");
	if (!ffin.is_open())
	{
		cout << "Highscore file is not open!";
	}
	for (int i = 0; i < 10; ++i)
	{
		ffin >> h_score[i];
		ffin.getline(names[i], 100);
	}
	ffin.close();
	int x = n;
	if (scor < scores[n - 1])
	{
		return;
	}
	for (int i = n - 1; i >= 0; --i)
	{
		if (scor <= scores[i])
		{
			x = i + 1;
			break;
		}
		if (i == 0 && scor > scores[i])
		{
			x = 0; 
			break;
		}
	}
	for (int i = n - 1; i > x; --i)
	{
		scores[i] = scores[i - 1];
		for (int j = 0; j < 30; ++j)
		{
			name[i][j] = name[i - 1][j];
		}
	}
	scores[x] = scor;
	int s = strlen(nam);
	for (int i = 0; i < 30; ++i)
	{
		name[x][i] = '\0';
	}
	for (int i = 0; i < s; ++i)
	{
		name[x][i] = nam[i];
	}
	ofstream fout("high.txt");
	for (int i = 0; i < n; ++i)
	{
		fout << scores[i] << " " << name[i] << endl;
	}
	fout.close();
}
void loging(char name[], int score, int cc, int ic)
{
	ofstream logout("quiz_log.txt", ios::app);
	if (!logout.is_open())
	{
		cout << "File for logging data is not open!\n";
		return;
	}
	logout << setw(30) << setfill(' ') << left << name;
	logout << " Score: " << setw(5) << setfill(' ') << left << score;
	logout << " Correct: " << setw(5) << setfill(' ') << left << cc;
	logout << " Incorrect: " << setw(5) << setfill(' ') << left << ic;
	logout << "Time & Date: " << __TIME__ << endl;
	logout << __DATE__;
	logout.close();
}
void review()
{
	system("cls");
	cout << "===============Quiz Game=============\n";
	cout << "              Answer Key             \n\n";
	int n = sizeof(wrong_ques[10]);
	for (int i = 0; i < n; ++i)
	{
		cout << "---------------------------------\n";
		for (int j = 0; j < 1; ++j)
		{
			cout << ques[x - 1][i][j] << endl;
		}
		for (int j = 1; j < 5; ++j)
		{
			cout << j << "- " << ques[x - 1][i][j] << endl;
		}
		for (int j = 5; j < 6; ++j)
		{
			{
				cout << "  Correct answer was " << ques[x - 1][i][j] << endl;
			}
		}
		cout << "=================================\n";
	}
	system("pause");
	cout << "Do you want to replay the Questions(1 for Yes/0 for No)\n";
	int asdf;
	cin >> asdf;
	while (asdf != 1 && asdf != 0)
	{
		cout << "Invalid input\n";
		cin >> asdf;
	}
	if (asdf == 1)
	{
		replay();
	}
}
void replay() 
{
	cout << "===============Quiz Game=============\n";
	cout << "      Replaying Same questions       \n";
	cout << "---------------------------------\n";
	question_display();
}