#include "clusters.h"
//Defined Variables:
int clusters::numberOfClusters = 0;
std::vector<std::vector<double>>* clusters::rawDataforCalcs = nullptr;
std::vector<double> clusters::minimumCoordinates;
std::vector<double> clusters::maximumCoordinates;

//Parameterized constructors:
clusters::clusters(int clusterNumber, const std::vector<double> clusterCoordinates) { //More for testing, cluster number and coordinates.
	this->clusterNumber = clusterNumber;
	this->clusterCoordinates = clusterCoordinates;
}

clusters::clusters(std::vector<std::vector<double>> &rawData) { //Raw data constructor
    this->clusterNumber = 0;
	rawDataforCalcs = &rawData;
    minimumCoordinates = minimumCoordinatesCalculations();
    maximumCoordinates = maximumCoordinatesCalculations();
}

clusters::clusters(int clusterNumber) { //Will generate a cluster and attach a vector of cluster coordinates.
	this->clusterNumber = clusterNumber;

}

//Member Functions

std::vector<double> clusters::minimumCoordinatesCalculations() {
    size_t cols = 0;
    for (const auto& row : *rawDataforCalcs) {
        if (row.size() > cols) cols = row.size();
    }

    std::vector<double> mins(cols, std::numeric_limits<double>::infinity());

    for (size_t c = 0; c < cols; ++c) {
        for (size_t r = 0; r < rawDataforCalcs->size(); ++r) {
            if (c < (*rawDataforCalcs)[r].size()) {
                mins[c] = std::min(mins[c], (*rawDataforCalcs)[r][c]);
            }
        }
    }

    return mins;
}

std::vector<double> clusters::maximumCoordinatesCalculations() {
    size_t cols = 0;
    for (const auto& row : *rawDataforCalcs) {
        if (row.size() > cols) cols = row.size();
    }

    std::vector<double> maxs(cols, -std::numeric_limits<double>::infinity());

    for (size_t c = 0; c < cols; ++c) {
        for (size_t r = 0; r < rawDataforCalcs->size(); ++r) {
            if (c < rawDataforCalcs[r].size()) {
                maxs[c] = std::max(maxs[c], (*rawDataforCalcs)[r][c]);
            }
        }
    }

    return maxs;
}

std::vector<double> clusters::getMinimumValues() {

    return clusters::minimumCoordinates;
}

std::vector<double> clusters::getMaximumValues() {

    return clusters::maximumCoordinates;
}