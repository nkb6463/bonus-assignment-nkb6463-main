#include <stdio.h>

#include "utils.h"

int main() {
    printf("Rolling d4: %d\n", roll(4));
    printf("Rolling d6: %d\n", roll(6));
    printf("Rolling d8: %d\n", roll(8));
    printf("Rolling d10: %d\n", roll(10));
    printf("Rolling d12: %d\n", roll(12));
    printf("Rolling d20: %d\n", roll(20));

    return 0;
}
