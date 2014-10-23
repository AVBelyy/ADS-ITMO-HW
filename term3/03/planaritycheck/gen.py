import planarity

n = 6
m = n * (n - 1) / 2

out = "1"

for x in xrange(1, pow(2, m)):
    edgelist = []
    u, v = 1, 1
    for y in xrange(m):
        u += 1
        if u >= v:
            v += 1
            u = 1
        if x & (1<<(m-y-1)):
            edgelist.append((u, v))
    out += "1" if planarity.is_planar(edgelist) else "0"

print(out)
