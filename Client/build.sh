#!/usr/bin/env bash

g++ -fpermissive -pthread -I ../ -o ../output/TrafficGuideClient.out \
    ../Kernel/Functional/*          \
    Client.cpp                      \
    Entry.cpp