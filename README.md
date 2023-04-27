# SoftEngBattleships

The implementation of the game Battleships for the course Software Engineering during FS2023.

Filenames, variables, member functions and object names are written in snake_case, Class names are written in CamelCase.

## Documents & Links ##

- [Example Lama Project](https://gitlab.ethz.ch/hraymond/cse-lama-example-project/-/tree/master/)

- [Software Requirements Specification](https://docs.google.com/document/d/1ZKqCuUC45hqn9-1J77-43FbJHm3ckngDs78T6qiKq5g/edit)
- [SRS Presentation](https://docs.google.com/presentation/d/1fHumCKMQ6Kvi-mJ-6OxfkvS3h7o4NQuNK3A8KhN9980/edit?usp=sharing)
- [Software Design Specification](https://docs.google.com/document/d/1EQSFysfbPWMtOsfs9r5SwyRhid3R1U1N3jasiMDwmeI/edit#)
- [SDS Presentation](https://docs.google.com/presentation/d/1i-HfX4yBY-yjnPVfB7hTyjN0mOqWYwwlQLtLIh6Suf0/edit?usp=sharing)

- [Zoom Meeting Link](https://ethz.zoom.us/j/66328319238)


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
