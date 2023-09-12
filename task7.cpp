#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <omp.h>

#pragma

// remember to add .txt to the end of filename
int runTask7(std::vector<double> a, std::vector<double> b, std::vector<double> c, int n_steps, std::string filename) {

	/*  In a completely general algorithm the boundary conditions should also be
	inputs. They are assumed to be u(0) = u(1) = 0 here. As the boundary conditions 
	are stated before the algorithms are mentioned, we have assumed that the general 
	algorithm is general due to the arbitrary tridiagonal matrix, not due to 
	arbitrary boundary conditions. */
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
	// The first value is set to zero, as it is not in use. This is done
	// to ensure that the indices match with the algorithm described in the pdf.
	std::vector<double> b_tilde = { 0., b[1] };
	std::vector<double> g_tilde = { 0., g[1] };

	// forward for loop to calculate the primes' indices
	// note that the loop starts from the second value, as
	// b_tilde[1] and g_tilde[1] is found separately (above).

#pragma omp parallel for
	for (int i = 2; i < n_steps; i++) {
		double frac_i = a[i] / (b_tilde[i - 1]);
		b_tilde.push_back(b[i] - frac_i * c[i-1]);
		g_tilde.push_back(g[i] - frac_i * g_tilde[i - 1]);
	}

	// backward for loop to calculate each index of v
	// note that the loop starts at the third to last value, 
	// as the second to last value is found separately.

	v[n_steps - 1] = g_tilde[n_steps - 1] / b_tilde[n_steps - 1];

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
