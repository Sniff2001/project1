#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <functional>
#include "taskheader.h"

int main(int argc, char* argv[]) {
    runTask2();

    std::vector<int> n_steps = { 10, 100, 1000, 1000000, 10000000};

    for (int i = 0; i < n_steps.size(); i++) {

        // Define the tridiagonal
        std::vector<double> a(n_steps[i], -1);
        std::vector<double> b(n_steps[i] + 1, 2);
        std::vector<double> c(n_steps[i], -1);

        a[0] = 0;
        b[0] = 0;
        c[0] = 0;

        std::string output_file_name = "output_task7_" + std::to_string(n_steps[i]) + ".txt";
        runTask7(a, b, c, n_steps[i], output_file_name);
     
        double avg_time = runTask10(runTask7, a, b, c, n_steps[i], "test_output.txt", 100);

        std::cout << n_steps[i] << " steps time: " << avg_time << " s" << std::endl;

    }
    
    // All is well. Exit program with return code 0.
    return 0;
}
