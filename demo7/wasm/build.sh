. ./.env

cd $EMSDK_HOME
. ./emsdk_env.sh
cd -

rm -rf build

mkdir build && cd build && emcmake cmake .. && emmake make 

