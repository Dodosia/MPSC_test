#!/bin/sh -e
RES=$((readlink -f -- "${0}" || realpath -- "${0}") | xargs -- dirname --)
cmake -P "${RES}/format.cmake"
