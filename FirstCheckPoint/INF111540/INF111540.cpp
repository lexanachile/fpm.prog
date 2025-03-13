#include <iostream>
#include <list>
#include <vector>
#include <queue>

using namespace std;

class Graph {
private:
    bool *visited;
    vector<list<int> > vecl;
    int num;

public:
    int connected = 0;
    vector<list<int> > links;

    Graph() {
        num = 0;
        visited = nullptr;
    }

    ~Graph() {
        vecl.clear();
        delete[] visited;
    }

    void dfs(int n, int con) {
        visited[n] = true;
        links[con].push_back(n);
        for (int d: vecl[n]) {
            if (!visited[d]) dfs(d, con);
        }
    }

    void solve_dfs() {
        for (int i = 0; i < num; i++) {
            if (visited[i] == false) {
                connected++;
                links.resize(connected);
                dfs(i, connected - 1);
            }
        }
    }

    void solve_wfs() {
        for (int i = 0; i < num; i++) {
            if (visited[i] == false) {
                connected++;
                links.resize(connected);
                queue<int> sk;
                sk.push(i);
                visited[i] = true;

                while (!sk.empty()) {
                    int u = sk.front();
                    sk.pop();
                    links[connected - 1].push_back(u);
                    for (int d: vecl[u]) {
                        if (visited[d] == false) {
                            sk.push(d);
                            visited[d] = true;
                        }
                    }
                }
            }
        }
    }

    friend void operator>>(istream &, Graph &);
};

void operator>>(istream &inf, Graph &G) {
    int k, n, m;
    inf >> G.num >> k;
    G.visited = new bool[G.num];
    for (int i = 0; i < G.num; i++) {
        G.visited[i] = false;
    }
    G.vecl.resize(G.num);

    for (int i = 0; i < k; i++) {
        inf >> n >> m;
        n -= 1;
        m -= 1;
        G.vecl[n].push_back(m);
        G.vecl[m].push_back(n);
    }
}

int main() {
    Graph G;
    cin >> G;
    //G.solve_dfs();
    G.solve_wfs();
    cout << G.connected << endl;
    for (int i = 0; i < G.connected; i++) {
        cout << G.links[i].size() << endl;
        for (int j: G.links[i]) {
            cout << j + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
