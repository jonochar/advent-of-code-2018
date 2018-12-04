#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 

using namespace std;

int main()
{
    int count = 0;
    string line;
    int number = 0;
    ifstream inputFile("input.txt");
    if (inputFile.is_open()) {
        while(getline(inputFile, line)) {
            stringstream n(line);
            n >> number; 
            count += number;
        }
        inputFile.close();
    }

    cout << "Sum = " << count << endl;
}
