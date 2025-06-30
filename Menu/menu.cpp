#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
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
                try
                {
                    if (addProgram())
                    {
                        cout << "Program has been added\n";
                    }
                }
                catch (const string &x)
                {
                    cout << x;
                }
            }
            else if (nextChoice == 2)
            {
                try
                {
                    if (deleteProgram())
                    {
                        cout << "Program has been deleted\n";
                    }
                }
                catch (const string &x)
                {
                    cout << x;
                }
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
    bool nameExists = false;
    bool pathExists = false;
    bool spacesInNewPath = false;
    string newName, newPath, line, projectName, projectPath;
    vector<pair<string, string>> projects; // reading current file content into a vector of pairs: name, path
    ifstream inFile("projects.txt");

    // storing the current programs
    while (getline(inFile, line))
    {
        if (line.find("name:") == 0)
        {
            projectName = line.substr(5);
            getline(inFile, line);
            if (line.find("path:") == 0)
            {
                projectPath = line.substr(5);
                projects.push_back(make_pair(projectName, projectPath));
            }
        }
        if (line == "END OF FILE")
        {
            break;
        }
    }
    inFile.close();

    // Adding new program details
    while (!success)
    {
        cout << "Enter the name of the new program (or 0 to abort): ";
        getline(cin, newName);
        if (newName == "0")
        {
            throw string("Add Program Aborted\n");
        }
        for (const pair<string, string> &project : projects)
        {
            if (project.first == newName)
            {
                cout << "Name already exists. Please try again.\n";
                nameExists = true;
                break;
                // breaks out of the name checking so we can restart the while loop
            }
        }
        if (nameExists)
        {
            continue;
            // if the name exists, restart the while loop from the beginning
        }

        cout << "Enter the name of the new program (or 0 to abort): ";
        getline(cin, newPath);
        if (newPath == "0")
        {
            throw string("Add Program Aborted\n");
        }
        for (const pair<string, string> &project : projects)
        {
            if (project.second == newPath)
            {
                cout << "Path already exists. Please try again.\n";
                pathExists = true;
                break;
                // same logic as with name
            }
        }
        if (pathExists)
        {
            continue;
            // same logic as with name
        }

        // if we made it here, we have a valid name and path to add
        success = true;
    }

    // only if the path we want to add has any spaces will we need to wrap it in quotes
    if (newPath.find(' ') != string::npos)
    {
        newPath = "\"" + newPath + "\"";
    }

    projects.push_back(make_pair(newName, newPath));

    // writing updated content back to file
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

bool deleteProgram()
{
    bool success = false;
    string name;
    vector<pair<string, string>> projects;

    // Reading current projects into a vector
    ifstream file("projects.txt");
    string line;
    while (getline(file, line))
    {
        if (line.find("name:") == 0)
        {
            string projectName = line.substr(5);
            getline(file, line);
            if (line.find("path:") == 0)
            {
                string projectPath = line.substr(5);
                projects.push_back(make_pair(projectName, projectPath));
            }
        }
        if (line == "END OF FILE")
        {
            break;
        }
    }
    file.close();

    // Attempting to delete a program
    while (true)
    {
        cout << "Enter the name of the program you want to delete (or 0 to abort): ";
        getline(cin, name);
        if (name == "0")
        {
            throw string("Delete Program Aborted\n");
        }

        // could just use auto instead since this looks like cancer
        vector<pair<string, string>>::iterator projectToDelete = find_if(projects.begin(), projects.end(), [&](const pair<string, string> &project)
                                                                         { return project.first == name; });
        // if return project.first == name; ever returns true, the loop ends
        // and our variable called 'projectToDelete' will be the element in the vector that we want to delete

        // end is a null so if our variable is null that means we reached the end without finding the name
        if (projectToDelete == projects.end())
        {
            cout << "Program not found. Please try again.\n";
            continue;
        }
        else
        {
            cout << "Deleting name: " << projectToDelete->first << endl;
            cout << "Deleting path: " << projectToDelete->second << endl;
            projects.erase(projectToDelete);
            success = true;
            break;
        }
    }

    // Writing updated content back to file
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