#include <stdio.h>

// Exercise One: Time a cache hit and miss, report the results. 
// Repeat 1M times and plot a distribution of data collected for misses and hits.
int main() {

    // Create the results csv file
    FILE *fp = fopen("results.csv", "w");

    // Flush the cache
    _mm_clflush();

    // Loop 1M times
    for (int i = 0; i < 1000000; i++) {
        // Time a cache miss

        // Time a cache hit

        // Store results in csv file

        // Flush the cache
        _mm_clflush();

    }

    // Close the results csv file pointer
    fclose(fp);

    return 0;
}