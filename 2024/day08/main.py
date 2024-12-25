import math
import sys
from collections import defaultdict
from typing import List

INF = 1e-8


class Solution:
    # def __init__(self):
    #     self.stack = []

    # Distance functions
    # def euclidean_dist_squared(self, p1, p2):
    #     return (p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2
    def printGrid(good):
        print(
            "\n".join(
                "".join("#" if (i, j) in good else "." for j in range(m))
                for i in range(n)
            )
        )

    def dist(self, p1: List[int], p2: List[int]) -> int:
        return math.sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)

    def part1(self, grid: List[int]) -> int:
        m, n = len(grid), len(grid[0])
        nodes = defaultdict(list)

        for i in range(n):
            for j in range(m):
                if grid[i][j] != ".":
                    nodes[grid[i][j]].append((i, j))

        good = set()
        for i in range(n):
            for j in range(m):
                for k, v in nodes.items():
                    for v1 in v:
                        for v2 in v:
                            if v1 == v2:
                                continue
                            dx, dy = v2[0] - v1[0], v2[1] - v1[1]
                            dcp = (-(j - v1[1]), i - v1[0])

                            if dcp[0] * dx + dcp[1] * dy == 0:
                                d1 = self.dist((i, j), v1)
                                d2 = self.dist((i, j), v2)

                                if abs(d1 - d2 * 2) <= 1e-8 or abs(d2 - d1 * 2) <= 1e-8:
                                    good.add((i, j))
                                    break

        return len(good)

    def part2(self, grid: List[int]) -> int:
        m, n = len(grid), len(grid[0])
        nodes = defaultdict(list)

        for i in range(n):
            for j in range(m):
                if grid[i][j] != ".":
                    nodes[grid[i][j]].append((i, j))

        good = set()
        for i in range(n):
            for j in range(m):
                for k, v in nodes.items():
                    for v1 in v:
                        for v2 in v:
                            if v1 == v2:
                                continue
                            dx, dy = v2[0] - v1[0], v2[1] - v1[1]
                            dcp = (-(j - v1[1]), i - v1[0])

                            if dcp[0] * dx + dcp[1] * dy == 0:
                                good.add((i, j))
                                break

        return len(good)


if __name__ == "__main__":
    f = open("in.txt", "r")
    # f = open("test.txt", "r")

    # data format
    content = f.read().strip()
    lines = content.split("\n")
    solution = Solution()

    print("P1:", solution.part1(lines))
    print("P2:", solution.part2(lines))
