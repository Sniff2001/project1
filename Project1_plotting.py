import matplotlib.pyplot as plt
import numpy as np
#Problem 2
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

#Problem 7
def compare_sol(filename):
    #exact
    x = np.linspace(0, 1, 1000)
    u_x = 1 - (1-np.exp(-10))*x - np.exp(-10*x)
    #numerical
    infile = open(filename, "r")
    u_val = []
    x_val = []
    for line in infile:
        x, u = line.split()
        x_val.append(float(x))
        u_val.append(float(u))
    plt.plot(x, u_x, label="exact")

#Problem 8
#"""
def absolute_relative_error(u_i, v_i, x_i, n_steps):
    absolute_error = np.abs(u_i - v_i)
    relative_error = np.abs((u_i - v_i)/u_i)
    fig, (ax1, ax2) = plt.subplot(1, 2)
    fig.suptitle(f"Absolte/relative error for n_steps = {n_steps}")
    ax1.plot(x_i, np.log(absolute_error), label="absolute error")
    ax1.legend()
    ax1.setxlabel("x_i")
    ax1.setylabel("error")
    ax2.plot(x_i, np.log(relative_error), label="relative error")
    ax2.legend()
    ax2.setxlabel("x_i")
    ax2.setylabel("error")
    fig.tight_layout()
    plt.show()
#absolute_relative_error(u_i, v_i, x_i, n_steps)
#"""

