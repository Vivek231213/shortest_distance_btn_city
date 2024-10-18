#include <iostream>
#include<bits/stdc++.h>

using namespace std;

const string FILENAME = "graph.txt"; 

// Dijkstra's Algorithm for finding the shortest path
void findShortestPath(string start, string destination, unordered_map<string, vector<pair<string, int>>> &cityGraph) {
    unordered_map<string, int> sortDist;
    unordered_map<string, string> privCity;

    
    for (auto &city : cityGraph) {
        sortDist[city.first] = INT_MAX;
        privCity[city.first] = "";
    }
    sortDist[start] = 0;

    
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        string currentCity = pq.top().second;
        pq.pop();

        if (currentCity == destination) break; 

        for (auto &neighbor : cityGraph[currentCity]) {
            string neighborCity = neighbor.first;
            int distanceToNeighbor = neighbor.second;

            // Update distance 
            if (sortDist[currentCity] + distanceToNeighbor < sortDist[neighborCity]) {
                sortDist[neighborCity] = sortDist[currentCity] + distanceToNeighbor;
                privCity[neighborCity] = currentCity;
                pq.push({sortDist[neighborCity], neighborCity});
            }
        }
    }

    if (sortDist[destination] == INT_MAX) {
        cout << "No path found between " << start << " and " << destination << ".\n";
    } else {
        cout << "Shortest distance between " << start << " and " << destination << " is: " << sortDist[destination] << " km.\n";
        // Print the path
        cout << "Path: ";
        string pathCity = destination;
        vector<string> path;
        while (pathCity != "") {
            path.push_back(pathCity);
            pathCity = privCity[pathCity];
        }
        for (int i = path.size() - 1; i >= 0; --i) {
            cout << path[i];
            if (i != 0) cout << " -> ";
        }
        cout << endl;
    }
}

int main() {

    unordered_map<string, vector<pair<string, int>>> cityGraph;
    unordered_set<string> citySet; 

    ifstream inputFile(FILENAME); 
    if (!inputFile) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    int numcity, numroad;
    inputFile >> numcity;

    vector<string> cities(numcity);
    for (int i = 0; i < numcity; ++i) {
        inputFile >> cities[i];
        cityGraph[cities[i]] = vector<pair<string, int>>();
        citySet.insert(cities[i]); 
    }

    inputFile >> numroad;

    for (int i = 0; i < numroad; ++i) {
        string city1, city2;
        int distance;
        inputFile >> city1 >> city2 >> distance;
        cityGraph[city1].push_back({city2, distance});
        cityGraph[city2].push_back({city1, distance}); 
    }

    inputFile.close();

    string start, destination;
    cout << "Enter start city: ";
    cin >> start;
    cout << "Enter destination city: ";
    cin >> destination;



    if (citySet.find(start) == citySet.end()) {
        cout << "Start city not found!" << endl;
        return 1;
    }
    if (citySet.find(destination) == citySet.end()) {
        cout << "Destination city not found!" << endl;
        return 1;
    }



    findShortestPath(start, destination, cityGraph);

    return 0;
}
