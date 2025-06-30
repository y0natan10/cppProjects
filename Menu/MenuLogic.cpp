// compile command for when things get rough
// g++ MenuApp.cpp MenuLogic.cpp MenuApp.res -o MenuApp.exe -mwindows
#include <windows.h>
#include "MenuLogic.h"
#include <fstream>
#include <shellapi.h>
#include <algorithm>

using namespace std;

// UTF-8 to UTF-16
static wstring s2ws(const string &str)
{
    if (str.empty())
    {
        return wstring();
    }
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.data(), (int)str.size(), NULL, 0);
    wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.data(), (int)str.size(), &wstr[0], size_needed);
    return wstr;
}

// UTF-16 to UTF-8
static string ws2s(const wstring &wstr)
{
    if (wstr.empty())
        return string();
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int)wstr.size(), NULL, 0, NULL, NULL);
    string str(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int)wstr.size(), &str[0], size_needed, NULL, NULL);
    return str;
}

vector<Project> loadProjects()
{
    vector<Project> projects;
    ifstream file("projects.txt");
    string line, name, path;
    while (getline(file, line))
    {
        if (line.find("name:") == 0)
        {
            name = line.substr(5);
            getline(file, line);
            if (line.find("path:") == 0)
            {
                path = line.substr(5);
                // Only add if both name and path are not empty
                if (!name.empty() && !path.empty())
                    projects.push_back(Project(s2ws(name), s2ws(path)));
            }
        }
        if (line == "END OF FILE")
            break;
    }

    // Sort projects alphabetically by name (case-insensitive)
    sort(projects.begin(), projects.end(), [](const Project &a, const Project &b)
         { return _wcsicmp(a.name.c_str(), b.name.c_str()) < 0; });

    return projects;
}

void saveProjects(const vector<Project> &projects)
{
    ofstream out("projects.txt");
    for (const Project &p : projects)
    {
        out << "name:" << ws2s(p.name) << "\n";
        out << "path:" << ws2s(p.path) << "\n\n";
    }
    out << "END OF FILE\n";
}

void launchProject(const wstring &path)
{
    ShellExecuteW(NULL, L"open", path.c_str(), NULL, NULL, SW_SHOWNORMAL);
}