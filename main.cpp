//this is the file for task 2
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <numeric>

std::vector<double> u(std::vector<double> x) {
    std::vector<double> new_vec(x.size());
    for (int i = 0; i < x.size(); i++) {
        new_vec[i] = 1 - (1 - exp(-10)) * x[i] - exp(-10 * x[i]);
    }
    return new_vec;
}

int main() {

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
    int n_steps = 10;

    // Initialising the vector
    // First declare the size of the vector to be n_steps
    std::vector<double> v1(n_steps);
    // iota lets us make a vector with consecutive numbers
    std::iota(v1.begin(), v1.end(), 1);
    
    // Print the vector to make sure the next for loop won't run into problems
    for (int i = 0; i < n_steps; i++) {
        std::cout << v1.at(i) << " ";
    }

    // Some width and precision parameters we will use to format the output
    int width = 12;
    int prec = 4;

    // Initialize the values of u(x) using v1, which is a vector of x-values
    std::vector<double> y = u(v1);

    // Loop over steps
    for (int i = 0; i < n_steps; i++)
    {
        // Write a line with the current x and y values (nicely formatted) to file
        ofile << std::setw(width) << std::setprecision(prec) << std::scientific << v1[i]
            << std::setw(width) << std::setprecision(prec) << std::scientific << y[i]
            << std::endl;
    }

    // Close the output file
    ofile.close();

    // All is well. Exit program with return code 0.
    return 0;
}

/* Write a program that defines a vector of 
values, evaluates the exact solution
above for these points, and outputs the and
values as two columns in a data file.The numbers 
should be written to file in scientific notation 
and with a fixed number of decimals. (Choose a sensible number.) 
*/