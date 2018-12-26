#!/usr/bin/env bash

g++ -g -I ../ -pthread -fpermissive      \
    -o ../output/TrafficGuideServer.exe  \
    Infrastructure/*                     \
    Entry.cpp
