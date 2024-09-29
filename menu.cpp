// cout and cin
#include <iostream>
// need for sleep(time in miliseconds)
#include <windows.h>
// self explanatory
#include <queue>
using namespace std;

void fillProjects(queue<string> &projects);
void printProjects(queue<string> projects);
void chooseProgram(const int &choice);

const char *Menu_Path = "C:\\Users\\yonir\\Documents\\CppPractice\\cppProjects\\Menu\\menu.exe";
const char *Job_Board_Path = "C:\\Users\\yonir\\Documents\\CppPractice\\cppProjects\\Scripting\\KarutaJobBoard\\KarutaJobBoard.exe";
const char *Resin_Calc_Path = "C:\\Users\\yonir\\Documents\\CppPractice\\cppProjects\\resinCalculator\\resinCalculator.exe";

enum MENU
{
    MENU = 1,
    KARUTA_JOB_BOARD,
    RESIN_CALCULATOR
};
#define MAGIC_NUMBER 3;

int main()
{
    int upperLimit = MAGIC_NUMBER + 1;
    int choice;
    queue<string> projects;
    fillProjects(projects);
    do
    {
        system("cls");
        cout << "Menu:\n";
        printProjects(projects);
        cout << "0 to exit\nEnter your choice: ";

        do
        {
            cin >> choice;
            if (choice == 0)
            {
                break;
            }
        }

        while (choice < 0 || choice > upperLimit);
        chooseProgram(choice);

    } while (choice != 0);

    for (int i = 3; i >= 1; --i)
    {
        cout << i << endl;
        Sleep(1000);
    }

    return 0;
}

void fillProjects(queue<string> &projects)
{
    projects.push("Menu (you're already here dufus)");
    projects.push("Karuta Job Board");
    projects.push("Resin Calculator");
}

// does not use the & so the pop does change the original
void printProjects(queue<string> projects)
{
    for (int i = 1; !projects.empty(); ++i)
    {
        cout << i << ". " << projects.front() << endl;
        projects.pop();
    }
}

void chooseProgram(const int &choice)
{
    switch (choice)
    {
    case MENU:
        cout << "really?" << endl;
        Sleep(1500);
        cout << "i mean really?\n";
        Sleep(2500);
        cout << "you were in the menu and you wanna go more into the menu?\n";
        Sleep(1500);
        cout << "why";
        Sleep(10000);
        system(Menu_Path);
        break;
    case KARUTA_JOB_BOARD:
        system(Job_Board_Path);
        break;
    case RESIN_CALCULATOR:
        system(Resin_Calc_Path);
        break;
    default:
        cout << "Exiting Menu\n";
        break;
    }
}
