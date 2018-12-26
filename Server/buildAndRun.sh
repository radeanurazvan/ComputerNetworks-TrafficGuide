#!/usr/bin/env bash

printf "Building\n"

./build.sh

printf "\nSuccessfully built. Running:\n\n"

../output/TrafficGuideServer.exe
