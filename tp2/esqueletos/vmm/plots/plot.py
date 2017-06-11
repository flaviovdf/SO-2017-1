# -*- coding: utf8

import matplotlib.pyplot as plt
import pandas as pd


def main():
    in_fpath = 'circular.dat'
    df = pd.read_csv(in_fpath)

    print(df.groupby(['algorithm']).mean())

    fifo = df[df['algorithm'] == 'fifo']
    random = df[df['algorithm'] == 'random']

    x_fifo = fifo['cachesize']
    y_fifo = fifo['faults']
    x_rand = random['cachesize']
    y_rand = random['faults']

    plt.scatter(x_fifo, y_fifo, label='FIFO')
    plt.scatter(x_rand, y_rand, label='RND')
    plt.ylabel('# Page Faults')
    plt.xlabel('Cache Size')
    plt.legend()
    plt.savefig('plot.pdf')


if __name__ == '__main__':
    main()
