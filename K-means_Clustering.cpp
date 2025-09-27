/*
K - means_Clustering.cpp : Defines the entry point for the application.

Author: Christopher Sefcik

Program Use: Optimized version of K-means Clustering

Development Notes:
1: Need to take in the input file, parse it and create two vector of vectors, one for the identifer fields, the second for the
clustering data.

2:Parameters to run the program:
A: Does it have a header row
B: Number of columns from the left that are considered keys, but are not run through the analysis exe:0 = no columns, 1, 2, 3
C: The number of clusters

How to run program:

*/ 

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include "K-means_Clustering.h"
#include "importData.h"
#include <vector>
#include <sstream>
#include <utility>


using namespace std;
namespace fs = std::filesystem;


int main(int argc, char** argv)
{

//VARIABLES:
    
    int k = 3;

   importData myData("2");
    
   auto [converted, failed] = myData.dataForProcess(); //Note Creates two vectors of vectors: convertedRecords and failedRecords.
   vector<string> headerData = myData.getheaderRowData();
   vector<vector<string>> identifierColumns = myData.getidentifierCols();
        
        for (const auto& header: headerData) {
        cout << header << endl;
        }

        cout << endl;

        for (const auto& record : identifierColumns) {
            for (const auto& field : record) {
                cout << field << " ";
            }
            cout << " " << endl;
        }
     
        cout << endl;


        cout << "These are the converted records: " << endl;
        for (const auto& record : converted) {
            for (const auto& field : record) {
                cout << field << " ";
            }
            cout << " " << endl;
        }
        cout << "These are the failed records: " << endl;
        for (const auto& record : failed) {
            for (const auto& field : record) {
                cout << field << " ";
            }
            cout << " " << endl;
        }

        //TEST CLUSTER COORDINATES
        clusters cluster(converted);

        cout << " " << endl;

       //Test Minimum Values:

        clusters::clusters(converted);
        
        vector<double> minimumValues = cluster.getMinimumValues();
        cout << "These are the minimum Values: " << endl;
        for (const auto& record : minimumValues) {
                cout << record << " ";
        }

        cout << " " << endl;

        vector<double> maximumValues = cluster.getMaximumValues();
        cout << "These are the maximum Values: " << endl;
        for (const auto& record : maximumValues) {
            cout << record << " ";
        }

        cout << " " << endl;
        vector<double> centroidValues = cluster.getcentroidCalculation();
        cout << "The centroid values are: " << endl;
        for (const auto& record : centroidValues) {
            cout << record << " ";
        }
        
//Output File Code:
	return 0;
}
