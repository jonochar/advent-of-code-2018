#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <iomanip>
#include <ctime>

using namespace std;

const int WAKES = -1;
const int SLEEPS = -2;

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
        while (getline(f, line)) {
            count++;
            boost::split(v, line, boost::is_any_of("[- :]#"));
            int i = 1;
            timestamp = "";
            event = 0;
            for (auto it = v.begin()+2; it != v.end(); it++) {
                if (i < 5) {
                    timestamp += *it;
                    if (i<4) timestamp += ":";
                } else {
                    if (*it == "falls") {
                        event = SLEEPS;
                    } else if (*it == "wakes") {
                        event = WAKES;
                    } else if (*it == "Guard") {
                        it += 2;    // there's a null because of the #
                        stringstream ss(*it);
                        ss >> event;
                    }
                }
                i++;
            }
            sorted_events[timestamp] = event;
        }
        f.close();
    }
    string timefmt = "%m:%d:%H:%M";
    struct tm last_event, cur_event;
    double slept = 0;
    int cur_guard, eval;
    map<int, double> asleep_total;
    map<int, vector<int > > hist;

    for (auto it = sorted_events.begin(); it != sorted_events.end(); it++) {
        timestamp = it->first;
        istringstream ss(timestamp);
        ss >> get_time(&cur_event, timefmt.c_str());
        eval = it->second;
        if (eval > 0) {
            cur_guard = eval;
            if (hist[cur_guard].size() < 60) {
                vector<int> minutes(60, 0);
                hist[cur_guard] = minutes;
            }
        } else if (eval == SLEEPS) {
            last_event = cur_event;
        } else if (eval == WAKES) {
            time_t cur_time = mktime(&cur_event);
            time_t last_time = mktime(&last_event);
            asleep_total[cur_guard] += difftime(cur_time, last_time);
            for (int i = last_event.tm_min; i < cur_event.tm_min; i++) {
                hist[cur_guard][i]++;
            }
        } else {
            cout << "\nerror\n";
        }
    }

    double max = -1;
    int guard = -1;
    for (auto it = asleep_total.begin(); it != asleep_total.end(); it++) {
        if (it->second > max) {
            guard = it->first;
            max = it->second;
        }
    }

    int freq_min = -1;
    int freq_val = -1;
    int freq_guard = -1;

    for (auto it = hist.begin(); it != hist.end(); it++) {
        int key = it->first;
        cout << key << " < ";
        for (int i=0; i<60; i++) {
            cout << hist[key][i] << " ";
            if (hist[key][i] > freq_val) {
                freq_val = hist[key][i];
                freq_guard = key;
                freq_min = i;
            }
        }
        cout << " > " << asleep_total[key] << endl;
    }

    int best_min = -1;
    int minute_val = -1;
    cout << "Best guard: ";
    cout << guard << " < ";
    for (int i=0; i<60; i++) {
        cout << hist[guard][i] << " ";
        if (hist[guard][i] > minute_val) {
            minute_val = hist[guard][i];
            best_min = i;
        }
    }
    cout << " > " << asleep_total[guard] << endl;

    max = max/60;
    cout << "Guard: " << guard << " sleeps the most at: " << max << " minutes\n";
    cout << "This many loops: " << count << endl;
    cout << "Best minute = " << best_min << endl;
    cout << "guard*min: " << best_min * guard << endl;

    cout << "Guard: " << freq_guard << " was most frequent at " << freq_min << ". g*m = " << freq_guard * freq_min << endl;
}