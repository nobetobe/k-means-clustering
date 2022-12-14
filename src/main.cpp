#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "k-means.h"

#define NUM_DIMS 2

template <int dims>
std::vector<data_point<dims>> csv_to_data(std::string file_name);

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("usage: %s <input-data.csv> <output-data.csv>", argv[0]);
        return 1;
    }

    int num_clusters;

    std::cout << "Enter number of clusters to create: ";
    std::cin >> num_clusters;

    std::vector<data_point<NUM_DIMS>> data = csv_to_data<NUM_DIMS>(argv[1]);

    if (num_clusters <= 0 || num_clusters > data.size()) {
        std::cout << "Invalid input." << std::endl;
        return 1;
    }

    k_means<NUM_DIMS>(num_clusters, data);

    FILE *output = fopen(argv[2], "w");
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < NUM_DIMS; j++) {
            fprintf(output, "%f,", data.at(i).data[j]);
        }
        fprintf(output, "%d\n", data.at(i).group);
    }

    return 0;
}

template <int dims>
std::vector<data_point<dims>> csv_to_data(std::string file_name) {
    std::fstream data_file(file_name, std::ios::in);
    std::vector<data_point<dims>> res;

    std::string curr_line;
    std::string curr_word;
    float temp_val;
    int counter = 0;
    while (std::getline(data_file, curr_line)) {
        res.push_back(data_point<dims>());

        std::stringstream line(curr_line);
        for (int i = 0; std::getline(line, curr_word, ','); i++) {
            temp_val = std::stof(curr_word);
            res.at(counter).data[i] = temp_val;
        }
        counter++;
    }
    return res;
}
