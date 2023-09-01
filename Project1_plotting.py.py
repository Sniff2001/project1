import matplotlib.pyplot as plt
import numpy as np
#Problem 2 and 7
def readfile_plot(filename, name):
    infile = open(filename, "r")
    y_val = []
    x_val = []
    for line in infile:
        x, y = line.split()
        x_val.append(float(x))
        y_val.append(float(y))
    infile.close()
    plt.plot(x_val, y_val, label="u(x)")
    plt.legend()
    plt.xlabel("x")
    plt.ylabel("u(x)")
    plt.grid()
    plt.title("u(x)")
    plt.show()
    plt.savefig(name)
readfile_plot(r"*/x_vec.txt", r"x_vec_plot.png")
#readfile_plot( , "")
#Problem 8
"""
def absolute_relative_error(u_i, v_i, x_i):
    #absolute error
    #relative error
"""

