#! /bin/bash

SOURCE=${BASH_SOURCE[0]}
while [ -L "$SOURCE" ]; do
  DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )
  SOURCE=$(readlink "$SOURCE")
  [[ $SOURCE != /* ]] && SOURCE=$DIR/$SOURCE
done
DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )


cd ${DIR}
mkdir -p local
cd local

if [ ! -d oneTBB ] ; then
  git clone https://github.com/oneapi-src/oneTBB.git
fi

cd oneTBB

mkdir -p build && cd build
cmake -DCMAKE_INSTALL_PREFIX=${DIR}/local/tbb -DCMAKE_INSTALL_MESSAGE=LAZY -DTBB_TEST=OFF ..
cmake --build .
cmake --install .
