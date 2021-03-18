import matplotlib.pyplot as plt

t = ["Thread 2", "Thread 4", "Thread 8", "Thread 16","Thread 32", "Thread 64", "Thread 128", "Thread 256"]



# GRAFICO VETORES - ALEATORIOS

speedup_10000 = [
    0.334232,
    0.71862,
    0.462978,
    0.075118,
    0.0411277,
    0.0309394,
    0.0333392,
    0.0144625,
]

speedup_100000 = [
    0.256837,
    0.332833,
    0.402095,
    0.191075,
    0.142821,
    0.0778385,
    0.048474,
    0.0268233,
]

speedup_1000000 = [
    0.396807,
    0.320419,
    0.324115,
    0.325186,
    0.282187,
    0.212654,
    0.103954,
    0.0604802,
]

speedup_10000000 = [
    0.606010,
    0.549997,
    0.530902,
    0.571483,
    0.490756,
    0.385208,
    0.199729,
    0.102784,
]

plt.xticks(rotation=25)
plt.ylabel("Speedup", fontsize=14, labelpad=15)
plt.gca().yaxis.grid(True)
plt.box(False)
plt.title("Entrada Aleatória")
plt.plot(t, speedup_10000, "D-", label="10 mil")
plt.plot(t, speedup_100000, "p-", label = "100 mil")
plt.plot(t, speedup_1000000, "o-", label = "1 milhão")
plt.plot(t, speedup_10000000, "s-", label = "10 milhões")
plt.legend(bbox_to_anchor=(0.80, 0.95), loc=2, borderaxespad=0.)
plt.show()



# GRAFICO VETORES - ORDENADOS INVERSAMENTE

speedup_10000 = [
    0.209811,
    0.173675,
    0.064802,
    0.082666,
    0.027292,
    0.022363,
    0.013131,
    0.008679,
]

speedup_100000 = [
    0.246890,
    0.251107,
    0.401007,
    0.114089,
    0.079281,
    0.053047,
    0.036310,
    0.018724,
]

speedup_1000000 = [
    0.244652,
    0.210284,
    0.225149,
    0.221276,
    0.194946,
    0.129579,
    0.067399,
    0.038391,
]

speedup_10000000 = [
    0.259386,
    0.248626,
    0.239372,
    0.240149,
    0.240427,
    0.167790,
    0.089408,
    0.046774,
]

plt.xticks(rotation=25)
plt.ylabel("Speedup", fontsize=14, labelpad=15)
plt.gca().yaxis.grid(True)
plt.box(False)
plt.title("Entrada Inversa")
plt.plot(t, speedup_10000, "D-", label="10 mil")
plt.plot(t, speedup_100000, "p-", label = "100 mil")
plt.plot(t, speedup_1000000, "o-", label = "1 milhão")
plt.plot(t, speedup_10000000, "s-", label = "10 milhões")
plt.legend(bbox_to_anchor=(0.80, 0.95), loc=2, borderaxespad=0.)
plt.show()
