from random import randint
outfile = open("stations.txt", "a+")

for i in range(0, 100000):
    start = randint(-1000000, 1000000)
    finish = randint(-1000000, 1000000)
    outfile.write("ADD " + str(start) + " " + str(finish) + "\n")

outfile.close()

