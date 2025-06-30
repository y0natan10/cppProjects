#ifndef UTILS_H
#define UTILS_H

#include <string>

void fillBoard(std::string &letterArray, std::string fillJobBoard[5]);
void clearBoard(std::string &letterArray, std::string boardClear[5]);
void sendSentence(std::string sentence, bool dryRun = false);
void typeChar(int keyCode);
std::string getNode();

#endif // UTILS_H
