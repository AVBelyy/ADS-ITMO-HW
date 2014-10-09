n_str, P_str = open("nextpartition.in").readline().strip().split("=")
n, P = int(n_str), map(int, P_str.split("+"))

S = [P[0]]
for x in xrange(1, len(P)):
    S.append(S[x - 1] + P[x])

Sum     = lambda x: S[x] if x >= 0 else 0
GenTail = lambda c, s: [c] * ((s / c) - 1) + [c + s % c]

flag1 = True
for x in xrange(len(P) - 1, -1, -1):
    d = n - Sum(x - 1) - P[x]
    if d >= 1:
        flag1 = False
        flag2 = True
        for y in xrange(1, d + 1):
            if n - Sum(x - 1) - P[x] - y >= P[x] + y:
                flag2 = False
                P[x] += y
                P[x + 1:] = GenTail(P[x], n - Sum(x - 1) - P[x])
                break
        if flag2:
            P[x] += d
            P[x + 1:] = []
        break

if flag1:
    ans = "No solution"
else:
    ans = ("%d=" % n) + "+".join(map(str, P))
open("nextpartition.out", "w").write(ans + "\n")
