//ANTONIO MANUEL RODRIGUEZ MARTOS

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>
//ojo error si no gcc -lm
int esPrimo(int n){
int i, tope;
int primo = 1;

tope = sqrt(n);
for (i = 2; i <= tope && primo; i++)
    if (n % i == 0)
        primo = 0;
return primo;
}

int main(int argc, char *argv[]){
int inicio, final;
inicio = atoi(argv[1]);
final = atoi(argv[2]);

for (int i = inicio; i < final; i++){
    if (esPrimo(i))
        write(STDOUT_FILENO, &i, sizeof(int));
}
return 0;
}
