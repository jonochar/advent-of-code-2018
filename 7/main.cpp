#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <set>

using namespace std;

void handleEvents(stack <char>* st, map<char, set<char> >* graph, map<char, int>* visited, char cur)
{
    if ((*graph)[cur].empty()) {
        return;
    }

    if ((*visited)[cur] > 0) {
        return;
    }

    for (auto it = (*graph)[cur].end(); it != (*graph)[cur].begin(); it--) {
        handleEvents(st, graph, visited, *it);
    }
    
    (*visited)[cur] = 1;
    st->push(cur);
}

int main()
{
    ifstream f("input.txt");
    string line, word;

    int actionIdx = 7, prereqIdx = 1, i;
    char action, prereq, start; //this only works because of pre-knowledge of the file format
    map<char, set<char> > graph, igraph;
    map<char, int> visited;
    vector<char> events;
    queue <char> q;

    if (f.is_open()) {
        while(getline(f, line)) {
            if (line == "\n") continue;
            stringstream words(line);
            i=0;
            while(getline(words, word, ' ')) {
                if (i == actionIdx) {
                    action = word[0];
                } else if (i == prereqIdx) {
                    prereq = word[0];
                } 
                i++;
            }
            graph[prereq].insert(action);
            igraph[action].insert(prereq);
            if (igraph[action].size() == 0) start = action;
        }
    }
    stack<char> st;
    handleEvents(&st, &graph, &visited, start);
    
    cout << "Graph Size: " << graph.size() << endl;
    for (auto it = graph.begin(); it != graph.end(); it++) {
        cout << "Node: " << it->first << " has " << it->second.size() << "elements\n";
    }

    cout << "Order:\n";
    while (!st.empty()) {
        cout << st.top();
        st.pop();
    }
    cout << endl;
}