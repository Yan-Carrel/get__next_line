*This project has been created as part of the 42 curriculum by yaandria.*

# get_next_line

# Description

The get_next_line project is a fundamental exercise in file handling and memory management in C. Its objective is to implement a function that reads a file descriptor line by line, returning one line per call. This requires a precise understanding of how low-level input operations work, particularly the use of the read system call.

Unlike standard input functions, this implementation must handle buffering manually, ensuring that data read from the file is preserved between function calls. A static variable is used to store any remaining content that has not yet been returned, allowing the function to continue reading seamlessly from where it left off.

Additionally, the project emphasizes careful memory allocation and deallocation to avoid leaks, as well as robust handling of edge cases such as end-of-file, empty files, or varying buffer sizes. Overall, get_next_line strengthens skills in string manipulation, dynamic memory management, and efficient file reading in C.

# Instructions

## Compilation

To compile the project, use the cc compiler with the flags -Wall -Wextra -Werror to ensure strict error checking. The mandatory version is compiled using the files get_next_line.c, get_next_line_utils.c, and get_next_line.h. You can also define the BUFFER_SIZE for read(). For example:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl
```

The bonus version, which supports reading from multiple file descriptors simultaneously, must be compiled separately using the bonus files: `get_next_line_bonus.c`, `get_next_line_utils_bonus.c`, and `get_next_line_bonus.h`. For example:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus
```

# Resources

During the development of this project, several resources were used to better understand file descriptors, buffering, and memory management in C. These references helped clarify key concepts such as static variables, the `read` system call, and efficient string handling:

- GNU C Library Documentation (man pages: `read`, `open`, `close`)
- Linux `man 2 read` and `man 3 malloc`
- C Programming Language (K&R) – for foundational understanding of memory and pointers
- 42 School internal subjects and guidelines on `get_next_line`
- Various articles and tutorials on line-by-line file reading and buffering techniques in C

# AI Usage

Artificial Intelligence was used as a supportive tool during the development of this project. It was mainly used for:

- Clarifying concepts related to static variables and persistent buffers
- Helping understand edge cases such as EOF handling and partial reads

All core implementation work, logic design, and coding decisions were still done manually, with AI serving only as a guide for explanation and documentation support.

# Usage

To use get_next_line, include the appropriate header file and call the function in a loop until it returns `NULL`, indicating that the end of the file has been reached. Each call returns the next line from the given file descriptor, allowing you to process the file step by step.

Below is a simple example of a `main` function that reads a file and prints each line:

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

void ft_putstr(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        write(1, &str[i], 1);
        i++;
    }
}

int main(int argc, char **argv)
{
    int     fd;
    int     i;
    int     n;
    char    *line;

    fd = open(argv[1], O_RDONLY);
    n = 7;
    i = 0;
    while (i < n)
    {
        line = get_next_line(fd);
        if (line)
        {
            ft_putstr(line);
            free(line);
        }
        else
            break;
        i++;
    }
    close(fd);
    return (0);
}
```

# Features

This project implements a function that reads a file descriptor line by line, with support for both mandatory and bonus requirements. The main features include:

- Reading a file one line at a time using a custom implementation
- Handling any valid file descriptor
- Preserving unread data between function calls using static storage
- Managing dynamic memory safely to avoid leaks
- Supporting different buffer sizes defined at compile time (`BUFFER_SIZE`)
- Bonus version supporting multiple file descriptors simultaneously

# Technical Choices

The implementation of get_next_line is based on the use of a static buffer to store leftover data between function calls. This allows the function to continue reading from where it previously stopped without losing any information.

The read system call is used to retrieve data in chunks defined by `BUFFER_SIZE`, ensuring efficient memory usage. After each `read`, the buffer is processed to extract a full line ending with `\n` or the end of the file.

String manipulation is handled manually using custom utility functions to comply with project constraints and avoid reliance on standard library helpers. Memory is carefully allocated and freed at each step to prevent leaks, especially when joining buffers and extracting lines.

The bonus implementation extends this logic by maintaining separate static storage for each file descriptor, allowing simultaneous reading from multiple sources without data mixing.

# Algorithm Overview

1. Read data from the file descriptor into a buffer
2. Append the buffer to a static stash
3. Check if a newline exists in the stash
4. If a newline is found:
    - Extract the line up to `\n`
    - Save the remaining content back into the stash
5. If no newline is found:
    - Continue reading until EOF or a newline appears
6. Return the extracted line
7. Free memory appropriately when no more data remains

# Algorithm Explanation and Technical Choices

The algorithm used in this implementation of **get_next_line** is based on a buffer accumulation strategy with persistent storage, designed to efficiently read a file descriptor line by line while minimizing unnecessary system calls.

## Core Idea

The main idea is to progressively read chunks of data from a file descriptor using a fixed buffer size (`BUFFER_SIZE`), and store the accumulated result in a static variable (`saved`). This static storage allows the function to preserve unread data between successive calls, which is essential for returning one complete line per function call.

Instead of processing the file character by character, the algorithm reads in blocks, then searches for a newline character (`\n`) inside the accumulated data. This approach significantly improves performance compared to naive single-character reading.

## Persistent Buffer Strategy (Static Storage)

A static pointer `saved` is used to retain leftover data between calls to `get_next_line`.

- If `saved` already contains a full line (detected using ft_memchr_index), no new reading is performed.
- Otherwise, read_file() is called to append more data until either:
    - a newline is found, or
    - the end of file is reached.

This design ensures that no data is lost between calls and that partially read lines are completed in subsequent executions.

## Reading Mechanism

The function `read_file()` is responsible for interacting with the system call `read()`:

- Data is read into a temporary buffer (`stash`) of size `BUFFER_SIZE`
- The buffer is null-terminated to safely use string operations
- The new data is appended to `saved`:
    - If `saved` already exists → concatenate using `ft_strjoin`
    - Otherwise → initialize using `ft_strdup`

This incremental construction avoids overwriting previously unread data and ensures continuity of the stream.

The loop stops when either:

a newline is found in `saved`, or
`read()` returns 0 (EOF), or
an error occurs

## Line Extraction Strategy

Once data is available in `saved`, the function `split_and_return()` handles the separation of:

the line to return
the remaining data to keep for the next call

This is done using the helper function `extract()`:

`extract(saved, '\n', 1)` → extracts the line up to and including `\n`
`extract(saved, '\n', -1)` → extracts the remaining content after `\n`

This dual extraction approach cleanly splits the buffer without scanning multiple times manually.

## End-of-File Handling

When `read()` returns `0`, meaning no more data is available:

- If `saved` still contains data, it is returned as the last line
- `saved` is then set to `NULL` to reset the static state

This ensures correct behavior even when the file does not end with a newline.

## Summary of Algorithm Flow

1. Check if `saved` already contains a newline
2. If not, read from file and append to `saved`
3. Stop when newline or EOF is reached
4. Extract one full line from `saved`
5. Keep remaining data for next call
6. Return the extracted line
