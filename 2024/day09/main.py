import math
import sys
from collections import defaultdict
from typing import List

INF = 1e-8


class Solution:
    # def __init__(self):
    #     self.stack = []

    def line_to_block(self, line: str) -> List[str]:
        b = list()
        idx = 0
        for i in range(0, len(line), 2):
            b.extend([str(idx)] * int(line[i]))
            if i + 1 < len(line):
                b.extend(["."] * int(line[i + 1]))
            idx += 1
        return b

    def part1(self, line: str) -> int:
        b = self.line_to_block(line)
        r, l = 0, len(b) - 1
        i = 0
        sum = 0

        while r <= l:
            # print(r, l, b[r], b[l])
            if b[r] == "." and b[l] != ".":
                b[r], b[l] = b[l], "."
                sum += i * int(b[r])
                # print(i, int(b[r]), "=", i * int(b[r]))
                i += 1
                r += 1
                l -= 1
            elif b[r] != ".":
                sum += i * int(b[r])
                # print(i, int(b[r]), "=", i * int(b[r]))
                i += 1
                r += 1
            else:
                l -= 1

        # print("".join(b))
        return sum

    def part2(self, line: str) -> int:
        segs = {}
        files = {}
        cur = 0
        id = 0
        fill = True

        for dx in line:
            dx = int(dx)
            if fill:
                segs[id] = (cur, cur + dx)
                for i in range(cur, cur + dx):
                    files[i] = id
                id += 1
            fill = not fill
            cur += dx

        sorted_segs = sorted(segs.keys(), reverse=True):
        for s in sorted_segs:
            print(s) # print >> 0

            curs, cure = segs[s]
            file_size = cure - curs

            pos = -1
            for start in range(curs):
                if all(start + i not in files for i in range(file_size)):
                    pos = start
                    break

            if pos != -1:
                for i in range(curs, cure):
                    del files[i]
                for i in range(pos, pos + file_size):
                    files[i] = s

        return sum(key * val for key, val in files.items())


if __name__ == "__main__":
    f = open("in.txt", "r")
    # f = open("test.txt", "r")

    # data format
    line = f.read().strip()
    # line = content.split("\n")
    solution = Solution()

    print("P1:", solution.part1(line))
    print("P2:", solution.part2(line))
