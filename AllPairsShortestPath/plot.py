
import matplotlib.pyplot as plt
import csv
  
x = []
  
# plt.plot(x, y, color = 'g', linestyle = 'dashed',
#          marker = 'o',label = "Weather Data")

with open('bench.csv','r') as csvfile:
    lines = csv.reader(csvfile, delimiter=',')
    for row in lines:
        if x == []:
            x = list(map(int, row[1:-1]))
        else:
            wrds = [(wrd.capitalize()) for wrd in row[0].replace(".cpp", "").split("_")]

            if wrds[0] == 'Dijkstra': lab = wrds[0]
            else:
                wrds[1] = '('+wrds[1]+')'
                lab = " ".join(wrds)
            
            print(x, list(map(float, row[1:-1])))
            plt.plot(x, list(map(float, row[1:-1])), label=lab)
    # plt.plot(x, [xi**3/3e9 for xi in x], label='N^3')

# plt.xticks(rotation = 25)
plt.xlabel('N')
plt.ylabel('Time (Seconds)')
# plt.title('Weather Report', fontsize = 20)
# plt.grid()
plt.legend()
plt.show()