
# Create build files
mkdir -p build/
cd build/

if [ "$1" = "release" ] || [ -z "$DISPLAY" ]; then
    echo "Building as release"
    cmake  -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
else
    echo "Building as debug"
    cmake  -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
fi

# Generate compile_commands.json symlink if it doesn't exist (for clangd)
if [ ! -f "../compile_commands.json" ]; then
    CDIR=$(pwd)
    cd ..
    ln -s $CDIR/compile_commands.json compile_commands.json
    cd build/
fi

# Build
cmake --build . -j $(nproc)
cd ../..
