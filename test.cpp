#include "histogram.h"

#include <cassert>

void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == -1);
    assert(max == -1);
}

int
main() {
    test_positive();
}
