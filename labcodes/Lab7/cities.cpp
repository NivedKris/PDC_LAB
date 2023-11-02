#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <omp.h>
// Function to find the shortest tour using OpenMP
double findShortestTour(const std::vector<std::vector<int>> &distanceMatrix)
{
    int numCities = distanceMatrix.size();
    double shortestDistance = std::numeric_limits<double>::max();
#pragma omp parallel
    {
        double localShortestDistance = std::numeric_limits<double>::max();
#pragma omp for
        for (int startCity = 0; startCity < numCities; ++startCity)
        {
            std::vector<bool> visited(numCities, false);
            int currentCity = startCity;
            double localTourDistance = 0.0;
            for (int i = 0; i < numCities - 1; ++i)
            {
                visited[currentCity] = true;
                int nearestCity = -1;
                int minDistance = std::numeric_limits<int>::max();
                // Find the nearest unvisited city
                for (int j = 0; j < numCities; ++j)
                {
                    if (!visited[j] && j != currentCity)
                    {
                        if (distanceMatrix[currentCity][j] < minDistance)
                        {
                            minDistance = distanceMatrix[currentCity][j];
                            nearestCity = j;
                        }
                    }
                }
                if (nearestCity != -1)
                {
                    localTourDistance +=
                        minDistance;
                    currentCity =
                        nearestCity;
                }
            }
            // Return to the starting city
            localTourDistance += distanceMatrix[currentCity][startCity];
            if (localTourDistance < localShortestDistance)
            {
                localShortestDistance = localTourDistance;
            }
        }
#pragma omp critical
        {
            if (localShortestDistance < shortestDistance)
            {
                shortestDistance = localShortestDistance;
            }
        }
    }
    return shortestDistance;
}
int main()
{
    // Read the number of cities from the input file
    int numCities;
    std::cout << "NIVED KRISHNA 2021BCS0028\n";
    std::ifstream inputFile("cities.txt");
    inputFile >> numCities;
    // Read the distance matrix from the input file
    std::vector<std::vector<int>> distanceMatrix(numCities,
                                                 std::vector<int>(numCities));
    for (int i = 0; i < numCities; ++i)
    {
        for (int j = 0; j < numCities; ++j)
        {
            inputFile >> distanceMatrix[i][j];
        }
    }
    inputFile.close();
    // Find the shortest tour
    double shortestDistance = findShortestTour(distanceMatrix);
    std::cout << "Shortest tour distance: " << shortestDistance << std::endl;
    return 0;
}