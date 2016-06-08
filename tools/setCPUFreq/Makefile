all: testCPUFreq artificialCode

testCPUFreq:
	# link against /local/ libcpufreq
	#gcc testCPUFreq.c cpufrequtils/lib/cpufreq.o cpufrequtils/lib/proc.o cpufrequtils/lib/sysfs.o -o testCPUFreq
	#
	# link against /system-wide/ libcpufreq
	gcc -lcpufreq testCPUFreq.c -o testCPUFreq

artificialCode:
	# link against /local/ libcpufreq
	#g++ artificialCodeRaw.cpp cpufrequtils/lib/cpufreq.o cpufrequtils/lib/proc.o cpufrequtils/lib/sysfs.o -o artificialCode
	#
	# link against /system-wide/ libcpufreq
	g++ -lcpufreq artificialCodeRaw.cpp -o artificialCode

clean:
	rm -f testCPUFreq artificialCode
