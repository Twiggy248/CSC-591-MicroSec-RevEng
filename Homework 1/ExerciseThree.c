#include <stdio.h>
#include <immintrin.h> // Library for _rdtscp and AVX512 Operations
#include <string.h>
/**
    @file ExerciseThree.c
    @author Caleb Twigg
    Exercise Three: Time any AVX512 operation.
*/
int main() {

    // Initialize variables for timing
    int beforeOp, afterOp, elapsedTime;
    int aux;
    
    // Load in the virtual registers (this time using the mm512 operation in the AVX512 family)
    __m512 evens = _mm512_set_ps (2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 22.0, 24.0, 26.0, 28.0, 30.0, 32.0);
    __m512 odds = _mm512_set_ps (1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0, 17.0, 19.0, 21.0, 23.0, 25.0, 27.0, 29.0, 31.0);
    volatile __m512 result;
    
    // Perform and time the operation
    beforeOp = __rdtscp(&aux);
    result = _mm512_mul_ps(evens,odds);
    afterOp = __rdtscp(&aux);

    printf("Time: %d\n", afterOp-beforeOp);

    return 0;
}