#include <stdio.h>
#include <stdlib.h>

#define PAGE_FAULT -1 // Define a constant to represent an unmapped page

// Function to calculate the number of bits required for a given size
int calculate_bits(unsigned int size) {
    int bits = 0;
    while (size > 1) {
        size >>= 1;
        bits++;
    }
    return bits;
}

int main() {
    unsigned int num_pages, num_frames, page_size_kb;
    
    // Input for the page table details
    printf("Enter the number of pages: ");
    scanf("%u", &num_pages);
    printf("Enter the number of frames: ");
    scanf("%u", &num_frames);
    printf("Enter the page size in KB: ");
    scanf("%u", &page_size_kb);

    // Calculate page size in bytes
    unsigned int page_size_bytes = page_size_kb * 1024;

    // Create and initialize the page table with PAGE_FAULT (-1) to simulate unmapped pages
    int page_table[num_pages];
    for (int i = 0; i < num_pages; i++) {
        page_table[i] = PAGE_FAULT;
    }

    // Input mapped pages for the page table
    printf("Enter the frame number for each mapped page (enter -1 if unmapped):\n");
    for (int i = 0; i < num_pages; i++) {
        printf("Frame for Page %d: ", i);
        scanf("%d", &page_table[i]);
    }

    // Input the virtual address in hexadecimal
    unsigned int virtual_address;
    printf("Enter the virtual address in hexadecimal: ");
    scanf("%x", &virtual_address);

    // Calculate the number of bits for page number and offset
    int offset_bits = calculate_bits(page_size_bytes);
    int page_bits = calculate_bits(num_pages);

    // Extract page number and offset from virtual address
    unsigned int page_number = virtual_address >> offset_bits;
    unsigned int offset = virtual_address & (page_size_bytes - 1);

    // Check for page fault
    if (page_number >= num_pages || page_table[page_number] == PAGE_FAULT) {
        printf("Page Fault\n");
    } else {
        // Get the frame number from the page table
        int frame_number = page_table[page_number];

        // Calculate physical address
        unsigned int physical_address = (frame_number << offset_bits) | offset;

        // Output the results
        printf("Page Number: %u\n", page_number);
        printf("Offset: %u\n", offset);
        printf("Frame Number: %u\n", frame_number);
        printf("Physical Address: 0x%X\n", physical_address);
    }

    return 0;
}
