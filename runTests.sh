#!/bin/bash

./buildUtils.sh
ctest --test-dir build --output-on-failure -j $(nproc)