#include <stdio.h>

#define device1 "/dev/NIM"
#define device2 "/dev/Nama"
int input;
int main() {
	
	
	char buffer[256];

	printf("Result calling kernel module using character device driver\n");

	
	printf("\n\nPilihan Menu : \n");
	printf("1. Ketik 1 untuk menampilkan Nama : \n");
	printf("2. Ketik 2 untuk menampilkan NIM : \n");
    scanf("%d", &input);

	
	if (input == 1) {
		FILE *fNama;
		fNama = fopen(device2,"r");
		if(fNama == NULL) {
		printf("Can't open file %s\n",device2);
		return 0;
	}
		
		fread(buffer,sizeof(buffer),1,fNama);
		printf("\nNama : %s\n",buffer);
		fclose(fNama);

	}
	
	else if (input == 2) {
		FILE *fNIM;
		fNIM = fopen(device1,"r");
		if(fNIM == NULL) {
		printf("Can't open file %s\n",device1);
		return 0;
	}
		fread(buffer,sizeof(buffer),1,fNIM);
		printf("\nNIM : %s\n",buffer);
		fclose(fNIM);
	}
	
	else {
		printf("Instruksi tidak sesuai\n");
	}


	return 0;
}
