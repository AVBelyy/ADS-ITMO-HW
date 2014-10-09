S = [open("bwt.in").read().rstrip()]
open("bwt.out", "w").write("".join(map(lambda s: s[-1], sorted(S + map(lambda x: S[0][x:] + S[0][:x], xrange(1, len(S[0])))))) + "\n")
