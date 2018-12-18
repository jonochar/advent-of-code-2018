#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

void eval(vector<char>* list)
{
    if (list->size() < 2) return;
    if ((list->back() ^ 32) == (*list)[list->size()-2]) {
        list->pop_back();
        list->pop_back();
        eval(list);
    }
}

int main()
{
    ifstream inputFile("input.txt");
    vector<char> list;
    map<char, int> char_list;
    char c;
    int count=0;
    if (inputFile.is_open()) {
        while(inputFile.get(c)) {
            if (c == '\n') break;
            list.push_back(c);
            eval(&list);
            char_list[c] = 0;
            count++;
        }
    }

    inputFile.clear();
    inputFile.seekg(0, ios::beg);
    auto best = char_list.begin();
    for (auto it = char_list.begin(); it != char_list.end(); it++) {
        vector<char> temp;
        if (inputFile.is_open()) {
            while(inputFile.get(c)) {
                if (c == '\n') break;
                if (c == it->first || (c ^ 32) == it->first) continue;
                temp.push_back(c);
                eval(&temp);
            }
            inputFile.clear();
            inputFile.seekg(0, ios::beg);
        }
        it->second = temp.size();
        if (it->second < best->second) best = it;
    }

    cout << "Unoptimized Size: " << list.size() << "/" << count << endl;
    cout << "  Optimized Size: " << best->first << " resulting in size: " << best->second << endl;
}
