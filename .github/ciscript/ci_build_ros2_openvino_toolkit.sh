#!/bin/bash

# Color definitions for foreground
FG_NONE='\033[0m'
FG_RED='\033[0;31m'
FG_GREEN='\033[0;32m'
FG_YELLOW='\033[0;33m'
FG_BLUE='\033[0;34m'

WORK_DIR=/github/workflow/ros2_ws
package_name=ros2_openvino_toolkit

ls -lha /github/workspace

echo -e "$FG_BLUE Install git $FG_NONE"
apt-get update && apt-get install -y git

echo -e "$FG_BLUE workdir /github/workflow/ros2_ws/src/${package_name} $FG_NONE"
mkdir -p /github/workflow/ros2_ws/src/
cd /github/workflow/ros2_ws/src
cp -rf /github/workspace /github/workflow/ros2_ws/src/${package_name}
ls -lha /github/workflow/ros2_ws/src/${package_name}

# install object_msgs
echo "$FG_BLUE install object_msgs $FG_NONE"
apt update && apt install -y ros-dashing-object-msgs

cd ${WORK_DIR}
echo -e "$FG_BLUE build $FG_NONE"

# export env
mkdir -p /opt/openvino_toolkit
ln -sf /root/deps/openvino /opt/openvino_toolkit/dldt
export InferenceEngine_DIR=/opt/openvino_toolkit/dldt/inference-engine/build/
export CPU_EXTENSION_LIB=/opt/openvino_toolkit/dldt/inference-engine/bin/intel64/Release/lib/libcpu_extension.so
export GFLAGS_LIB=/opt/openvino_toolkit/dldt/inference-engine/bin/intel64/Release/lib/libgflags_nothreads.a

source /opt/ros/dashing/setup.sh
colcon build --symlink-install

echo -e "$FG_BLUE Copy working directory to physical machine $FG_NONE"
cp -rf ${WORK_DIR} /github/workspace/
