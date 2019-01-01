#!/usr/bin/env bash

g++ -g -I ../ -pthread -fpermissive      \
    -o ../output/TrafficGuideServer.out  \
    ../Kernel/Functional/*               \
    ../Kernel/Identity/*                 \
    ../Kernel/Communication/*            \
    ../Kernel/Helpers/*                  \
    App/*                                \
    Domain/Car/EventHandlers/*           \
    Domain/Car/Events/*                  \
    Domain/Car/*.cpp                     \
    Domain/WorldMap/*                    \
    Domain/News/Jobs/*                   \
    Domain/News/*.cpp                    \
    Events/*                             \
    Infrastructure/Persistence/*         \
    Infrastructure/*.cpp                 \
    Jobs/*                               \
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
