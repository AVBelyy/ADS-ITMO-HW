test = ["%d %d" % (x, x) for x in xrange(5000)]

open("spantree.in", "w").write("%d\n%s" % (len(test), "\n".join(test)))
