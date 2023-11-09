import random


# lower = random.randint(1, 300_000)
# upper = random.randint(600_000, 1_000_000)
#
# with open("./tests/12.dat", "w") as test_file:
#     for i in range(1, 500_000):
#         print(f"k {random.randint(0, 300_000)}", file=test_file, end=" ")
#         if i % 10 == 0:
#             print(file=test_file)
#
#     for i in range(1, 500_000):
#         print(f"k {random.randint(600_000, 1_000_000)}", file=test_file, end=" ")
#         if i % 10 == 0:
#             print(file=test_file)
#
#     print(f"q {lower} {upper}", file=test_file)

with open("./tests/12.dat", "w") as test_file:
    for i in range(1, 500_000):
        print(f"k {i}", file=test_file, end=" ")
    print(f"q {1} {499_999}", file=test_file)
