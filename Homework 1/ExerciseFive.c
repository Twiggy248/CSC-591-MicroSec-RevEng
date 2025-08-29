#include <stdio.h>
#include <immintrin.h> // Library for _rdtscp and AVX operations
#include <string.h>
#include <unistd.h> // Library for usleep

/**
    @file ExerciseFive.c
    @author Caleb Twigg
    Exercise Five: Time an AVX multiplication, wait for 100 ms, and time another AVX multiplication. 
    Is there a timing difference? Repeat 1M times and plot a distribution of data.
*/
int main() {

    // Note: Recorded the difference in the first and second operation timings just in case
    // it was later revealed that it was information needed

    // Create the results csv file
    FILE *fp = fopen("Exercise5_Results.csv", "w");
    fprintf(fp, "Trial,First,Second,Difference\n");

    // Initialize variables for timing
    int beforeOp, afterOp, first, second;
    int aux;
    
    // Load in the virtual registers
    __m256 evens = _mm256_set_ps (2.0 , 4.0 , 6.0 , 8.0 , 10.0 , 12.0 , 14.0 , 16.0) ;
    __m256 odds = _mm256_set_ps (1.0 , 3.0 , 5.0 , 7.0 , 9.0 , 11.0 , 13.0 , 15.0) ;
    volatile __m256 result;

    // Loop 1M times and record the results in the csv file
    for (int i = 0; i < 1000000; i++) {
        
        // Perform and time the 1st operation
        beforeOp = __rdtscp(&aux);
        result = _mm256_mul_ps(evens,odds);
        afterOp = __rdtscp(&aux);

        first = afterOp - beforeOp;

        // Wait for 100ms
        usleep(100000);

        // Perform and time the 2nd operation
        beforeOp = __rdtscp(&aux);
        result = _mm256_mul_ps(evens,odds);
        afterOp = __rdtscp(&aux);

        second = afterOp - beforeOp;

        // Store results in csv file
        fprintf(fp, "%d,%d,%d,%d\n", i + 1, first, second, first-second);

    }

    // Close the results csv file pointer
    fclose(fp);

    return 0;
}