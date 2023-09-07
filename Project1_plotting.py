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
    plt.legend(fontsize=14)
    plt.xlabel("x", fontsize=14)
    plt.ylabel("u(x)", fontsize=14)
    plt.xticks(fontsize=14)
    plt.yticks(fontsize=14)
    plt.grid(linestyle="dotted")
    plt.title("u(x)", fontsize=16)
    plt.savefig(name)
    plt.show()
readfile_plot(r"x_vec.txt", r"x_vec_plot.png")

#Problem 7
def compare_sol(filename):
    #exact
    x = np.linspace(0, 1, 1000)
    u_x = 1 - (1-np.exp(-10))*x - np.exp(-10*x)
    #numerical
    for i in range(len(filename)):
        infile = open(filename[i], "r")
        u_val = []
        x_val = []
        for line in infile:
            x, u = line.split()
            x_val.append(float(x))
            u_val.append(float(u))
        plt.plot(x_val, u_val, label=f"{filename[i]}")
    plt.plot(x, u_x, label="exact")
    plt.legend(fontsize=14)
    plt.xlabel("x", fontsize=14)
    plt.ylabel("u(x)", fontsize=14)
    plt.xticks(fontsize=14)
    plt.yticks(fontsize=14)
    plt.grid(linestyle="dotted")
    plt.title("u(x)", fontsize=16)
    plt.savefig("Comparison numerical and exact solutions")
    plt.show()
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

