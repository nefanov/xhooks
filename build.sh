#!/usr/bin/env bash
g++ -I/usr/lib/jvm/java-8-openjdk-amd64/include -I/usr/lib/jvm/java-8-openjdk-amd64/include/linux -shared -lib  -o libxrep.so -fPIC -c impl.cpp -lxcb -lX11
