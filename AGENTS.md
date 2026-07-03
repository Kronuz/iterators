# AGENTS

Two headers of lazy iteration adaptors extracted verbatim from Xapiand:
`itertools.hh` (`itertools::transform`, `itertools::chain`) and `reversed.hh`
(`reversed()`).

- Header-only, standard-library only. Consumers include `itertools.hh` and/or
  `reversed.hh` by name -- keep those filenames.
- Forward-iterator wrappers, lazy (no allocation/materialization). The value_type
  comes from the source iterator.
- `itertools.hh` still uses the deprecated `std::iterator` base (verbatim from
  Xapiand); left as-is to keep the extraction faithful. Modernize deliberately if ever.
- `test/test.cc` covers transform, chain concatenation, and reversed order.
