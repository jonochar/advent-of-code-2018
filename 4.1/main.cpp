#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <boost/algorithm/string.hpp>

using namespace std;

void parseAndSortFile(string fname);

int main()
{
    parseAndSortFile("input.txt");
}

void parseAndSortFile(string fname)
{
    map<string, int> sorted_events;
    char ch;
    int event;
    int count = 0;
    string status_text, line, timestamp;
    vector<string> v;
    ifstream f(fname);
    if (f.is_open()) {
        try {
            while (getline(f, line)) {
                count++;
                boost::split(v, line, boost::is_any_of("[- :]#"));
                int i = 1;
                timestamp = "";
                event = 0;
                for (auto it = v.begin()+2; it != v.end(); it++) {
                    if (i < 5) {
                        timestamp += *it;
                    } else {
                        if (*it == "falls") {
                            event = -1;
                        } else if (*it == "wakes") {
                            event = -2;
                        } else if (*it == "Guard") {
                            it += 2;    // there's a null because of the #
                            stringstream ss(*it);
                            ss >> event;
                        }
                    }
                    cout << *it;
                    i++;
                }
                cout << "\n";
                sorted_events[timestamp] = event;
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

    cout << "This many loops: " << count << endl;
}