# iterators

Part of [Kronuz C++ Libraries](https://github.com/Kronuz/cpp-libraries), a collection of small, reusable C++ libraries.

[![CI](https://github.com/Kronuz/iterators/actions/workflows/ci.yml/badge.svg)](https://github.com/Kronuz/iterators/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)
![Header-only](https://img.shields.io/badge/header--only-yes-green.svg)

Header-only lazy iteration adaptors for C++20: transform, chain and reversed for range-for loops, with no allocation.
Each adaptor is a small object holding iterators: `itertools::transform` maps elements as the
loop advances, `itertools::chain` walks two iterator ranges back to back, and `reversed`
iterates a container back to front. Reach for it when a loop already has iterator pairs and
`chain` saves building a joined copy.

## ✨ Highlights

- **`itertools::transform(fn, begin, end)`.** Calls `fn` on each element as the loop reads
  it.
- **`itertools::chain(b1, e1, b2, e2)`.** Walks two ranges back to back; the two iterator
  types may differ.
- **`reversed(container)`.** Iterates back to front through `std::rbegin` and `std::rend`.
- **No allocation, no dependencies.** Two headers and the standard library.

## 🚀 Quick start

```cpp
#include "itertools.hh"
#include "reversed.hh"

#include <cstdio>
#include <list>
#include <vector>

int main() {
	std::vector<int> a{1, 2};
	std::list<int> b{3, 4};
	for (int x : itertools::chain(a.begin(), a.end(), b.begin(), b.end())) {
		std::printf("%d ", x);  // 1 2 3 4
	}
	for (int x : itertools::transform([](int n) { return n * 2; }, a.begin(), a.end())) {
		std::printf("%d ", x);  // 2 4
	}
	for (int x : reversed(b)) {
		std::printf("%d ", x);  // 4 3
	}
	std::printf("\n");
}
```

## 📦 Installation

Requires a C++20 compiler; CMake 3.16 or newer for the CMake route. CI builds it on Linux
(x86_64, arm64), macOS (arm64, x86_64), and FreeBSD, plus ASan, UBSan, and TSan builds.

```cmake
include(FetchContent)
FetchContent_Declare(iterators
  GIT_REPOSITORY https://github.com/Kronuz/iterators.git
  GIT_TAG        55cd86b30730130fc3e28a92d8658a557df2c950)  # or main, to track the tip
FetchContent_MakeAvailable(iterators)

target_link_libraries(my_app PRIVATE iterators::iterators)
```

```cpp
#include "itertools.hh"
#include "reversed.hh"
```

## 🎯 When to use it

Use it for range-for loops over iterator pairs, and to walk two containers of the same
element type in one loop without copying them; `std::views::concat` arrives only in C++26.

Not for:

- **Code that can use `std::views`.** `std::views::transform` and `std::views::reverse`
  compose with the rest of the ranges library.
- **Raw pointers.** The adaptors read `I::value_type` and friends, so `int*` iterators do
  not compile.
- **Writing through the adaptor.** `chain` and `transform` return elements by value.
- **Temporaries with `reversed`.** It keeps a reference to its argument, so
  `reversed(make_vector())` in a range-for dangles.

## 📚 Documentation

- [ARCHITECTURE.md](ARCHITECTURE.md): how each adaptor is built.
- [CHANGELOG.md](CHANGELOG.md): dated changes.
- [AGENTS.md](AGENTS.md): repository map and traps.
- [Kronuz C++ Libraries](https://github.com/Kronuz/cpp-libraries): the catalog.

## 🛠️ Building and testing

```sh
cmake -B build
cmake --build build
ctest --test-dir build
```

## 🤝 Contributing

Read [AGENTS.md](AGENTS.md) and the [catalog's rules](https://github.com/Kronuz/cpp-libraries/blob/main/AGENTS.md)
first.

## 📄 License

MIT, Copyright (c) 2026 Germán Méndez Bravo and (c) 2015-2020 Dubalu LLC. See
[LICENSE](LICENSE). Extracted from [Xapiand](https://github.com/Kronuz/Xapiand).
