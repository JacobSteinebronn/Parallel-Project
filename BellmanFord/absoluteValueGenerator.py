line = input().split()
numNodes = int(line[0])
numEdges = int(line[1])

print(numNodes, numEdges)

for i in range(numEdges):
    line = input().split()
    u = int(line[0])
    v = int(line[1])
    w = abs(int(line[2]))

    print(u, v, w)