
#include <Windows.h>
#include <string>
#include <iostream>
#include <cctype>

using namespace std;
void sendSentence(std::string sentence, bool dryRun);
void typeChar(int keyCode);
string intToString(int i);

void newSection();

int main()
{
    int magnitude = 6;
    // cout << "input magnitude\n";
    // cin >> magnitude;
    for (int i = 1; i <= magnitude; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            cout << i;
        }
        cout << endl;
    }
    for (int i = magnitude - 1; i > 0; --i)
    {
        for (int j = 0; j < i; ++j)
        {
            cout << i;
        }
        cout << endl;
    }

    newSection();

    for (int i = 0; i <= magnitude; ++i)
    {
        // print spaces
        for (int j = i; j < magnitude; ++j)
        {
            cout << " ";
        }
        // print numbers
        for (int j = 0; j < (2 * i) - 1; ++j)
        {
            cout << magnitude - i;
            // cout << "*";
        }
        cout << endl;
    }

    // // i want to send a message every 5-6 seconds starting from a certain number that the user specifies
    // int startNumber;
    // cin >> startNumber;
    // Sleep(2000); // wait 2 seconds to give the user time to switch to the chat window
    // for (int i = startNumber + 1; i < 1000000; ++i)
    // {
    //     sendSentence(intToString(i), false); // send the message to the chat window
    //     Sleep(5100 + (rand() % 1000));       // randomize the input times
    // }
}

void sendSentence(std::string sentence, bool dryRun)
{
    for (int i = 0; i < sentence.length(); ++i)
    {
        Sleep((rand() % 15) + 5); // randomize indavidual key press times
        typeChar(sentence[i]);
    }
    // after each 'sentence' we need an enter key pressed to send the message into the chat window
    if (!dryRun)
    {
        typeChar('\n');
    }
}

void typeChar(int keyCode)

{
    if (GetAsyncKeyState(VK_ESCAPE))
    {
        // if escape is pressed while this method is being called running, we want to stop the script
        // in this case, every ~5 seconds, we will check if the escape key is pressed
        throw("Scripting has stopped\n");
    }

    if (keyCode == '\n')
    {
        keybd_event(VK_RETURN, 0, KEYEVENTF_EXTENDEDKEY, 0);
        Sleep(5);
        keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
        Sleep((rand() % 501) + 200); // randomize the input times
        return;
    }
    // cout << "Typing key '" << (char)keyCode << "\t' {" << (int)keyCode << "}" << endl;
    keyCode = toupper(keyCode);
    keybd_event(keyCode, 0, KEYEVENTF_EXTENDEDKEY, 0);
    Sleep(5);
    keybd_event(keyCode, 0, KEYEVENTF_KEYUP, 0);
    Sleep(50);
}

string intToString(int i)
{
    string s = to_string(i);
    return s;
}

void newSection()
{
    for (int i = 0; i < 4; ++i)
    {
        cout << endl;
    }
}