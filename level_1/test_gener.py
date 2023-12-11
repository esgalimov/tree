import random


with open("./tests/13.dat", "w") as test_file:
    for i in range(1, 1000_000):
        print(f"k {random.randint(100_000, 800_000)}", file=test_file, end=" ")
        if i % 50_000 == 0:
            print(file=test_file)
            lower = random.randint(100_000, 600_000)
            upper = random.randint(300_000, 800_000)
            print(f"q {lower} {upper}", file=test_file)
    print(f"q {1} {1000_000}", file=test_file)

