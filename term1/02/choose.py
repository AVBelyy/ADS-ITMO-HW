n, k = map(int, open("choose.in").read().split())
out = []

def gen(K, p):
    if p == k:
        out.append(" ".join(map(str, K + [1])))
    else:
        for x in xrange(K[-1] + 1 if len(K) > 0 else 1, n + 1):
            gen(K + [x], p + 1)

gen([], 0)

open("choose.out", "w").write("\n".join(out))
