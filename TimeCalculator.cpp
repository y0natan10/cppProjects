#include <iostream>
#include <windows.h>
using namespace std;
class Time
{

public:
    Time() : days(0), hours(0), minutes(0), seconds(0) {};
    Time(Time &oldTime);
    Time(int _days, int _hours, int _minutes, int _seconds) : days(_days), hours(_hours), minutes(_minutes), seconds(_seconds) {};
    Time operator+(const Time &rhs);
    friend istream &operator>>(istream &input, Time &rhs);
    friend ostream &operator<<(ostream &output, Time &rhs);

private:
    int days;
    int hours;
    int minutes;
    int seconds;
};

int main()
{
    Time currentTime;
    Time addedTime;
    cout << "for the current time:\n";
    cin >> currentTime;
    cout << "for the added time:\n";
    cin >> addedTime;
    Time newTime(currentTime + addedTime);
    cout << newTime;
    cout << "\nexiting in: \n";
    // i love doing this countdown stuff
    for (int i = 5; i != 0; --i)
    {
        cout << i << endl;
        Sleep(1000);
    }

    return 0;
}

Time::Time(Time &oldTime)
{
    hours = oldTime.hours;
    minutes = oldTime.minutes;
    seconds = oldTime.seconds;
}

Time Time::operator+(const Time &rhs)
{
    int totalSeconds = this->seconds + rhs.seconds;
    int totalMinutes = this->minutes + rhs.minutes;
    int totalHours = this->hours + rhs.hours;
    int totalDays = 0;
    while (totalSeconds > 59)
    {
        ++totalMinutes;
        totalSeconds -= 60;
    }
    while (totalMinutes > 59)
    {
        ++totalHours;
        totalMinutes -= 60;
    }
    while (totalHours > 23)
    {
        ++totalDays;
        totalHours -= 24;
    }

    return Time(totalDays, totalHours, totalMinutes, totalSeconds);
}

istream &operator>>(istream &input, Time &rhs)
{
    cout << "input hours: ";
    input >> rhs.hours;
    cout << "input minutes: ";
    input >> rhs.minutes;
    cout << "input seconds: ";
    input >> rhs.seconds;

    return input;
}

ostream &operator<<(ostream &output, Time &rhs)
{
    if (rhs.days == 1)
    {
        output << "1 day later\n";
    }
    if (rhs.days > 1)
    {
        output << rhs.days << " days later\n";
    }

    output << "The time will be ";
    output << ((rhs.hours < 10) ? "0" : "") << rhs.hours << ":";
    output << ((rhs.minutes < 10) ? "0" : "") << rhs.minutes << ":";
    output << ((rhs.seconds < 10) ? "0" : "") << rhs.seconds;
    return output;
}
