# -*- coding: utf8

import random


def main():
    num_pages = 127
    num_refs = 2000
    for num_frames in range(1, 128):
        with open('noloc_cache_size_%d.dat' % num_frames, 'w') as outfile:
            print(num_pages, num_frames, file=outfile)
            for i in range(num_refs):
                is_read = random.randint(0, 1) == 0
                page_num = random.randint(0, num_pages-1)
                print(page_num, 'r' if is_read else 'w', file=outfile)


if __name__ == '__main__':
    main()
