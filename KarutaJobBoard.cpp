#include <iostream>
#include <string>
#include "utils.cpp"
// constexpr auto DISCORD_PATH = "C:\\Users\\yonir\\AppData\\Local\\Discord\\app-1.0.9157\\Discord.exe";
//  constexpr auto DISCORD_PATH = "C:\\Windows\\System32\\notepad.exe";
using namespace std;
// fn7lgh, cdlmtj, 72kjfb, 44npm7, lwvcxl, 4w8x2k, fxgfc3, gssp25, gl2gzb, 4nbpbk
// 10 fn7lgh, cdlmtj, 72kjfb, 44npm7, lwvcxl, 4w8x2k, fxgfc3, gssp25, gl2gzb, 4nbpbk 1

// should return
// kjw a fn7lgh
// kjw b cdlmtj
// kjw c 72kjfb
// kjw d 44npm7
// kjw e lwvcxl

void script(string letterArray, string boardClear[5], string fillJobBoard[5]);

int main()
{
	int timeToScript = 0;
	int numCodes = 0;
	string code;
	string boardClear[5];
	string fillJobBoard[5];
	string letterArray = "abcde";

	cout << "How many codes:\n";
	cin >> numCodes;
	if (!numCodes)
	{
		cout << "no codes no commands\n";
		return 0;
	}
	string *codes = new string[numCodes];
	cout << "Paste codes: \n";

	// removes commas, if present at the end of the code, from the code
	for (int i = 0; i < numCodes; ++i)
	{
		cin >> code;
		if (code.back() == ',')
		{
			code.pop_back(); // removes the last element of the string
		}
		codes[i] = code;
	}

	// the 2 for loops below are for debugging/user purpose
	// they allow the user to check if the commands are/seem to be correct

	// creates the strings of kjw a, b, c and so on
	for (int i = 0; i < letterArray.length(); ++i)
	{
		boardClear[i] = "kjw " + string(1, letterArray[i]);
		// cout << boardClear[i] << endl;
	}

	// makes commands for kjw a code, b code, c code and so on
	for (int i = 0; i < letterArray.length(); ++i)
	{
		fillJobBoard[i] = "kjw " + string(1, letterArray[i]) + " " + *(codes + i);
		// cout << fillJobBoard[i] << endl;
	}

	// 10 fn7lgh, cdlmtj, 72kjfb, 44npm7, lwvcxl, 4w8x2k, fxgfc3, gssp25, gl2gzb, 4nbpbk

	do
	{
		cout << "Are you ready for the scripting? 1 for yes, 0 for no\n";
		cin >> timeToScript;

		if (!timeToScript) // user (me) is not ready
						   // then show all lines to be pasted into discord
		{
			cout << "current prepared lines\n";
			cout << "clearing job board commands\n";
			for (int i = 0; i < letterArray.length(); ++i)
			{
				cout << boardClear[i] << endl;
			}
			cout << endl;

			cout << "Filling in the job board commands\n";
			for (int i = 0; i < letterArray.length(); ++i)
			{
				cout << fillJobBoard[i] << endl;
			}
			cout << endl;
		}
	} while (!timeToScript);

	cout << "The scripting process will now take over\n";

	// at this point there are 5 strings inside the Commands array
	// now i want my computer to automatically move over to discord, and type each command line by line
	// conditions for this to work
	// the discord channel that i want this to paste into MUST BE OPEN before running this program

	// yes this could be in the main method instead of jumping to a secondary main method
	// but it's more organized this way
	try
	{
		script(letterArray, boardClear, fillJobBoard);
	}
	catch (const string x)
	{
		cout << x;
	}

	delete[] codes;

	cout << "done\n";
	return 0;
}

void script(string letterArray, string boardClear[5], string fillJobBoard[5])
{
	string node;
	// 10 fn7lgh, cdlmtj, 72kjfb, 44npm7, lwvcxl, 4w8x2k, fxgfc3, gssp25, gl2gzb, 4nbpbk
	// system(DISCORD_PATH);
	// this opens discord
	keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY, 0); // this is the left windows key
	Sleep(5);
	keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
	Sleep(75);
	sendSentence("discord");
	Sleep(1000); // there is a lag time between hitting enter after typing discord into the windows text box
	// and discord actually openening, therefor a time delay is needed
	// this will eventually be replaced with screen reading inforation to tell when discord is open

	// for a-z you would do 0x41 to 0x5A  (this is in base 16)
	// for numbers 0-9 you would do 0x30 to 0x39
	// enter keyCode is 0x0D or VK_RETURN
	// windows keyCode is 0x5B or VK_LWIN

	// if (GetAsyncKeyState(VK_ESCAPE))
	//{
	//	//if i hit escape at any time during the scripting it will stop
	//	return;
	// }

	// clear the job board
	clearBoard(letterArray, boardClear);

	// fill the job board
	fillBoard(letterArray, fillJobBoard);
	// 10 fn7lgh, cdlmtj, 72kjfb, 44npm7, lwvcxl, 4w8x2k, fxgfc3, gssp25, gl2gzb, 4nbpbk

	// view collection in order of effort
	sendSentence("kc o is eff");

	// view job board
	sendSentence("kjb");

	// Sleep(1500);

	// sendSentence("kn");

	// method for finding the node i need to work on
	// node = getNode();

	// sendSentence("kjn abcde " + node);

	// sendSentence("kwork");

	// // alt tab to bring the console up again
	// keybd_event(VK_LMENU, 0, KEYEVENTF_EXTENDEDKEY, 0); // VK_LMENU is left alt
	// Sleep(5);

	// keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY, 0);
	// Sleep(5);
	// keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
	// Sleep(50);

	// keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);
	// Sleep(50);
}
