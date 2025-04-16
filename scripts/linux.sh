rm -rf build _deps
rm Makefile CMakeCache.txt cmake_install.cmake

export PATH=$PATH:/snap/bin

cmake CmakeLists.txt

make
