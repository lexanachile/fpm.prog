#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <stdexcept>
#include <algorithm>

using namespace std;

class MatrixGraph {
protected:
    vector<vector<int>> gmatrix;
    int n;
public:
    MatrixGraph() : n(0) {}
    MatrixGraph(int size) : n(size), gmatrix(size, vector<int>(size)) {}
};

class Dijkstra : public MatrixGraph {
    vector<int> distances;
    vector<int> parents;
    const int infNum = numeric_limits<int>::max();
public:
    Dijkstra() : MatrixGraph() {}
    Dijkstra(int size) : MatrixGraph(size) {
        clear();
    }
    void clear() {
        distances.assign(n, infNum);
        parents.resize(n);
        for (int i = 0; i < n; ++i) {
            parents[i] = i;
        }
    }
    void solve(int startPos) {
        if (startPos < 1 || startPos > n)
            throw invalid_argument("Invalid start vertex");
        clear();
        distances[startPos - 1] = 0;
        parents[startPos - 1] = startPos - 1;

        using pii = pair<int, int>;
        auto cmp = [](const pii& a, const pii& b) { return a.first > b.first; };
        priority_queue<pii, vector<pii>, decltype(cmp)> pq(cmp);
        pq.push({0, startPos - 1});

        while (!pq.empty()) {
            auto [curDist, curV] = pq.top();
            pq.pop();
            if (curDist > distances[curV]) continue;

            for (int i = 0; i < n; ++i) {
                int w = gmatrix[curV][i];
                if (w == -1) continue;
                int newDist = curDist + w;
                if (newDist < distances[i]) {
                    distances[i] = newDist;
                    parents[i] = curV;
                    pq.push({newDist, i});
                }
            }
        }
    }
    int getDistance(int vertex) const {
        return distances[vertex - 1];
    }
    void readGraph(istream& in, int& S, int& F) {
        in >> n >> S >> F;
        gmatrix.assign(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                in >> gmatrix[i][j];
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Dijkstra d;
    int S, F;
    d.readGraph(cin, S, F);
    d.solve(S);

    int dist = d.getDistance(F);
    if (dist == numeric_limits<int>::max()) {
        cout << -1 << "\n";
    } else {
        cout << dist << "\n";
    }

    return 0;
}
