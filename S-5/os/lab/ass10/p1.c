#include <stdio.h>
#include <math.h>

int main() {
    unsigned int virtual_address_space_bits;
    unsigned int page_size_kb;
    unsigned int physical_memory_size_mb;

    // Input for virtual address space (in bits), page size (in KB), and physical memory size (in MB)
    printf("Enter the virtual address space (in bits): ");
    scanf("%u", &virtual_address_space_bits);
    printf("Enter the page size (in KB): ");
    scanf("%u", &page_size_kb);
    printf("Enter the physical memory size (in MB): ");
    scanf("%u", &physical_memory_size_mb);

    // Convert page size to bytes
    unsigned long long page_size_bytes = page_size_kb * 1024;

    // Calculate total virtual address space in bytes
    unsigned long long virtual_address_space_bytes = (unsigned long long)1 << virtual_address_space_bits;

    // Calculate the number of pages in virtual address space
    unsigned long long number_of_pages = virtual_address_space_bytes / page_size_bytes;

    // Convert physical memory size to bytes
    unsigned long long physical_memory_size_bytes = physical_memory_size_mb * 1024 * 1024;

    // Calculate the number of frames in physical memory
    unsigned long long number_of_frames = physical_memory_size_bytes / page_size_bytes;

    // Output the results
    printf("Number of pages in the virtual address space: %llu\n", number_of_pages);
    printf("Number of frames in the physical memory: %llu\n", number_of_frames);

    return 0;
}
