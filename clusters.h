// K-means_Clustering.h : Include file for standard system include files,
// or project specific include files.
#ifndef CLUSTERS_H
#define CLUSTERS_H
#pragma once
#include <vector>
#include <limits>
#include <cmath>
#include <iostream>
#include <random>


// TODO: Reference additional headers your program requires here.
class clusters {
private:

	//STATIC MEMBERS FOR COORDINATE CALCULATIONS:
	
	static std::vector<std::vector<double>> *rawDataforCalcs;
	static std::vector<double> minimumCoordinates;
	static std::vector<double> maximumCoordinates;
	static std::vector<double> centroidCoordinates;
	static double radius; //Radius


	static std::vector<double> minimumCoordinatesCalculations();
	static std::vector<double> maximumCoordinatesCalculations();
	static std::vector<double> centroidCalculation();
	static double radiusCalculation();
	//static std::pair<std::vector<double>, double> computeCentroidAndRadius();

public:
	clusters();
	clusters(std::vector<std::vector<double>> &rawData); //Used for the total RawData

	//Get Minimum values:
	static std::vector<double> getMinimumValues();

	//Get Maximum values:
	static std::vector<double> getMaximumValues();

	//Get Centroid Calculation
	static std::vector<double> getcentroidCalculation();
	
	//Get Radius Calculation
	static double getRadiusCalculation();

};

class clusterNode : public clusters {
private:
	int clusterNumber; //The number identified for this cluster.

	static int numberOfClusters; //Number of total clusters

	std::vector<double> clusterNodeValues; //Coordinates for the cluster nodes

public:
	clusterNode(int clusterNumber);
	std::vector<double> randomPointOnSphere();

	std::vector<double> getRandomPointOnSphere();
};

#endif