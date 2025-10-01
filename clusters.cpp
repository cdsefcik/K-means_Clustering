#include "clusters.h"
/*
These are the functions for the parent class

*/
//Defined Variables:
std::vector<std::vector<double>>* clusters::rawDataforCalcs = nullptr;
std::vector<double> clusters::minimumCoordinates;
std::vector<double> clusters::maximumCoordinates;
std::vector<double> clusters::centroidCoordinates;
double clusters::radius = std::numeric_limits<double>::infinity();
int clusterNode::numberOfClusters = 0;

//Parameterized constructors:
clusters::clusters() {

}
clusters::clusters(std::vector<std::vector<double>> &rawData) { //Raw data constructor
	rawDataforCalcs = &rawData;
    minimumCoordinates = minimumCoordinatesCalculations();
    maximumCoordinates = maximumCoordinatesCalculations();
    centroidCoordinates = centroidCalculation();
    radius = radiusCalculation();
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


double clusters::radiusCalculation() {
    // Radius = half the largest width
    radius = std::numeric_limits<double>::infinity(); //Updates the class member
    if (minimumCoordinates.empty() || maximumCoordinates.empty()) {
        return radius;
    }
    if (minimumCoordinates.size() != maximumCoordinates.size()) {
        return radius;
    }
    size_t dim = minimumCoordinates.size();
    
    for (size_t i = 0; i < dim; i++) {
        radius = std::min(radius, (maximumCoordinates[i] - minimumCoordinates[i]) / 2.0);
    }

    return radius;
}


//THESE ARE THE METHODS FOR THE CLUSTER CLASS
std::vector<double> clusters::getMinimumValues() {

    return clusters::minimumCoordinates;
}

std::vector<double> clusters::getMaximumValues() {

    return clusters::maximumCoordinates;
}

std::vector<double> clusters::getcentroidCalculation() {
    return clusters::centroidCoordinates;
}

double clusters::getRadiusCalculation() {
    return clusters::radius;
}

//THESE ARE THE METHODS AND VARIABLES FOR THE CLUSTER NODE CLASS

clusterNode::clusterNode(int clusterNumber) {
    this->clusterNumber = clusterNumber;
    this->clusterNodeValues = randomPointOnSphere();

}

std::vector<double> clusterNode::randomPointOnSphere() {

    std::vector<double> centroidCalculation = getcentroidCalculation();
    double radius = getRadiusCalculation();

    size_t dim = centroidCalculation.size();
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::normal_distribution<double> dist(0.0, 1.0);  // Gaussian distribution

    // Step 1: generate random Gaussian vector
    std::vector<double> vec(dim);
    for (size_t i = 0; i < dim; i++) {
        vec[i] = dist(gen);
    }

    // Step 2: normalize to unit length
    double norm = 0.0;
    for (double v : vec) norm += v * v;
    norm = std::sqrt(norm);
    for (size_t i = 0; i < dim; i++) {
        vec[i] /= norm;
    }

    // Step 3: scale by radius and shift by centroid
    for (size_t i = 0; i < dim; i++) {
        vec[i] = centroidCalculation[i] + radius * vec[i];
    }

    return vec;
}

std::vector<double> clusterNode::getRandomPointOnSphere() {

    return clusterNode::clusterNodeValues;
}