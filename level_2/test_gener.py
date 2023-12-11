import random

st = random.sample(range(-1000_000, 1000_000), 1000_000)
with open("./tests/09.dat", "w") as test_file:
    for i in range(0, 500_000):
        print(f"k {st[i]}", file=test_file, end=" ")
        if (i + 1) % 100_000 == 0:
            print(file=test_file)
            print(f"m {random.randint(1, i - 1)}", file=test_file)
            print(f"n {random.randint(0, 1000_000)}", file=test_file)

