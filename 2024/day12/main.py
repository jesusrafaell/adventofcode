import heapq
import re
import sys
from collections import Counter, defaultdict, deque
from typing import List

DIRS = [(-1, 0), (0, 1), (1, 0), (0, -1)]


class Solution:
    def __init__(self, infile):
        self.infile = infile
        self.grid = self.read_input()
        self.ROWS = len(self.grid)
        self.COLS = len(self.grid[0])

    def read_input(self):
        with open(self.infile, "r") as f:
            return f.read().strip().split("\n")

    def part1(self, g: List[str]):
        n, m = self.ROWS, self.COLS
        seen = set()
        ans = 0

        for i in range(n):
            for j in range(m):
                if (i, j) in seen:
                    continue
                queue = deque([(i, j)])
                area = 0
                perimeter = 0

                while queue:
                    x, y = queue.popleft()
                    if (x, y) in seen:
                        continue
                    seen.add((x, y))
                    area += 1

                    for dx, dy in DIRS:
                        rr, cc = x + dx, y + dy
                        if 0 <= rr < n and 0 <= cc < m and g[rr][cc] == g[x][y]:
                            queue.append((rr, cc))
                        else:
                            perimeter += 1

                ans += area * perimeter

        return ans

    def part2(self, g: List[str]):
        n, m = self.ROWS, self.COLS
        seen = set()
        ans = 0

        for i in range(n):
            for j in range(m):
                if (i, j) in seen:
                    continue
                queue = deque([(i, j)])
                area = 0
                per = dict()

                while queue:
                    x, y = queue.popleft()
                    if (x, y) in seen:
                        continue
                    seen.add((x, y))
                    area += 1

                    for dx, dy in DIRS:
                        rr, cc = x + dx, y + dy
                        if 0 <= rr < n and 0 <= cc < m and g[rr][cc] == g[x][y]:
                            queue.append((rr, cc))
                        else:
                            if (dx, dy) not in per:
                                per[(dx, dy)] = set()
                            per[(dx, dy)].add((x, y))

                count = 0
                for idx, nodes in per.items():
                    pseen = set()
                    for p1, p2 in nodes:
                        if (p1, p2) not in pseen:
                            count += 1
                            queue = deque([(p1, p2)])
                            while queue:
                                x, y = queue.popleft()
                                if (x, y) in pseen:
                                    continue
                                pseen.add((x, y))
                                for dx, dy in DIRS:
                                    rr, cc = x + dx, y + dy
                                    if (rr, cc) in nodes:
                                        queue.append((rr, cc))

                ans += area * count

        return ans


if __name__ == "__main__":
    infile = sys.argv[1] + ".txt" if len(sys.argv) >= 2 else "in.txt"

    solution = Solution(infile)

    p1 = solution.part1(solution.grid)
    print("Part 1:", p1)

    p2 = solution.part2(solution.grid)
    print("Part 2:", p2)
