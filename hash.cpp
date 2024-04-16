// Hashing from: https://github.com/PeterScott/murmur3
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "helper.cpp"
#include "hashing/crc32.cpp"
#include "murmur/murmur3.c"
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <stdint.h>
#include <fstream> // for std::ofstream
using namespace std;

#define number_of_iterations 100
#define number_of_hashes 2
// #ifndef CAM_SIZE //if not defined used default values
// #define CAM_SIZE 32
// #endif

// #ifndef division_of_cam //if not defined used default values
// #define division_of_cam 8
// #endif

// #ifndef range_of_CAM //if not defined used default values
// #define range_of_CAM 128
// #endif
int main(int argc, char *argv[])
{ // seed for random number generation

    if (argc != 4) // Check the value of argc. If not enough parameters have been passed, inform user and exit.
    {
        std::cerr << "Usage: " << argv[0] << " CAM_SIZE division_of_cam range_of_CAM\n";
        return 1;
    }

    int CAM_SIZE = std::atoi(argv[1]);
    int division_of_cam = std::atoi(argv[2]);
    int range_of_CAM = std::atoi(argv[3]);

    int false_positive_rate = 0;
    int false_negative_rate = 0; // if it says its not there but it is actually there

    std::cout << "Value of CAM size is:" << CAM_SIZE << endl;
    std::cout << "Number of sub banks are:" << division_of_cam << endl;
    std::cout << "Value of range of CAM is:" << range_of_CAM << endl;
    std::srand(std::time(0));
    // Pre defined values
    int size = CAM_SIZE;

    std::vector<int> array_range_of_cam(range_of_CAM); // creates a vector of size 128. Basically possible values to store between LN_Reg (2^(n+k))
    std::vector<int> positive_rate_measure(number_of_iterations);
    std::vector<int> negative_rate_measure(number_of_iterations);
    // Bloom filters variable
    int number_of_bloom_filters = division_of_cam;
    int number_of_elements_in_each_cam = CAM_SIZE / division_of_cam;

    // populate with sequential values
    //  poplate with sequential values
    for (int i = 0; i < range_of_CAM; ++i)
    {
        array_range_of_cam[i] = i;
    }
    // Hashing variables
    for (int iteration_number = 0; iteration_number < number_of_iterations; iteration_number++)
    {
        false_positive_rate = 0;
        false_negative_rate = 0;
        // define new bloom filters
        int *bloom_filter = new int[number_of_bloom_filters];
        //intialize each bloom filter to 0
        for (int i = 0; i < number_of_bloom_filters; i++)
        {
            bloom_filter[i] = 0;
        }

        // define a new seed for the hashing
        uint32_t seed = rand()%100; /* Seed value for hash */

        uint32_t hash_output_arr[size*number_of_hashes]; // save the hash output in this array

        // Logic for random values
        int arr[size]; // Array to store random values
        // Generate random seed

        // Shuffle the array
        for (int i = range_of_CAM - 1; i > 0; --i)
        {
            int j = std::rand() % (i + 1);                           // Generate random index
            std::swap(array_range_of_cam[i], array_range_of_cam[j]); // Swap elements at indices i and j
        }

        // take the first "size" values
        for (int i = 0; i < size; ++i)
        {
            arr[i] = array_range_of_cam[i];
        }

        // Print the array
        print_array(arr, size);
        // Logic for random values ends

        // Main logic
        // Divide each CAM into the number of divisions and use hash the values and store the values

        for (int i = 0; i < size; ++i)
        {

            MurmurHash3_x86_32(&arr[i], sizeof(arr[i]), seed, &hash_output_arr[i]);
            // cout << "hash_output_arr is:" << std::hex << hash_output_arr[i] << endl;
        }

        // Now i need to perform a bit wise or of the hash_output_arr depending on the division and store it in the bloom filter
        for (int i = 0; i < number_of_bloom_filters; i++)
        {

            // perform a bitwise or (element wise) of each of the bloom filter
            for (int j = i * number_of_elements_in_each_cam; j < (i + 1) * number_of_elements_in_each_cam; j++)
            {
                // cout<<"performing for Cam number i:"<<i<<" and element j:"<<j<<endl;
                bloom_filter[i] = bloom_filter[i] | hash_output_arr[j];
            }
        }

        // print all the values in the bloom filter
        for (int i = 0; i < number_of_bloom_filters; i++)
        {
            cout << "bloom_filter is:" << std::hex << bloom_filter[i] << std::endl;
        }

        // Free the memory
        // Test working of equation
        // match'=H(D)'.BF
        // take bitwise complement of the search query

        // // test values
        // uint32_t search_query = 0x4000;
        // uint32_t bloom_filter_value = 0x18400;
        // Choose a random value between the index from the array itself
        int value_to_match = arr[rand() % size];
        cout << "Value to match is:" << value_to_match << endl;

        // search this value in cam and return the index
        int index = linear_search(arr, size, value_to_match);
        cout << "\n Index of the value is:" << std::dec << index << endl;
        cout << "Value at index is:" << arr[index] << endl;

        // get the bank number on the basis of index
        int bank_number = -1;
        if (index != -1)
        {
            bank_number = index / number_of_elements_in_each_cam;
        }

        // the bloom filter should return this bank number
        cout << "Bank number is:" << bank_number << endl;

        // now employ the bloom filter

        // calculate the hash of the value to match
        uint32_t hash_output_value_to_match;
        MurmurHash3_x86_32(&value_to_match, sizeof(value_to_match), seed, &hash_output_value_to_match);
        cout << "hash_output of integer is:" << hash_output_value_to_match << endl;
        cout << "\n\n";
        // now for each of the bloom filters call the matching bloom filter function
        for (int i = 0; i < number_of_bloom_filters; i++)
        {
            if (matching_bloom_filter(hash_output_value_to_match, bloom_filter[i]))
            {
                cout << "Match found in bank number:" << i << endl;
                if (i != bank_number) // if it does not match the answer implies positive rate
                {
                    false_positive_rate++;
                }
            }
            else
            {
                cout << "Match not found in bank number:" << i << endl;
                if (i == bank_number)
                {
                    false_negative_rate++;
                }
            }
        }

        cout << "\nThe false postive rate is " << (false_positive_rate * 100) / (division_of_cam) << endl;
        cout << "The false negative rate is " << (false_negative_rate * 100) / (division_of_cam) << endl;

        positive_rate_measure[iteration_number] = (false_positive_rate * 100) / (division_of_cam);
        negative_rate_measure[iteration_number] = (false_negative_rate * 100) / (division_of_cam);
        delete[] bloom_filter;
    }

    // print the postive rate
    for (int i = 0; i < number_of_iterations; i++)
    {
        cout << "Positive rate for iteration " << i << " is:" << positive_rate_measure[i] << endl;
    }

    std::ofstream file("output_of_mean.txt", std::ios::app); // Open the file in append mode
    double mean = std::accumulate(positive_rate_measure.begin(), positive_rate_measure.end(), 0.0) / positive_rate_measure.size();
    file << "Configuration is CAM_SIZE:" << CAM_SIZE << " division_of_cam:" << division_of_cam << " range_of_CAM:" << range_of_CAM << std::endl;
    file << "\n mean " << mean << std::endl;
    file.close();
    return 0;
}
