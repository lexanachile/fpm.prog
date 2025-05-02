#include <QCoreApplication>
#include <QTextStream>
#include "dijkstra.h"
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication QTApp(argc, argv);
    QTextStream in(stdin);
    QTextStream out(stdout);

    int n = 3, start = 2, aim = 1;
    //in >> n >> start >> aim;

    QString Matrix = "0 1 1 4 0 1 2 1 0";
    // for (int i = 0; i < n; ++i) {
    //     QString line = in.readLine();
    //     if (line.isNull())
    //         throw "Malo strok";
    //     Matrix.append(line);
    // }
    // Matrix = "0 30 10 -1 \n"
    //          "30 0 10 10 \n"
    //          "10 10 0 -1 \n"
    //          "-1 10 -1 0 \n";

    Dijkstra myGraph(n);
    myGraph.setGraph( Matrix);
    myGraph.solve(start);
    out << myGraph.showTime(aim) << Qt::endl;
    vector<int> ans = myGraph.getPath(aim);
    for (int i = ans.size() - 1; i >= 0; --i) {
        out << ans[i] + 1 << " ";
    }
    // out << Qt::endl;
    // out << myGraph;
    return QTApp.exec();
}
