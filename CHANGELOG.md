# Changelog

Notable changes to `iterators`, newest first. The format follows
[Keep a Changelog](https://keepachangelog.com/en/1.1.0/); the library has no releases, so
entries are dated.

## 2026-11-01

### Changed

- The README follows the family README standard: the description as its first sentence,
  Quick start before Installation, a pinned FetchContent tag, and "Not for" limits. It
  names CMake 3.16, the version `CMakeLists.txt` requires, where it said 3.14, and no
  longer recommends the library for pre-C++20 code, since the target requires C++20. The
  limits name raw-pointer iterators, by-value elements and `reversed` of a temporary.
