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
#include <vector>
#include <sstream>
#include <utility>


using namespace std;
namespace fs = std::filesystem;

vector<vector<std::string>> inputFile() {
    //Input File Code:
    vector<vector<string>> returnData;
    std::string folder = "\Data";
    vector<string> records;

    try {
        for (const auto& entry : fs::directory_iterator(folder)) {
            if (entry.is_regular_file()) {  // skip directories, symlinks, etc.
                std::string filename = entry.path().string();
                std::cout << "Reading file: " << filename << std::endl;

                std::ifstream file(filename);
                if (!file) {
                    std::cerr << "Could not open file: " << filename << std::endl;
                    continue;
                }

                std::string line;
                while (std::getline(file, line)) {
                    //std::cout << line << std::endl; // process line as needed
                    records.push_back(line);
                }
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    //Push individual records into the vector of vectors.
    for (const auto& record : records) {
        std::stringstream ss(record);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        returnData.push_back(tokens);
    }

    return returnData;
};

vector<string> headerRow(vector<vector<string>> *rawData) {
    vector<string> headerRow = rawData->front();
    if (!rawData->empty()) {
        rawData->erase(rawData->begin());
    }

    return headerRow;
};


vector<vector<string>> identifierColumns(vector<vector<string>>& rawData, string nbrOfColumns) {
    vector<vector<string>> identiferColumns;

    int nCols = stoi(nbrOfColumns);

    for (auto& row : rawData) {  // non-const reference so we can modify
        vector<string> rowAdd;

        // Only loop up to the smaller of nCols or row.size()
        for (int i = 0; i < nCols && i < (int)row.size(); i++) {
            rowAdd.push_back(row[i]);
        }

        // Erase those first nCols elements from the row
        if ((int)row.size() > 0) {
            row.erase(row.begin(), row.begin() + min(nCols, (int)row.size()));
        }

        identiferColumns.push_back(rowAdd);
    }

    return identiferColumns;
}

std::pair<std::vector<std::vector<double>>*, std::vector<std::vector<std::string>>*>
dataForProcess(std::vector<std::vector<std::string>>& rawData) {
    auto* convertedRecords = new std::vector<std::vector<double>>();
    auto* failedRecords = new std::vector<std::vector<std::string>>();

    for (const auto& rawDataRecord : rawData) {
        std::vector<double> convertedRow;
        bool rowFailed = false;

        for (const auto& value : rawDataRecord) {
            try {
                size_t sizeValue;
                double val = std::stod(value, &sizeValue);

                if (sizeValue == value.size()) {
                    convertedRow.push_back(val);
                }
                else {
                    rowFailed = true;  // partial parse
                    break;
                }
            }
            catch (const std::exception&) {
                rowFailed = true;      // conversion failed
                break;
            }
        }

        if (rowFailed) {
            failedRecords->push_back(rawDataRecord);   // keep full original row
        }
        else {
            convertedRecords->push_back(convertedRow); // keep fully converted row
        }
    }
    return { convertedRecords, failedRecords };
}


int main(int argc, char** argv)
{

//VARIABLES:
    string nbrOfColumbs = "2";
    int k = 3;

    vector<vector<string>>* rawData = new vector<vector<string>>(inputFile()); //Raw Data
    vector<string> headerRowData = headerRow(rawData);
    vector<vector<string>> identifierColumnsData = identifierColumns(*rawData, nbrOfColumbs);
    //NEXT STEP, PROCESS THE DATA FOR ANALYSIS, EXPORT EACH RECORD TO ANOTHER FILE THAT DOES NOT PASS THE CONVERSION.
    auto [converted, failed] = dataForProcess(*rawData); //Note Creates two vectors of vectors: convertedRecords and failedRecords.
    

        for (const auto& header: headerRowData) {
        cout << header << endl;
        }

        cout << endl;

        for (const auto& record : *rawData) {
            for (const auto& field : record) {
                cout << field << " ";
            }
            cout << " " << endl;
        }

        cout << endl;

        for (const auto& record : identifierColumnsData) {
            for (const auto& field : record) {
                cout << field << " ";
            }
            cout << " " << endl;
        }

        cout << endl;
        cout << "These are the converted records: " << endl;
        for (const auto& record : *converted) {
            for (const auto& field : record) {
                cout << field << " ";
            }
            cout << " " << endl;
        }
        cout << "These are the failed records: " << endl;
        for (const auto& record : *failed) {
            for (const auto& field : record) {
                cout << field << " ";
            }
            cout << " " << endl;
        }

        //TEST CLUSTER COORDINATES
        vector<double> *testCoordinates = new vector<double>();
        *testCoordinates = { 1,2,3,4,5,6,7,8,9,10};

        //Code builds the clusters:
        for (int i = 0; i < k; i++) {
            clusters clusters(i+1, *testCoordinates);
        }

        cout << " " << endl;

       //Test Minimum Values:

        clusters::clusters(*converted);
        
        vector<double> minimumValues = clusters::getMinimumValues();
        cout << "These are the minimum Values: " << endl;
        for (const auto& record : minimumValues) {
                cout << record << " ";
        }

        cout << " " << endl;

        vector<double> maximumValues = clusters::getMaximumValues();
        cout << "These are the maximum Values: " << endl;
        for (const auto& record : maximumValues) {
            cout << record << " ";
        }

        delete rawData;
        delete converted;
        delete failed;
        delete testCoordinates;
        
//Output File Code:
	return 0;
}
