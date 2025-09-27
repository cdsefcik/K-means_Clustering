// K-means_Clustering.h : Include file for standard system include files,
// or project specific include files.
#ifndef CLUSTERS_H
#define CLUSTERS_H
#pragma once
#include <vector>


// TODO: Reference additional headers your program requires here.
class clusters {
private:
	int clusterNumber; //The number identified for this cluster.
	std::vector<double> clusterCoordinates;

	//STATIC MEMBERS FOR COORDINATE CALCULATIONS:
	static int numberOfClusters;
	static std::vector<std::vector<double>> *rawDataforCalcs;
	static std::vector<double> minimumCoordinates;
	static std::vector<double> maximumCoordinates;


	static std::vector<double> minimumCoordinatesCalculations();
	static std::vector<double> maximumCoordinatesCalculations();

public:
	clusters(int clusterNumber, std::vector<double> clusterCoordinates);
	clusters(std::vector<std::vector<double>> &rawData); //Used for the total RawData
	clusters(int clusterNumber); //Used for the total RawData

	//Get Minimum values:
	static std::vector<double> getMinimumValues();

	//Get Maximum values:
	static std::vector<double> getMaximumValues();

	//Get clusterCoordinates

	//Set clusterCoordinates

	//Get clusterNumber

	//STATIC MEMBERS FOR CLUSTER COORDINATE CALCULATIONS:

};

#endif