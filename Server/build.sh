#!/usr/bin/env bash

g++ -g -I ../ -pthread -fpermissive      \
    -o ../output/TrafficGuideServer.exe  \
    ../Kernel/Functional/*               \
    ../Kernel/Identity/*                 \
    ../Kernel/Communication/*            \
    ../Kernel/Helpers/*                  \
    Infrastructure/*                     \
    App/*                                \
    Entry.cpp
