import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

var01_file = "../PROB01_TRANSPOSE/result_bench_op2_var01.csv"
var02_file = "../PROB01_TRANSPOSE/result_bench_op2_var02.csv"
var03_file = "../PROB01_TRANSPOSE/result_bench_op2_var03.csv"

# Generate data frame

vars = []

for filename in [var01_file, var02_file, var03_file]:
    data = pd.read_csv(filename)
    data = data[data.index % 16 != 15]
    data = data.rename(columns=lambda x: x.strip())

    data["m"] = data["m"].astype(int)
    data["n"] = data["n"].astype(int)
    data["rs_src"] = data["rs_src"].astype(int)
    data["cs_src"] = data["cs_src"].astype(int)
    data["rs_dst"] = data["rs_dst"].astype(int)
    data["cs_dst"] = data["cs_dst"].astype(int)

    data["GB_per_s"] = data["GB_per_s"].astype(float)

    root_average_size = [np.sqrt(a * b) for a, b in zip(data["m"], data["n"])]

    data.insert(7, "root_average_size", root_average_size, True)

    vars.append(data)


# Plot 1

for idx, variant in enumerate(vars):

    var_num = idx + 1

    for i in range(1, 8):  # Plot each case (1-7)

        case_num = i

        x = vars[idx]["root_average_size"].iloc[16 * (case_num - 1) : 16 * case_num]
        y = vars[idx]["GB_per_s"].iloc[16 * (case_num - 1) : 16 * case_num]

        plt.scatter(x, y, label=("Test " + str(case_num)))

        m, b = np.polyfit(x, y, 1)
        plt.plot(x, m * x + b)

    overall_x = vars[idx]["root_average_size"]
    overall_y = vars[idx]["GB_per_s"]
    m, b = np.polyfit(overall_x, overall_y, 1)
    plt.plot(overall_x, m * overall_y + b)

    plt.xlabel("Root Number of elements in Matrix")
    plt.ylabel("GB per s")
    plt.legend()
    title = "Variant " + str(var_num) + " Performance"
    plt.title(title)
    plt.savefig("Plot_" + title + ".png")
    plt.close()

# Plot 2

xs = []
ys = []

for idx, variant in enumerate(vars):
    var_num = idx + 1
    y = np.mean(vars[idx]["GB_per_s"])

    xs.append("Variant " + str(var_num))
    ys.append(y)

plt.bar(xs, ys)
plt.xticks(ticks=xs, labels=["var01", "var02", "var03"])

plt.xlabel("Variant")
plt.ylabel("GB per s")
plt.title("Per-Variant Performance")
plt.savefig("Plot_Overall Performance.png")
