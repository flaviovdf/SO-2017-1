#!/bin/bash

INPUT=belady
CLOCK=1

echo "algorithm,faults,cachesize,clockfreq,input"
for algorithm in "random" "fifo"; do
  for fpath in $INPUT/*; do
    cachesize=`head -1 $fpath | cut -d" " -f2` # pega a segunda coluna do in
    out=`./vmm $algorithm $CLOCK < $fpath` # joga a saída do comando em out
    echo "$algorithm,$out,$cachesize,$CLOCK,$INPUT"
  done
done
