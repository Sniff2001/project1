#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <omp.h>

#pragma

std::vector<double> u(std::vector<double> x) {
    std::vector<double> new_vec(x.size());
    for (int i = 0; i < x.size(); i++) {
        new_vec[i] = 1. - (1. - exp(-10.)) * x[i] - exp(-10. * x[i]);
    }
    return new_vec;
}

int runTask2() {
    // Set a filename
    std::string filename = "x_vec.txt";

    /* Create and open the output file. Or, technically, create
    an "output file stream" (type std::ofstream) and connect it to our filename. */
    std::ofstream ofile;
    ofile.open(filename);

    // Starting and ending value
    double x_min = 0.0;
    double x_max = 1.0;
    // Number of steps
    int n_steps = 101;
    double h = x_max / (n_steps-1);

    // Initialising the vector
    // First declare the size of the vector to be n_steps
    std::vector<double> x(n_steps);

#pragma omp parallel for
    for (int i = 0; i < n_steps; i++) 
    {
        x[i] = x[0] + h * i;
    }

    // Print the vector to make sure the next for loop won't run into problems

    //for (int i = 0; i < n_steps; i++) {
    //    std::cout << x.at(i) << " ";
    //}

    // Some width and precision parameters we will use to format the output
    int width = 12;
    int prec = 4;

    // Initialize the values of u(x) using v1, which is a vector of x-values
    std::vector<double> y = u(x);

    // Loop over steps

#pragma omp parallel for
    for (int i = 0; i < n_steps; i++)
    {
        // Write a line with the current x and y values (nicely formatted) to file
        ofile << std::setw(width) << std::setprecision(prec) << std::scientific << x[i]
            << std::setw(width) << std::setprecision(prec) << std::scientific << y[i]
            << std::endl;
    }

    // Close the output file
    ofile.close();

    return 0;
}

