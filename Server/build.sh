#!/usr/bin/env bash

g++ -g -I ../ -pthread -fpermissive      \
    -o ../output/TrafficGuideServer.exe  \
    ../Kernel/Functional/*               \
    Infrastructure/*                     \
    Entry.cpp
