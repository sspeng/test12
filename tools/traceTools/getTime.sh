#!/bin/bash

~/scratch/energyprofiler/trunk/tools/sampleDataTester/timeTester $1 | head -n $(($2 + 1)) | tail -n 1
