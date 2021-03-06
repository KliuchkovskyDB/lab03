#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"

using namespace std;

vector<double>input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}

vector <size_t>make_histogram(const vector<double>& numbers,  size_t &bin_count , double min, double max)
{
    vector <size_t> bins (bin_count);
    for (double number: numbers)
    {
       size_t bin = (size_t)((number-min)/(max-min)*bin_count);
       if (bin==bin_count)
       {
           bin--;
       }
       bins[bin]++;
}
return bins;
}

void show_histogram_text (vector<size_t> bins)
{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

    size_t max_bins = bins [0];
    for (size_t bin : bins)
    {
        if (bin > max_bins)
        {
            max_bins = bin;
        }
    }
    for (size_t bin : bins)
    {
        size_t height = bin;
        if (max_bins > MAX_ASTERISK)
        {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_bins);
        }
        if (bin<100)
        {
            cout<< " ";
        }
        if (bin < 10)
        {
            cout<< " ";
        }
        cout << bin << "|";
        for (size_t i=0; i<height; i++)
        {
            cout<<"*";
        }
        cout<<'\n';
    }
}

int main()
{
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    cerr << "Enter numbers: ";
    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter bin count: \n";
    cin >> bin_count;

    double min;
    double max;
    find_minmax(numbers, min, max);

    const auto bins = make_histogram(numbers,bin_count , min, max);

    show_histogram_svg(bins);

    return 0;
}
