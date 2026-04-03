#! /bin/bash

wget https://snap.stanford.edu/data/soc-LiveJournal1.txt.gz

mkdir -p graphs

gunzip soc-LiveJournal1.txt.gz

mv soc-LiveJournal1.txt graphs/

# remove 3 first lines because the dataset doesnt start from specifying the edges.
