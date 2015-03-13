num_lines = 1000

with open("search4.in", "w") as f:
    f.write(str(num_lines) + "\n")
    for x in xrange(1, num_lines + 1):
        f.write("".join(["a"] * x) + "\n")
    f.write("".join(["a"] * 1000000))
