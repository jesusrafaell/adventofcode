import time
import re
from typing import List

mr = 103
mc = 101

def parse_input(lines : List[str]) -> list:

    robots = []
    regex = r'p=(\d+),(\d+)\s*v=(-?\d+),(-?\d+)'
    for line in lines:
        match = re.search(regex, line)
        x, y, vx, vy = map(int, match.groups())
        robots.append({'p': [x, y], 'v': [vx, vy]})
    
    return robots

def part_1(robots: List[List[int]])  -> int:
    moves = 100

    quads = [0, 0, 0, 0]
    for robot in robots:
        robot['p'][0] = (robot['p'][0] + robot['v'][0] * moves) % mc
        robot['p'][1] = (robot['p'][1] + robot['v'][1] * moves) % mr

        if robot['p'][0] < mc // 2 and robot['p'][1] < mr // 2:
            quads[0] += 1
        elif robot['p'][0] < mc // 2 and robot['p'][1] > mr // 2:
            quads[1] += 1
        elif robot['p'][0] > mc // 2 and robot['p'][1] < mr // 2:
            quads[2] += 1
        elif robot['p'][0] > mc // 2 and robot['p'][1] > mr // 2:
            quads[3] += 1

    return quads[0] * quads[1] * quads[2] * quads[3]

def part_2(robots : List[List[int]])  -> int:
    time = 0
    while True:
        time += 1
        seen = set()
        for robot in robots:
            nx = (robot['p'][1] + time * robot['v'][1]) % mr
            ny = (robot['p'][0] + time * robot['v'][0]) % mc

            seen.add((ny, nx))

        if len(seen) == len(robots):    
            map = [[' ' for _ in range(mc)] for _ in range(mr)]
            for x in seen:
                map[x[1]][x[0]] = '#'
            print('\n'.join([''.join(i) for i in map]))
            print(f'time: {time}')

    return None

if __name__ == '__main__':
    f = open('in.txt', 'r')
    lines = f.readlines()
    robots = parse_input(lines)

    p1 = part_1(robots)
    print("P1: ", p1)

    part_2(robots)