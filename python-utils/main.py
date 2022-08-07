import matplotlib.pyplot as plt
import csv

x = []
y = []

with open('../build/lbs.csv', 'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')

    for row in plots:
        x.append(int(row[0]))
        y.append(int(row[1]))

plt.plot(x, y, color='g', label="Numbers")
plt.ylabel('Time')
plt.xlabel('Elements count')
plt.xscale('log')
plt.title('Sorting')
plt.legend()
plt.show()
