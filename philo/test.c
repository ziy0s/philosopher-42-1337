#include <stdio.h>

// Function to delay for a specified number of microseconds
void delay_microseconds(long microseconds)
{
    // Approximate number of iterations per microsecond (calibrate this for your CPU)
    const long iterations_per_microsecond = 1000; // Example value, needs calibration

    // Total iterations for the desired delay
    long total_iterations = microseconds * iterations_per_microsecond;

    // Busy-wait loop
    volatile long i = 0; // 'volatile' prevents the compiler from optimizing away the loop
    while (i < total_iterations)
    {
        i++;
    }
}

int main(void)
{
    printf("Starting delay...\n");
    delay_microseconds(5000000); // Delay for 500,000 microseconds (0.5 seconds)
    printf("Delay complete!\n");

    return 0;
}
