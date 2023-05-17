# SoftEngBattleships

The implementation and unit tests of the game Battleships for the course Software Engineering during FS2023.

## Documents & Links

- [Software Requirements Specification (Google docs)](https://docs.google.com/document/d/1ZKqCuUC45hqn9-1J77-43FbJHm3ckngDs78T6qiKq5g/edit)

- [Software Design Specification (Google docs)](https://docs.google.com/document/d/1EQSFysfbPWMtOsfs9r5SwyRhid3R1U1N3jasiMDwmeI/edit#)

- [SRS Presentation](https://docs.google.com/presentation/d/1fHumCKMQ6Kvi-mJ-6OxfkvS3h7o4NQuNK3A8KhN9980/edit?usp=sharing)

- [SDS Presentation](https://docs.google.com/presentation/d/1i-HfX4yBY-yjnPVfB7hTyjN0mOqWYwwlQLtLIh6Suf0/edit?usp=sharing)

- [Example Lama Project](https://gitlab.ethz.ch/hraymond/cse-lama-example-project/-/tree/master/)

- [Zoom Meeting Link](https://ethz.zoom.us/j/66328319238)

## Development

### Formatting rules

Filenames, variables, member functions and object names are written in snake_case, Class names are written in CamelCase.
Private member variables should be named with a trailing underscore.

Example:

```cpp
// example_class.cpp

class Example {
    public:
        void example_function();

        int example_member_1;

    private:
        int example_member_2_;
};

```

### Installing dependencies

After cloning this repo, load the submodules with

```
git submodule update --init --recursive
```

Updating dependencies:

```
git submodule update --remote --recursive
```

### Resources

- sockpp TCP example
  - [TCP Server Example](https://github.com/fpagliughi/sockpp/blob/master/examples/tcp/tcpechosvr.cpp)
  - [TCP Client Example](https://github.com/fpagliughi/sockpp/blob/master/examples/tcp/tcpecho.cpp)

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

## Documentation

Doxygen documentation for this project is provided in the "build/docs'" folder. Doxygen needs to be installed via

```bash
sudo apt-get install doxygen
```

on Linux and

```bash
sudo brew install doxygen
```

on macOS using Homebrew.

To obtain the documentation, build the target "docs" and open "build/docs/index.html" in your browser of preference.
