# iterators

[![CI](https://github.com/Kronuz/iterators/actions/workflows/ci.yml/badge.svg)](https://github.com/Kronuz/iterators/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)
![Header-only](https://img.shields.io/badge/header--only-yes-green.svg)

Three small, lazy iteration adaptors for C++20 range-for loops: `transform`,
`chain`, and `reversed`, with no allocation and no ranges library.

## ✨ Highlights

- **`itertools::transform(fn, begin, end)`** maps each element as you iterate.
- **`itertools::chain(b1, e1, b2, e2)`** walks two ranges back to back.
- **`reversed(container)`** iterates back to front.
- **Header-only, no dependencies.**

## 📦 Installation

Requires a C++20 compiler; CMake 3.14 or newer for the CMake route. CI builds it
on Linux (x86_64, arm64), macOS (arm64, x86_64), and FreeBSD, plus ASan, UBSan,
and TSan builds.

```cmake
include(FetchContent)
FetchContent_Declare(iterators
  GIT_REPOSITORY https://github.com/Kronuz/iterators.git
  GIT_TAG        main)
FetchContent_MakeAvailable(iterators)

target_link_libraries(my_app PRIVATE iterators::iterators)
```

## 🚀 Quick start

```cpp
#include "itertools.hh"
#include "reversed.hh"

#include <cstdio>
#include <vector>

int main() {
	std::vector<int> a{1, 2}, b{3, 4};
	for (int x : itertools::chain(a.begin(), a.end(), b.begin(), b.end())) { std::printf("%d ", x); }   // 1 2 3 4
	for (int x : itertools::transform([](int n) { return n * 2; }, a.begin(), a.end())) { std::printf("%d ", x); }   // 2 4
	for (int x : reversed(b)) { std::printf("%d ", x); }   // 4 3
}
```

## 🎯 When to use it

- ✅ Pre-C++20 code, or tight loops where you want nothing beyond these three.
- ❌ C++20 code that can use `std::views::transform`, `std::views::reverse`, and
  friends.

## 📚 Documentation

- [ARCHITECTURE.md](ARCHITECTURE.md): how each adaptor is built.
- [AGENTS.md](AGENTS.md): repository map and traps.

## 🛠️ Building and testing

```sh
cmake -B build && cmake --build build && ctest --test-dir build
```

## 🤝 Contributing

Issues and pull requests are welcome. Read [AGENTS.md](AGENTS.md) first. CI must
pass on every platform.

## 📄 License

MIT, Copyright (c) 2019 Dubalu LLC. See [LICENSE](LICENSE). Extracted from
[Xapiand](https://github.com/Kronuz/Xapiand).
