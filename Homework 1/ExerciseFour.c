#include <stdio.h>
#include <immintrin.h> // Library for _rdtscp
#include <string.h>
#include <unistd.h> // Library for usleep

/**
    @file ExerciseFour.c
    @author Caleb Twigg
    Exercise Four: Time an AVX512 multiplication, wait for 100 ms (for example with usleep), and time another AVX512 multiplication. Is
    there a timing difference? Repeat 1M times and plot a distribution of data.
*/
int main() {

    // Note: Recorded the difference in the first and second operation timings just in case
    // it was later revealed that it was information needed

    // Create the results csv file
    FILE *fp = fopen("Exercise4_Results.csv", "w");
    fprintf(fp, "Trial,First,Second,Difference\n");

    // Initialize variables for timing
    int beforeOp, afterOp, first, second;
    int aux;
    
    // Load in the virtual registers (this time using the mm512 operation in the AVX512 family)
    __m512 evens = _mm512_set_ps (2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 22.0, 24.0, 26.0, 28.0, 30.0, 32.0);
    __m512 odds = _mm512_set_ps (1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0, 17.0, 19.0, 21.0, 23.0, 25.0, 27.0, 29.0, 31.0);
    volatile __m512 result;

    // Loop 1M times and record the results in the csv file
    for (int i = 0; i < 1000000; i++) {
        
        // Perform and time the 1st operation
        beforeOp = __rdtscp(&aux);
        result = _mm512_mul_ps(evens,odds);
        afterOp = __rdtscp(&aux);

        first = afterOp - beforeOp;

        // Wait for 100ms
        usleep(100);

        // Perform and time the 2nd operation
        beforeOp = __rdtscp(&aux);
        result = _mm512_mul_ps(evens,odds);
        afterOp = __rdtscp(&aux);

        second = afterOp - beforeOp;

        // Store results in csv file
        fprintf(fp, "%d,%d,%d,%d\n", i + 1, first, second, first-second);

    }

    // Close the results csv file pointer
    fclose(fp);

    return 0;
}