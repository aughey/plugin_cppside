yum install -y gcc gcc-c++ make wget openssl-devel
cd /tmp
wget https://github.com/Kitware/CMake/releases/download/v3.28.1/cmake-3.28.1.tar.gz
tar -xvf cmake-3.28.1.tar.gz
cd cmake-3.28.1
./configure
make -j `nproc`
make install
cd /tmp
rm -rf cmake-3.28.1.tar.gz cmake-3.28.1