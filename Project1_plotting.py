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

n_steps = [1e1, 1e2, 1e3, 1e6, 1e7]
# exp of the number of steps, for formatting purposes in legend()
n_exp = np.log10(np.array(n_steps))
filenames = ["output_task7_10.txt","output_task7_100.txt","output_task7_1000.txt",
             "output_task7_1000000.txt", "output_task7_10000000.txt"]

def compare_sol(filename, n_steps):
    fig, (ax1, ax2) = plt.subplots(1, 2)
    fig.set_size_inches(14,6)

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
        ax1.plot(x_val, u_val, label=r"$n_{step}$ = " + fr"$10^{np.int_(n_exp[i])}$")
        ax2.plot(x_val, u_val, label=r"$n_{step}$ = " + fr"$10^{np.int_(n_exp[i])}$")

    #analytical
    x_exact = np.linspace(0, 1, 1000)
    u_x = 1 - (1-np.exp(-10))*x_exact - np.exp(-10*x_exact)
    ax1.plot(x_exact, u_x, label="analytical", color="black", linestyle="dotted", linewidth=3)
    ax2.plot(x_exact, u_x, label="analytical", color="black", linestyle="dotted", linewidth=3)

    ax1.legend(fontsize=14, loc="upper right")
    ax1.set_xlabel("x", fontsize=14)
    ax1.set_ylabel("u(x)", fontsize=14)
    ax1.grid(linestyle="dotted")
    ax1.set_title("Regular plot", fontsize=16)

    ax2.legend(fontsize=14, loc="lower center")
    ax2.set_xlabel("x", fontsize=14)
    ax2.set_ylabel("u(x)", fontsize=14)
    ax2.grid(linestyle="dotted")
    ax2.set_title("LogLog plot", fontsize=16)
    ax2.loglog()

    plt.savefig("task7plot.pdf")
    plt.close()

compare_sol(filenames, n_steps)


#Problem 8

def absolute_relative_error(filename, n_steps):
    #Function to plot abs/rel error and the max of the rel error compared to n_step

    fig, (ax1, ax2) = plt.subplots(1, 2)
    fig.set_size_inches(14,6)
    fig.suptitle(f"Error comparison", fontsize=16)

    #relative error max array
    rel_max = np.zeros(len(n_steps))

    #plotting absolute/relative error for each n_step in the same plots
    for i in range(len(filename)):
        x = np.linspace(0, 1, int(n_steps[i])+1)
        # analytic values of u(x)
        u_x = 1 - (1 - np.exp(-10)) * x - np.exp(-10 * x)
        # redefine array to exclude the known boundary points u(0) = u(1) = 0
        u_x = u_x[1:-1]
        # extract v(x) values from .txt file
        infile = open(filename[i], "r")
        v_val = []
        x_val = []
        for line in infile:
            x_i, v = line.split()
            x_val.append(float(x_i))
            v_val.append(float(v))
        # turn lists into arrays
        v_val = np.array(v_val)
        x_val = np.array(x_val)
        # redefine arrays to exclude the known boundary points u(0) = u(1) = 0
        v_val = v_val[1:-1]
        x_val = x_val[1:-1]
        # find log10 of abs/rel error
        abs_error =  np.abs(u_x - v_val) 
        rel_error =  np.abs((u_x - v_val)/u_x) 

        ax1.plot(x_val, abs_error, label=r"$n_{step}$ = " + fr"$10^{np.int_(n_exp[i])}$")
        ax1.legend(fontsize=14, loc="lower center")
        ax1.set_xlabel("x", fontsize=14)
        ax1.set_ylabel(r"absolute error $\Delta$", fontsize=14)
        ax1.set_yscale("log")
        ax1.grid(linestyle="dotted")
    
        ax2.plot(x_val, rel_error, label=r"$n_{step}$ = " + fr"$10^{np.int_(n_exp[i])}$")
        ax2.legend(fontsize=14, loc="lower center")
        ax2.set_xlabel("x", fontsize=14)
        ax2.set_ylabel(r"relative error $\epsilon$", fontsize=14)
        ax2.set_yscale("log")
        ax2.grid(linestyle="dotted")
    
        # finding maximum relative error
        rel_max[i] = np.max(rel_error)
        # write out maximum relative error data
        print(f"rel_max {n_steps[i]:10.0f}:  {rel_max[i]:15.6g}")
    
    #fig.tight_layout()
    plt.savefig("Task_8ab.pdf")
    plt.close()

    #plotting maximum relative error
    plt.plot(n_steps, rel_max)
    plt.scatter(n_steps, rel_max, marker="x", color = "black", label="data points")
    plt.legend(fontsize=14)
    plt.xlabel(r"$n_{steps}$", fontsize=14)
    plt.ylabel(r"max($\epsilon$)", fontsize=14)
    plt.loglog()
    plt.title(r"Maximum relative error vs. $n_{steps}$",fontsize=16)
    plt.grid(linestyle="dotted")
    plt.savefig("Task_8c.pdf")
    plt.close()


absolute_relative_error(filenames, n_steps)

#Problem 10

#benchmark times from terminal
timeTask7 = [0.000170869, 0.000212493, 0.00195841, 0.613911] # [s]
timeTask9 = [0.000517247, 0.000624843, 0.00159843, 0.545412] # [s]
n_steps_limited = n_steps[:-1]                               # we omit 10^7 in task 10
plt.figure(figsize=(10,5))
plt.plot(n_steps_limited, timeTask7, label="general algorithm")
plt.plot(n_steps_limited, timeTask9, label="special algorithm")
plt.legend(fontsize=14, loc="lower center")
plt.xlabel(r"$n_{steps}$", fontsize=14)
plt.ylabel("time [s]", fontsize=14)
plt.xticks(fontsize=14)
plt.yticks(fontsize=14)
plt.loglog()
plt.title(r"Benchmarking at different n$_{steps}$ for the general and special algorithm", fontsize=16)
plt.grid(linestyle="dotted")
plt.savefig("Task_9.pdf")
plt.close()