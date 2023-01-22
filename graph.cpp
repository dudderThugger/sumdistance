#include "graph.h"

Graph::Graph(int n, int m) :vexes(), rows(n), columns(m), sumDistance(0) {
    adjacencyList= new std::vector<int>[n * m];
    initCells();
    initAdjencyList();
}

void Graph::initCells() {
        // Make a 2 dimension array for the chars of the input
        cells = new char*[rows];
        for(int i = 0; i < rows; ++i) {
            cells[i] = new char[columns];
        }

        // Ignore the last enter in the buffer
        std::cin.ignore(1);

        // Fill the arrays with the characters
        for(int i = 0; i < rows; ++i) {
            char line[columns + 1];
            std::cin.getline(line, columns + 1);
            for(int j = 0; j < columns; j++) {
                cells[i][j] = line[j];
                if(cells[i][j] == 'T') {
                    startIndex = i * columns + j;
                }
                if(isxdigit(cells[i][j])) {
                    checkNodes.push_back(i* columns + j);
                }
            }
        }
}

void Graph::initAdjencyList() {
        for(int i = 0; i < rows; ++i) {
            for(int j = 0; j < columns; ++j) {
                setupEdges(i, j);
            }
        }
}

void Graph::setupEdges(int row, int column) {
    char vex = cells[row][column];
    int indexVex = row * columns + column;
    vexes.push_back(vex);

    char upperNeighbour; // The type of the neighbour, 0 if it is not valid (out of bounds)
    int upperNeighbourIndex = (row - 1) * columns + column; // The index of the upperNeighbour
    
    if(row != 0) {
        upperNeighbour = cells[row-1][column];
    } else {
        upperNeighbour = 'N';
    }

    char rightNeighbour;
    int rightNeighbourIndex = row * columns + column + 1 ;
    if(column != columns - 1) {
        rightNeighbour = cells[row][column + 1];
    } else {
        rightNeighbour = 'N';
    }

    char leftNeighbour;
    int leftNeighbourIndex = row * columns + column - 1;
    if(column != 0) {
        leftNeighbour = cells[row][column - 1];
    } else {
        leftNeighbour = 'N';
    }

    char bottomNeighbour;
    int bottomNeighbourIndex = (row + 1) * columns + column;
    if(row != rows - 1) {
        bottomNeighbour = cells[row + 1][column];
    }else {
        bottomNeighbour = 'N';
    }

    // Vex is a cell we can go through
    if(vex == '-' || vex == 'T') {
        // If it has a reachable neighbour add an edge to the adjency list
        if(neighbourNotBarrier(rightNeighbour)) {
            if(isxdigit(rightNeighbour)) {
                int right = hexToBinary(rightNeighbour);
                if(openFromLeft(right)) {
                    adjacencyList[indexVex].push_back(rightNeighbourIndex);
                }
            } else {
                adjacencyList[indexVex].push_back(rightNeighbourIndex);
            }
        }

        if(neighbourNotBarrier(leftNeighbour)) {
            if(isxdigit(leftNeighbour)) {
                if(openFromRight(hexToBinary(leftNeighbour))) {
                    adjacencyList[indexVex].push_back(leftNeighbourIndex);
                }
            } else {
                adjacencyList[indexVex].push_back(leftNeighbourIndex);
            }
        }

        if(neighbourNotBarrier(upperNeighbour)){
            if(isxdigit(upperNeighbour)) {
                int top = hexToBinary(upperNeighbour);
                if(openFromBottom(top)){
                    adjacencyList[indexVex].push_back(upperNeighbourIndex);
                }                
            } else {
                adjacencyList[indexVex].push_back(upperNeighbourIndex);
            }
        }

        if(neighbourNotBarrier(bottomNeighbour)) {
            if(isxdigit(bottomNeighbour)) {
                int bottom = hexToBinary(bottomNeighbour);
                if(openFromTop(bottom)) {
                    adjacencyList[indexVex].push_back(bottomNeighbourIndex);
                }
            } else {
                adjacencyList[indexVex].push_back(bottomNeighbourIndex);
            }
        }
    }
}

int Graph::hexToBinary(char hex) {
    switch(hex) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'A': return 10;
    case 'B': return 11;
    case 'C': return 12;
    case 'D': return 13;
    case 'E': return 14;
    case 'F': return 15;
    default: return -1;
    }
}

Graph::~Graph() {
    for(int i = 0; i < rows; ++i) {
        delete[] cells[i];
    }
    delete[] cells;
    delete[] adjacencyList;
}

void Graph::printCells() {
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            std::cout << cells[i][j];
        }
    }
}

void Graph::bfs() {
    std::set<int> reached;
    reached.insert(startIndex);
    reachedNodes.push_back(startIndex);
    distance.push_back(-1);
    bfsTree.push_back(startIndex);
    size_t actual = 0;
    size_t previous_size = 0;
    // int loop = 0;
    // Loop has to stop, when we are at the last element of the reached nodes vector, and all of its neighbour''s has already been added
    while(!((reachedNodes.size() == previous_size) && (actual == reachedNodes.size() - 1))) {
        previous_size = reachedNodes.size();
        int ind = reachedNodes[actual];
        //std::cout << "Loop no. " << loop++ << " the actual node is: " << ind << " which has "<< adjacencyList[ind].size() << " neighbours"<< std::endl;
        for(std::vector<int>::iterator it = adjacencyList[ind].begin(); it != adjacencyList[ind].end(); ++it) {
            if(reached.find(*it) == reached.end()) {
                reached.insert(*it);
                reachedNodes.push_back(*it);
                distance.push_back(distance[actual] + 1);
                bfsTree.push_back(ind);
            }
        }

        actual++;
    }

    // Count the final result
    for(size_t i = 0; i < checkNodes.size(); i++) {
        int indexOfCheckNode = checkNodes[i];
        for(size_t j = 0; j < reachedNodes.size(); ++j) {
            if(reachedNodes[j] == indexOfCheckNode) {
                sumDistance += distance[j];
                break;
            }
        }
    }
}

void Graph::printEdges() {
    for(int i = 0; i < rows * columns; ++i) {
        std::vector<int>::iterator it;
        std::cout <<  "No. " << i << " vex is \"" << vexes.at(i) << "\" with the neighbours: ";
        for(it = adjacencyList[i].begin(); it != adjacencyList[i].end(); it++) {
            std::cout << " \""<< vexes[*it] << "\" at " << *it << ", ";
        }
        std::cout << std::endl;
    }
}

void Graph::printBfs() {
    for(size_t i = 0; i < reachedNodes.size(); ++i) {
        std::cout << reachedNodes[i] << " " << vexes[reachedNodes[i]] << " " << distance[i] << " " << bfsTree[i] << std::endl;
    }
}

int Graph::getResult() {
    return sumDistance;
}