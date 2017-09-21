//Nicolas Stoian
//This program needs 3 command line arguments
//argv[1] "input1" for text file representing the directed graph
//argv[2] "input2" for integer representing the source node
//argv[3] "output1" to write the outputs

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

void loadMatrix(int** costMatrix, int arraySize, ifstream& inFile);
void printGraph(int** costMatrix, int arraySize, ofstream& outFile);
void dijkstraAlgorithm(int** costMatrix, int arraySize, int sourceNode, int* marked, int* parent, int* bestCost);
void printPaths(int** costMatrix, int arraySize, int sourceNode, int* parent, int* bestCost, ofstream& outFile);
string pathGenerator(int source, int destination, int arraySize, int* parent);
void printCostMatrix(int** costMatrix, int arraySize, ofstream& outFile);

int main(int argc, char* argv[]){
    ifstream inFile;
    inFile.open(argv[1]);
    int numNodes;
    inFile >> numNodes;
    int** costMatrix;
    costMatrix = new int* [numNodes];
    for(int i = 0; i < numNodes; i++){
        costMatrix[i] = new int [numNodes];
    }
    for(int row = 0; row < numNodes; row++){
        for(int col = 0; col < numNodes; col++){
            if(row == col){
                costMatrix[row][col] = 0;
            }
            else{
                costMatrix[row][col] = -1;
            }
        }
    }
    loadMatrix(costMatrix, numNodes, inFile);
    stringstream source(argv[2]);
    int sourceNode;
    source >> sourceNode;
    ofstream outFile;
    outFile.open(argv[3]);
    printGraph(costMatrix, numNodes, outFile);
    outFile << endl;
    cout << endl;
    printCostMatrix(costMatrix, numNodes, outFile);
    cout << "\nThe source node is " << sourceNode << endl << endl;
    outFile << "\nThe source node is " << sourceNode-- << endl << endl;
    int* marked = new int [numNodes];
    for(int i = 0; i < numNodes; i++){
        marked[i] = 0;
    }
    int* parent = new int [numNodes];
    for(int i = 0; i < numNodes; i++){
        parent[i] = sourceNode;
    }
    int* bestCost = new int [numNodes];
    for(int i = 0; i < numNodes; i++){
        bestCost[i] = costMatrix[sourceNode][i];
    }
    dijkstraAlgorithm(costMatrix, numNodes, sourceNode, marked, parent, bestCost);
    printPaths(costMatrix, numNodes, sourceNode, parent, bestCost, outFile);
}

void loadMatrix(int** costMatrix, int arraySize, ifstream& inFile){
    int row;
    int col;
    int cost;
    while(inFile >> row){
        inFile >> col;
        inFile >> cost;
        costMatrix[row - 1][col - 1] = cost;
    }
}

void printGraph(int** costMatrix, int arraySize, ofstream& outFile){
    for(int row = 0; row < arraySize; row++){
        for(int col = 0; col < arraySize; col++){
            if (costMatrix[row][col] != -1 && costMatrix[row][col] != 0){
                outFile << row + 1 << " " << col + 1 << " " << costMatrix[row][col] << endl;
                cout << row + 1 << " " << col + 1 << " " << costMatrix[row][col] << endl;
            }
        }
    }
}

void dijkstraAlgorithm(int** costMatrix, int arraySize, int sourceNode, int* marked, int* parent, int* bestCost){
    int minNode = sourceNode;
    int numMarked = 0;
    while(numMarked != arraySize){
        marked[minNode] = 1;
        numMarked++;
        for(int i = 0; i < arraySize; i++){
            if(marked[i] == 0){
                int newNode = i;
                if(costMatrix[minNode][newNode] != -1){
                    int tempCost = bestCost[minNode] + costMatrix[minNode][newNode];
                    if (bestCost[newNode] == -1){
                        bestCost[newNode] = tempCost;
                        parent[newNode] = minNode;
                    }
                    else if(tempCost < bestCost[newNode]){
                        bestCost[newNode] = tempCost;
                        parent[newNode] = minNode;
                    }
                }
            }
        }
        int smallestBestCost = 0;
        for(int i = 0; i < arraySize; i++){
            if (bestCost[i] > smallestBestCost){
                smallestBestCost = bestCost[i];
            }
        }
        for(int i = 0; i < arraySize; i++){
            if (marked[i] != 1 && bestCost[i] != -1 && bestCost[i] != 0 && bestCost[i] < smallestBestCost){
                smallestBestCost = bestCost[i];
            }
        }
        for(int i = 0; i < arraySize; i++){
            if (marked[i] != 1 && bestCost[i] == smallestBestCost){
                minNode = i;
            }
        }
    }
}

void printPaths(int** costMatrix, int arraySize, int sourceNode, int* parent, int* bestCost, ofstream& outFile){
    for(int i = 0; i < arraySize; i++){
        if(i != sourceNode){
            outFile << sourceNode + 1 << " to " << i + 1 << " (" << bestCost[i] << ") and path: " << pathGenerator(sourceNode, i, arraySize, parent) << endl;
            cout << sourceNode + 1 << " to " << i + 1 << " (" << bestCost[i] << ") and path: " << pathGenerator(sourceNode, i, arraySize, parent) << endl;
        }
    }
}

string pathGenerator(int source, int destination, int arraySize, int* parent){
    stringstream toReturn;
    toReturn << destination + 1 << " <-- ";
    if(parent[destination] == source){
        toReturn << source + 1;
    }
    else{
        while(parent[destination] != source){
            toReturn << parent[destination] + 1 << " <-- ";
            destination = parent[destination];
        }
        toReturn << source + 1;
    }
    return toReturn.str();
}

void printCostMatrix(int** costMatrix, int arraySize, ofstream& outFile){
    outFile << right << setw(5) << "index";
    cout << right << setw(5) << "index";
    for(int col = 0; col < arraySize; col++){
            outFile  << setw(3) << col + 1;
            cout  << setw(3) << col + 1;
    }
    outFile << endl;
    cout << endl;
    for(int row = 0; row < arraySize; row++){
        outFile << setw(5) << row + 1;
        cout << setw(5) << row + 1;
        for(int col = 0; col < arraySize; col++){
            if(costMatrix[row][col] == -1){
                outFile << setw(3) << "-";
                cout << setw(3) << "-";
            }
            else{
                outFile << setw(3) << costMatrix[row][col];
                cout << setw(3) << costMatrix[row][col];
            }
        }
        outFile << endl;
        cout << endl;
    }
}
