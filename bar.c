#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/mman.h>

FILE *output_file = NULL;

// Macro to print to both stdout and the file
#define PRINT_BOTH(...)            \
    do {                           \
        printf(__VA_ARGS__);       \
        if (output_file)          \
            fprintf(output_file, __VA_ARGS__); \
    } while (0)

uint8_t main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <input_device_or_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Open output file
    output_file = fopen("output.txt", "w");
    if (!output_file)
    {
        fprintf(stderr, "Failed to open output.txt for writing: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    uint32_t sys_handle = open(argv[1], O_RDWR | O_SYNC);
    fprintf("Opening File : %s\n", argv[1]);

    uint8_t type_width = sizeof(uint32_t);
    if (sys_handle == -1)
    {
        fprintf("Failed to open with error : %s\n", strerror(errno));
        fclose(output_file);
        return EXIT_FAILURE;
    }

    off_t target = 0;
    off_t target_base = target & ~(sysconf(_SC_PAGE_SIZE) - 1);
    uint32_t map_size = 4096UL;

    void *map_base = mmap(0, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, sys_handle, target_base);
    if (map_base == MAP_FAILED)
    {
        fprintf("Memory mapping failed: %s\n", strerror(errno));
        close(sys_handle);
        fclose(output_file);
        return EXIT_FAILURE;
    }

    fprintf("PCI Memory mapped to: 0x%08lx.\n", (unsigned long)map_base);

    for (uint16_t i = 0; i < 0x1000 / type_width + 1; i++)
    {
        uint32_t read_result = *((uint32_t *)(map_base + i * type_width + target - target_base));
        PRINT_BOTH("16'h%04X : rd_rsp_data <= 32'h%08X;\n", (uint32_t)(i * type_width + target), read_result);
    }

    munmap(map_base, map_size);
    close(sys_handle);
    fclose(output_file);

    return EXIT_SUCCESS;
}

