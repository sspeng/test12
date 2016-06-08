#!/bin/bash

# exit immediately after any failed command
set -e

`tail -n 9 run.stdout | head -n 1`
mv [[:digit:]]*.fe.excess-project.eu measurement_data

cd measurement_data/
#cat Channel_0_* > Channel_0.dat
#rm -f Channel_[234567]_*
~/scratch/energyprofiler/trunk/tools/traceTools/interpolateTimestamps Time_1.dat Time_interpolated.dat 12500
cd ..

#~/scratch/energyprofiler/trunk/tools/traceTools/attachLogs measurement_data/Channel_0.dat measurement_data/Time_interpolated.dat profile.xml timeline.plt

cd measurement_data/
~/scratch/energyprofiler/trunk/evaluate/evaluate ../profile.xml ../profile_energy.xml 12500
cd ..
