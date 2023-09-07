#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <numeric>

// remember to add .txt to the end of filename
int runTask7(std::vector<double> a, std::vector<double> b, std::vector<double> c, int n_steps, std::string filename) {
	// x_max - x_min = 1 - 0 = 1
	double h = 1./n_steps;

	double g0 = std::pow(h, 2.0) * 100 * exp(-10 * 0);
	double gn = std::pow(h, 2.0) * 100 * exp(-10 * 1);

	// Define the solution vectors
	std::vector<double> v(n_steps + 1);
	std::vector<double> x(n_steps + 1);

	// creating an even number of points between 0 and 1 of n_steps length
	//std::iota(x.begin(), x.end(), h);
	x[0] = 0;
	for (int i = 1; i < x.size(); i++) {
		x[i] = i * h;
	}

	// Setting up boundary values
	v[0] = 0;
	v[n_steps-1] = 0;
	std::vector<double> bi_tilde = { 2 };
	std::vector<double> gi_tilde = { g0 };

	// gaussian elim here

	// forward for loop to calculate the primes' indices
	for (int i = 1; i < n_steps; i++) {
		double frac_i = a[i] / (bi_tilde[i - 1]);
		bi_tilde.push_back((b[i] - frac_i) * c[i-1]);
		double gi = std::pow(h, 2.0) * 100 * exp(-10 * x[i]);
		gi_tilde.push_back((gi - frac_i) * gi_tilde[i - 1]);
	}

	// backward for loop to calculate each index of v
	for (int i = v.size() - 1; i >= 0; i--) {
		v[i] = (gi_tilde[i] - (v[i + 1] * b[i])) / bi_tilde[i];
	}
	
	//write to data file, same setup as for task 2
	std::ofstream ofile;
	ofile.open(filename);
	std::vector<double> v1(n_steps);
	int width = 12;
	int prec = 4;
	for (int i = 0; i < x.size(); i++)
	{
		ofile << std::setw(width) << std::setprecision(prec) << std::scientific << x[i]
			<< std::setw(width) << std::setprecision(prec) << std::scientific << v[i]
			<< std::endl;
	}
	ofile.close();

	return 0;
}
