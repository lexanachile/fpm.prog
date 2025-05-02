#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <queue>
#include <vector>
#include <QTextStream>
#include <QString>
#include <QList>
#include <QRegularExpression>
using namespace std;

class MatrixGraph{
    protected:
    vector<vector<int>> gmatrix;
    int n;
};

class Dijkstra : public MatrixGraph
{
    vector<bool> marked;
    vector<int> distances;
    vector<int> papaIMama;
    int infNum = 2147483647;
public:
    Dijkstra(){
        n = 0;
    };
    Dijkstra(int x) {
        n = x;
        clear();
        gmatrix.resize(n);
        for(int i = 0; i < n; ++i){
            gmatrix[i].resize(n);
        }
    };
    Dijkstra(const Dijkstra &x){
        gmatrix = x.gmatrix;
        marked = x.marked;
        n = x.n;
        distances = x.distances;
        papaIMama = x.papaIMama;
    }
    // Dijkstra(Dijkstra &&x){
    //     *this = x;

    // }
    void solve(int startPos){
        if(startPos > n) throw "Too big vertex for this graph";
        clear();

        papaIMama[startPos - 1] = startPos - 1;
        auto cmp = [](const pair<int,int> &p1, const pair<int,int> &p2) -> bool {
            return p1.first > p2.first;
        };
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> myq(cmp);
        myq.push({0, startPos - 1});
        while(!myq.empty()){
            auto [curDist, curV] = myq.top();
            myq.pop();
            if(curDist > distances[curV]) continue;
            for(int i = 0; i < n; ++i){
                int dist = gmatrix[curV][i];
                if(dist == -1) continue;
                dist += curDist;
                if(dist < distances[i]){
                    myq.push({dist,i});
                    distances[i] = dist;
                    papaIMama[i] = curV;
                }
            }
        }
    }
    void clear(){
        distances.resize(n, infNum);
        papaIMama.resize(n);
        for(int i = 0; i<n; ++i){
            papaIMama[i] = i;
        }
    }
    int showTime(const int &aim){
        return distances[aim - 1];
    }
    vector<int> getPath(const int &aim){
        vector<int> vec;
        int v = aim - 1;
        while(papaIMama[v] != v){
            vec.push_back(v);
            v = papaIMama[v];
        }
        vec.push_back(papaIMama[v]);
        return vec;
    }
    void setGraph(QString str){
        QStringList nums = str.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                auto buf = nums.front().toInt();
                gmatrix[i][j] = buf;
                nums.pop_front();
            }
        }
        //"0  30  10 -1"
        // "30  0  10 10"
        // "10 10   0 -1"
        // "-1 10  -1  0";
    }
    friend QTextStream &operator>>(QTextStream &in, Dijkstra &d);
    friend QTextStream &operator<<(QTextStream &out, Dijkstra &d);
};
// QTextStream &operator>>(QTextStream &in, Dijkstra &d){

// };
QTextStream &operator<<(QTextStream &out, Dijkstra &d){
    for (int i = 0; i < d.n; ++i) {
        for (int j = 0; j < d.n; ++j) {
            out << d.gmatrix[i][j] << " ";
        }
        out << Qt::endl;
    }
    return out;
};
#endif // DIJKSTRA_H
