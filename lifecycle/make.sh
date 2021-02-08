
export COMPUTE_CPP_ROOT=~/tool_chain/computecpp/ComputeCpp-CE-1.0.3-Ubuntu-16.04-x86_64
export CC=${COMPUTE_CPP_ROOT}/bin/compute++
${CC} -std=c++11 main1.cpp -lpthread
