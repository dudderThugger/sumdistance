#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <set>

/**
 * @brief Graph class, each character in the matrix represents a node in the graph
 * The edges are represented in an adjacency list
 */
class Graph {

    std::vector<char> vexes; /**< The nodes as characters*/
    int startIndex; /**< The position of the character T*/
    int rows; /**< The number of rows in the matrix*/
    int columns; /**< The number of columns in the matrix*/
    int sumDistance; /**< The final result of the problem*/
    char** cells; /**< The matrix of characters*/
    std::vector<int> bfsTree, distance, checkNodes, reachedNodes; /**< The desired vecotrs for the breadth first search algorithm*/
    std::vector<int> *adjacencyList; /**< The edges of the graph stored in an adjacency matrix*/
public:
    /**
     * @brief Construct a new Graph object
     * 
     * @param n Number of rows
     * @param m Number of columns
     */
    Graph(int n, int m);

    /**
     * @brief Initialize the matrix of characters
     * 
     */
    void initCells();

    /**
     * @brief Initialize the adjency list
     * Iterates through each node's each neighbour and decides 
     * wether an edge should be drawn (edge is drawn when it is reachable)
     */
    void initAdjencyList();

    /**
     * @brief Set ups a node's edges
     * 
     * @param row The number of the row the node is at
     * @param column The number of column the node is at
     */
    void setupEdges(int row, int column);

    /**
     * @brief Converts a character of a hexadecimal number to integer
     * 
     * @param hex The character of the hexadecimal number
     * @return int The integer
     */
    int hexToBinary(char hex);

    /**
     * @brief Prints each cell on the standard output
     * 
     */
    void printCells();

    /**
     * @brief Prints each edge on the standar output
     * 
     */
    void printEdges();

    /**
     * @brief Runs the breadth first search algorithm on the graph
     * 
     */
    void bfs();

    /**
     * @brief Get the Result object
     * 
     * @return int The result of the problem
     */
    int getResult();

    /**
     * @brief Prints the result of the bfs algorithm
     * 
     */
    void printBfs();

    /**
     * @brief Checks if the char is a barrier (bound/'X')
     * 
     * @param neighbourChar The character of the neighbour
     */
    inline bool neighbourNotBarrier(char neighbourChar) {
        return (neighbourChar != 'X' && neighbourChar != 'N');
    }

    /**
     * @brief Checks if the "right flag" is on
     * 
     * @param number The flag of the number
     * @return true The "checkpoint" reachable
     * @return false The "checkpoint" is unreachable
     */
    inline bool openFromRight(int number) {
        return ((number & 1) == 1);
    }

    /**
     * @brief Checks if the "left flag" is on
     * 
     * @param number the flags
     * @return true The checkpoint is reachable
     * @return false The checkpoint is unreachable
     */
    inline bool openFromLeft(int number) {
        return ((number & 4) == 4);
    }

    /**
     * @brief Checks if the "top flag" is on
     * 
     * @param number the flags
     * @return true The checkpoint is reachable
     * @return false The checkpoint is unreachable
     */
    inline bool openFromTop(int number) {
        return ((number & 2) == 2);
    }

    /**
     * @brief Checks if the "bottom flag" is on
     * 
     * @param number the flags
     * @return true The checkpoint is reachable
     * @return false The checkpoint is unreachable
     */
    inline bool openFromBottom(int number) {
        return ((number & 8) == 8);
    }
    
    /**
     * @brief Destroy the Graph object
     *  
     */
    ~Graph();
};

#endif