# synthCore

synthCore is the C++20 signal-processing core of OSynth, a synthesizer project. It builds as one static library, `OSynth::Core`, that each platform's target project links.

**Status:** pre-release. The API changes without notice.

## Features

- Oscillator with pulse, sine, saw and triangle waveforms, tuned by frequency, semitones and cents
- Gain stage, set in linear or decibel units
- Fixed-capacity queues: a single-producer, single-consumer queue and a note-history queue

## Requirements

| Tool | Version | Notes |
| --- | --- | --- |
| GCC or Clang | <version you tested> | Linux |
| MSVC | 18.11.0 | Windows, through Visual Studio |
| CMake | 3.24 or newer | |
| Network access | | The first configure downloads GoogleTest 1.18.0, and so does each `cfg_` test |

## Quick start

On Linux:

```sh
git clone https://github.com/EclipseLunaria/synthCore.git
cd synthCore
cmake -S . -B build/full
cmake --build build/full
ctest --test-dir build/full --output-on-failure
```

On Windows, the default Visual Studio generator keeps several configurations in one build folder, so name one when you build and when you test:

```powershell
git clone https://github.com/EclipseLunaria/synthCore.git
cd synthCore
cmake -S . -B build/full
cmake --build build/full --config Debug
ctest --test-dir build/full -C Debug --output-on-failure
```

When everything passes, ctest reports `100% tests passed, 0 tests failed out of N`.

## Building

Choose a profile when you configure. Settings are stored in the build folder's cache, so give each profile its own folder:

```sh
cmake -S . -B build/lite -DOSYNTH_PROFILE=lite
cmake --build build/lite
```

| Profile | Use for |
| --- | --- |
| `full` (default) | Desktop builds |
| `lite` | Memory-constrained targets |

An unknown profile stops the configure step with:

```text
OSynth Core: tiny not in available profiles: full;lite
```

To change one limit of the chosen profile, set its override when you configure:

```sh
cmake -S . -B build/mv8 -DOSYNTH_MAX_VOICES=8
```

| Override | Rule |
| --- | --- |
| `OSYNTH_MAX_VOICES` | Positive whole number |
| `OSYNTH_MAX_BLOCK_SIZE` | Positive whole number |
| `OSYNTH_WAVETABLE_LENGTH` | Positive whole number |
| `OSYNTH_OVERSAMPLING_FACTOR` | Positive whole number |
| `OSYNTH_COMMAND_QUEUE_SIZE` | Power of 2 |
| `OSYNTH_CACHE_LINE_SIZE` | Power of 2 |

A value that breaks its rule stops the configure step with a message like:

```text
OSynth Core: OSYNTH_COMMAND_QUEUE_SIZE must be a power of 2, got 1000
```

Other build settings:

- **Build type:** with Makefiles or Ninja, add `-DCMAKE_BUILD_TYPE=Release` when you configure. With Visual Studio, use `--config Release` when you build and `-C Release` when you test.
- **Compiler:** to build with Clang, add `-DCMAKE_CXX_COMPILER=clang++` when you configure a new build folder.
- **Warnings:** when synthCore is the top-level project, the library treats every warning as an error: `-Wall -Wextra -Wpedantic` on GCC and Clang, `/W4 /permissive-` on MSVC.
- **Exceptions and RTTI:** the library is compiled without either; the test program is not.

## Running tests

| To run | Command |
| --- | --- |
| Every test | `ctest --test-dir build/full --output-on-failure` |
| Tests whose names match a pattern | `ctest --test-dir build/full -R ConfigTests` |
| Everything except the configure tests | `ctest --test-dir build/full -E cfg_` |
| One suite, from the test program | `./build/full/tests/testSynthCore --gtest_filter='ConfigTests.*'` |

On Windows, add `-C Debug` to each ctest command; the test program is `build\full\tests\Debug\testSynthCore.exe`.

- `LinkerTests` constructs every public class and calls one method on each, so a member without a definition fails the build.
- tests/classes/ holds one test file per class, and tests/structures/ one per queue.
- Each `cfg_` test runs CMake again with an override, to check that the configure step accepts it.

## Using the library

Add synthCore to your project as a Git submodule:

```sh
git submodule add https://github.com/EclipseLunaria/synthCore.git external/synthCore
```

Then add it to your build and link `OSynth::Core`:

```cmake
add_subdirectory(external/synthCore)
target_link_libraries(my_app PRIVATE OSynth::Core)
```

Choose the profile on your own project's configure line, for example `-DOSYNTH_PROFILE=lite`. Linking `OSynth::Core` makes your target compile as C++20 or newer. When synthCore isn't the top-level project, its tests aren't built and its warnings aren't errors.

Headers live under `osynth/`, and everything is in the `OSynth::Core` namespace:

```cpp
#include "osynth/gain.h"

int main() {
    OSynth::Core::Gain gain;
    gain.setGainInDecibels(-6.0f);
    return 0;
}
```

## Project layout

```text
CMakeLists.txt       library target, profiles and overrides
include/osynth/      public headers
  structures/        fixed-capacity queues
src/                 library sources
tests/
  CMakeLists.txt     test program and the GoogleTest download
  builds/            configure tests for the overrides
  classes/           one test file per class
  structures/        one test file per queue
  linkerTests.cpp    links every public class
.gitmessage          commit message template
.github/             pull request template
```

## Known limitations

- The `lite` profile and the overrides are checked when you configure, but the code doesn't read them yet. Don't rely on either to change a value.
- macOS hasn't been tested, and there is no CI: Linux and Windows builds are checked by hand.

## Contributing

Branches are named `type/topic`, for example `fix/config-profiles`, and commits follow Conventional Commits. Point Git at the commit template once per clone:

```sh
git config commit.template .gitmessage
```

Pull requests start from `.github/pull_request_template.md`; fill in every section. Every commit on `main` builds and passes its tests.

## License

No license has been chosen yet, so default copyright applies: others can view and fork this repository on GitHub, but have no permission to reuse the code.