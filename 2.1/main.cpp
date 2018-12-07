#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
    string line;
    ifstream f("input.txt");
    int all2 = 0;
    int all3 = 0;

    if (f.is_open()) {
        while (getline(f, line)) {
            auto it = line.begin();
            map<char,int> hist;   

            while (it != line.end()) {
                if (hist.find(*it) == hist.end()) {
                    hist[*it] = 1;
                } else {
                    hist[*it]++;
                }
                it++;
            }

            int flags = 0;

            for (auto i = hist.begin(); i != hist.end(); i++) { 
                if (i->second == 2) {
                    flags |= 1;
                } else if (i->second == 3) {
                    flags |= 2;
                }
            }
            if ((flags & 1) > 0) all2++;
            if ((flags & 2) > 0) all3++;
            cout << line << ": " << flags << ": " << all2 << "*" << all3 << endl;
        }
        f.close();
    }
    cout << "\nOnly 2: " << all2 << endl;
    cout << "Only 3: " << all3 << endl;
    cout << "Checksum: " << all2 * all3 << endl;
}