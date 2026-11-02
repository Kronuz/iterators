# Changelog

Notable changes to `iterators`, newest first. The format follows
[Keep a Changelog](https://keepachangelog.com/en/1.1.0/); the library has no releases, so
entries are dated.

Upgrading a pin from before 2026-10-30: [the consumer upgrade note](https://github.com/Kronuz/cpp-libraries/blob/main/docs/UPGRADING-2026-10.md#iterators) lists what changes for callers, how to find affected inputs, the commits not to pin, and the speedup.

## 2026-11-01

### Fixed

- The iterators of `transform` and `chain` derived from `std::iterator`, deprecated since
  C++17: clang with libc++ and GCC 12 or newer warn on every include of `itertools.hh`
  (`-Wdeprecated-declarations`). They declare the five member typedefs instead
  (`iterator_category` as `std::forward_iterator_tag`, and `value_type`,
  `difference_type`, `pointer` and `reference` from the source iterator, the second one for
  `chain`), the same types the base supplied, so `std::iterator_traits` reads the same
  values.

### Tests

- `iterators_test` builds with `-Wall -Wextra -Wdeprecated -Wdeprecated-declarations
  -Werror` on GCC and Clang, so a deprecated base fails the build (the old header fails it
  on every CI job: clang with libc++ and libstdc++ 14 report
  `'iterator<std::forward_iterator_tag, int>' is deprecated`), and `static_assert`s check
  the five traits of both iterators.

### Changed

- The README follows the family README standard: the description as its first sentence,
  Quick start before Installation, a pinned FetchContent tag, and "Not for" limits. It
  names CMake 3.16, the version `CMakeLists.txt` requires, where it said 3.14, and no
  longer recommends the library for pre-C++20 code, since the target requires C++20. The
  limits name raw-pointer iterators, by-value elements and `reversed` of a temporary.
