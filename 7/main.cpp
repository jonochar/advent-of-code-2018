#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
    ifstream f("input.txt");
    string line, word;

    int actionIdx, prereqIdx, i;
    char action = 7, prereq = 1, step; //this only works because of pre-knowledge of the file format
    map<char, map<char, int> > prereqs, unlocks;
    vector<char> events;

    if (f.is_open()) {
        i=0;
        while(getline(f, line)) {
            stringstream words(line);
            while(getline(words, word, ' ')) {
                if (i == actionIdx) action = word[0];
                if (i == prereqIdx) prereq = word[0];
                i++;
            }
            unlocks[prereq][action]++;
            prereqs[action][prereq]++;
            if (prereqs[action].size() == 0) step = prereq;
        }
    }

    while (!unlocks.empty()) {
        events.push_back(step);
    }
}