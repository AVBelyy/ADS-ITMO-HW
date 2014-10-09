f = open("biconv.in", "w")
for x in xrange(200000/3):
    f.write(str(3*x + 1) + " " + str(3*x + 2) + "\n")
    f.write(str(3*x + 2) + " " + str(3*x + 3) + "\n")
    f.write(str(3*x + 3) + " " + str(3*x + 1) + "\n")
for x in xrange(200000/3 - 1):
    f.write(str(3*x + 1) + " " + str(3*x + 4) + "\n")
f.close()
