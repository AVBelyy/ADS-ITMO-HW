out = []

for x in xrange(1, 1000):
    out.append(" ".join(map(str, [998] + filter(lambda t: t != x, range(1, 1000)))))

print "\n".join(out)
