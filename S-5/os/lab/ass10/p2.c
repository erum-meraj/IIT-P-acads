#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    unsigned int num_pages, num_frames;

    // Input for number of pages and number of frames
    printf("Enter the number of pages: ");
    scanf("%u", &num_pages);
    printf("Enter the number of frames: ");
    scanf("%u", &num_frames);

    // Check if the number of frames is at least equal to the number of pages
    if (num_frames < num_pages) {
        printf("Error: Number of frames should be at least equal to the number of pages.\n");
        return 1;
    }

    // Initialize the page table array to store the frame number for each page
    int page_table[num_pages];

    // Initialize an array to keep track of used frames
    int used_frames[num_frames];
    for (int i = 0; i < num_frames; i++) {
        used_frames[i] = 0;
    }

    // Seed the random number generator
    srand(time(0));

    // Assign each page to a unique frame randomly
    for (int i = 0; i < num_pages; i++) {
        int frame;
        do {
            frame = rand() % num_frames; // Generate a random frame number
        } while (used_frames[frame]); // Repeat if frame is already used

        used_frames[frame] = 1; // Mark the frame as used
        page_table[i] = frame;  // Map the page to this frame
    }

    // Output the page table
    printf("Page Table (Page Number -> Frame Number):\n");
    for (int i = 0; i < num_pages; i++) {
        printf("Page %d -> Frame %d\n", i, page_table[i]);
    }

    return 0;
}
