#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>
#include <initializer_list>
#include <chrono>
#include <thread>
#ifdef _WIN32
#include <conio.h>
#endif

using namespace std;

// --- Declarations ---

struct Shape
{
    int fret[6]{};
    int fing[6]{};
    Shape()
    {
        for (int i = 0; i < 6; ++i)
        {
            fret[i] = 0;
            fing[i] = 0;
        }
    }
};

class Chord
{
public:
    string root, qual;
    Shape shape;
    Chord(string r, string q) : root(r), qual(q) {}
    set<int> pcs() const;
};

vector<Chord> lib();

void printDiagVertical(const Chord &c);
void printNoteLocations(const string &note);
void wait_with_pause(int ms_per_chord);
extern const vector<string> NOTE;
int pcOf(string raw);

struct Sym
{
    string root;
    string qual;
};
bool parse(const string &t, Sym &o);

// --- Main ---

int main()
{
    auto library = lib();
    cout << "Enter notes OR chord progression (e.g.  C Am F G E7)\n> ";
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<string> tokens;
    string tok;
    while (ss >> tok)
    {
        tokens.push_back(tok);
    }
    if (tokens.empty())
    {
        cerr << "No input provided.\n";
        return 0;
    }

    // If exactly one token is entered, let the user choose the viewing mode.
    if (tokens.size() == 1)
    {
        cout << "You entered a single token: " << tokens[0] << "\n";
        cout << "Enter 1 for chord diagram, 2 for note locations: ";
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            Sym parsed;
            if (parse(tokens[0], parsed))
            {
                auto it = find_if(library.begin(), library.end(), [&](const Chord &c)
                                  { return c.root == parsed.root && c.qual == parsed.qual; });
                if (it != library.end())
                    printDiagVertical(*it);
                else
                {
                    Chord tmp{parsed.root, parsed.qual};
                    cout << "\n(no diagram) " << parsed.root << parsed.qual << " contains: ";
                    for (int p : tmp.pcs())
                        cout << NOTE[p] << " ";
                    cout << "\n";
                }
            }
            else
            {
                int p = pcOf(tokens[0]);
                if (p != -1)
                    printNoteLocations(tokens[0]);
                else
                    cerr << "Invalid token.\n";
            }
        }
        else if (choice == 2)
        {
            printNoteLocations(tokens[0]);
        }
        else
        {
            cerr << "Invalid choice.\n";
        }
        return 0;
    }

    // For multiple tokens, use chord progression mode (if any token parses as a chord symbol),
    // otherwise use melody-note mode.
    vector<Sym> prog;
    set<int> melody;
    for (auto &t : tokens)
    {
        Sym s;
        if (parse(t, s))
            prog.push_back(s);
        else
        {
            int p = pcOf(t);
            if (p != -1)
                melody.insert(p);
            else
                cerr << "?? '" << t << "' ignored\n";
        }
    }
    if (!prog.empty())
    {
        // Ask for time signature and tempo
        int beats_per_measure = 4, seconds_per_beat = 1;
        cout << "Enter beats per measure (default 4): ";
        string bpm_in;
        getline(cin >> ws, bpm_in);
        if (!bpm_in.empty())
            beats_per_measure = stoi(bpm_in);
        cout << "Enter seconds per beat (default 1): ";
        string spb_in;
        getline(cin >> ws, spb_in);
        if (!spb_in.empty())
            seconds_per_beat = stoi(spb_in);
        int ms_per_chord = beats_per_measure * seconds_per_beat * 1000;

        cout << "Chord progression will play. Press ESC to pause, 'p' to resume.\n";
        for (const auto &s : prog)
        {
            auto it = find_if(library.begin(), library.end(), [&](const Chord &c)
                              { return c.root == s.root && c.qual == s.qual; });
            if (it != library.end())
                printDiagVertical(*it);
            else
            {
                Chord tmp{s.root, s.qual};
                cout << "\n(no diagram) " << s.root << s.qual << " contains: ";
                for (int p : tmp.pcs())
                    cout << NOTE[p] << " ";
                cout << "\n";
            }
            wait_with_pause(ms_per_chord);
        }
        return 0;
    }
    if (melody.empty())
    {
        cerr << "No valid notes.\n";
        return 0;
    }
    // Melody-note mode: suggest chords that contain all the entered notes.
    vector<Chord> match;
    for (const Chord &c : library)
        if (includes(c.pcs().begin(), c.pcs().end(), melody.begin(), melody.end()))
            match.push_back(c);
    if (match.empty())
    {
        cout << "Nothing in the library fits all those notes.\n";
        return 0;
    }
    for (const Chord &c : match)
        printDiagVertical(c);
    return 0;
}

// --- Implementations ---

const vector<string> NOTE = {"C", "C#", "D", "D#", "E", "F",
                             "F#", "G", "G#", "A", "A#", "B"};

int pcOf(string raw)
{
    for (char &c : raw)
        c = toupper(c);
    if (raw == "B#")
        raw = "C";
    if (raw == "E#")
        raw = "F";
    static const vector<string> names = {"C", "C#", "D", "D#", "E", "F",
                                         "F#", "G", "G#", "A", "A#", "B"};
    for (int i = 0; i < 12; ++i)
        if (raw == names[i])
            return i;
    return -1;
}

bool parse(const string &t, Sym &o)
{
    if (t.empty())
        return false;
    int i = 0;
    char L = tolower(t[0]);
    if (L < 'a' || L > 'g')
        return false;
    string root;
    root += toupper(t[i++]);
    if (i < t.size() && (t[i] == '#' || t[i] == 'b'))
        root += t[i++];
    if (root == "B#")
        root = "C";
    if (root == "E#")
        root = "F";
    string tail;
    while (i < t.size())
        tail += t[i++];
    string q;
    if (tail.empty() || tail == "maj")
        q = "maj";
    else if (tail == "m" || tail == "min")
        q = "min";
    else
        q = tail;
    o = {root, q};
    return true;
}

set<int> Chord::pcs() const
{
    static map<string, vector<int>> iv{
        {"maj", {0, 4, 7}},
        {"min", {0, 3, 7}},
        {"7", {0, 4, 7, 10}},
        {"m7", {0, 3, 7, 10}}};
    auto it = iv.find(qual);
    if (it == iv.end())
        return {};
    const auto &v = it->second;
    int r = pcOf(root);
    set<int> out;
    for (int i : v)
        out.insert((r + i) % 12);
    return out;
}

vector<Chord> lib()
{
    auto S = [](string r, string q, initializer_list<int> fr, initializer_list<int> fi) -> Chord
    {
        Chord c{r, q};
        int k = 0;
        for (int v : fr)
            c.shape.fret[k++] = v;
        k = 0;
        for (int v : fi)
            c.shape.fing[k++] = v;
        return c;
    };

    vector<Chord> v;
    v.push_back(S("C", "maj", {-1, 3, 2, 0, 1, 0}, {0, 3, 2, 0, 1, 0}));
    v.push_back(S("D", "maj", {-1, -1, 0, 2, 3, 2}, {0, 0, 0, 1, 3, 2}));
    v.push_back(S("E", "maj", {0, 2, 2, 1, 0, 0}, {0, 2, 3, 1, 0, 0}));
    v.push_back(S("F", "maj", {-1, -1, 3, 2, 1, 1}, {0, 0, 3, 2, 1, 1}));
    v.push_back(S("G", "maj", {3, 2, 0, 0, 3, 3}, {2, 1, 0, 0, 3, 4}));
    v.push_back(S("A", "maj", {-1, 0, 2, 2, 2, 0}, {0, 0, 2, 3, 4, 0}));
    v.push_back(S("B", "maj", {-1, 2, 4, 4, 4, 2}, {0, 1, 3, 4, 2, 1}));
    v.push_back(S("A", "min", {-1, 0, 2, 2, 1, 0}, {0, 0, 2, 3, 1, 0}));
    v.push_back(S("E", "min", {0, 2, 2, 0, 0, 0}, {0, 2, 3, 0, 0, 0}));
    v.push_back(S("D", "min", {-1, -1, 0, 2, 3, 1}, {0, 0, 0, 2, 3, 1}));
    v.push_back(S("E", "7", {0, 2, 0, 1, 0, 0}, {0, 2, 0, 1, 0, 0}));
    v.push_back(S("A", "7", {-1, 0, 2, 0, 2, 0}, {0, 0, 2, 0, 3, 0}));
    v.push_back(S("D", "7", {-1, -1, 0, 2, 1, 2}, {0, 0, 0, 2, 1, 3}));
    v.push_back(S("G", "7", {3, 2, 0, 0, 0, 1}, {2, 1, 0, 0, 0, 3}));
    v.push_back(S("C", "7", {-1, 3, 2, 3, 1, 0}, {0, 3, 2, 4, 1, 0}));
    return v;
}

void printDiagVertical(const Chord &c)
{
    static const char *STRINGS[6] = {"E", "A", "D", "G", "B", "e"}; // low→high

    // Determine highest fret to display (always at least 3 frets).
    int maxFret = 0;
    for (int f : c.shape.fret)
        maxFret = max(maxFret, f);
    int rows = max(3, maxFret);

    // Print chord header.
    cout << "\n► " << c.root << (c.qual == "maj" ? "" : (c.qual == "min" ? "m" : c.qual)) << "\n";

    // Print string names along the top.
    cout << "    ";
    for (int s = 0; s < 6; ++s)
        cout << setw(3) << STRINGS[s];
    cout << "\n    " << string(6 * 3, '-') << "\n";

    // Print each fret row with the fret number on the left.
    for (int f = 0; f <= rows; ++f)
    {
        cout << setw(2) << f << " ";
        for (int s = 0; s < 6; ++s)
        {
            char marker = ' '; // Default is blank.
            if (f == 0)
            { // Nut: show muted (x) or open (o), or blank if fretted higher.
                marker = (c.shape.fret[s] == -1) ? 'x' : (c.shape.fret[s] == 0) ? 'o'
                                                                                : ' ';
            }
            else if (c.shape.fret[s] == f)
            { // Finger placement at this fret.
                int fing = c.shape.fing[s];
                marker = (fing >= 1 && fing <= 4) ? char('0' + fing) : '*';
            }
            else
            {
                marker = '|';
            }
            cout << setw(3) << marker;
        }
        cout << "\n";
    }
}

void printNoteLocations(const string &note)
{
    static const string STRINGS[6] = {"E", "A", "D", "G", "B", "e"};
    static const vector<int> OPEN_NOTES = {pcOf("E"), pcOf("A"), pcOf("D"), pcOf("G"), pcOf("B"), pcOf("E")};

    int targetPC = pcOf(note);
    if (targetPC == -1)
    {
        cout << "Invalid note: " << note << "\n";
        return;
    }
    cout << "\nNote locations for " << note << ":\n";
    cout << "Fret |  E  A  D  G  B  e\n";
    cout << "------------------------\n";
    for (int fret = 0; fret <= 12; ++fret)
    {
        cout << setw(4) << fret << " |";
        for (int s = 0; s < 6; s++)
        {
            int stringPC = (OPEN_NOTES[s] + fret) % 12;
            cout << setw(3) << ((stringPC == targetPC) ? "●" : "-");
        }
        cout << "\n";
    }
}

void wait_with_pause(int ms_per_chord)
{
#ifdef _WIN32
    int elapsed = 0;
    const int step = 50; // ms
    bool paused = false;
    while (elapsed < ms_per_chord)
    {
        if (_kbhit())
        {
            int ch = _getch();
            if (ch == 27)
            { // ESC
                std::cout << "\nPaused. Press 'p' to resume...\n";
                paused = true;
                while (true)
                {
                    if (_kbhit())
                    {
                        int ch2 = _getch();
                        if (ch2 == 'p' || ch2 == 'P')
                        {
                            std::cout << "Resuming...\n";
                            paused = false;
                            break;
                        }
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
            }
        }
        if (!paused)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(step));
            elapsed += step;
        }
    }
#else
    // On non-Windows, just sleep (no pause support)
    std::this_thread::sleep_for(std::chrono::milliseconds(ms_per_chord));
#endif
}