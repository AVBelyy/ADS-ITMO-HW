from random import randint

with open("tree.in", "w") as f:
    #f.write("ab" * (100000 / 2) + "\n")
    f.write("a" * (100000 / 2) + "b" * (100000 / 2) + "\n")
    #f.write("a" * 100000 + "\n")
    #f.write("".join(map(lambda _: chr(randint(ord('a'), ord('z'))), range(100000))) + "\n")
