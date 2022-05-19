#include <stdio.h>
#include <inttypes.h>

static uint32_t arith_shift(uint32_t num, uint32_t k) {
    return (int32_t)num >> k;
}

static uint32_t arith_shift_fixed(uint32_t num, uint32_t k) {
    static const uint32_t n = 32;
    uint32_t mask = ~((-((num >> (n-1)) & 0x1)) << (n - k)) | (-((k & 31) == 0));
    return arith_shift(num, k) & mask;
}

static uint32_t logical_shift(uint32_t num, uint32_t k) {
    return num >> k;
}

static int run_test(uint32_t num, uint32_t k) {
    uint32_t expected = logical_shift(num, k);
    uint32_t actual = arith_shift_fixed(num, k);
    uint32_t filthy = arith_shift(num, k);

    if (actual != expected) {
        fprintf(stderr, "oops! shifted 0x%08" PRIx32 " >> %" PRIu32
                        " and expected: 0x%08" PRIx32 " but got 0x%08"
                        PRIx32 ". filthy is 0x%08" PRIx32 "\n",
                num, k, expected, actual, filthy);
        return 1;
    } else {
        fprintf(stderr, "nice, shifted 0x%08" PRIx32 " >> %" PRIu32
                        " and expected: 0x%08" PRIx32 " and got 0x%08"
                        PRIx32 " instead of 0x%08" PRIx32 "\n",
                num, k, expected, actual, filthy);
        return 0;
    }

    return 0;
}

int main(void) {
    if (run_test(-1, 1) ||
        run_test(-1, 8) ||
        run_test(4, 2) ||
        run_test(-16, 7) ||
        run_test(-8, 32) ||
        run_test(-1, 0)) {
        return 1;
    }

    return 0;
}
