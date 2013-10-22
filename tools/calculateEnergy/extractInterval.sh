#!/bin/bash
#usage: extractInverval <inFile> <begin> <end> <outFile>

head -c $(($3 * 8)) $1 | tail -c $((($3 - $2) * 8)) > $4
