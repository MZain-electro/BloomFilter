#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
using namespace std;

void print_array(int *arr, int size);

bool matching_bloom_filter(uint32_t search_query, uint32_t bloom_filter_value);

int linear_search(int *arr, int size, int value);