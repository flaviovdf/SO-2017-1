# -*- coding: utf8

import random


TOTAL = 4194304
HEADER = 16
NODE = 32


def main():
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

    print(len(ops))
    idxs = [i for i in range(len(ops))]
    random.shuffle(idxs)

    p = 0.5
    prev = []
    for i, s in enumerate(ops):
        prev.append(i)
        if random.random() < p and prev:
            random.shuffle(prev)
            print(prev.pop(0), '-1', 'f')
        print(i, s, 'a')


if __name__ == '__main__':
    main()
