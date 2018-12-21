#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

void handleEvents(stack <char>* st, map<char, map<char> >* graph, vector<char>* events, char cur)
{
    if ((*graph)[cur].empty()) {
        st->push(cur);
        return;
    }

    
}

int main()
{
    ifstream f("input.txt");
    string line, word;

    int actionIdx, prereqIdx, i;
    char action = 7, prereq = 1, step; //this only works because of pre-knowledge of the file format
    map<char, map<char> > prereqs, unlocks;
    vector<char> events;
    queue <char> q;

    if (f.is_open()) {
        i=0;
        while(getline(f, line)) {
            stringstream words(line);
            while(getline(words, word, ' ')) {
                if (i == actionIdx) action = word[0];
                if (i == prereqIdx) prereq = word[0];
                i++;
            }
            unlocks[prereq].insert(action);
            prereqs[action].insert(prereq);
            if (prereqs[action].size() == 0) step = prereq;
        }
    }
    stack<char> st;
    handleEvents(&st, &unlocks, &events);
}