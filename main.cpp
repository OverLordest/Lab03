#include "histogram.h"
#include "histogram_svg.h"
#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

vector<double> input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}
vector <size_t> make_histogram(vector <double> numbers,size_t bin_count,double min,double max)
{
    vector<size_t> bins(bin_count);
    for (double number : numbers)
    {
        size_t bin = (size_t)((number - min) / (max - min) * bin_count);
        if (bin == bin_count)
        {
            bin--;
        }
        bins[bin]++;
    }
    return(bins);
}
void show_histogram_text(vector<size_t>bins,size_t number_count)
{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;

    size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;

    for (size_t bin : bins)
    {
        if (bin < 100)
        {
            cout << ' ';
        }
        if (bin < 10)
        {
            cout << ' ';
        }
        cout << bin << "|";

        size_t height = bin;
        if (scaling_needed)
        {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            height = (size_t)(bin * scaling_factor);
        }

        for (size_t i = 0; i < height; i++)
        {
            cout << '*';
        }
        cout<<' ';
        for (size_t i=height;i<max_count+1;i++)
            {
            cout<<" ";
            }
        cout<<(double)bin/number_count*100<<"%";
        cout << '\n';
    }
}


int main()
{

    DWORD mask = 0x0000ffff;
    DWORD mask_major = 0b00000000'00000000'00000000'11111111;
    DWORD info = GetVersion();
    DWORD platform = info >> 16;
    DWORD version = info & mask;
    DWORD version_major = version & mask_major;
    DWORD version_minor = version >> 8;
    printf("Windows v%u.%u (build %u)",version_major,version_minor,platform );
    //printf(" Build %u", platform);
    //printf("Your platform is %u.", platform);
    //printf("Windows major version is %u.", version_major);
    //printf("Windows minor version is %u.", version_minor);

  /*  if ((info & 0x40000000) == 0) {
        DWORD build = platform;
        printf(" build %u", build);
    }*/

   /* // ���� ������
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    cerr << "Enter numbers: ";
    const auto numbers=input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;

    // ��������� ������
    double min;
    double max;
    find_minmax(numbers,min,max);

    const auto bins = make_histogram(numbers, bin_count,min,max);
    show_histogram_svg(bins,number_count); */




    // ����� ������


    return 0;
}
