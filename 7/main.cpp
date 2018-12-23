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

void handleEvents(stack <char>* st, map<char, set<char> >* graph, map<char, int>* visited, char cur, priority_queue<char>* buf)
{
    cout << cur;
    if ((*visited)[cur] > 0) {
        return;
    }

    if ((*graph)[cur].empty()) {    // Last node
        (*visited)[cur] = 1;
        st->push(cur);
        return;
    }

    for (auto it = (*graph)[cur].rbegin(); it != (*graph)[cur].rend(); it++) {
        if (!buf->empty() && buf->top() > *it) {
            char qFront = buf->top();
            buf->pop();
            handleEvents(st, graph, visited, buf->top(), buf);
        }
        handleEvents(st, graph, visited, *it, buf);
    }
    
    (*visited)[cur] = 1;
    st->push(cur);
}

int main()
{
    ifstream f("input.txt");
    string line, word;

    int actionIdx = 7, prereqIdx = 1, i;
    char action, prereq, start = 'a';
    map<char, set<char> > graph, igraph;
    map<char, int> visited;
    vector<char> events;
    queue <char> q;
    set<char> actions, prereqs;
    priority_queue<char> buf;

    if (f.is_open()) {
        while(getline(f, line)) {
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
            if ((int)action > 64 && (int)action < 91 && (int)action > 64 && (int)action < 91) {
                graph[prereq].insert(action);
                actions.insert(action);
                prereqs.insert(prereq);
                visited[action] = 0;
                visited[prereq] = 0;
            }
        }
    }

    set<char> starters;
    cout << "Start Nodes: ";
    for (auto it=prereqs.begin(); it!= prereqs.end(); it++) {
        if (actions.find(*it) == actions.end()) {
            cout << *it;
            starters.insert(*it);
            buf.push(*it);
        }
    }
    cout << endl;
    
    set<char> enders;
    cout << "End Nodes: ";
    for (auto it=actions.begin(); it!= actions.end(); it++) {
        if (prereqs.find(*it) == prereqs.end()){
            cout << *it;
            enders.insert(*it);
        } 
    }
    cout << endl;

    start = *(starters.begin());

    for (auto it = enders.begin(); it != enders.end(); it++) {
        graph[*it];
    }

    stack<char> st;

    cout << "Graph:\n";
    for (auto it = graph.begin(); it != graph.end(); it++) {
        cout << it->first << ":";
        for (auto id = it->second.begin(); id != it->second.end(); id++) {
            cout << *id;
        }
        cout << endl;
    }

    cout << "Entering Recursion:\n";
    handleEvents(&st, &graph, &visited, start, &buf);

    cout << "Visited:\n";
    for (auto it = visited.begin(); it != visited.end(); it++) {
        cout << it->first << ":" <<it->second << endl;
    }

    cout << "\nOrder:\n";
    while (!st.empty()) {
        cout << st.top();
        st.pop();
    }
    cout << endl;
}