#!/usr/bin/env bash

g++ -fpermissive -pthread -I ../ -o ../output/TrafficGuideClient.out \
    ../Kernel/Functional/*          \
    ../Kernel/Communication/*       \
    ../Kernel/Helpers/*             \
    App/*                           \
    Infrastructure/*                \
    Entry.cpp