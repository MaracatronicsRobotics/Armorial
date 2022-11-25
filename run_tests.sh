#!/bin/sh

cd test
rm -rf build
mkdir build
cd build && qmake .. && make && cd ..
cd bin && ./Armorial-Test 

if [ $? -ne 0 ]; then
	echo "Unit tests failed."
	exit 1
fi
