#include <iostream>
#include <vector>
#include <functional>
#include <chrono>

double runTask10(std::function<int(std::vector<double>, std::vector<double>, std::vector<double>, int, std::string)> func, std::vector<double> a, std::vector<double> b, std::vector<double> c, int n_steps, std::string filename, int times = 10) {
    double sum = 0;

    for (int i = 0; i < times; i++) {
        auto t1 = std::chrono::high_resolution_clock::now();

        func(a, b, c, n_steps, filename);

        auto t2 = std::chrono::high_resolution_clock::now();
        sum += std::chrono::duration<double>(t2 - t1).count();
    }

    double average_time = sum / times;

    return average_time;
}