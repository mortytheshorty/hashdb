#!/bin/bash

git submodule init
git submodule update

tar xf src/test/data/rockyou/rockyou.txt.tar.gz -C src/test/data
./build/hashdb_test