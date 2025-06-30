#ifndef utils
#include <Windows.h>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <GdiPlus.h>
#include <string>
#include <iostream>
#include <cctype>
#include <fstream>
#pragma comment(lib, "GdiPlus.lib")

void fillBoard(std::string &letterArray, std::string fillJobBoard[5]);
void clearBoard(std::string &letterArray, std::string boardClear[5]);
void sendSentence(std::string sentence, bool dryRun = false);
void typeChar(int keyCode);
std::string getNode();

// 10 fn7lgh, cdlmtj, 72kjfb, 44npm7, lwvcxl, 4w8x2k, fxgfc3, gssp25, gl2gzb, 4nbpbk 1

void fillBoard(std::string &letterArray, std::string fillJobBoard[5])
{
	for (int i = 0; i < letterArray.length(); ++i)
	{
		sendSentence(fillJobBoard[i]);
	}
}

void clearBoard(std::string &letterArray, std::string boardClear[5])
{
	for (int i = 0; i < letterArray.length(); ++i)
	{
		sendSentence(boardClear[i]);
	}
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

std::string getNode()
{
	sendSentence("kn", false);
	Sleep(5000); // wait for the message to be sent
	// Initialize GDI+
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

	// Hardcoded region for 1920x1080 primary screen
	int x = 0, y = 0;
	int width = 1920;
	int height = 1080;

	HDC hdcScreen = GetDC(nullptr);
	HDC hdcMem = CreateCompatibleDC(hdcScreen);
	HBITMAP hbmScreen = CreateCompatibleBitmap(hdcScreen, width, height);
	SelectObject(hdcMem, hbmScreen);

	BitBlt(hdcMem, 0, 0, width, height, hdcScreen, x, y, SRCCOPY);

	Gdiplus::Bitmap bitmap(hbmScreen, nullptr);

	CLSID pngClsid;
	CLSIDFromString(L"{557CF406-1A04-11D3-9A73-0000F81EF32E}", &pngClsid); // PNG CLSID
	bitmap.Save(L"screen.png", &pngClsid, nullptr);

	ReleaseDC(nullptr, hdcScreen);
	DeleteDC(hdcMem);
	DeleteObject(hbmScreen);

	Gdiplus::GdiplusShutdown(gdiplusToken);

	// Use Tesseract to read the image
	tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();

	// Tesseract expects the path to the tessdata directory itself
	const char *tessdataPrefix = std::getenv("TESSDATA_PREFIX");
	// Default fallback: C:/tesseract/tessdata/
	std::string tessdataPath = tessdataPrefix ? tessdataPrefix : "C:/tesseract/tessdata/";

	if (api->Init(tessdataPath.c_str(), "eng")) // path to tessdata directory
	{
		std::cerr << "Could not initialize tesseract.\n";
		return "";
	}

	Pix *image = pixRead("screen.png");
	api->SetImage(image);
	std::string outText = api->GetUTF8Text();

	// Write OCR result to a text file
	std::ofstream outFile("ocr_output.txt");
	if (outFile.is_open())
	{
		outFile << outText;
		outFile.close();
	}
	else
	{
		std::cerr << "Could not write to ocr_output.txt\n";
	}

	// Clean up
	api->End();
	pixDestroy(&image);
	delete api;

	// Return the OCR result as before
	return outText;
}

#endif // !utils
