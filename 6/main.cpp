#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

using namespace std;

int calcManhattan(int x1, int y1, int x2, int y2)
{
    int x = x1 - x2;
    int y = y1 - y2;
    x = x < 0 ? -1*x : x;
    y = y < 0 ? -1*y : y;
    return x + y;
}

int main()
{
    ifstream inputFile("input.txt");
    map<int, map<int, int> > points;
    string line;
    int x, y, m_x =-1, m_y = -1, l_x = 500, l_y = 500, threshold = 10000, d, ld, p, md, ma=0, ca=0, td;
    char c;

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            stringstream n(line);
            n >> x >> c >> y;
            points[x][y] = 0;
            m_x = x > m_x ? x : m_x;
            m_y = y > m_y ? y : m_y;
            l_x = x < l_x ? x : l_x;
            l_y = y < l_y ? y : l_y;
        }

        inputFile.close();
    }
    
    auto besty = (points.begin()->second).begin();
    auto bestx = points.begin();
    md = calcManhattan(l_x, l_y, m_x, m_y);

    for (int i=l_x; i<=m_x; i++) {
        for (int j=l_y; j<=m_y; j++) {
            ld = md;
            auto cury = (points.begin()->second).begin();
            auto curx = points.begin();
            p = 0;
            td = 0;
            for (auto it = points.begin(); it != points.end(); it++) {
                for (auto jt = (it->second).begin(); jt != (it->second).end(); jt++) {
                    d = calcManhattan(i, j, it->first, jt->first);
                    td += d;
                    if (d <= ld) {
                        p = d == ld ? 0 : 1;
                        ld = d;
                        cury = jt;
                        curx = it;
                    }
                }
            }
            if (td < threshold) ca++;
            if (i == l_x || i == m_x || j == l_y || j == m_y) {
                cury->second = -1;
            } else if (cury->second > -1) {
                cury->second += p;
            }

            if ((cury->second > besty->second) && (cury->second > -1)) {
                besty = cury;
                bestx = curx;
            }
        }
    }

    cout << "Greatest area: " << bestx->first << "," << besty->first << " : " << besty->second << endl;
    cout << "Central Area: " << ca << endl;
}
