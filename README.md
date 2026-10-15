# iterators

[![CI](https://github.com/Kronuz/iterators/actions/workflows/ci.yml/badge.svg)](https://github.com/Kronuz/iterators/actions/workflows/ci.yml)

Lightweight, lazy iteration adaptors extracted from
[Xapiand](https://github.com/Kronuz/Xapiand). No allocation, no ranges-v3 -- just
small forward-iterator wrappers you drop into a range-for.

```cpp
#include "itertools.hh"   // itertools::transform, itertools::chain
#include "reversed.hh"    // reversed()

for (auto x : itertools::transform([](int n){ return n*2; }, v.begin(), v.end())) { ... }
for (auto x : itertools::chain(a.begin(), a.end(), b.begin(), b.end())) { ... }  // a then b
for (auto x : reversed(v)) { ... }   // back to front, via std::rbegin/rend
```

- `itertools::transform(fn, begin, end)` -- lazily maps each element through `fn`.
- `itertools::chain(b1, e1, b2, e2)` -- iterates two ranges back to back.
- `reversed(iterable)` -- a reversing range adaptor over `std::rbegin`/`std::rend`.

Header-only, standard-library only.

## Dependencies

**None** — header-only, standard library only.

## Build / test
```sh
cmake -B build && cmake --build build && ctest --test-dir build
```

## Use (FetchContent)
```cmake
FetchContent_Declare(iterators GIT_REPOSITORY https://github.com/Kronuz/iterators.git GIT_TAG main)
FetchContent_MakeAvailable(iterators)
target_link_libraries(your_app PRIVATE iterators::iterators)
```
