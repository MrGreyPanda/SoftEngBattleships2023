# SoftEngBattleships

The implementation of the game Battleships for the course Software Engineering during FS2023.

Filenames, variables, member functions and object names are written in snake_case, Class names are written in CamelCase.

[Software Design Specification](https://docs.google.com/document/d/1EQSFysfbPWMtOsfs9r5SwyRhid3R1U1N3jasiMDwmeI/edit#)

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
