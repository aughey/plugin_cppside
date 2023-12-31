# aoc16_cpp20


```
docker run --rm -it --volumes-from c4b88 --mount source=plugin_rustside-79f163945866b71c71ac9677fbadba8d1f854a24b0b58724b777c7b10d35bfcc,target=/rustworkspace registry.access.redhat.com/ubi7/ubi:7.9-1255
sh /workspaces/plugin_cppside/bootstrap_ubi7.sh
cd /tmp
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release /workspaces/plugin_cppside
cmake --build . --config Release
```