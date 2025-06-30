#include <iostream>
#include <string>
#include <windows.h>
#include "utils.h"
constexpr auto DISCORD_PATH = "C:\\Users\\yonir\\AppData\\Local\\Discord\\app-1.0.9189\\Discord.exe";

// fn7lgh, cdlmtj, 72kjfb, 44npm7, lwvcxl, 4w8x2k, fxgfc3, gssp25, gl2gzb, 4nbpbk
// 10 fn7lgh, cdlmtj, 72kjfb, 44npm7, lwvcxl, 4w8x2k, fxgfc3, gssp25, gl2gzb, 4nbpbk 1

// should return
// kjw a fn7lgh
// kjw b cdlmtj
// kjw c 72kjfb
// kjw d 44npm7
// kjw e lwvcxl

void script(std::string letterArray, std::string boardClear[5], std::string fillJobBoard[5]);

int main()
{
	int timeToScript = 0;
	int numCodes = 0;

	std::string code;
	// std::string code = getNode();
	std::string boardClear[5];
	std::string fillJobBoard[5];
	std::string letterArray = "abcde";

	std::cout << "How many codes:\n";
	std::cin >> numCodes;
	if (!numCodes)
	{
		std::cout << "no codes no commands\n";
		return 0;
	}
	std::string *codes = new std::string[numCodes];
	std::cout << "Paste codes: \n";

	for (int i = 0; i < numCodes; ++i)
	{
		std::cin >> code;
		if (code.back() == ',')
		{
			code.pop_back();
		}
		codes[i] = code;
	}

	std::cout << "\ncommands to be used\n";
	for (int i = 0; i < letterArray.length(); ++i)
	{
		boardClear[i] = "kjw " + std::string(1, letterArray[i]);
		std::cout << boardClear[i] << std::endl;
	}

	for (int i = 0; i < letterArray.length(); ++i)
	{
		fillJobBoard[i] = "kjw " + std::string(1, letterArray[i]) + " " + *(codes + i);
		std::cout << fillJobBoard[i] << std::endl;
	}

	do
	{
		std::cout << "\nAre you ready for the scripting? 1 for yes, 0 for no\n";
		std::cin >> timeToScript;

		if (!timeToScript)
		{
			std::cout << "current prepared lines\n";
			std::cout << "clearing job board commands\n";
			for (int i = 0; i < letterArray.length(); ++i)
			{
				std::cout << boardClear[i] << std::endl;
			}
			std::cout << std::endl;

			std::cout << "Filling in the job board commands\n";
			for (int i = 0; i < letterArray.length(); ++i)
			{
				std::cout << fillJobBoard[i] << std::endl;
			}
			std::cout << std::endl;
		}
	} while (!timeToScript);

	std::cout << "The scripting process will now take over\n";

	try
	{
		script(letterArray, boardClear, fillJobBoard);
	}
	catch (const std::string x)
	{
		std::cout << x;
	}

	delete[] codes;

	std::cout << "done\n";
	return 0;
}

void script(std::string letterArray, std::string boardClear[5], std::string fillJobBoard[5])
{
	std::string node;
	system(DISCORD_PATH);
	keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY, 0);
	Sleep(50);
	keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
	Sleep(75);
	sendSentence("discord");
	Sleep(2000);

	clearBoard(letterArray, boardClear);
	fillBoard(letterArray, fillJobBoard);

	node = getNode();
	// sendSentence("kjn abcde " + node);
	sendSentence("kc o is eff");
	sendSentence("kjb");

	// sendSentence("kwork");
}
