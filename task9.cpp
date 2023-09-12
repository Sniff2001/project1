#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <omp.h>
#include <cmath>

#pragma

// remember to add .txt to the end of filename
int runTask9(std::vector<double> a, std::vector<double> b, std::vector<double> c, int n_steps, std::string filename) {

	/* Special algorithm where matrix A has signature (-1,2,-1), meaning a = -1, b = 2 and c = -1 
	Note that the parameters in the definiton are not used in the actuall algorithm, they were 
	included to make the come more uniform later on */

	double h = 1. / n_steps;

	// Define the solution vectors
	std::vector<double> g(n_steps + 1);
	std::vector<double> v(n_steps + 1);
	std::vector<double> x(n_steps + 1);

	// creating an even number of points between 0 and 1 of n_steps length
	int xsize = x.size();

#pragma omp parallel for
	for (int i = 0; i < xsize; i++) {
		x[i] = i * h;
		g[i] = pow(h, 2.) * 100 * exp(-10 * x[i]);
	}

	// Setting up boundary values
	v[0] = 0.;
	v[n_steps] = 0.;
	std::vector<double> b_tilde = { 0., 2. };
	std::vector<double> g_tilde = { 0., g[1] };

	// forward for loop to calculate the primes' indices

	for (int i = 2; i < n_steps; i++) {
		b_tilde.push_back(2. - 1. / (b_tilde[i - 1]));
		g_tilde.push_back(g[i] + g_tilde[i - 1] / b_tilde[i - 1]);
	}

	// backward for loop to calculate each index of v
	// note that the loop starts at the third to last value, 
	// as the second to last value is found separately.

	v[n_steps - 1] = g_tilde[n_steps - 1] / b_tilde[n_steps - 1];

	for (int i = v.size() - 2; i > 0; i--) {
		v[i] = (g_tilde[i] + v[i + 1]) / b_tilde[i];
	}
	
	//write to data file, same setup as for task 2
	std::ofstream ofile;
	ofile.open(filename);
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
