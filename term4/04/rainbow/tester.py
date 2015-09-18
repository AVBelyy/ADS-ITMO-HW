from random import random, randrange

with open("rainbow.in", "w") as f:
    n = randrange(2, 101)
    m = randrange(1, 5001)
    f.write("%d %d\n" % (n, m))
    for x in xrange(m):
        u = 0
        v = 0
        while u == v:
            u = randrange(1, n + 1)
            v = randrange(1, n + 1)
        color = randrange(1, 101)
        f.write("%d %d %d\n" % (u, v, color))
