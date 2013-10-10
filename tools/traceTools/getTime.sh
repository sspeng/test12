#!/bin/bash

~/scratch/energyprofiler/trunk/tools/sample_data_tester/time_tester fullTime.dat | head -n $(($1 + 1)) | tail -n 1
