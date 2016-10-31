//ANTONIO MANUEL RODRIGUEZ MARTOS

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
int fd1[2];
int fd2[2];
pid_t esclavo1, esclavo2;
char intervalo[4];
int numprim_h1, numprim_h2, val1, val2;
char inicio[10];
char final[10];



if(argc < 3) {
printf("\nNumero de argumentos no valido en maestro");
exit(-1);
}


//intervalos hijo 1
intervalo[0] = atoi(argv[1]);
intervalo[1] = ((atoi(argv[2])+atoi(argv[1])) / 2) - 1;

//intervalos hijo 2
intervalo[2] = intervalo[1] + 1; 
intervalo[3] = atoi(argv[2]);


pipe(fd1);
pipe(fd2);


esclavo1 = fork();

sprintf(inicio, "%d", intervalo[0]);
sprintf(final, "%d", intervalo[1]);

//hijo 1
if (esclavo1 == 0){

	close(fd1[0]); //cierro lectura
	dup2(fd1[1],STDOUT_FILENO);
        
	if(execl("./esclavo", "esclavo", inicio, final, NULL) < 0) {
		perror("\nError en el execl");
		exit(-1);
	}

}else { //padre
	close(fd1[1]); //cierro descriptor de escritura
	printf("\nPrimer intervalo de numeros primos");
	while((numprim_h1 = read(fd1[0],&val1, sizeof(int))) > 0){
		printf("%d ", val1);
	}
	close(fd1[0]);
	printf("\n");

}


esclavo2 = fork();

sprintf(inicio, "%d", intervalo[2]);
sprintf(final, "%d", intervalo[3]);

//hijo 2
if (esclavo2 == 0){
    close(fd2[0]); //cierro descriptor de lectura
    dup2(fd2[1],STDOUT_FILENO);
    
    if(execl("./esclavo", "esclavo", inicio, final, NULL) < 0) {
        perror("\nError en el execl");
        exit(-1);
    }
}else{ // Proceso padre.

	close(fd2[1]); //cierro descriptor de escritura
	printf("\nSegundo intervalo de numeros primos");
	while((numprim_h2 = read(fd2[0],&val2, sizeof(int))) > 0){
		printf("%d ", val2);
	}
	close(fd2[0]);
	printf("\n");

}


return 0;





}
