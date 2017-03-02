#!/bin/bash
pushd /root/overlay/
echo 'y' | pacman -Syu
printf '\n\n\ny\n' | pacman -S base-devel kde-development-environment-meta k3b libkcddb
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr    \
    -DCMAKE_CXX_COMPILER=clang++    \
    -DKDE_INSTALL_LIBDIR=lib    \
    -DKDE_INSTALL_LIBEXECDIR=lib    \
    -DKDE_INSTALL_USE_QT_SYS_PATHS=ON   \
    -DK3B_BUILD_API_DOCS=ON \
    -DK3B_ENABLE_PERMISSION_HELPER=ON   \
    -DK3B_DEBUG=ON
make -j4
