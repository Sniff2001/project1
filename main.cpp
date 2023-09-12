#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include <functional>
#include "taskheader.h"

int main(int argc, char* argv[]) {
    runTask2();

    std::vector<int> n_steps = { 10, 100, 1000, 1000000, 10000000};

    // Task 10 file of benchmarks
    std::string benchmark = "benchmark.txt";

    std::ofstream ofile10;
	ofile10.open(benchmark);
	int width = 15;
	int prec = 7;

    for (int i = 0; i < n_steps.size(); i++) {

        // Define the tridiagonal
        std::vector<double> a(n_steps[i], -1);
        std::vector<double> b(n_steps[i] + 1, 2);
        std::vector<double> c(n_steps[i], -1);

        // in order to match the indices with the indices shown in the pdf algorithm
        a[0] = 0;
        b[0] = 0;
        c[0] = 0;

        std::string output_file_name7 = "output_task7_" + std::to_string(n_steps[i]) + ".txt";
        runTask7(a, b, c, n_steps[i], output_file_name7);

        std::string output_file_name9 = "output_task9_" + std::to_string(n_steps[i]) + ".txt";
        runTask9(a, b, c, n_steps[i], output_file_name9);

        // we do not wish to include n_steps = 10^7 in task 10
        if (n_steps[i] <= 1000000) {

            double avg_time7 = runTask10(runTask7, a, b, c, n_steps[i], "test_output.txt", 100);
            std::cout << n_steps[i] << " steps time task 7: " << avg_time7 << " s" << std::endl;

            double avg_time9 = runTask10(runTask9, a, b, c, n_steps[i], "test_output.txt", 100);
            std::cout << n_steps[i] << " steps time task 9: " << avg_time9 << " s" << std::endl;

            // write into benchmark.txt

            ofile10 << std::setw(width) << std::setprecision(prec) << std::scientific << n_steps[i]
            << std::setw(width) << std::setprecision(prec) << std::scientific << avg_time7
			<< std::setw(width) << std::setprecision(prec) << std::scientific << avg_time9
			<< "\n";
        }
        
    }
    
    ofile10.close();

    // All is well. Exit program with return code 0.
    return 0;
}
