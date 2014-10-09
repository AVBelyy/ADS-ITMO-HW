def is_good(pr):
    return len(set(pr)) == len(pr)

n = int(open("permutations.in").read())
out = []

def gen(k, p):
    if p == n:
        out.append(" ".join(map(str, k)))
    else:
        for x in xrange(1, n + 1):
            prefix = k + [x]
            if is_good(prefix):
                gen(prefix, p + 1)

gen([], 0)

open("permutations.out", "w").write("\n".join(out))
