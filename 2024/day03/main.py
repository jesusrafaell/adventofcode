import re

f = open("input.txt", "r")
# f = open("test.txt", "r")
content = f.read().strip()

regex = r"mul\((\d+),(\d+)\)"


def solution1(line: str) -> int:
    result = 0
    operations = re.findall(regex, "".join(line))

    for op in operations:
        a, b = map(int, op)
        result += a * b

    return result


def solution2(line: str) -> int:
    d_regex = r"do\(\)|don't\(\)"
    result = 0
    operations = re.findall(f"({regex}|{d_regex})", "".join(line))

    f = True
    for op in operations:
        ins, a, b = op
        if ins == "do()":
            f = True
            continue
        elif ins == "don't()":
            f = False
            continue
        if f:
            result += int(a) * int(b)

    return result


print("S1", solution1(content))
print("S2", solution2(content))
