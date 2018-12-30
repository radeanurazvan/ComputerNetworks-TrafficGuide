#!/usr/bin/env bash

g++ -g -I ../ -pthread -fpermissive      \
    -o ../output/TrafficGuideServer.exe  \
    ../Kernel/Functional/*               \
    ../Kernel/Identity/*                 \
    ../Kernel/Communication/*            \
    ../Kernel/Helpers/*                  \
    App/*                                \
    Domain/Car/*                         \
    Domain/WorldMap/*                    \
    Domain/News/*                    \
    Infrastructure/Persistence/*         \
    Infrastructure/*.cpp                 \
    Middlewares/*                        \
    Pipeline/*                           \
    Resources/Cars/Requests/*            \
    Resources/Cars/*.cpp                 \
    Resources/News/Requests/*            \
    Resources/News/Adapters/*            \
    Resources/News/*.cpp                 \
    Resources/Common/*                   \
    Scaffolding/*                        \
    Entry.cpp
