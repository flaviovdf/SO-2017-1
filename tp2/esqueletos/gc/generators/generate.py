# -*- coding: utf8

from collections import defaultdict

import random


TOTAL = 4194304
HEADER = 16
NODE = 36       # Pior caso, 32bits de cabeçalho do nó + int de refs


def main():
    counts = defaultdict(int)

    left = 4194304
    left -= HEADER
    left -= NODE

    max_size = 2048
    ops = []
    while left > 0:
        aloca = random.randint(NODE+1, NODE+max_size)
        if left - aloca < 0:
            aloca = left

        left -= aloca
        ops.append(aloca - NODE)
        counts[ops[-1]] += 1


    print(len(ops))
    idxs = [i for i in range(len(ops))]
    random.shuffle(idxs)

    p = 0.4
    # back refs
    for i, op in enumerate(idxs):
        if random.random() < p:
            counts[op] += 1
            ops.append(op)

    seen = set()
    for op in ops:
        if op not in seen:
            print(op, ops[op], 'a')
        else:
            print(op, '-1', 'r')

    random.shuffle(ops)
    for op in ops:
        print(op, '-1', 'f')


if __name__ == '__main__':
    main()
