#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> 
#include <typeinfo>

using namespace std;

struct claim_t {
    int id;
    int left_edge;
    int top_edge;
    int width;
    int height;
};

claim_t parseLine(string line);
void populateFabric(vector< vector< vector<int> > >* fabric, claim_t claim);
void resizeFabric(vector< vector< vector<int> > >* fabric, claim_t claim);
int string_to_int(string line);

int main()
{
    claim_t claim;
    int init = 1000;
    vector< vector< vector<int> > > fabric(init, vector<vector<int> > (init, vector<int>(0)));
    ifstream f("input.txt");
    string line;
    int claim_count = 0;

    if (f.is_open()) {
        try {
            while (getline(f, line)) {
                claim = parseLine(line);
                resizeFabric(&fabric, claim);
                populateFabric(&fabric, claim);
                claim_count++;
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
    int candidate = 0;
    vector<bool> claim_list(claim_count+1, true);

    for (int x=0; x<cur_w; x++) {
        for (int y=0; y<cur_h; y++) {
            if (fabric[x][y].size() > 1) {
                area++;
                for (auto id = fabric[x][y].begin(); id != fabric[x][y].end(); id++) {
                    claim_list[*id] = claim_list[*id] & false;
                }
            }
        }
    }

    cout << "\nGood claims: \n";
    for (int i=1; i<= claim_count; i++) {
        if (claim_list[i]) {
            cout << "id: " << i << endl;
        }
    }

    cout << "\nTotal Claims: " << claim_count << endl;
    cout << "Shared Area: " << area << endl;
    cout << "Total Area: " << cur_h * cur_w << endl;
}

claim_t parseLine(string line)
{
    cout << "parseLine: ";
    claim_t claim;
    auto ch = line.begin();
    string x_string, y_string, id_string, height, width;

    if (*ch == '#') ch++;

    while (*ch != ' ') {
        id_string += *ch;
        ch++;
    }
    claim.id = string_to_int(id_string);

    if (*ch == ' ') ch++;
    if (*ch == '@') ch++;

    while (*ch !=',') {
        x_string += *ch;
        ch++;
    }
    claim.left_edge = string_to_int(x_string);

    if (*ch ==',') ch++;

    while (*ch != ':') {
        y_string += *ch;
        ch++;
    }
    claim.top_edge = string_to_int(y_string);

    if (*ch == ':') ch++;
    if (*ch == ' ') ch++;

    while(*ch != 'x') {
        width += *ch;
        ch++;
    }
    claim.width = string_to_int(width);

    if (*ch == 'x') ch++;

    while (ch != line.end()) {
        height += *ch;
        ch++;
    }
    claim.height = string_to_int(height);

    cout 
    << claim.id << " "
    << claim.left_edge << " "
    << claim.top_edge << " "
    << claim.width << " "
    << claim.height << "/ \n";

    return claim;
}

void populateFabric(vector< vector< vector<int> > >* fabric, claim_t claim)
{
    // cout << "populateFabric\n";
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
    // cout << "resizeFabric ";
    int cur_w = fabric->size();
    int cur_h = 0;
    if (cur_w > 0) cur_h = (fabric->front()).size();
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
    // cout << fabric->size() << " x " << (fabric->front()).size() << endl;
}

int string_to_int(string line)
{
    int number = 0;
    stringstream n(line);
    n >> number;
    return number;
}
