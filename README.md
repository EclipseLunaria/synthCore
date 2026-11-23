# OSynth Core

A high-performance realtime audio synthesis library. Designed and created targeting from Desktops down to Bare-metal machines.

**Status:** <pre-release or stable>. <What may change without notice, and what has been tested.>

## Features

- <A capability that works on main today, in the reader's terms>

## Requirements

### Tools
| Tool | Version | Notes |
| --- | --- | --- |
| CMake | 3.24 | |

### Platforms
| Compiler | Version | Platform |
| --- | --- | ---|
| MSVC | MSBuild 18.11.0 | Windows|
| Clang| | Linux


## Quick start

```sh
git clone https://github.com/EclipseLunaria/synthCore
cd synth_core
cmake . -B build  # -DOSYNTH_BUILD_PROFILE=lite
cd build
ctest
```

<The line of output that means it worked.>

## Building

<How to choose a profile, option or build type, with one example command each.>

| Option | Values | Default | Effect |
| --- | --- | --- | --- |
| `<NAME>` | <Allowed values, and the rule CMake enforces> | <Default> | <What it changes> |

## Running tests

<How to run every test, a subset by name, and one test program directly.>

## Using the library

<How another project adds this one and links it, then the smallest example that compiles.>

## Project layout

```text
<folder/>        <what lives here, in a few words>
```

## Documentation

- [<Doc title>](docs/<file>.md): <the question it answers>

## Known limitations

- <What doesn't work yet, stated plainly>

## Contributing

<Branch, commit and PR conventions in three lines, or a link to CONTRIBUTING.md.>

## License

<License name>. See [LICENSE](LICENSE).