from random import random, randrange

with open("multispan.in", "w") as f:
    n = randrange(2, 101)
    m = randrange(1, 2001)
    f.write("%d %d\n" % (n, m))
    for x in xrange(m):
        u = 0
        v = 0
        while u == v:
            u = randrange(1, n + 1)
            v = randrange(1, n + 1)
        f.write("%d %d\n" % (u, v))
