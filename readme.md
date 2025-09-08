# Multithreading
Implement the `Task:` in [src/logger.hpp](src/logger.hpp).

## Windows
Required [Visual Studio Community 2022](https://visualstudio.microsoft.com/vs/community/) components.

```
Workloads
✅ Desktop development with C++
   ✅ C++ CMake tools for Windows
   ✅ vcpkg package manager

Individual Components
✅ Windows Universal C Runtime
✅ C++ Clang Compiler for Windows
```

## Linux
Instructions for Debian 12 (Bookworm).

```sh
# Update system.
sudo apt update
sudo apt upgrade

# Install build tools.
sudo apt install build-essential curl flex git ninja-build tar unzip zip

# Install latest CMake version (>= 3.31 && < 4.0).
curl -L https://github.com/Kitware/CMake/releases/download/v3.31.8/cmake-3.31.8-linux-x86_64.tar.gz -o cmake.tar.gz
sudo mkdir /opt/cmake
sudo tar xf cmake.tar.gz -C /opt/cmake -m --strip-components=1
sudo tee /etc/profile.d/cmake.sh >/dev/null <<'EOF'
export PATH="/opt/cmake/bin:${PATH}"
EOF
sudo chmod 0755 /etc/profile.d/cmake.sh
source /etc/profile.d/cmake.sh

# Build and install the latest GCC version.
curl -L https://github.com/gcc-mirror/gcc/archive/refs/tags/releases/gcc-15.2.0.tar.gz -o gcc.tar.gz
mkdir gcc
tar xf gcc.tar.gz -C gcc -m --strip-components=1
mkdir gcc/build
env --chdir=gcc contrib/download_prerequisites
env --chdir=gcc/build ../configure --prefix=/opt/gcc --enable-languages=c,c++ --disable-multilib
env --chdir=gcc/build make -j$(nproc)
env --chdir=gcc/build sudo make install

# Build and run project.
cd multithreading

LD_LIBRARY_PATH=/opt/gcc/lib64 CXX=/opt/gcc/bin/g++ cmake --workflow debug
LD_LIBRARY_PATH=/opt/gcc/lib64 build/debug/bin/multithreading

LD_LIBRARY_PATH=/opt/gcc/lib64 CXX=/opt/gcc/bin/g++ cmake --workflow release
LD_LIBRARY_PATH=/opt/gcc/lib64 build/release/bin/multithreading
```

Instructions for any Linux if `vcpkg` is not in `PATH` or `/opt/vcpkg`.

```sh
# Install Vcpkg.
sudo mkdir /opt/vcpkg
sudo chown $(id -u):$(id -g) /opt/vcpkg
git clone https://github.com/microsoft/vcpkg /opt/vcpkg
env --chdir=/opt/vcpkg ./bootstrap-vcpkg.sh -disableMetrics
```

Run benchmarks if the `benchmark` library or `vcpkg` are available.

```sh
sudo cpupower frequency-info
sudo cpupower frequency-set -g performance
LD_LIBRARY_PATH=/opt/gcc/lib64 setarch -R build/release/bin/benchmarks
```
