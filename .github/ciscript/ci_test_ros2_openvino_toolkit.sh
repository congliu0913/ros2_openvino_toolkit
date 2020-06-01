#!/bin/bash

# Color definitions for foreground
FG_NONE='\033[0m'
FG_RED='\033[0;31m'
FG_GREEN='\033[0;32m'
FG_YELLOW='\033[0;33m'
FG_BLUE='\033[0;34m'

WORK_DIR=/github/workflow/ros2_ws

echo -e "$FG_BLUE copy working $FG_NONE"
cp -rf /github/workspace/ros2_ws /github/workflow

echo -e "$FG_BLUE source env $FG_NONE"
# export env
mkdir -p /opt/openvino_toolkit
ln -sf /root/deps/openvino /opt/openvino_toolkit/dldt
export InferenceEngine_DIR=/opt/openvino_toolkit/dldt/inference-engine/build/
export CPU_EXTENSION_LIB=/opt/openvino_toolkit/dldt/inference-engine/bin/intel64/Release/lib/libcpu_extension.so
export GFLAGS_LIB=/opt/openvino_toolkit/dldt/inference-engine/bin/intel64/Release/lib/libgflags_nothreads.a

source /opt/ros/dashing/setup.sh
source ${WORK_DIR}/install/setup.sh

echo -e "$FG_BLUE colcon test $FG_NONE"
cd ${WORK_DIR}
colcon test  |tee test.log

TEST_ERRS=$(cat test.log|sed -n '$p'|awk -F":" '{print $2}')

for TEST_ERR in ${TEST_ERRS}
do
        echo -e "$FG_YELLOW --${TEST_ERR}-- $FG_NONE"
        cd ${WORK_DIR}/build/${TEST_ERR}
        ctest |tee ctest.log
        for ctest_err in $(cat ctest.log |sed -n '/FAILED/, $p'|sed '1d'|awk '{print $3}')
        do
                echo -e "\n$FG_RED --${ctest_err}-- $FG_NONE\n"
                ctest -V -R ${ctest_err}
        done
done
