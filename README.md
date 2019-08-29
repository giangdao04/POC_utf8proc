============================================================================

[ INFO ] Benchmarking NFC normalization for different languages


[ INFO ] NFC normalization for korean takes 28.8202 ns/byte on average.
[ INFO ] NFC normalization for greek takes 30.7518 ns/byte on average.
[ INFO ] NFC normalization for english takes 30.341 ns/byte on average.
[ INFO ] NFC normalization for chinese takes 15.0701 ns/byte on average.
[ INFO ] NFC normalization for japanese takes 20.1697 ns/byte on average.
[ INFO ] NFC normalization for vietnamese takes 44.8031 ns/byte on average.

============================================================================
============================================================================

[ INFO ] Testing encode and decode


[ INFO ] Valid ASCII                                       [✅]
[ INFO ] Decoded UTF-8 character looks like a
[ INFO ] Valid 2 Octet Sequence                            [✅]
[ INFO ] Decoded UTF-8 character looks like ñ
[ INFO ] Invalid 2 Octet Sequence                          [✅]
[ INFO ] Invalid Sequence Identifier                       [✅]
[ INFO ] Valid 3 Octet Sequence                            [✅]
[ INFO ] Decoded UTF-8 character looks like ₡
[ INFO ] Invalid 3 Octet Sequence (in 2nd Octet)           [✅]
[ INFO ] Invalid 3 Octet Sequence (in 3rd Octet)           [✅]
[ INFO ] Valid 4 Octet Sequence                            [✅]
[ INFO ] Decoded UTF-8 character looks like 𐌼
[ INFO ] Invalid 4 Octet Sequence (in 2nd Octet)           [✅]
[ INFO ] Invalid 4 Octet Sequence (in 3rd Octet)           [✅]
[ INFO ] Invalid 4 Octet Sequence (in 4th Octet)           [✅]
[ INFO ] Encoding takes 16.7188 ns/byte on average.
[ INFO ] Validation takes 9.25 ns/byte on average.
[ INFO ] Decoding takes 11.1875 ns/byte on average.

============================================================================
============================================================================

[ INFO ] Memory usage for normalization


[ INFO ] korean saw a 0% increase in memory consumption for string storage after  NFC normalization.
[ INFO ] Normalization process consumed about ~0Kb/bytes of string normalized.
[ INFO ] greek saw a -3.02687% increase in memory consumption for string storage after  NFC normalization.
[ INFO ] Normalization process consumed about ~0Kb/bytes of string normalized.
[ INFO ] english saw a 0% increase in memory consumption for string storage after  NFC normalization.
[ INFO ] Normalization process consumed about ~0Kb/bytes of string normalized.
[ INFO ] chinese saw a 0% increase in memory consumption for string storage after  NFC normalization.
[ INFO ] Normalization process consumed about ~0Kb/bytes of string normalized.
[ INFO ] japanese saw a 0% increase in memory consumption for string storage after  NFC normalization.
[ INFO ] Normalization process consumed about ~0Kb/bytes of string normalized.
[ INFO ] vietnamese saw a 0% increase in memory consumption for string storage after  NFC normalization.
[ INFO ] Normalization process consumed about ~0Kb/bytes of string normalized.
============================================================================

============================================================================

[ INFO ] Validating normalization

κόσμε with size 11
[ INFO ] Normalization C:  κόσμε with size 10
[ INFO ] Normalization D:  κόσμε with size 12
[ INFO ] Normalization KD: κόσμε with size 12
[ INFO ] Normalization KC: κόσμε with size 10
============================================================================

