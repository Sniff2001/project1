#pragma once
int runTask2();
int runTask7(std::vector<double> a, std::vector<double> b, std::vector<double> c, int n_steps, std::string filename);
int runTask9(int n_steps, std::string filename);
double runTask10(std::function<int(std::vector<double>, std::vector<double>, std::vector<double>, int, std::string)> func, std::vector<double> a, std::vector<double> b, std::vector<double> c, int n_steps, std::string filename, int times = 10);