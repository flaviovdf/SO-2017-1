# -*- coding: utf8

import random


TOTAL = 4194304
HEADER = 16
NODE = 24


def main():
    left = 4194304
    left -= HEADER
    left -= NODE

    max_size = 4096
    ops = []
    while left > 0:
        aloca = random.randint(NODE+1, NODE+max_size)
        if left - aloca < 0:
            aloca = left

        left = left - aloca
        ops.append(aloca - NODE)

    print(len(ops)*2)
    for i, s in enumerate(ops):
        print(i, s, 'a')

    j = len(ops)
    idxs = [i for i in range(j)]
    random.shuffle(idxs)
    k = 0
    for i in idxs:
        print(i, -1, 'f')
        print(j, ops[i], 'a')
        j += 1
        k += 1


if __name__ == '__main__':
    main()
