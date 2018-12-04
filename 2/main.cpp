#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
#include <map>

using namespace std;

int string_to_int(string);

int main()
{
    map<int,int> found;    
    int sum = 0;
    int number = 0;
    string line;
    ifstream inputFile("input.txt");
    
    if (inputFile.is_open()) {
        while(1) {
            if (getline(inputFile, line)) {
                number = string_to_int(line);
                sum += number;
                if (found.find(sum) == found.end()) {
                    found[sum] = 1;
                } else {
                    found[sum] = 2;
                    break;
                }
            } else {
                inputFile.clear();
                inputFile.seekg(0, ios::beg);
            }
        }
        inputFile.close();
    } else {
        cout << "File read error" << endl;
    }

    cout << "Repeated number: " << sum << endl;
}

int string_to_int(string line)
{
    int number = 0;
    stringstream n(line);
    n >> number;
    return number;
}