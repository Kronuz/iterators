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

- `itertools.hh` still derives its iterators from the deprecated `std::iterator` base —
  verbatim from Xapiand, left as-is to keep the extraction faithful. Modernizing it (to
  explicit member typedefs) is a deliberate change, not a drive-by.
- Consumers include `itertools.hh` and/or `reversed.hh` by name; keep those filenames.
