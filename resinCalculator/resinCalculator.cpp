#include <iostream>
#include <fstream>
#include <queue>
#include <filesystem>

using namespace std;
const char *PROGRAM_PATH = "C:\\Users\\yonir\\Downloads\\cppProjects\\resinCalculator";
const char *RESIN_PATH = "C:\\Users\\yonir\\Downloads\\cppProjects\\resinCalculator\\resinDetails.txt";
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
    // need this (i think) for the opening of the text file
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
    if (inputs.empty())
    {
        return;
    }

    // from #include <fstream>
    ofstream outputFile("resinDetails.txt");
    int counter = 0;

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
Weeks: 12
Days: 5
Hours: 15
Minutes: 4
Seconds: 13

Entries: 56
Total Resin Needed: 84690
Total Days: 470.5
Fragile Resin needed: 1411.5
Days Inputted:
0.4 5.2 6.8 5.3 12.8
8.6 8.3 18 29.3 8.9
7.7 9.1 13.9 10.6 14.1
12.6 7.6 14.1 12 13.7
13.9 11.7 13.9 14.1 13.9
14.1 14.1 13.9 5.1 1.1
3.1 3.1 1.3 1.1 8.3
0.9 2.1 2.4 0.6 7.4
0.9 1.3 4.1 18.7 4.7
18.7 18.7 0.9 1.3 14.2
2.7 2.7 2.1 1.3 6.4
6.7
0


*/