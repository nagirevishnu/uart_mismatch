cc=gcc
cflags=-Iinclude
src1=source/uart_baudrate_mismatch.c
target= built/baud_mismatch

$(target):$(src1)
	$(cc) $(cflags) $(src1) -o $(target)
clean:
	rm -rf $(target)
