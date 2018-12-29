#!/usr/bin/env bash

g++ -g -I ../ -pthread -fpermissive      \
    -o ../output/TrafficGuideServer.exe  \
    ../Kernel/Functional/*               \
    ../Kernel/Identity/*                 \
    ../Kernel/Communication/*            \
    ../Kernel/Helpers/*                  \
    App/*                                \
    Domain/*.cpp                         \
    Infrastructure/Persistence/*         \
    Infrastructure/*.cpp                 \
    Resources/Cars/Adapters/*            \
    Resources/Cars/Requests/*            \
    Resources/Cars/*.cpp                 \
    Resources/Common/*                   \
    Scaffolding/*                        \
    Entry.cpp
