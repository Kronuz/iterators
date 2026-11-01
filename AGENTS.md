# AGENTS

Two headers of lazy iteration adaptors extracted verbatim from Xapiand:
`itertools.hh` (`itertools::transform`, `itertools::chain`) and `reversed.hh`
(`reversed()`).

- Header-only, standard-library only. Consumers include `itertools.hh` and/or
  `reversed.hh` by name -- keep those filenames.
- Forward-iterator wrappers, lazy (no allocation/materialization). The value_type
  comes from the source iterator.
- The adaptors' iterators declare the five member typedefs `std::iterator_traits` reads and
  derive from nothing (`std::iterator` is deprecated since C++17). Keep it that way: the
  test target builds with `-Werror -Wdeprecated`.
- `test/test.cc` covers transform, chain concatenation, reversed order, and the iterator
  traits of both adaptors.

## Verification and benchmarks

The shared method is the catalog's
[PERFORMANCE.md](https://github.com/Kronuz/cpp-libraries/blob/main/docs/PERFORMANCE.md). From a
fresh clone:

```sh
cmake -B build && cmake --build build && ctest --test-dir build --output-on-failure
```

- **Test.** `iterators` (`test/test.cc`) checks `transform` (doubles each element), `chain` (two
  ranges in order) and `reversed` (back to front) against the expected vectors, and
  `static_assert`s the five `std::iterator_traits` of both adaptors' iterators. It builds with
  `-Wall -Wextra -Wdeprecated -Wdeprecated-declarations -Werror` on GCC and Clang, so a deprecated
  base is a build failure. It prints `all iterators tests passed`.
- **Revert check.** The header from before the `std::iterator` fix fails that build on every CI
  job and on Apple clang (`'iterator<std::forward_iterator_tag, int>' is deprecated`):
  `git show e87b125^:itertools.hh > itertools.hh && cmake --build build`, then
  `git checkout itertools.hh`.
- **CI.** `.github/workflows/ci.yml` calls the catalog's shared
  [`cmake.yml`](https://github.com/Kronuz/cpp-libraries/blob/main/.github/workflows/cmake.yml):
  Linux x86_64 (GCC, Clang) and arm64 (GCC), macOS arm64 and x86_64, and FreeBSD, at `-O2 -g` with
  the standard library's assertions on, plus ASan+UBSan and TSan jobs over the same test (the
  adaptors hold no shared state). The ASan+UBSan job, on Linux:

  ```sh
  CC=clang CXX=clang++ cmake -B build-asan -DCMAKE_BUILD_TYPE=Debug \
    "-DCMAKE_CXX_FLAGS=-fsanitize=address,undefined -fno-sanitize-recover=undefined -fno-omit-frame-pointer -D_GLIBCXX_ASSERTIONS" \
    -DCMAKE_EXE_LINKER_FLAGS=-fsanitize=address,undefined
  cmake --build build-asan && ASAN_OPTIONS=detect_leaks=1 ctest --test-dir build-asan --output-on-failure
  ```

- **Not here.** No differential test, mutation script, fuzz target or benchmark, and no
  performance claim.
