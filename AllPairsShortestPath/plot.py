
import matplotlib.pyplot as plt
import csv
import sys
x = []
  
# plt.plot(x, y, color = 'g', linestyle = 'dashed',
#          marker = 'o',label = "Weather Data")


print(sys.argv)

fname = "bench.csv"
if len(sys.argv) > 1:
    fname = sys.argv[1]

print("Opening", fname)

with open(fname,'r') as csvfile:
    lines = csv.reader(csvfile, delimiter=',')
    for row in lines:
        if x == []:
            x = list(map(int, row[1:-1]))
        else:
            wrds = [(wrd.capitalize()) for wrd in row[0].replace(".cpp", "").split("_")]

            lab = wrds[0]
            wrds = wrds[1:]
            if len(wrds) > 0:
                lab += " ("
                for wrd in wrds:
                    if len(wrd) == 0:
                        lab += ", "
                    else: lab += wrd.capitalize()+" "
                lab = lab[0:-1]+")"
            else:
                lab += " (Sequential)"

            print(x, list(map(float, row[1:-1])))
            plt.plot(x, list(map(float, row[1:-1])), label=lab)
    # plt.plot(x, [xi**3/3e9 for xi in x], label='N^3')

# plt.xticks(rotation = 25)
plt.xlabel('N')
plt.ylabel('Time (Seconds)')
# plt.title('Weather Report', fontsize = 20)
# plt.grid()
plt.legend()

if(len(sys.argv) >= 3): 
    title = str(sys.argv[2])

    plt.title(" ".join(title.split("_")))

plt.savefig(fname.split('.')[0]+'.png')
plt.show()