# utf8proc Proof-Of-Concept results

## Benchmarking NFC normalization for different languages


- NFC normalization for **korean** takes 28.8202 ns/byte on average.
- NFC normalization for **greek** takes 30.7518 ns/byte on average.
- NFC normalization for **english** takes 30.341 ns/byte on average.
- NFC normalization for **chinese** takes 15.0701 ns/byte on average.
- NFC normalization for **japanese** takes 20.1697 ns/byte on average.
- NFC normalization for **vietnamese** takes 44.8031 ns/byte on average.

==============================================================

## Testing encode and decode

Test data:
```txt
'Valid ASCII' => "a",
'Valid 2 Octet Sequence' => "\xc3\xb1",
'Invalid 2 Octet Sequence' => "\xc3\x28",
'Invalid Sequence Identifier' => "\xa0\xa1",
'Valid 3 Octet Sequence' => "\xe2\x82\xa1",
'Invalid 3 Octet Sequence (in 2nd Octet)' => "\xe2\x28\xa1",
'Invalid 3 Octet Sequence (in 3rd Octet)' => "\xe2\x82\x28",
'Valid 4 Octet Sequence' => "\xf0\x90\x8c\xbc",
'Invalid 4 Octet Sequence (in 2nd Octet)' => "\xf0\x28\x8c\xbc",
'Invalid 4 Octet Sequence (in 3rd Octet)' => "\xf0\x90\x28\xbc",
'Invalid 4 Octet Sequence (in 4th Octet)' => "\xf0\x28\x8c\x28",
```

- Valid ASCII                                       [✅]
- Decoded UTF-8 character looks like a
- Valid 2 Octet Sequence                            [✅]
- Decoded UTF-8 character looks like ñ
- Invalid 2 Octet Sequence                          [✅]

- Invalid Sequence Identifier                       [✅]

- Valid 3 Octet Sequence                            [✅]

- Decoded UTF-8 character looks like ₡

- Invalid 3 Octet Sequence (in 2nd Octet)           [✅]

- Invalid 3 Octet Sequence (in 3rd Octet)           [✅]

- Valid 4 Octet Sequence                            [✅]

- Decoded UTF-8 character looks like 𐌼

- Invalid 4 Octet Sequence (in 2nd Octet)           [✅]

- Invalid 4 Octet Sequence (in 3rd Octet)           [✅]

- Invalid 4 Octet Sequence (in 4th Octet)           [✅]

- Encoding takes 16.7188 ns/byte on average.

- Validation takes 9.25 ns/byte on average.

- Decoding takes 11.1875 ns/byte on average.

========================================================================

## Memory usage for normalization


- **korean** saw a 0% increase in memory consumption for string storage after  NFC normalization.

- Normalization process consumed about ~0Kb/bytes of string normalized.

- **greek** saw a -3.02687% increase in memory consumption for string storage after  NFC normalization.

- Normalization process consumed about ~0Kb/bytes of string normalized.

- **english** saw a 0% increase in memory consumption for string storage after  NFC normalization.

- Normalization process consumed about ~0Kb/bytes of string normalized.

- **chinese** saw a 0% increase in memory consumption for string storage after  NFC normalization.

- Normalization process consumed about ~0Kb/bytes of string normalized.

- **japanese** saw a 0% increase in memory consumption for string storage after  NFC normalization.

- Normalization process consumed about ~0Kb/bytes of string normalized.

- **vietnamese** saw a 0% increase in memory consumption for string storage after  NFC normalization.

- Normalization process consumed about ~0Kb/bytes of string normalized.

========================================================================

## Validating normalization

κόσμε with size 11

- Normalization C:  κόσμε with size 10
- Normalization D:  κόσμε with size 12
- Normalization KD: κόσμε with size 12
- Normalization KC: κόσμε with size 10
