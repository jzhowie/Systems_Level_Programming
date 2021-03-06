# Notes
- Variables & Control Structures
	- 0 is false, everything else is true
	- Declaring a variable means requesting memory from the system
	- Declare functions at the top of a .c or in a .h

- Compiling
	- Preprocessor
		- Text replacement
		- Preprocessor commands start with a #
			- `#include` - adds entire text of included file
			- `#define <arg1> <arg2>` - replaces every instance of arg1 with arg2
				- You can also define function-like stuff:
				- `#define MAX(a, b) a > b ? a : b`
			- `#ifndef <IDENTIFIER> ... #endif` - If identifier is not defined for preprocessor, read up to #endif, else don't.
				- Example:
				` #ifndef PI
				#define PI 3.14
				#endif `
	- Compiler
		- Code → binary code
		- Doesn't create an executable
		- Only one C file at a time
		- gcc -c runs preprocessor and compiler
		- gcc -E runs through preprocessor
	- Linker
		- Combines binary files into an executable
		- Automatically searches for standard library source code
		- If multiple definitions for identifiers are found, the linker will fail
		- Only one main function
		- Gcc compiles each file then links them together
			- Giving gcc .o files will skip the compilation step
	- Make
		- Compiling tool
		- make will look for a file makefile
			- Targets: Things to make (executables)
			- Dependencies: Files/other targets needed to make a target
			- Rules: Command to create target
		- Make will always run the first target
		- Make recursively checks dependencies
		- Syntax:
			`target: dependency0 dependency1 ...
			TAB rule`

			- Other make targets:	`make <run, clean, file>`

- Memory
	- Binary: A 0 or 1 is a bit, 8 bits = 1 byte
	- Volatile, requires power to store data
	- Opening a file: Computer copies file from storage into memory
		- Saving does the reverse
		- Running programs use memory (declaring variables)

	- Endianness
		- Significance of bytes
		- 261 as an int would be stored as 00000000 00000000 00000001 00000101
			- Big endian - most significant byte is at the start
				- Print as a short would not include the last two bytes
			- Little endian is the opposite (00000101 00000001 00000000 00000000)
				- Print would include the full value

- Memory Addresses
	- Identifier - variable name
	- Value - variable data
	- Address - location of data in memory
		- Addressed from first byte up
		- Potential memory addresses is a processor limitation
			- A 32-bit processor can only process no more than 32 bits at once
		- OS defines address space
		- You can get the address of any variable using the address of operator: &
		- %p prints out memory address in hexadecimal format
			- You can also see it as an unsigned long  
		`%u(nsigned), %d(ecimal), %o(ctal), (he)%x(adecimal)`  
			- h will print 2 bytes
			- hh will print 1 byte

	- Pointers
		- Pointers are variables that store memory addresses
			- Unsigned
			- 8 bytes long on 64-bit systems
			- Declaration:
				`int *p = &x;`
			- In Java NullPointerExceptions come from when object pointers point to memory address 0
		- Pointer Arithmetic
			- Can add or subtract
			- Scales by the size of type (char increments by 1, int increments by 4)
			`*cp++ != (*cp)++`
			- Pointers can store memory addresses outside the physical limit, but won't be able to dereference
		- Arrays
			- Block of memory that holds multiple pieces of the same data type
			- C arrays have no length attribute, no boundaries
			- Size of an array is set at declaration (cannot be dynamic)
			- Declaration:
				`float ray[5];
				ray[2] = 8.22;`
			- Requests enough memory for 5 floats

			Array Variables
				Immutable pointer to the beginning of the allocated array block
				sizeof(variable) can give the size of a variable
				You can keep track of array size like this:
					int ARR_SIZE = 10;
					float arr[ARR_SIZE];
				Normal pointers can also be assigned to array pointers (it will do normal pointer things)

				If you did float *rp = ray;
				sizeof(rp) would return 8, sizeof(ray) would return 20

					`float ray[5];
					float *rp = &ray;
					Then:
						ray[3] = rp[3] = *(ray + 3) = *(rp + 3) = 3[rp]`


C functions
	Pass by value
	When a function is called, arguments are copied to new variables
	Pointers can be passed as arguments
	When you pass an array as an argument, it is treated as a memory address
		void arr_func(int arr[]);
		void point_func(int *arr); // preferable because passing an array would be treated as a pointer

Strings
	Character array where the last entry in the array is NULL
		['h', 'e', 'l', 'l', 'o', 0]
	Creating a string literal makes a char array long enough to store the string + the terminating NULL
	String literals are immutable
	If a string literal is repeated in code, only one string literal is used
		80 "hello" strings will ALL point to one "hello"
	String declaration:
		char s[256]; Declares char array
		char s[256] = "Imagine"; Creates string literal + copies literal + NULL into array (in this case it would be the first 8 bytes)
			You can go "out of bounds" with a large enough string
		char s[] = "Tuesday";
			Creates string literal + creates string length + 1 long array + copies into array
		char *s = "Mankind";
			Creates string literal + s points to string (least mutable)

		char s[10] = "Yankees";
		s = "Mets"; is an error
		s[0] = 'M'; is ok

		char *s = "AL East Champions";
		s = "The Best"; is ok
		s[0] = 'M'; is not

Structs
	Custom data type that is a collection of values
	Declaration:
		struct { int a; char x; } s;
		Anonymous struct
		Everything up to s is the type
		. operator accesses value inside struct
		s.a = 10;
		s.x = '@';
	Prototyping structs
		Declaration:
			struct foo { int a; char x; };
			struct foo becomes a valid type so you can declare variables with that type
			foo is not a variable name
		Assignment copies variables into struct
			Could be potentially memory-heavy
		Try to keep structs outside functions (mainly .h files)
	You can make a pointer to a struct
		Declaration:
			struct foo *p = &s;
			. happens before *
			(*p).a != *p.a
			Also p->x is syntactic shorthand for (*p).x
	The value of a struct != The address of a struct (unlike an array variable)

Stack memory
	Stack stores all normally declared variables
	Functions are pushed onto the stack in the order they are called
	When a function is popped off the stack, any memory associated is released
Heap memory
	Heap memory stores dynamically allocated memory
	Data remains in the heap until it is manually released or the program ends
	malloc (size_t x)
	Allocates x bytes of heap memory
		Returns the address at the beginning of the allocation (void pointer)
	free (void* p)
		Releases dynamically allocated memory
		P must point to the beginning of a dynamically allocated block of memory
		*Every* call to malloc/calloc should have a corresponding call to free
	calloc(size_t n, size_t x)
		Allocates n * x bytes of memory and ensures every bit is 0
	realloc(void *p, size_t x)
		Changes the amount of memory allocated for a block to x bytes
		P must point to the beginning of a block
		Returns a pointer to the beginning of the block (could move entire thing), if x is smaller than the original size, the extra bytes are released
2D arrays
	int b[2][4]; -> 2 * 4 * 4 bytes = 32 bytes
	int **bp = b; -> Pointer scaling is inaccurate
	int (*bp1)[4] = b; -> Pointer scaling is accurate
	void foo(int a[2][4]);
	void foo(int (*a)[4]);
	void foo(int a[][4]);
	Alternatively you can work in heap memory
	int **bp = malloc(2 * sizeof(int *));
	bp[i] = malloc(4 * sizeof(int));
Bits
	You can declare ints as a binary, octal, or hexadecimal
	0b1101 == 015 == 0xD == 13
Bitwise Operators
	Evaluated on every bit of a value
	~x
		Negation
		"Flip" every bit of x
	a | b			0011 | 1001 == 1011
		Bitwise or
		Perform logical or for each pair of bits in (a, b)
	a & b			0011 & 1001 == 0001
		Bitwise and
		Bitwise or but and
	a ^ b			1101 ^ 1011 == 0110
		Bitwise xor
		Bitwise or but xor
File permissions
	Read, write, execute
	Perms can be represented in binary or octal
	3 permission "areas" - user, group, others
	Membership is mutually exclusive
	The creator of the file is the default setting for the user and group of a file
	chmod <permissions> file
		Owner (or root) of a file can change permissions
		File ownership and group can be changed with chown and chgrp
File table
	List of all files being used by a program while it is running
	File table has limited space (power of 2)
		Find it with getdtablesize()
	Every file in table gets integer index (file descriptor)
	3 files are always open in the table
		0 is stdin
		1 is stdout
		2 is stderr
	open - <fnctl.h>
		Adds file to table and returns descriptor
		-1 is returned when function fails
		open(path, flags, mode)
			Path is path
			Flags determine what you do with the file
	umask - <sys/stat.h>
		Certain permissions are auto-disabled on file creation
		Umask overrides this
			Default mask is 0002
			new_permissions = ~mask & mode
	read & write - <unistd.h>
	Both methods require a file descriptor, pointer to start of data, how much data is being used
	lseek - <unistd.h>
		Moves the "bookmark"
		Needs file, offset, whence (SEEK_SET, SEEK_CUR, SEEK_END)
	stat - <sys/stat.h>
		Get metadata
		Needs path to file, pointer to a struct stat
		st_size, st_uid, st_gid, st_mode, st_atime, st_mtime
		ctime(time), returns time as a string
	Directories - <dirent.h>
		opendir() needs DIR *d
		readdir() returns struct dirent
Input
	int main(int argc, char *argv[])
		argc - number of arguments
		argv - array of arguments as strings
	sscanf - <stdio.h>
		Read data from a string using a format string to determine types
		"A reverse printf"
	 	sscanf(char * s, char * format, void * p1 ...)
	stdin
		OS determines behavior of standard input stream
			Captures data input from keyboard as characters
			Buffered file stream, data remains inside stdin until it is read
			Enter sends a newline character and triggers program to read from stdin
			read(STDIN_FILENO, buffer, sizeof(buffer));
			fgets - <stdio.h>
				Read in data from a file stream and store it in a string
				fgets(char * s, int n, FILE * f)
				stdin is a file stream variable
Processes
	Every running program is a process
	Program can spawn subprocesses
	A processor can handle 1 process per cycle per core
	"Multitasking" appears to happen because the processor switches between all the active processes quickly
	On *nix style machines, processes are also files in /proc directory
	pid
		Every process has a pid
		pid 1 is the init process
		getpid() - <unistd.h> - return current process' pid
		getppid() - <unistd.h> - return current process parent's pid
	Signals
		Sends an integer to a process
		kill -signal pid
		killall -signal process_name
		kill(pid, signal) - literally the kill command
		sighandler - intercepts signals
			Cannot catch SIGKILL or SIGSTOP
		static void sighandler(int signo)
fork() - <unistd.h>
	Creates separate process based on current one
	Everything is copied (except pid)
	Returns 0 to child and pid or -1 to parent
wait - <sys/wait.h>
	Stops a parent process from running until any child has exited
	Return pid of child that exited or -1, reaps info about child process
	wait(status)
		status stores information about how process exited
		MACRO(status)
			WIFEEXITED - child exits normally
			WEXITSTATUS - return value
			WIFSIGNALED - child exits because of signal
			WTERMSIG - signal number intercepted by child
waitpid - <sys/wait.h>
	waitpid(pid, status, options)
Redirection
	Change usual i/o behavior of program
	\> Takes output (stdout) of command and sends it to file (overwrites)
	\>> Redirection but appending
	< Takes file and treats it like stdin
dup - <unistd.h>
	dup(fd)
	Duplicated entry in file table
	Returns new file descriptor
dup2 - <unistd.h>
	dup2(fd1, fd2)
	Redirects fd2 to fd1
	Any use of fd2 will now act on the file for fd1
	Basically use dup to save STDOUT

Inter-Process Communication
	Shared Memory
	Semaphores
	Message Queues
	Two standards:
		Portable Operating System Interface (POSIX)
		System V
		Both provide same features through different function calls
		Both cover more than IPC

	Shared Memory - <sys/ipc.h>, <sys/shm.h>, <sys/types.h>
		Segment of heap-like memory that can be accessed by multiple processes
		Accessed with a key that is known by any process that needs it
		Does NOT get released when program exits
		Operations:
			Create the segment (once) - shmget
			Access the segment (once per process) - shmget
			Attach the segment to a variable (once per process) - shmat
			Detach the segment from a variable (once per process) - shmdt
			Remove the segment (once) - shmctl
	Semaphores -
		Created by Edsger Dijkstra
		Controls access to a shared resource
		Used as a counter representing how many processes can access a resource at a given time
		Most semaphore operations are atomic, meaning they will not be split up into multiple processor instructions
		Operations:
			Maintenance:
				Create a semaphore
				Set an initial value
				Remove a semaphore
			Traditional:
				Up(S) | V(S) - atomic
					Release the semaphore to signal you are done
				Down(S) | P(S) - atomic
					Attempt to take the semaphore
					Waits for semaphore to be available if it is 0
		Creating a single semaphore and initializing its value to 1:
			int semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
			union semun us;
			us.val = 1;
			r = semctl(semd, 0, SETVAL, us);
		Removing a semaphore: semctl(semd, IPC_RMID, 0);
		Getting a a semaphore & upping and downing it.
			semd = semget(KEY, 1, 0); //get access
			struct sembuf sb;
			sb.sem_num = 0;
			sb.sem_flg = SEM_UNDO;
			sb.sem_op = -1; //setting the operation to down

			semop(semd, &sb, 1); //perform the operation
			printf("got the semaphore!\n");
			sleep(10); //simulate doing something.

			sb.sem_op = 1; //set the operation to up
			semop(semd, &sb, 1); //perform the operation
Pipe
	A conduit in memory between 2 separate process on the same computer
	Have a read end and a write end
	Named pipe - works like a file
		Also known as FIFOs
		Have identifying names
		Unidirectional like unnamed pipes
	Unnamed pipe - no external identifier
	Pipes will block on open until there are two processes attached
	pipe - <unistd.h>
		Creates unnamed pipe, returns 0 or -1
	pipe(descriptors)
		Array of two ints that contains the descriptors

Three-way Handshake
	Two processes (or computers) communicating via pipes
	They will only know that they can read data off of the other
	They don't know if their data is going through
	Procedure in pseudocode:
		1. P0 sends message to P1 (SYN)
		2. P1 sends back a message based on P0's message (ACK)
		3. P0 sends a message based on P1's response (SYN_ACK)
	Pipe 3-way Handshake
		0. S creates a well-known pipe, waits for connection
		1. C creates a secret pipe, send that name to S
		2. S sends a message on the secret pipe
		3. C sends acknowledgement message to S
	3-way handshake
		0. Server creates WKP, waits for connection
		1. Client creates secret pipe
		2. Client sends message to server
		3. Server removes WKP
		4. Server sends message to client
		5. Client receives response, removes secret pipe
		6. Client sends final verification message

Persistent Single Server
	Server handles one client at a time
	Server waits for next client when done
	Handshake, data, repeat

Multiple Clients
	0. S creates WKP, block
	1. C creates PP
	2. C opens WKP, sends PP to S
	3. C blocks on PP
	4. S reads PP
	5. S forks
	6. S removes and closes WKP
	7. S reinitializes
	8. SS sends message to client
	9. C gets message and removes PP
	10. C responds
	11. Normal R/W cycle

Networking
	OSI (Open Systems Interconnections)
	TCP/IP
		1. Application
		2. Support
		3. Internet
			Transmission of data between separate networks
			Addressing and routing
			Routers connect different local networks
				Routers break IPv4 packets into fragments
				Upon receiving a packet it can:
					Send it to the local network
					Pass the packet to another router
					Routers have address tables that identify all connected networks
				IPv4 packet format: header source destination data
					header 12B: metadata
						format: type size fragmentinfo ttl protocol headerchecksum
						type - IPv4 or v6
						size - size of packet
						fragmentinfo - Identifies packet number
						ttl - number of devices packet can hit
					source and destination 4B each: IP address
					data: MTU is 65,536 bytes
			Internet Protocol covers standards for addressing and packet format
		4. Link
			Point-to-point transmission between devices on the same network
			Combines physically connecting computers with basic addressing and transmission protocols
			Physical: How do we transmit bits between two computers (electrons, photons, radio waves)
			Thicknet
				A single coaxial cable, "vampire taps" cut into cable and connect to a computer
			Thinnet
				Single coaxial cable, T-connectors connect computers
			Token ring
				Ring of computers
				One computer has the token and can transmit data
				No signal degradation, no signal collision
			Ethernet
				Multiple computers connected to a hub or switch
				Hub - Broadcasts data to all computers
				Switch - Sends data to specific computer
			In order for data to be sent between computers:
				Each computer needs a unique address (MAC address)
				Media Access Control Address
					6-byte hex address
					MAC addresses only need to be unique on the same local network
				Data needs to be sent in a standardized format
				Frame
					Format: prefix dest source type data checksum
					prefix 8B: 10101010 x7 + 10101011
					dest & source 6B each: MAC addresses
					type 2B
					data: MTU (Maximum Transmission Unit) of 1500B
					checksum 4B: data integrity
