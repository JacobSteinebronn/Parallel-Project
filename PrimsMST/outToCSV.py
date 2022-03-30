import sys
import csv

reader = open('runtime.out', 'r')

filename = "bench1.csv"
if __name__ == "__main__":
    if len(sys.argv) > 1:
        filename = sys.argv[1]
base = int(reader.readline().strip())
header = ['N']
sequential_data = ["sequential"]
parallel_data = ["parallel"]
# read in input from runtimeComparison.sh
for i in range(10):
    sequential_data.append(float(reader.readline().strip()))
    parallel_data.append(float(reader.readline().strip()))
reader.close()
for i in range(10):
    header.append(base*(i+1))

with open('../csv/'+filename, 'w') as f:
    writer = csv.writer(f)
    writer.writerow(header)
    writer.writerow(sequential_data)
    writer.writerow(parallel_data)