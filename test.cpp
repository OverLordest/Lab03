#include "histogram.h"
#include "histogram_svg.h"
#include <cassert>

void test_positive()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}
void
test_negative()
{
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}
void
test_1_3()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 1, 1}, min, max);
    assert(min == 1);
    assert(max == 1);
}
void
test_1_1()
{
    double min = 0;
    double max = 0;
    find_minmax({1}, min, max);
    assert(min == 1);
    assert(max == 1);
}
void
test_empty()
{
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}
void
test_proc()
{
    size_t bin=10;
    size_t number_count=100;
    double p = proc(bin,number_count);
    assert(p == 10);
}
test_proc2()
{
    size_t bin=100;
    size_t number_count=0;
    double p = proc(bin,number_count);
    assert(p == 0);
}
int
main()
{
    test_positive();
    test_negative();
    test_1_3();
    test_1_1();
    test_empty();
    test_proc();
    test_proc();
}
