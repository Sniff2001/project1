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
    plt.savefig(name)
    plt.close()

readfile_plot(r"x_vec.txt", r"task2plot.pdf")


#Problem 7
def compare_sol(filename, n_steps):
    plt.figure(figsize=(8,6))

    #exact
    x_exact = np.linspace(0, 1, 1000)
    u_x = 1 - (1-np.exp(-10))*x_exact - np.exp(-10*x_exact)

    #numerical
    for i in range(len(filename)):
        infile = open(filename[i], "r")
        u_val = []
        x_val = []
        for line in infile:
            x, u = line.split()
            x_val.append(float(x))
            u_val.append(float(u))
        u_val = np.array(u_val)
        x_val = np.array(x_val)
        plt.plot(x_val, u_val, label=f"n_step = {n_steps[i]}")

    plt.plot(x_exact, u_x, label="analytical", color="black", linestyle="dotted", linewidth=3)

    plt.legend(fontsize=14, loc="lower left")
    plt.xlabel("x", fontsize=14)
    plt.ylabel("u(x)", fontsize=14)
    plt.loglog()
    plt.xticks(fontsize=14)
    plt.yticks(fontsize=14)
    plt.grid(linestyle="dotted")
    plt.savefig("task7plot.pdf")
    plt.close()

n_steps = [1e1, 1e2, 1e3, 1e6, 1e7]
filenames = ["output_task7_10.txt","output_task7_100.txt","output_task7_1000.txt",
             "output_task7_1000000.txt", "output_task7_10000000.txt"]

compare_sol(filenames, n_steps)


#Problem 8

#Function to plot abs/rel error and the max of the rel error compared to n_step
def absolute_relative_error(filename, n_steps):
    fig, (ax1, ax2) = plt.subplots(1, 2)
    fig.suptitle(f"Absolute/relative error for n_steps = {n_steps}", fontsize=14)
    #relative error max array
    rel_max = np.zeros(len(n_steps))
    #plotting absolute/relative error for each n_step in the same plots
    for i in range(len(filename)):
        x = np.linspace(0.001, 1, int(n_steps[i])+1)
        u_x = 1 - (1 - np.exp(-10)) * x - np.exp(-10 * x)
        infile = open(filename[i], "r")
        v_val = []
        x_val = []
        for line in infile:
            x_i, v = line.split()
            x_val.append(float(x_i))
            v_val.append(float(v))
        v_val = np.array(v_val)
        x_val = np.array(x_val)
        absolute_error = np.abs(u_x - v_val)
        relative_error = np.abs((u_x - v_val)/u_x)
        ax1.plot(x_val, absolute_error, label=f"absolute error (nstep ={n_steps[i]})")
        ax1.legend(fontsize=14)
        ax1.set_xlabel("x_i", fontsize=14)
        ax1.set_ylabel("error", fontsize=14)
        """
        ax1.tick_params(axis="x", labelsize=14)
        ax1.tick_params(axis="y", labelsize=14)
        """
        ax2.plot(x_val, relative_error, label=f"relative error (nstep ={n_steps[i]})")
        ax2.legend(fontsize=14)
        ax2.set_xlabel("x_i", fontsize=14)
        ax2.set_ylabel("error", fontsize=14)
        """
        ax2.tick_params(axis="x", labelsize=14)
        ax2.tick_params(axis="y", labelsize=14)
        """
        # finding maximum relative error
        rel_max[i] = np.max(relative_error[1:-1])
        ax1.loglog()
        ax2.loglog()
    #fig.tight_layout()
    plt.savefig("Task_8ab.pdf")
    plt.show()
#plotting maximum relative error
    plt.plot(n_steps, rel_max, label="maximum relative error")
    plt.legend(fontsize=14)
    plt.xlabel("n_steps", fontsize=14)
    plt.ylabel(r"max($\epsilon_i$)", fontsize=14)
    plt.title("max relative error vs n_steps",fontsize=16)
    plt.loglog()
    plt.savefig("Task_8c.pdf")
    plt.show()
absolute_relative_error(filenames, n_steps)


