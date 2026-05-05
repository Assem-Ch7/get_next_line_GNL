*This activity has been created as part of the 42 curriculum by aschebly.*

# get_next_line

## Description
The `get_next_line` project is a fundamental C programming challenge designed to teach the use of static variables and dynamic memory allocation. The goal of this activity is to write a function that returns a single line read from a file descriptor (`fd`). 

By calling the function in a loop, a program can read an entire text file line-by-line without loading the entire file into memory at once. It safely handles varying buffer sizes, consecutive newlines, and End-Of-File (EOF) conditions without causing memory leaks or segmentation faults.

## Algorithm Explanation and Justification

Below is the visual flowchart of the implemented logic:

![get_next_line Flowchart]

**The Algorithm (Buffer-to-Stash Accumulation):**
1. **Validation:** The function first checks if the file descriptor or `BUFFER_SIZE` is invalid.
2. **Reading (`read_to_stash`):** We allocate a temporary `buf` on the heap. Using a `while` loop, we read chunks of data from the file into `buf`. After every successful read, we use `ft_strjoin_and_free` to append the new chunk onto our `static char *stash`.
3. **Early Exit:** The reading loop immediately breaks the moment a `\n` is detected in the `stash`, fulfilling the requirement to "read as little as possible."
4. **Extraction (`ft_strdup_modified`):** We scan the `stash` up to the first `\n`, allocate an exactly-sized string, and extract the complete line.
5. **Cleanup (`clean_stash`):** We identify the remaining characters after the `\n` in the `stash`, copy them into a new pointer, and free the old memory. The static variable is updated with the leftovers for the next function call.

**Justification:**
This algorithm was chosen because it cleanly separates responsibilities into specialized helper functions, adhering to the 42 Norm. By allocating the temporary buffer on the heap (`malloc(BUFFER_SIZE + 1)`) rather than the stack, the code survives extreme testing values (e.g., `BUFFER_SIZE=10000000`). Relying on a single `static char *` ensures that memory is strictly controlled and efficiently cleaned up even when encountering unexpected EOFs.

## Instructions

**Compilation:**
Because this project relies on the `read()` function, you must define the `BUFFER_SIZE` at compile time using the `-D` flag. 
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c

**Execution:**

This project provides a function intended for integration into larger C applications. To utilize get_next_line in your code:

    1. Include the Header
    Add the following include directive to your C source files to access the function prototype:
    

    #include "get_next_line.h"

    2. Implement the Reading Loop
    The function should be called within a loop to retrieve the file content line-by-line. It is the caller's responsibility to free the memory allocated for each line to prevent memory leaks.
    #include "get_next_line.h"
    #include <fcntl.h>
    #include <stdio.h>
    #include <stdlib.h>

    int main(void)
    {
        int     fd;
        char    *line;

        fd = open("test_file.txt", O_RDONLY);
        if (fd == -1)
            return (1);
        while ((line = get_next_line(fd)) != NULL)
        {
            printf("%s", line);
            free(line); // Critical: avoid memory leaks
        }
        close(fd);
        return (0);
    }
**Resources:**
*   **Manuals:** `man 2 read`, `man 3 malloc`, `man 3 free`
*   **Concepts:** C Static Variables, File Descriptors, Heap vs. Stack memory allocation.
*   **AI Usage:**
    *   AI was utilized to generate a Mermaid.js logic flowchart based on the written C code to better understand the execution path.
    *   AI assisted in formatting this README.md document to ensure it met all formatting guidelines outlined in the subject requirements. All code logic and implementation remain originally written and fully understood by the author.
