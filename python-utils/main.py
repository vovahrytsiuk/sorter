import matplotlib.pyplot as plt
import csv

x = []
y = []

with open('../build/array.csv', 'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')

    for row in plots:
        x.append(int(row[0]))
        y.append(int(row[1]))

plt.bar(x, y, color='g', width=0.72, label="Numbers")
plt.ylabel('Numbers')
plt.title('AArray')
plt.legend()
plt.show()
