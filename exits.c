#include "shell.h"

#define WRITE_BUF_SIZE 1024  // You can adjust this buffer size as needed
#define BUF_FLUSH '\0'

static int write_buffer(char c, int fd, char *buf, int *i);

/**
 * _eputs - prints an input string to stderr
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
    if (!str)
        return;

    while (*str)
    {
        _eputchar(*str);
        str++;
    }
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
    static int i = 0;
    static char buf[WRITE_BUF_SIZE];

    return write_buffer(c, 2, buf, &i);
}

/**
 * _putfd - writes the character c to the given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
    static int i = 0;
    static char buf[WRITE_BUF_SIZE];

    return write_buffer(c, fd, buf, &i);
}

/**
 * _putsfd - prints an input string to the specified file descriptor
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters put
 */
int _putsfd(char *str, int fd)
{
    int count = 0;

    if (!str)
        return 0;

    while (*str)
    {
        count += _putfd(*str, fd);
        str++;
    }

    return count;
}

/**
 * write_buffer - helper function to write characters to a buffer
 * @c: The character to print
 * @fd: The file descriptor to write to
 * @buf: The buffer to store characters
 * @i: The index of the buffer
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
static int write_buffer(char c, int fd, char *buf, int *i)
{
    if (c == BUF_FLUSH || *i >= WRITE_BUF_SIZE)
    {
        write(fd, buf, *i);
        *i = 0;
    }

    if (c != BUF_FLUSH)
        buf[(*i)++] = c;

    return 1;
}

