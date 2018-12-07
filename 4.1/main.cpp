#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <

using namespace std;

void parseAndSortFile(string fname);

int main()
{
    parseAndSortFile("input.txt");
}

void parseAndSortFile(string fname)
{
    map<string, string> sorted_events;
    char ch;
    int year, month, day, hour, min;
    string status_text, line, idx;
    
    ifstream f(fname);
    if (f.is_open()) {
        try {
            while (getline(f, line)) {
                stringstream ss(line); 
                ss >> ch >> year >> ch >> month >> ch >> day >> ch >> hour >> ch >> min >> ch >> ch >> status_text;
                stringstream concat;
                sorted_events[idx] = status_text;
            }
        } catch (int e) {
            f.close();
            cout << "\n\nError Error Error: \n\n";
            throw e;
        }
        f.close();
    }

    for (auto it = sorted_events.begin(); it != sorted_events.end(); it++) {
        cout << it->first << ": " << it->second << endl;
    }
}