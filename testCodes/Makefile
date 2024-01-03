SRCDIR = ../src
OBJDIR = ../obj
LIBDIR = ../lib
CC 	   = c++
CFLAGS = -Wall -Werror -Wextra -std=c++11

all:

testRegular:
	$(CC) $(CFLAGS) testRegular.cpp ${SRCDIR}/File.cpp ${SRCDIR}/RegularFile.cpp -o testRegular.exe

testProgram:
	$(CC) $(CFLAGS) testProgram.cpp ${SRCDIR}/File.cpp ${SRCDIR}/RegularFile.cpp -o testProgram.exe

testDirectory:
	$(CC) $(CFLAGS) testDirectory.cpp ${SRCDIR}/File.cpp ${SRCDIR}/Directory.cpp -o testDirectory.exe

testOs:
	$(CC) $(CFLAGS) testOs.cpp ${SRCDIR}/File.cpp ${SRCDIR}/MyOs.cpp ${SRCDIR}/RegularFile.cpp ${SRCDIR}/Directory.cpp ${SRCDIR}/Disk.cpp -o testOs.exe

clean:
	@rm -f *.o

fclean: clean
	@rm -f *.exe