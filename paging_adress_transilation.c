#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int vspace_mb, page_kb;
    unsigned int virtual_address;

    unsigned int virtual_space_bytes;
    unsigned int page_size_bytes;
    unsigned int num_pages;

    unsigned int page_number, offset;
    unsigned int *page_table;

    // Check correct arguments
    if (argc != 4) {
        printf("Usage: %s <VirtualSpace_MB> <PageSize_KB> <VirtualAddress>\n", argv[0]);
        return 1;
    }

    // Input from command line
    vspace_mb = atoi(argv[1]);
    page_kb = atoi(argv[2]);
    virtual_address = atoi(argv[3]);

    // Convert to bytes
    virtual_space_bytes = vspace_mb * 1024 * 1024;
    page_size_bytes = page_kb * 1024;

    // Validate virtual address
    if (virtual_address >= virtual_space_bytes) {
        printf("Invalid Virtual Address\n");
        return 1;
    }

    // Calculate number of pages
    num_pages = virtual_space_bytes / page_size_bytes;

    // Allocate page table
    page_table = (unsigned int *)malloc(num_pages * sizeof(unsigned int));
    if (page_table == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Identity mapping: page i → frame i
    for (unsigned int i = 0; i < num_pages; i++) {
        page_table[i] = i;
    }

    // Compute page number and offset
    page_number = virtual_address / page_size_bytes;
    offset = virtual_address % page_size_bytes;

    // Address translation
    if (page_number >= num_pages) {
        printf("Page Table Miss!\n");
    } else {
        printf("\n--- Address Translation ---\n");
        printf("Virtual Address: %u\n", virtual_address);
        printf("Page Number    : %u\n", page_number);
        printf("Offset         : %u\n", offset);
        printf("Physical Addr  : <%u, %u>\n",
               page_table[page_number], offset);
    }

    // Free memory
    free(page_table);

    return 0;
}