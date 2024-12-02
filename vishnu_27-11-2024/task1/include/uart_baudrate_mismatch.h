#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>
#include <fcntl.h>

#define SERIAL_READ_MIN 1
#define SERIAL_READ_TIMEOUT 5

