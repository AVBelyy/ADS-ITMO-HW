n = 500

with open("destroy.in", "w") as f:
    f.write("%d %d %d\n" % (n, n * (n - 1) / 2, 0))
    for x in xrange(1, n + 1):
        for y in xrange(x + 1, n + 1):
            f.write("%d %d %d\n" % (x, y, 1))
