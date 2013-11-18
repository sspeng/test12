#!/bin/bash

localProjectRoot=/home/hpcbjdic/scratch/energyprofiler/trunk/
remoteProjectRoot=/home/hpcbjdic/scratch/energyprofiler/trunk/

localWorkDir=$localProjectRoot/runs/scratch/
remoteWorkDir=$remoteProjectRoot/runs/scratch/

runAdditest=$localProjectRoot/tools/traceTools/runAdditest.sh
applicationCode=$remoteProjectRoot/tools/artificialCode/artificialCode


function checkSuccess () {
if [ "$?" -eq 0 ]
then
	echo "done"
else
	echo "failed"
	exit
fi
}


cd $localWorkDir

# begin measurement
sudo echo -n "begin measurement ... "
sudo -b $runAdditest &> additest.log
checkSuccess

sleep 1

# run application code
echo -n "run application code ... "
fullCmd+="module load mpi/openmpi/1.6.4-gnu-4.7.2"
fullCmd+=" && "
fullCmd+="cd "$remoteWorkDir
fullCmd+=" && "
fullCmd+=$applicationCode
fullCmd+=" && "
fullCmd+="cd - > /dev/null"
ssh numtest4 $fullCmd
checkSuccess

# wait for measurement to finish
echo -n "wait for measurement to finish ..."
psOutput=`ps -A | grep addi`
while [ ${#psOutput} -ne 0 ]
do
	sleep 1
	echo -n "."
	psOutput=`ps -A | grep addi`
done
echo " done"

# fetch trace and time profile
echo -n "fetch trace and time profile ... "
scp numtest4:$remoteWorkDir/*.pdxml $localWorkDir &> /dev/null
checkSuccess

# interpolate timestamps
echo -n "interpolate timestamps ... "
$localProjectRoot/tools/traceTools/interpolateTimestamps \
	$localWorkDir/data_1/power_result_volt_channel_timer.dat \
	$localWorkDir/interpolatedTimestamps.dat \
	1000 # TODO: get chunkSize from additest configuration!!!
checkSuccess

# attach trace logs
echo -n "attach trace logs ... "
$localProjectRoot/tools/traceTools/attachLogs \
	$localWorkDir/data_1/power_result_volt_channel_3.dat \
	$localWorkDir/interpolatedTimestamps.dat \
	$localWorkDir/call_log.time.pdxml \
	$localWorkDir/time.pdxml \
	$localWorkDir/logsAttached.gnuplot
checkSuccess

# create merged time/energy profile
echo -n "create merged time/energy profile ... "
$localProjectRoot/evaluate/evaluate \
	$localWorkDir/call_log.time.pdxml \
	$localWorkDir/time.pdxml \
	$localWorkDir/mergedProfile.pdxml \
	$localWorkDir/data_1/power_result_volt_channel_timer.dat \
	$localWorkDir/data_1/power_result_volt_channel_3.dat \
	$localWorkDir/data_1/power_result_volt_channel_5.dat \
	$localWorkDir/data_1/power_result_volt_channel_4.dat \
	$localWorkDir/data_1/power_result_volt_channel_6.dat
checkSuccess

echo

# call gnuplot
echo -n "call gnuplot ... "
gnuplot $localWorkDir/logsAttached.gnuplot &
echo

# call ShinyProfileViewer
echo -n "call ShinyProfileViewer ... "
java -jar $localProjectRoot/tools/ShinyProfileViewer/ShinyProfileViewer.jar \
	$localWorkDir/mergedProfile.pdxml
echo
