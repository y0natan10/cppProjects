#include <iostream>
#include <fstream>
#include <queue>
#include <filesystem>

using namespace std;
const char *PROGRAM_PATH = "C:\\Users\\yonir\\Documents\\CppPractice\\cppProjects\\resinCalculator";
const char *RESIN_PATH = "C:\\Users\\yonir\\Documents\\CppPractice\\cppProjects\\resinCalculator\\resinDetails.txt";
const char *START_TIME = "Start Date: September 21, 2024, 10PM Israel Time";

void collectInputs(queue<double> &inputs, int &entries, double &totalDays);
double calculateResinNeeded(double totalDays);
void writeOutputToFile(queue<double> &inputs, const int entries, const double resinNeeded, const double totalDays);
void writeTimeTakenToOutputFile(ostream &outputFile, queue<int> &timeSinceStart);
queue<int> secondsSinceStart();

int main()
{
    // #include <filesystem>
    // manually setting the directory every time it runs to ensure it works
    filesystem::current_path(PROGRAM_PATH);
    int entries = 0;
    double totalDays = 0;
    queue<double> inputs;

    collectInputs(inputs, entries, totalDays);
    double resinNeeded = calculateResinNeeded(totalDays);
    writeOutputToFile(inputs, entries, resinNeeded, totalDays);

    system(RESIN_PATH);

    return 0;
}

void collectInputs(queue<double> &inputs, int &entries, double &totalDays)
{
    double inputNumber;
    do
    {
        cout << "Enter the next number (0 to stop): ";
        cin >> inputNumber;
        if (inputNumber == 0)
        {
            break;
        }
        inputs.push(inputNumber);
        totalDays += inputNumber;
        ++entries;
        cout << endl;
    } while (inputNumber != 0);
}

double calculateResinNeeded(double totalDays)
{
    double minutes = totalDays * 24 * 60;

    return (minutes / 8);
}

void writeOutputToFile(queue<double> &inputs, const int entries, const double resinNeeded, const double totalDays)
{
    int counter = 0;
    // from #include <fstream>
    ofstream outputFile("resinDetails.txt");

    outputFile << START_TIME << endl;
    queue<int> timeSinceStart = secondsSinceStart();
    outputFile << "Time Passed\n";
    writeTimeTakenToOutputFile(outputFile, timeSinceStart);
    outputFile << "Entries: " << entries << endl;
    outputFile << "Total Resin Needed: " << resinNeeded << endl;
    outputFile << "Total Days: " << totalDays << endl;
    outputFile << "Fragile Resin needed: " << resinNeeded / 60 << endl;
    outputFile << "Days Inputted: \n";
    while (!inputs.empty())
    {
        outputFile << inputs.front() << " ";
        if (counter % 5 == 4) // new line every 5 entries
        {
            outputFile << endl;
        }
        inputs.pop();
        ++counter;
    }

    outputFile << endl
               << 0 << endl;
    outputFile.close();
}

void writeTimeTakenToOutputFile(ostream &outputFile, queue<int> &timeSinceStart)
{

    queue<string> timeUnit;
    timeUnit.push("Week");
    timeUnit.push("Day");
    timeUnit.push("Hour");
    timeUnit.push("Minute");
    timeUnit.push("Second");

    while (!timeSinceStart.empty())
    {
        if (!timeSinceStart.empty())
        {
            // print out the time unit of week, day etc
            outputFile << timeUnit.front();
            if (timeSinceStart.front() != 1)
            {
                outputFile << "s";
                // prints plural if number is not 1
            }
            outputFile << ": " << timeSinceStart.front() << endl;
        }
        timeSinceStart.pop();
        timeUnit.pop();
    }
    outputFile << endl;
}

queue<int> secondsSinceStart()
{
    queue<int> timeSinceStart;
    // time since january 1st 1970 to now
    const int epochToNow = time(0);
    // time since january 1st 1970 to start of project
    const int epochToStart = 1726945200;
    // difference has time in seconds from the start of the journey
    int difference = epochToNow - epochToStart;
    const int seconds = difference % 60;
    difference /= 60;
    const int minutes = difference % 60;
    difference /= 60;
    const int hours = difference % 24;
    difference /= 24;
    const int days = difference % 7;
    difference /= 7;
    const int weeks = difference;
    timeSinceStart.push(weeks);
    timeSinceStart.push(days);
    timeSinceStart.push(hours);
    timeSinceStart.push(minutes);
    timeSinceStart.push(seconds);

    return timeSinceStart;
}

/*
this is a backup for testing

Start Date: September 21, 2024, 10PM Israel Time
Time Passed
Week: 1
Days: 0
Hours: 2
Minutes: 34
Seconds: 49

Entries: 60
Total Resin Needed: 161280
Total Days: 896
Fragile Resin needed: 2688
Days Inputted:
2.9 7.2 10.8 10.2 8.4
 17.1 27.7 29 27.4 29
 25.4 16 29 26.9 28.8
 24.8 26.9 29 28.8 28
 28.4 29 28.1 4.7 8.8
 28.8 10.4 8.9 4.7 2.8
 3.8 6.8 14 4.3 5.9
 8.1 3.8 5.9 4.2 11.2
 3.8 7.8 4.7 4.3 25.4
 28.8 13.1 5.9 28.8 28.8
 6.8 8.1 2.8 26.9 4.7
 6.1 4.2 11.7 14 3.4

0
*/
