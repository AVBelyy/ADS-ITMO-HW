lines = ["100000 99999"]

for x in xrange(2, 100001):
    lines.append(str(x) + " 1")

open("game.in", "w").write("\n".join(lines))
