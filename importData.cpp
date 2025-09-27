#include "importData.h"

importData::importData(std::string nbrOfColumbs) {
    this->nbrOfColumbsIdColumns = nbrOfColumbs;
    rawData = inputFile();                                // call function, store result
    headerRowData = headerRow(&rawData);                  // extract header
    identifierCols = identifierColumns(rawData, nbrOfColumbsIdColumns);
}

// Read all files from Data folder
std::vector<std::vector<std::string>> importData::inputFile() {
    std::vector<std::vector<std::string>> returnData;
    std::string folder = "Data";   // FIXED path
    std::vector<std::string> records;

    try {
        for (const auto& entry : fs::directory_iterator(folder)) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().string();
                std::cout << "Reading file: " << filename << std::endl;

                std::ifstream file(filename);
                if (!file) {
                    std::cerr << "Could not open file: " << filename << std::endl;
                    continue;
                }

                std::string line;
                while (std::getline(file, line)) {
                    records.push_back(line);
                }
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

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
}

// Separate header row
std::vector<std::string> importData::headerRow(std::vector<std::vector<std::string>>* rawData) {
    if (rawData->empty()) return {};
    std::vector<std::string> headerRow = rawData->front();
    rawData->erase(rawData->begin()); // remove first row
    return headerRow;
}

// Extract identifier columns
std::vector<std::vector<std::string>> importData::identifierColumns(
    std::vector<std::vector<std::string>>& rawData,
    std::string nbrOfColumns
) {
    std::vector<std::vector<std::string>> identiferColumns;
    int nCols = std::stoi(nbrOfColumns);

    for (auto& row : rawData) {
        std::vector<std::string> rowAdd;

        for (int i = 0; i < nCols && i < (int)row.size(); i++) {
            rowAdd.push_back(row[i]);
        }

        if (!row.empty()) {
            row.erase(row.begin(), row.begin() + std::min(nCols, (int)row.size()));
        }

        identiferColumns.push_back(rowAdd);
    }

    return identiferColumns;
}

// Convert raw data to doubles (good + failed)
std::pair<std::vector<std::vector<double>>, std::vector<std::vector<std::string>>> importData::dataForProcess() {
    std::vector<std::vector<double>> convertedRecords;
    std::vector<std::vector<std::string>> failedRecords;

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
                rowFailed = true;
                break;
            }
        }

        if (rowFailed) {
            failedRecords.push_back(rawDataRecord);
        }
        else {
            convertedRecords.push_back(convertedRow);
        }
    }
    return { convertedRecords, failedRecords };
}

std::vector<std::string> importData::getheaderRowData() {
    return this->headerRowData;
};

//Return the identifier columns
std::vector<std::vector<std::string>> importData::getidentifierCols() {
    return this->identifierCols;
};