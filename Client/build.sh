#!/usr/bin/env bash

g++ -fpermissive -g -pthread -I ../ -o ../output/TrafficGuideClient.out \
    ../Kernel/Functional/*          \
    ../Kernel/Communication/*       \
    ../Kernel/Helpers/*             \
    ../Kernel/Jobs/*                \
    App/*                           \
    Contracts/*                     \
    Domain/*                        \
    Infrastructure/*                \
    Entry.cpp