#ifndef utils

#include <string>
#include <iostream>
#include <cctype>
#include <Windows.h>
using namespace std;
void fillBoard(string &letterArray, string fillJobBoard[5]);
void clearBoard(string &letterArray, string boardClear[5]);
void sendSentence(string sentence, bool dryRun = false);
void typeChar(int keyCode);
string getNode()
{
    string res = "";
    return res;
};

// 10 fn7lgh, cdlmtj, 72kjfb, 44npm7, lwvcxl, 4w8x2k, fxgfc3, gssp25, gl2gzb, 4nbpbk 1

void fillBoard(string &letterArray, string fillJobBoard[5])
{
    for (int i = 0; i < letterArray.length(); ++i)
    {
        sendSentence(fillJobBoard[i]);
    }
}

void clearBoard(string &letterArray, string boardClear[5])
{
    for (int i = 0; i < letterArray.length(); ++i)
    {
        sendSentence(boardClear[i]);
    }
}

void sendSentence(string sentence, bool dryRun)
{
    // switch case
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

// 10 fn7lgh, cdlmtj, 72kjfb, 44npm7, lwvcxl, 4w8x2k, fxgfc3, gssp25, gl2gzb, 4nbpbk 1
void typeChar(int keyCode)
{
    if (GetAsyncKeyState(VK_ESCAPE))
    {
        // if i hit escape at any time during the scripting it will stop
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

// Here lies the code that lived in the sendSentence method. It was good code. Jk. 2024-2024. It lived less than 24 hours, and will not be missed.
// if (keyCode == ' ')
// {
// 	keybd_event(VK_SPACE, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'a')
// {
// 	keybd_event(0x41, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x41, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'b')
// {
// 	keybd_event(0x42, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x42, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'c')
// {
// 	keybd_event(0x43, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'd')
// {
// 	keybd_event(0x44, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x44, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'e')
// {
// 	keybd_event(0x45, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x45, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'f')
// {
// 	keybd_event(0x46, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x46, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'g')
// {
// 	keybd_event(0x47, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x47, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'h')
// {
// 	keybd_event(0x48, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x48, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'i')
// {
// 	keybd_event(0x49, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x49, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'j')
// {
// 	keybd_event(0x4A, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x4A, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'k')
// {
// 	keybd_event(0x4B, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x4B, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'l')
// {
// 	keybd_event(0x4C, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x4C, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'm')
// {
// 	keybd_event(0x4D, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x4D, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'n')
// {
// 	keybd_event(0x4E, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x4E, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'o')
// {
// 	keybd_event(0x4F, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x4F, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'p')
// {
// 	keybd_event(0x50, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x50, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'q')
// {
// 	keybd_event(0x51, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x51, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'r')
// {
// 	keybd_event(0x52, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x52, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 's')
// {
// 	keybd_event(0x53, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x53, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 't')
// {
// 	keybd_event(0x54, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x54, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'u')
// {
// 	keybd_event(0x55, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x55, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'v')
// {
// 	keybd_event(0x56, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'w')
// {
// 	keybd_event(0x57, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x57, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'x')
// {
// 	keybd_event(0x58, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x58, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'y')
// {
// 	keybd_event(0x59, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x59, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == 'z')
// {
// 	keybd_event(0x5A, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(0x5A, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == '0')
// {
// 	keybd_event(VK_NUMPAD0, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(VK_NUMPAD0, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == '1')
// {
// 	keybd_event(VK_NUMPAD1, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(VK_NUMPAD1, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == '2')
// {
// 	keybd_event(VK_NUMPAD2, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(VK_NUMPAD2, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == '3')
// {
// 	keybd_event(VK_NUMPAD3, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(VK_NUMPAD3, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == '4')
// {
// 	keybd_event(VK_NUMPAD4, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(VK_NUMPAD4, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == '5')
// {
// 	keybd_event(VK_NUMPAD5, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(VK_NUMPAD5, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == '6')
// {
// 	keybd_event(VK_NUMPAD6, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(VK_NUMPAD6, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == '7')
// {
// 	keybd_event(VK_NUMPAD7, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(VK_NUMPAD7, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == '8')
// {
// 	keybd_event(VK_NUMPAD8, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(VK_NUMPAD8, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }
// else if (keyCode == '9')
// {
// 	keybd_event(VK_NUMPAD9, 0, KEYEVENTF_EXTENDEDKEY, 0);
// 	Sleep(5);
// 	keybd_event(VK_NUMPAD9, 0, KEYEVENTF_KEYUP, 0);
// 	Sleep(50);
// }

#endif // !utils