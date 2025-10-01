#ifndef IMPORTDATA_H
#define IMPORTDATA_H
#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>

namespace fs = std::filesystem;

// This will be the ImportData class used to get the data.
class importData {
private:
    std::string nbrOfColumbsIdColumns;

    std::vector<std::vector<std::string>> rawData;        // Raw Data
    std::vector<std::string> headerRowData;               // Header Row
    std::vector<std::vector<std::string>> identifierCols; // Identifier Columns

    // Helper functions
    std::vector<std::vector<std::string>> inputFile();
    std::vector<std::string> headerRow(std::vector<std::vector<std::string>>* rawData);
    std::vector<std::vector<std::string>> identifierColumns(std::vector<std::vector<std::string>>& rawData,std::string nbrOfColumns
    );

public:
    // Constructor
    explicit importData(std::string nbrOfColumbs);

    // Convert raw string data to numeric + failed rows
    std::pair<std::vector<std::vector<double>>, std::vector<std::vector<std::string>>> dataForProcess();

    //Return the header row
    std::vector<std::string> getheaderRowData();

    //Return the identifier columns
    std::vector<std::vector<std::string>> getidentifierCols();


};

#endif