#include "histogram_svg.h"
#include <math.h>
double proc(size_t bin,size_t number_count)
{
    const size_t rounding=10;
    if((bin==0)||(number_count==0))
    {
        return(0);
    }
    else
    {
        return(round((double)bin/number_count*100*rounding)/rounding);
    }

}
