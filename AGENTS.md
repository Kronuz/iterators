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
