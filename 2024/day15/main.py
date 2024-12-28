import heapq
import re
import sys
import math
from collections import Counter, defaultdict, deque
from typing import List, Tuple

class Solution:
	def __init__(self, data: str):
		g, moves = data.split('\n\n')
		moves = moves.replace('\n', '')
		self.moves = moves
		self.g = g

	def parse(self):
		g = self.g
		g, a = [list(line) for line in g.split()], g.index('@')
		x, y = a % (len(g[0]) + 1), a // (len(g[0]) + 1)
		g[y][x] = '.'
		return g, (x, y)

	def part1(self, g: List[List[str]], a: tuple[int,int]):
		DIRS = {'^': (0, -1), 'v': (0, 1), '<': (-1, 0), '>': (1, 0)}
		i, j =a
		for move in self.moves:
			d = DIRS[move]
			xn, yn =  j + d[1], i + d[0],
			# print(move, (xn, yn))
			while g[xn][yn] == 'O':
				yn, xn = yn + DIRS[move][0], xn + DIRS[move][1]
			if g[xn][yn] == '.':  # Empty space
				if abs(xn - j + yn - i) > 1:
					g[xn][yn] = 'O'
					g[j + DIRS[move][1]][i + DIRS[move][0]] = '.'
				i, j = i + DIRS[move][0], j + DIRS[move][1]

		# for i in g:
		# 	print(''.join(i))

		return sum(
			100 * y + x
			for y, i  in enumerate(g)
			for x, cell in enumerate(i)
			if cell == 'O'
		)

	def parse2(self):
		# g, moves = data.split('\n\n')
		# moves = moves.replace('\n', '')
		g = self.g
		g = [[('[' if i % 2 == 0 else ']') if line[i // 2] == 'O' else line[i // 2] for i in range(len(line) * 2)] for line in g.split()]
		for y, i in enumerate(g):
			if '@' in i:
				x = i.index('@')
				break
		a = (x, y)
		g[y][x] = '.'
		g[y][x + 1] = '.'

		return g, a

	def part2(self, g: List[List[str]], a: Tuple[int, int]):
		DIRS = {'>': 1, '<': -1, '^': -1, 'v': 1}
		x, y = a
		for move in ''.join(self.moves.split()):
			if move in ['>', '<']:
				d = DIRS[move]
				xn = x + d
				# print(move, (xn))
				while g[y][xn] in ['[', ']']: xn += d
				if g[y][xn] == '.':
					for xn in range(xn, x, -d): g[y][xn] = g[y][xn - d]
					x += d
			else:
				bs = [{(x, y)}]
				while bs[-1]:
					bs.append(set())
					for b in bs[-2]:
						if g[b[1] + d][b[0]] == '#': break
						if g[b[1] + d][b[0]] == '[': bs[-1] |= {(b[0], b[1] + d), (b[0] + 1, b[1] + d)}
						elif g[b[1] + d][b[0]] == ']': bs[-1] |= {(b[0], b[1] + d), (b[0] - 1, b[1] + d)}
					else: continue
					break
				else:
						for i in list(reversed(bs)):
							for b in i: g[b[1] + d][b[0]], g[b[1]][b[0]] = g[b[1]][b[0]], '.'
						y += d
		# for i in g:
		# 	print(''.join(i))

		return sum(
			100 * i + j
			for i, r in enumerate(g)
			for j, c in enumerate(r)
			if c == '['
		)

if __name__ == "__main__":
	infile = f"{sys.argv[1]}.txt" if len(sys.argv) >= 2 else "in.txt"
	f = open(infile, "r")
	data = f.read().strip()

	solution = Solution(data)

	g, a  = solution.parse()
	print('P1:', solution.part1(g, a))
	g, a  = solution.parse2()
	print('P2:', solution.part2(g, a))
