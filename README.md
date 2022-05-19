Testing how to get a logical right shift from an arithmetic right shift with no
branching. Here it is, where we are logically right shifting `num` by `k`, and
`n` is the number of bits in `num` (and is a power of 2):

```c
(num >> k) & (~((-((num >> (n-1)) & 0x1)) << (n - k)) | (-((k & (n-1)) == 0)))
```

To test this locally, you can do `make && ./tests`.
