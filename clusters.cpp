#include "clusters.h"
/*
These are the functions for the parent class

*/
//Defined Variables:
std::vector<std::vector<double>>* clusters::rawDataforCalcs = nullptr;
std::vector<double> clusters::minimumCoordinates;
std::vector<double> clusters::maximumCoordinates;
std::vector<double> clusters::centroidCoordinates;

//Parameterized constructors:
clusters::clusters(std::vector<std::vector<double>> &rawData) { //Raw data constructor
	rawDataforCalcs = &rawData;
    minimumCoordinates = minimumCoordinatesCalculations();
    maximumCoordinates = maximumCoordinatesCalculations();
    centroidCoordinates = centroidCalculation();
}

//Member Functions

//This function calculates all the minimum coordinstates
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

//This function calculates all the maximum coordinstates
std::vector<double> clusters::maximumCoordinatesCalculations() {
    size_t cols = 0;
    for (const auto& row : *rawDataforCalcs) {
        if (row.size() > cols) cols = row.size();
    }

    std::vector<double> maxs(cols, -std::numeric_limits<double>::infinity());

    for (size_t c = 0; c < cols; ++c) {
        for (size_t r = 0; r < rawDataforCalcs->size(); ++r) {
            if (c < (*rawDataforCalcs)[r].size()) {
                maxs[c] = std::max(maxs[c], (*rawDataforCalcs)[r][c]);
            }
        }
    }

    return maxs;
}

std::vector<double> clusters::centroidCalculation(){
    std::vector<double> centroid;

    if (minimumCoordinates.empty() || maximumCoordinates.empty()) {
        return centroid;
    }
    if (minimumCoordinates.size() != maximumCoordinates.size()) {
        return centroid;
    }

    for (int i = 0; i < minimumCoordinates.size(); i++) {
        double midpoint = (minimumCoordinates.at(i) + maximumCoordinates.at(i)) / 2;
            centroid.push_back(midpoint);
    }

    return centroid;
};


//RETURN VALUES for clusterNode class
std::vector<double> clusters::getMinimumValues() {

    return clusters::minimumCoordinates;
}

std::vector<double> clusters::getMaximumValues() {

    return clusters::maximumCoordinates;
}

std::vector<double> clusters::getcentroidCalculation() {
    return clusters::centroidCoordinates;
}