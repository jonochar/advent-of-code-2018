#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    string line;
    string word1;
    string word2;
    ifstream f("input.txt");
    vector<string> words;
    string::iterator ch;

    if (f.is_open()) {
        while (getline(f, line)) {
           words.push_back(line);
        }
        f.close();
    }

    sort(words.begin(), words.end());
    auto it = words.begin();
    int delta = 0;

    for (int i = 0; i <= words.size(); i++) {
        if (delta == 1) break;
        delta = 0;
        word1 = *it;
        it++;
        word2 = *it;
        auto ch1 = word1.begin();
        auto ch2 = word2.begin();
        
        while (ch1 != word1.end() || ch2 != word2.end()) {
            if ((*ch1) != (*ch2)) {
                delta++;
                ch = ch1;
            }
            ch1++;
            ch2++;
        }
    }

    cout 
    << "\n  " << word1 << endl 
    << "- " << word2 << endl 
    << "==============================\n";
    word1.erase(ch);
    cout << "  " << word1 << endl << endl; 
}