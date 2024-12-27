import heapq
import re
import sys
from collections import Counter, defaultdict, deque
from typing import List

import numpy as np


class Solution:

    def part1(self, ax, ay, bx, by, px, py):
        best = 5000
        for t1 in range(101):
            for t2 in range(101):
                nx = ax * t1 + bx * t2
                ny = ay * t1 + by * t2
                if px == nx and py == ny:
                    best = min(best, 3 * t1 + t2)

        if best < 5000:
            return best
        return 0

    def part2(self, ax, ay, bx, by, px, py):
        px += 10000000000000
        py += 10000000000000

        A = np.array([[ax, bx], [ay, by]])
        B = np.array([px, py])

        try:
            R = np.linalg.solve(A, B)
            pa = round(R[0])
            pb = round(R[1])

            if pa * ax + pb * bx == px and pa * ay + pb * by == py:
                return 3 * pa + pb
        except np.linalg.LinAlgError:
            return 0

        return 0


if __name__ == "__main__":
    infile = sys.argv[1] + ".txt" if len(sys.argv) >= 2 else "in.txt"

    f = open(infile, "r")
    data = f.read().strip().split("\n")

    ans1 = 0
    ans2 = 0

    solution = Solution()
    i, n = 0, len(data)
    while i < n:
        # A
        a = data[i].split()
        ax = int(a[2].split("+")[1].split(",")[0])
        ay = int(a[3].split("+")[1].split(",")[0])
        i += 1
        # B
        b = data[i].split()
        bx = int(b[2].split("+")[1].split(",")[0])
        by = int(b[3].split("+")[1].split(",")[0])
        i += 1
        # Price
        p = data[i].split()
        px = int(p[1].split("=")[1].split(",")[0])
        py = int(p[2].split("=")[1])
        i += 2
        # print(ax, ay, bx, by, px, py)
        ans1 += solution.part1(ax, ay, bx, by, px, py)
        ans2 += solution.part2(ax, ay, bx, by, px, py)

    print("Part 1:", ans1)
    print("Part 2:", ans2)
