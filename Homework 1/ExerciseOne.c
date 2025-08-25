#include <stdio.h>
#include <emmintrin.h> // Library for _mm_clflush and _mm_mfence
#include <immintrin.h> // Library for _rdtscp
#include <string.h>

// Exercise One: Time a cache hit and miss, report the results. 
// Repeat 1M times and plot a distribution of data collected for misses and hits.
int main() {

    // Create the results csv file
    FILE *fp = fopen("Exercise1_Results.csv", "w");
    fprintf(fp, "Trail,Hit,Miss\n");

    int hitStart, hitEnd, missStart, missEnd, hitTime, missTime;
    int aux;

    volatile char __attribute__ (( aligned (4096) ) ) x = 'A';

    // Flush the cache
    _mm_clflush((const void*)&x);
    _mm_mfence();

    // Loop 1M times
    for (int i = 0; i < 1000000; i++) {
        // Time a cache miss
        _mm_mfence();
        missStart = __rdtscp(&aux);
        (void)x;
        missEnd = __rdtscp(&aux);
        missTime = missEnd - missStart;

        // Time a cache hit
        _mm_mfence();
        hitStart = __rdtscp(&aux);
        (void)x;
        hitEnd = __rdtscp(&aux);
        hitTime = hitEnd - hitStart;

        // Store results in csv file
        fprintf(fp, "%d,%d,%d\n", i + 1, hitTime, missTime);;

        // Flush the cache
        _mm_clflush((const void*)&x);

    }

    // Close the results csv file pointer
    fclose(fp);

    return 0;
}