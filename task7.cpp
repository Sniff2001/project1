#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <numeric>
#include <omp.h>

#pragma

// remember to add .txt to the end of filename
int runTask7(std::vector<double> a, std::vector<double> b, std::vector<double> c, int n_steps, std::string filename) {
	// x_max - x_min = 1 - 0 = 1
	double h = 1./n_steps;

	double g0 = std::pow(h, 2.0) * 100 * exp(-10 * 0);

	// Define the solution vectors
	std::vector<double> g(n_steps + 1);
	std::vector<double> v(n_steps + 1);
	std::vector<double> x(n_steps + 1);

	// creating an even number of points between 0 and 1 of n_steps length
	x[0] = 0;
	int xsize = x.size();

#pragma omp parallel for
	for (int i = 1; i < xsize; i++) {
		x[i] = i * h;
		g[i] = std::pow(h, 2.0) * 100 * exp(-10 * x[i]);
	}

	// Setting up boundary values
	v[0] = 0;
	v[n_steps-1] = 0;
	std::vector<double> b_tilde = { 2 };
	std::vector<double> g_tilde = { g0 };

	// gaussian elim here


#pragma omp parallel for
	// forward for loop to calculate the primes' indices
	for (int i = 1; i < n_steps; i++) {
		double frac_i = a[i] / (b_tilde[i - 1]);
		b_tilde.push_back(b[i] - frac_i * c[i-1]);
		g_tilde.push_back(g[i] - frac_i * g_tilde[i - 1]);
	}


	// backward for loop to calculate each index of v

#pragma omp parallel for
	for (int i = v.size() - 2; i > 0; i--) {
		v[i] = (g_tilde[i] - (v[i + 1] * c[i])) / b_tilde[i];
	}
	
	//write to data file, same setup as for task 2
	std::ofstream ofile;
	ofile.open(filename);
	std::vector<double> v1(n_steps);
	int width = 15;
	int prec = 7;

#pragma omp parallel for
	for (int i = 0; i < xsize; i++)
	{
		ofile << std::setw(width) << std::setprecision(prec) << std::scientific << x[i]
			<< std::setw(width) << std::setprecision(prec) << std::scientific << v[i]
			<< "\n";
	}
	ofile.close();
	return 0;
}
