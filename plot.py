from matplotlib import pyplot as plt
import numpy as np
import statistics

xcor = []
ycor = []
i = 0
with open("test.txt", "r") as file2:
    count = 0
    for point in file2.readlines():
        count += 1
        if count % 10 == 0:
            ycor.append(float(point[:-1]))
            xcor.append(i)
            i += 1

# set axes limits
# axes = plt.gca()
# axes.set_xlim([0,100])
# axes.set_ylim([-1000,0])

plt.ylim(-1000,0)
# plt.plot(X,Y,color="black",linewidth=0.7)
# plt.plot(X,Y,'b.',linewidth=0.5)
# print(ycor)

plt.xlabel('Time', fontsize=16)
plt.ylabel('Total Energy', fontsize=16)
percentError = statistics.stdev(ycor)/statistics.mean(ycor)
print(percentError)
plt.scatter(xcor, ycor, color="red",linewidth=0.5,marker='.')
plt.show()