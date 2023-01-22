#include <iostream>
#include "graph.h"

int main(void) {
    int n, m;
    std::cin >> n;
    std::cin >> m;

    Graph g(n, m);
    g.bfs();
    std::cout << g.getResult() << std::endl;

    return 0;
}