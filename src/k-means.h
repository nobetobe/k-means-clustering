#pragma once

#include <vector>
#include <cmath>
#include <unordered_set>
#include <time.h>

#include "data_point.h"

template <int pt_dims>
float calc_distance(data_point<pt_dims> p1, data_point<pt_dims> p2) {
    float sum = 0;
    for (int i = 0; i < pt_dims; i++) {
        sum += powf(p1.data[i]-p2.data[i], 2);
    }
    return sqrtf(sum);
}

template <int pt_dims>
bool clusters_equal(std::vector<data_point<pt_dims>> a, std::vector<data_point<pt_dims>> b) {
    if (a.size() != b.size())
        return false;

    bool ret = true;
    for (int i = 0; i < a.size(); i++) {
        ret = ret && (a.at(i) == b.at(i));
    }
    return ret;
}

template <int pt_dims>
std::vector<data_point<pt_dims>> k_means(int K, std::vector<data_point<pt_dims>> &points) {
    std::unordered_set<int> random_numbers;
    srand((unsigned) time(NULL));
    while (random_numbers.size() < K) {
        random_numbers.insert(rand() % points.size());
    }
    std::vector<int> random_indexes(random_numbers.begin(), random_numbers.end());

    std::vector<data_point<pt_dims>> clusters;
    for (int i = 0; i < K; i++) {
        clusters.emplace_back(data_point<pt_dims>(points.at(random_indexes.at(i)).data));
        clusters.at(i).group = i;
        points.at(random_indexes.at(i)).group = i;
    }

    std::vector<data_point<pt_dims>> prev_clusters;

    while (!(clusters_equal(prev_clusters, clusters))) {
        // calculate groups
        for (int i = 0; i < points.size(); i++) {
            
            float min = calc_distance(points.at(i), clusters.at(0));
            float maybe_new_min;
            int new_cluster = 0;
            for (int j = 1; j < clusters.size(); j++) {
                maybe_new_min = calc_distance(points.at(i), clusters.at(j));
                if (maybe_new_min < min) {
                    min = maybe_new_min;
                    new_cluster = j;
                }
            }
            points.at(i).group = new_cluster;

        }

        // calculate means and new cluster centers;
        prev_clusters = clusters;
        std::vector<int> counts;
        std::vector<data_point<pt_dims>> means;
        for (int i = 0; i < K; i++) {
            counts.push_back(0);
            means.emplace_back(data_point<pt_dims>());
        }
        for (int i = 0; i < points.size(); i++) {
            int curr_cluster = points.at(i).group;
            for (int j = 0; j < pt_dims; j++) {
                means.at(curr_cluster).data[j] += points.at(i).data[j];
            }
            counts.at(curr_cluster)++;
        }
        for (int i = 0; i < means.size(); i++) {
            for (int j = 0; j < pt_dims; j++) {
                means.at(i).data[j] /= counts.at(i);
            }
        }

        
        clusters = means;
    }

    return clusters;
}
