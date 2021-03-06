#include "histogram_svg.h"
#include <iostream>

using namespace std;
void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}
void svg_end()
{
    cout << "</svg>\n";
}
void svg_rect(double x, double y, double width, double height,string stroke,string fill)
{
    cout << "<rect x='"<<x<<"' y='"<<y<<"' width='"<<width<<"' height='"<<height<<"' stroke='"<<stroke<<"' fill='"<<fill<<"' />";
}
void svg_text(double left, double baseline, string text,double bin)
{
    cout << "<text x='" << left << "' y='"<<baseline<<"'>"<<bin<<text<<"</text>";
}
/*double proc(size_t bin,size_t number_count)
{
    const size_t rounding=10;
    return(round((double)bin/number_count*100*rounding)/rounding);
}*/
void show_histogram_svg(const vector<size_t> bins,size_t number_count)
{
    const auto IMAGE_WIDTH = 600;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 5;
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    string stroke="black";
    string fill="red";
    size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;
    double scaling_factor = 1;
    for (size_t bin : bins)
    {
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, "",(double)bin);
        if (scaling_needed)
        {
            scaling_factor = (double)MAX_ASTERISK / max_count;
            bin = (size_t)(bin * scaling_factor);
        }

        const double bin_width = BLOCK_WIDTH * bin;
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,stroke,fill);
        svg_text(TEXT_WIDTH+TEXT_LEFT+(size_t)(max_count*BLOCK_WIDTH*scaling_factor), top + TEXT_BASELINE,"%",proc(bin,number_count));
        top += BIN_HEIGHT;

    }
    svg_end();
}
