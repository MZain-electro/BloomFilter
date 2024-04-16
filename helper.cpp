#include "helper.h"
using namespace std;


bool matching_bloom_filter(uint32_t search_query, uint32_t bloom_filter_value)
{
    uint32_t match = (~search_query) | bloom_filter_value;
    // now take complement of match
    uint32_t match_prime = ~match;
    //  if all zero implies match , if non zero implies no match
    if (match_prime == 0) //if all 0 implies true
    {   
       // cout<<"Match found"<<endl;
        return true;
    }
    else
    {
        //cout<<"Match not found"<<endl;
        return false;
    }
}

void print_array(int *arr, int size)
{
    for (int i = 0; i < size; ++i)
    {
        std::cout <<std::dec<< arr[i] << " ";
    }
    std::cout << std::endl;
}

// take the whole array, convert it to a string and then hash it


//linear search of the index value

//returns the index of the value in array if found else returns -1
int linear_search(int *arr, int size, int value)
{   printf("\n");
    for (int i = 0; i < size; ++i)
    {printf("%d ",arr[i]);
        if (arr[i] == value)
        {   
          //  cout<<"Value found at index:"<<i<<endl;
            return i;
        }
    }
    return -1;
}