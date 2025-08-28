#include <stdio.h>
#include <immintrin.h> // Library for _rdtscp and AVX2 Operations
#include <string.h>
/**
    @file ExerciseTwo.c
    @author Caleb Twigg
    Exercise Two: Time any AVX2 operation
*/
int main() {

    // Initialize variables for timing
    int beforeOp, afterOp, elapsedTime;
    int aux;
    
    // Load in the virtual registers
    __m256 evens = _mm256_set_ps (2.0 , 4.0 , 6.0 , 8.0 , 10.0 , 12.0 , 14.0 , 16.0) ;
    __m256 odds = _mm256_set_ps (1.0 , 3.0 , 5.0 , 7.0 , 9.0 , 11.0 , 13.0 , 15.0) ;
    volatile __m256 result;
    
    // Perform and time the operation
    beforeOp = __rdtscp(&aux);
    result = _mm256_mul_ps(evens,odds);
    afterOp = __rdtscp(&aux);

    printf("Time: %d\n", afterOp-beforeOp);

    return 0;
}