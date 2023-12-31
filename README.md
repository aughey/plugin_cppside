# aoc16_cpp20


```
winpty docker run --rm -it --volumes-from c4b88 registry.access.redhat.com/ubi7/ubi:7.9-1255
sh /workspaces/plugin_cppside/bootstrap_ubi7.sh
cd /tmp
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release /workspaces/plugin_cppside
cmake --build . --config Release
```