#include"uart_baudrate_mismatch.h" 
int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror("argc");
        return 1;
    }
 
    int serial_port = open(argv[1], O_RDWR);
    if (serial_port < 0) {
        perror("Error opening serial port");
        return 1;
    }
 
    struct termios tty;
    if (tcgetattr(serial_port, &tty) != 0) {
        perror("tcgetattr");
        close(serial_port);
        return 1;
    }
    tty.c_cflag |= (CREAD|CLOCAL);
    tty.c_cflag &= ~(CRTSCTS|CSIZE|CSTOPB|PARENB);
    tty.c_cflag|=CS8;
    tty.c_oflag=0;
    tty.c_iflag=0;
    tty.c_lflag = 0;
    tty.c_cc[VMIN] = SERIAL_READ_MIN;
    tty.c_cc[VTIME] = SERIAL_READ_TIMEOUT;
 
    speed_t desired_baud = B115200;
    cfsetispeed(&tty, desired_baud);
    cfsetospeed(&tty, B9600);
 
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        perror("tcsetattr");
        close(serial_port);
        return 1;
    }
    speed_t actual_input_baud = cfgetispeed(&tty);
    speed_t actual_output_baud = cfgetospeed(&tty);
 
    /*if (actual_input_baud != desired_baud || actual_output_baud != desired_baud) {
        printf("Baud rate mismatch\n");
        close(serial_port);
        return 1;
    } */  
    while (1) {
        char buffer[256] = {0};
        int bytes_read = read(serial_port, buffer, sizeof(buffer));
        if (actual_input_baud != desired_baud || actual_output_baud != desired_baud) {
        printf("Baud rate mismatch\n");
        close(serial_port);
        return 1;
	}
 
        if (bytes_read < 0) {
            perror("Error reading from serial port");
            break;
        } else if (bytes_read == 0) {
            printf("No data received within the timeout.\n");
        } else {
            buffer[bytes_read] = '\0'; 
            printf("Received: %s \n", buffer);
        }
    }
 
    close(serial_port);
    return 0;
}

