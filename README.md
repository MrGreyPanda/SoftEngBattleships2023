# SoftEngBattleships

The implementation of the game Battleships for the course Software Engineering during FS2023.

## Installing Development Dependencies

After cloning this repo, load the submodules with

```
git submodule update --init --recursive
```

## Testing

// TODO

## Building executables

The project is built using CMake.

To build the project (separate Debug and Release versions):

```bash
mkdir build
cd build
mkdir debug
mkdir release
cd debug
cmake -DCMAKE_BUILD_TYPE=Debug ../..
make
cd ..
cd release
cmake -DCMAKE_BUILD_TYPE=Release ../..
make
```

The executable file are built in the _build/debug_ and _build/release_ folder respectively
