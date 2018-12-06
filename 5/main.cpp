#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> 

using namespace std;

struct claim_t {
    int id;
    int left_edge;
    int top_edge;
    int width;
    int height;
};


claim_t parseLine(string line)
{
    claim_t claim;

    for (auto ch = line.begin(); ch != line.end(); ch++) {
        if (*ch == '#') {
            string id_string;
            while (*ch != ' ') {
                id_string += *ch;
                ch++;
            }
            claim.id = string_to_int(id_string);
        } else if (*ch == '@') {
            string x_string, y_string;
            while (*ch !=',') {
                x_string += *ch;
                ch++;
            }
            claim.left_edge = string_to_int(x_string);
            while (*ch != ':') {
                y_string += *ch;
                ch++;
            }
            claim.top_edge = string_to_int(y_string);
            ch++;
            string width, height;
            while(*ch != 'x') {
                width += *ch;
                ch++;
            }
            claim.width = string_to_int(width);
            while (*ch != '\n') {
                height += *ch;
                ch++;
            }
            claim.height = string_to_int(height);
        }
    }

    return claim;
}

void populateFabric(vector< vector< vector<int> > >* fabric, claim_t claim)
{
    int x0 = claim.left_edge-1;
    int y0 = claim.top_edge-1;

    for (int y=0; y < claim.height; y++) {
        for (int x = 0; x < claim.width; x++) {
            (*fabric)[x0 + x][y0 + y].push_back(claim.id);
        }
    }
}

void resizeFabric(vector< vector< vector<int> > >* fabric, claim_t claim)
{
    int cur_w = fabric->size();
    int cur_h = (fabric->front()).size();
    int req_w = (claim.left_edge-1) + claim.width; 
    int req_h = (claim.top_edge-1) + claim.height;
    if (req_w > cur_w) {
        fabric->resize(req_w);
        cur_w = req_w;
    }

    if (req_h > cur_h) {
        for (int i=0; i<cur_w; i++) {
            auto x = fabric->begin();
            x->resize(req_h);
        }
    }
}

int string_to_int(string line)
{
    int number = 0;
    stringstream n(line);
    n >> number;
    return number;
}

int main()
{
    claim_t claim;
    vector< vector< vector<int> > > fabric;
    ifstream f("input.txt");
    string line;

    if (f.is_open()) {
        try {
            while (getline(f, line)) {
                claim = parseLine(line);
                resizeFabric(&fabric, claim);
                populateFabric(&fabric, claim);
            }
        } catch (int e) {
            f.close();
            cout << "\n\nError Error Error: \n\n";
            throw e;
        }
        f.close();
    }
    int area = 0;
    int cur_w = fabric.size();
    int cur_h = (fabric.front()).size();
    for (int x=0; x<cur_w; x++) {
        for (int y=0; y<cur_h; y++) {
            if (fabric[x][y].size() > 1) {
                area++;
            }
        }
    }

    cout << "\nShared Area: " << area << endl;
}
