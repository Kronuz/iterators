# Architecture

Two headers of small, lazy iteration adaptors — forward-iterator wrappers you drop into
a range-for. No allocation, no materialization, no ranges-v3; each adaptor holds
iterators and transforms on the fly.

## The adaptors

- **`itertools::transform(fn, begin, end)`** (`itertools.hh`) — yields `fn(*it)` for each
  element, lazily. The `value_type` is whatever `fn` returns.
- **`itertools::chain(b1, e1, b2, e2)`** (`itertools.hh`) — iterates the first range to
  its end, then the second, as one sequence.
- **`reversed(iterable)`** (`reversed.hh`) — a reversing range adaptor built on
  `std::rbegin` / `std::rend`.

Each returns a lightweight object with `begin()`/`end()` (or is one), so it composes
directly with a range-for.

## Dependencies

**None.** Standard library only (`<iterator>`).

## Notes / invariants

- The adaptors' iterators declare the five member types `std::iterator_traits` reads
  (`iterator_category`, `value_type`, `difference_type`, `pointer`, `reference`), copied from
  the source iterator (the second one for `chain`), and derive from nothing: `std::iterator`
  is deprecated since C++17 and warns. The test target builds with `-Werror -Wdeprecated`.
- Consumers include `itertools.hh` and/or `reversed.hh` by name; keep those filenames.
