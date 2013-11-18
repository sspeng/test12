#!/bin/bash

additestPath=/home/hpcbjdic/scratch/additest/

i=1		# experiment ID

# f=10
f=10		# sample rate (us)
s=1000		# records per chunk
# 6s
n=100000	# total number of records
# 1min
#n=1000000	# total number of records
# 10min
#n=10000000	# total number of records
c=6		# number of channels
k=0		# channel offset
p=1		# calculate power
w=500		# number of samples for power calculation

_1=0		# write out the raw data
_2=0		# write out the converted data as ASCII text
a=1		# write out the converted data by channels

v=1		# verbosity level


sudo rm -fR data_$i

sudo $additestPath/addi  -i $i  -f $f  -s $s  -n $n  -c $c  -k $k  -p $p  -w $w  -1 $_1  -2 $_2  -a $a  -v $v

sudo chmod -R 777 data_$i
rm -f data_$i/power_result_pw_*
