#include <QCoreApplication>
#include <QTextStream>
#include <QString>
#include <queue>
#include <QTextStream>
#include <QString>
#include <QVector>
#include <QRegularExpression>
using namespace std;

class MatrixGraph{
protected:
    QVector<QVector<int>> gmatrix;
    int n;
};

class Dijkstra : public MatrixGraph
{
    QVector<bool> marked;
    QVector<int> distances;
    QVector<int> papaIMama;
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
        priority_queue<pair<int,int>, QVector<pair<int,int>>, decltype(cmp)> myq(cmp);
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
    QVector<int> getPath(const int &aim){
        QVector<int> vec;
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
QTextStream &operator>>(QTextStream &in, Dijkstra &d) {
    int N, S, F;
    in >> N >> S >> F;
    d.n = N;
    d.gmatrix.clear();
    d.gmatrix.resize(N);
    for (int i = 0; i < N; ++i) {
        d.gmatrix[i].resize(N);
    }
    d.clear();

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int w;
            in >> w;
            d.gmatrix[i][j] = w;
        }
    }

    d.solve(S);

    if (d.distances[F - 1] == d.infNum) {
        in.setDevice(nullptr); // отключаем поток, чтобы избежать ошибок
        QTextStream out(stdout);
        out << -1 << Qt::endl;
        return in;
    }

    QVector<int> path = d.getPath(F);
    QTextStream out(stdout);
    for (int i = path.size() - 1; i >= 0; --i) {
        out << (path[i] + 1);
        if (i != 0) out << " ";
    }
    out << Qt::endl;

    return in;
}

QTextStream &operator<<(QTextStream &out, Dijkstra &d) {
    for (int i = 0; i < d.n; ++i) {
        for (int j = 0; j < d.n; ++j) {
            out << d.gmatrix[i][j] << " ";
        }
        out << Qt::endl;
    }
    return out;
}

int main(int argc, char *argv[])
{
    QCoreApplication QTApp(argc, argv);
    QTextStream in(stdin);
    QTextStream out(stdout);

    Dijkstra myGraph;
    in >> myGraph;
    out << myGraph;
    return QTApp.exec();
}
