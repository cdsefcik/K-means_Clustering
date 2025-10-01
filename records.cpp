#include "records.h"

/*
Author: Christopher Sefcik

Class Use: Used 

Development Notes:

*/

class record {
private:
	int clusterNumber;
	bool firstAssignment = true; //This determines if the cluster number is being assigned for the first time.
	bool ChangedCluster = false; //This is if the cluster number changed since the last run.
	std::vector<double> recordCoordinates;


public:
	record(std::vector<double> recordCoordinates) {
		this->clusterNumber = clusterNumber;
		this->firstAssignment = firstAssignment;
		this->recordCoordinates = recordCoordinates;
		this->ChangedCluster = ChangedCluster;

	}

	//Method for updating the cluster number
};