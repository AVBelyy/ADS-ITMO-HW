from random import randint

with open("array.in", "w") as f:
    #f.write("ab" * (400000 / 2) + "\n")
    #f.write("a" * (400000 / 2) + "b" * (400000 / 2) + "\n")
    #f.write("a" * 400000 + "\n")
    f.write("".join(map(lambda _: chr(randint(ord('a'), ord('z'))), range(400000))) + "\n")
