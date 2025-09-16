/*
K - means_Clustering.cpp : Defines the entry point for the application.

Author: Christopher Sefcik

Program Use: Optimized version of K-means Clustering

Development Notes:

How to run program:

*/ 

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include "K-means_Clustering.h"

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char** argv)
{

//Input File Code:
    std::string folder = "\Data";

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
                    std::cout << line << std::endl; // process line as needed
                }
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }



//Output File Code:
	return 0;
}
