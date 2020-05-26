#include <sstream>
#include <string>
#include <curl/curl.h>
#include <iostream>
#include <vector>
#include "histogram.h"
#include "histogram_svg.h"
using namespace std;
struct Options
{
    size_t bins;
    bool bins_correct;
    bool use_help;
    char* url;
};
Options parse_args(int argc, char** argv)
{
    Options opt;
    opt.url=0;
    opt.bins=0;
    opt.bins_correct=false;
    opt.use_help = false;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            if (strcmp(argv[i],"-bins") == 0)
            {
                if(i+1<argc)
                {
                    opt.bins= atoi(argv[i+1]);
                    if (opt.bins)
                    {
                        opt.bins_correct=true;
                        i++;
                    }
                    else
                        {
                            opt.use_help=true;
                        }
                }

                else
                {
                    opt.use_help = true;
                }
            }
        }
        else
        {
            opt.url=argv[i];
        }
    }
    return opt;
}
vector<double>
input_numbers(istream& in,size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        in >> result[i];
    }
    return result;
}

Input
read_input(istream& in,bool prompt,const Options &opt) {
    Input data;
    size_t number_count;
    if (opt.bins_correct)
    {
        cerr << "Enter number count: ";
        in >> number_count;
        cerr << "Enter numbers: ";
        data.numbers = input_numbers(in, number_count);
        data.bin_count=opt.bins;
        return data;
    }
    if(prompt)
    {
    cerr << "Enter number count: ";
    in >> number_count;
    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);
    cerr << "Enter column count: ";
    in >> data.bin_count;
    }
    else
    {
        in >> number_count;
        data.numbers = input_numbers(in, number_count);
        in >> data.bin_count;
    }

    return data;
}

size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{
    const size_t data_size = item_size * item_count;
    const char* new_items = reinterpret_cast<const char*>(items);
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(new_items, data_size);
    return data_size;
}

Input
download(const string& address,const Options &opt) {
    stringstream buffer;

    curl_global_init(CURL_GLOBAL_ALL);

    CURL *curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if (res)
        {
            cout << curl_easy_strerror(res) << endl;
            exit(1);
        }
    }
   curl_easy_cleanup(curl);
   return read_input(buffer, false, opt);
}

int
main(int argc, char* argv[]) {
    Input input;
    Options opt=parse_args(argc,argv);
    if (opt.use_help)
    {
        cerr<<"Error";
        return 1;
    }
   if (opt.url)
    {
        input = download(opt.url,opt);
    }
    else
    {
        input = read_input(cin, true, opt);
    }
    const auto bins = make_histogram(input);
    show_histogram_svg(bins);
    //show_histogram_text(bins);
    return 0;
}
