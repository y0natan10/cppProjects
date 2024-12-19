#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

void printProjects();
bool addProgram();
bool deleteProgram();
queue<pair<string, string>> loadProjects();
pair<string, string> getProjectByChoice(int choice, queue<pair<string, string>> projects);

int main()
{
    int choice;
    int nextChoice;
    queue<pair<string, string>> projects;

    do
    {
        cout << "Menu:\n";
        printProjects();
        cout << "Or enter 0 to quit, add a new program, delete an old program\n";
        cout << "Enter your choice: ";

        cin >> choice;

        if (choice == 0)
        {
            cout << "Enter 0 to quit, 1 to add a new program, or 2 to delete a program: ";
            cin >> nextChoice;
            cin.ignore(); // Clear the newline character left in the buffer
            if (nextChoice == 0)
            {
                choice = 0;
                break;
            }
            else if (nextChoice == 1)
            {
                addProgram();
            }
            else if (nextChoice == 2)
            {
                deleteProgram();
            }
            else
            {
                cout << "invalid choice\n";
            }
        }
        else
        {
            projects = loadProjects();
            if (choice > 0 && (choice <= projects.size() + 1))
            {
                pair<string, string> project = getProjectByChoice(choice, projects);
                const string &filePath = project.second;
                system(filePath.c_str());
            }
            else
            {
                cout << "invalid choice\n";
            }
        }

    } while (choice != 0 || nextChoice != 0);

    Sleep(1000);
    return 0;
}

void printProjects()
{
    ifstream file("projects.txt");
    string line, name;
    int index = 1;
    while (getline(file, line))
    {
        if (line.find("name:") == 0)
        {
            name = line.substr(5);
            cout << index << ": " << name << endl;
            ++index;
            // Skip the next line because it's the path line
            getline(file, line);
        }
        if (line == "END OF FILE")
        {
            break;
        }
    }
    cout << endl;
    file.close();
}

bool addProgram()
{
    bool success = false;
    string name, path;
    // reading current file content into a vector
    ifstream inFile("projects.txt");
    vector<string> lines;
    string line;
    while (getline(inFile, line))
    {
        if (line == "END OF FILE")
        {
            break;
        }
        lines.push_back(line);
    }
    inFile.close();

    // Adding new program details
    cout << "Enter the name of the new program: ";
    getline(cin, name);
    cout << "Enter the path of the new program: ";
    getline(cin, path);
    if (name != "")
    {
        lines.push_back("name:" + name);          // Add name
        lines.push_back("path:\"" + path + "\""); // Add path with quotes for paths with spaces
        success = true;
    }
    lines.push_back("END OF FILE"); // Add end marker

    // writing updated content back to file
    ofstream outFile("projects.txt");
    for (const string &l : lines)
    {
        outFile << l << endl;
    }
    outFile.close();
    return success;
}

bool deleteProgram()
{
    bool success = false;
    string name;
    cout << "Enter the name of the program you want to delete: ";
    getline(cin, name);

    ifstream file("projects.txt");
    vector<pair<string, string>> projects;
    string line, projectName, projectPath;
    while (getline(file, line))
    {
        if (line.find("name:") == 0)
        {
            projectName = line.substr(5); // get project name
            getline(file, line);
            if (line.find("path:") == 0)
            {
                projectPath = line.substr(5); // get project path
                if (projectName != name)
                {
                    projects.push_back(make_pair(projectName, projectPath));
                }
                else
                {
                    cout << "Deleting name: " << projectName << endl;
                    cout << "Deleting path: " << projectPath << endl;
                    success = true;
                }
            }
        }
        if (line == "END OF FILE")
        {
            break;
        }
    }
    file.close();

    ofstream outFile("projects.txt");
    for (const pair<string, string> &project : projects)
    {
        outFile << "name:" << project.first << endl;
        outFile << "path:" << project.second << endl;
    }
    outFile << "END OF FILE" << endl;
    outFile.close();
    return success;
}

queue<pair<string, string>> loadProjects()
{
    queue<pair<string, string>> projects;
    ifstream file("projects.txt");
    string line, name, path;
    while (getline(file, line))
    {
        if (line.find("name:") == 0)
        {
            name = line.substr(5);       // .substr(5) skips to the 5th character of that line and takes everything after it
            getline(file, line);         // read the next line
            if (line.find("path:") == 0) // i know the next line will always be the path, but just in case
            {
                path = line.substr(5);                // Get the project path
                projects.push(make_pair(name, path)); // only push if we found both name and path
            }
        }
        if (line == "END OF FILE")
        {
            break;
        }
    }
    file.close();
    return projects;
}

pair<string, string> getProjectByChoice(int choice, queue<pair<string, string>> projects)
{
    pair<string, string> it = projects.front();
    for (int i = 1; i < choice; ++i)
    {
        projects.pop();
        it = projects.front();
    }
    // Enclose the path in double quotes
    it.second = "\"" + it.second + "\"";

    return it;
}
