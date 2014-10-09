n = int(open("subsets.in").read())
SS = []

for x in xrange(2**n):
    ss = []
    for y in xrange(n):
        if x & (1<<y):
            ss.append(y + 1)
    SS.append(ss)

SS.sort()
SS_str = map(lambda l: " ".join(map(str, l)), SS)
open("subsets.out", "w").write("\n".join(SS_str))
