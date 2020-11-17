#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int gen_rand() {
	int rand_num;
	int opened_file = open("/dev/random", O_RDONLY);
	if (opened_file == -1) {
		printf("Error Number %d\tError: %s\n", errno, strerror(errno)); 
		return -1;
	}
	int random = read(opened_file, &rand_num, sizeof(rand_num));
	if (random == -1) {
		printf("Error Number %d\tError: %s\n", errno, strerror(errno)); 
		return -1;
	}
	else {
		return rand_num;
	}
}

int main() {
	int random_array[10];
    int i;
    printf("\nGenerating Random Numbers:\n");
    for (i = 0; i < 10; i++)
    {
        random_array[i] = gen_rand();
        printf("Random Number %d: %d\n", i + 1, random_array[i]);
    }
    printf("\n");

    int out_file;
    out_file = open("./out_file", O_CREAT | O_RDWR, 0666);
    
    if (out_file == -1) {
		printf("Error Number %d\tError: %s\n", errno, strerror(errno)); 
		return -1;
	}

	int writer;
	printf("Writing numbers to the file...\n"); 
	writer = write(out_file, random_array, sizeof(random_array));

	if (writer == -1) {
		printf("Error Number %d\tError: %s\n", errno, strerror(errno)); 
		return -1;
	} 

	close(out_file);

	printf("\nReading numbers from file...\n\n");

	int read_file = open("./out_file", O_RDONLY);

	if (read_file == -1) {
		printf("Error Number %d\tError: %s\n", errno, strerror(errno)); 
		return -1;
	}

	int test_array[10];

	int reader;
    reader = read(read_file, test_array, sizeof(test_array));

    if (reader == -1) {
		printf("Error Number %d\tError: %s\n", errno, strerror(errno)); 
		return -1;
	}

	printf("Verification that written values were the same:\n");
	for (i = 0; i < 10; i++){
		printf("Random Number %d: %d\n", i + 1, test_array[i]);
	}

	close(read_file);
	
	return 0;
}