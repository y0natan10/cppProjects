#pragma once
#include <string>
#include <vector>

using namespace std;

class Project
{
public:
    wstring name;
    wstring path;

    Project() = default;
    Project(const wstring &n, const wstring &p) : name(n), path(p) {}
};

vector<Project> loadProjects();
void saveProjects(const vector<Project> &projects);
void launchProject(const wstring &path);