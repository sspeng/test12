#!/usr/bin/python

# extracts system memory BW from pcm-memory.x's output


import sys


file = open(sys.argv[1], 'r')
lines = file.readlines()
file.close()

startTime = int(lines[0].split(':')[1])

for line in lines:
    if line.find("System Memory Throughput") != -1:
	startTime += 1000000
        print startTime, float(line.split(':')[1].split('-')[0])
