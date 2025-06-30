// if you're having trouble compiling the way i was
// try this
// (and make sure you're in the right directory so it can actually have a chance at working)
// put these lines into terminal
// windres MenuApp.rc -O coff -o MenuApp.res
// g++ MenuApp.cpp MenuLogic.cpp MenuApp.res -o MenuApp.exe -mwindows

#define UNICODE
#define _UNICODE
#include <windows.h>
#include <vector>
#include <string>
#include "MenuLogic.h"
#include <algorithm>

using namespace std;

#define IDC_LISTBOX 101
#define IDC_LAUNCH 102
#define IDC_ADD 103
#define IDC_DELETE 104
#define IDC_CLOSE 105
#define IDD_ADDPROJECT 1000

struct AddProjectData
{
    wchar_t name[256];
    wchar_t path[512];
};

// Refreshes the listbox with the current projects
void refreshListBox(HWND hListBox, const vector<Project> &projects)
{
    SendMessageW(hListBox, LB_RESETCONTENT, 0, 0);
    for (const auto &p : projects)
    {
        SendMessageW(hListBox, LB_ADDSTRING, 0, (LPARAM)p.name.c_str());
    }
}

// Dialog procedure for the "Add Project" dialog
INT_PTR CALLBACK AddProjectDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    AddProjectData *data;
    if (msg == WM_INITDIALOG)
    {
        SetWindowLongPtrW(hDlg, GWLP_USERDATA, lParam);
        return TRUE;
    }
    data = reinterpret_cast<AddProjectData *>(GetWindowLongPtrW(hDlg, GWLP_USERDATA));
    switch (msg)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            if (data)
            {
                GetDlgItemTextW(hDlg, 1001, data->name, 255);
                GetDlgItemTextW(hDlg, 1002, data->path, 511);
            }
            EndDialog(hDlg, IDOK);
            return TRUE;
        }
        else if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, IDCANCEL);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

// Main window procedure for the application
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static vector<Project> projects;
    static HWND hListBox, hLaunch, hAdd, hDelete, hClose;

    switch (msg)
    {
    case WM_CREATE:
        projects = loadProjects();
        hListBox = CreateWindowW(L"LISTBOX", NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL,
                                 10, 10, 300, 200, hwnd, (HMENU)IDC_LISTBOX, NULL, NULL);
        hLaunch = CreateWindowW(L"BUTTON", L"Launch", WS_CHILD | WS_VISIBLE,
                                320, 10, 80, 30, hwnd, (HMENU)IDC_LAUNCH, NULL, NULL);
        hAdd = CreateWindowW(L"BUTTON", L"Add", WS_CHILD | WS_VISIBLE,
                             320, 50, 80, 30, hwnd, (HMENU)IDC_ADD, NULL, NULL);
        hDelete = CreateWindowW(L"BUTTON", L"Delete", WS_CHILD | WS_VISIBLE,
                                320, 90, 80, 30, hwnd, (HMENU)IDC_DELETE, NULL, NULL);
        hClose = CreateWindowW(L"BUTTON", L"Close", WS_CHILD | WS_VISIBLE,
                               320, 130, 80, 30, hwnd, (HMENU)IDC_CLOSE, NULL, NULL);
        refreshListBox(hListBox, projects);
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_LAUNCH)
        {
            int sel = (int)SendMessageW(hListBox, LB_GETCURSEL, 0, 0);
            if (sel != LB_ERR && sel < (int)projects.size())
            {
                launchProject(projects[sel].path);
            }
        }
        else if (LOWORD(wParam) == IDC_ADD)
        {
            AddProjectData data = {};
            if (DialogBoxParamW(
                    NULL,
                    MAKEINTRESOURCEW(IDD_ADDPROJECT),
                    hwnd,
                    AddProjectDlgProc,
                    reinterpret_cast<LPARAM>(&data)) == IDOK)
            {
                projects.push_back(Project(data.name, data.path));
                // Sort alphabetically by name (case-insensitive)
                sort(projects.begin(), projects.end(), [](const Project &a, const Project &b)
                     { return _wcsicmp(a.name.c_str(), b.name.c_str()) < 0; });
                saveProjects(projects);
                refreshListBox(hListBox, projects);
            }
        }
        else if (LOWORD(wParam) == IDC_DELETE)
        {
            int sel = (int)SendMessageW(hListBox, LB_GETCURSEL, 0, 0);
            if (sel != LB_ERR && sel < (int)projects.size())
            {
                projects.erase(projects.begin() + sel);
                saveProjects(projects);
                refreshListBox(hListBox, projects);
            }
        }
        else if (LOWORD(wParam) == IDC_CLOSE)
        {
            PostMessageW(hwnd, WM_CLOSE, 0, 0);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// Entry point for the application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    WNDCLASSW wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MenuAppClass";
    RegisterClassW(&wc);

    HWND hwnd = CreateWindowW(L"MenuAppClass", L"Project Menu", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
                              CW_USEDEFAULT, CW_USEDEFAULT, 430, 260, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return 0;
}