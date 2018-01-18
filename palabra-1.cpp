
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <string.h>
#include <strings.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <sys/param.h>
#include <sys/types.h>

#define px 800
#define py 600
#define FALSO 0
#define VERDADERO !FALSO
#define TAM 80


char name0[50];
char strAux2[150];
char mensaje1[45];
char mensaje2[45];
char mensaje3[45];
extern int alphasort();
char trayectoria[MAXPATHLEN];
int selecc_arch(const struct dirent *entry);
struct dirent **archivos;
int contar=0;

void buscador()
{
	int j;
	int tam=0;
		
    if ( getcwd(trayectoria,tam) == NULL )
    { 
		printf("Error obteniendo la trayectoria actual\n");
        exit(0);
    }
    printf("Directorio de trabajo actual: %s\n",trayectoria);
    
    contar = scandir(trayectoria, &archivos, selecc_arch, alphasort);
		
	if (contar <= 0)
		printf("No hay archivos en este direntorio\n");
	else
	{
		printf("Hay %d archivos.\n",contar);
		for (j=0; j<contar; ++j)
		{
			printf("%s  ", archivos[j]->d_name);
		}
		printf("\n"); 
	}
    
 
}

int selecc_arch(const struct dirent *entry)
{
	const char *ptr;
                
    if ((strcmp(entry->d_name, ".")== 0) || (strcmp(entry->d_name, "..") == 0))
        return (FALSO);
    
    
    ptr = rindex(entry->d_name, '.'); // Probar que tenga un punto 
    
    if ( (ptr != NULL ) && ( (strcmp(ptr, ".pgm") == 0)  || (strcmp(ptr, ".jpg") == 0) || (strcmp(ptr, ".png") == 0) || (strcmp(ptr, ".jpeg") == 0) || (strcmp(ptr, ".bmp") == 0) || (strcmp(ptr, ".JPG") == 0) ))
        return (VERDADERO);
    else
        return(FALSO);

}

int main()
{
	int n,m,i;
		
	srand(time(0));
	n = rand()%10 + 1;
	
	buscador();
	
	srand(time(0));
	m = rand()%contar;
	
		
	for(i=0;i<15;i++)
		name0[i] = archivos[m]->d_name[i];
	
	
	
	if(n==1)
	{
		char strAux[108] = "Todo el dia en facebook? O conectado al      MSN? Aprobecha para darle a estos medios     fines fraternos!";
		for(i=0;i<108;i++)
			strAux2[i] = strAux[i];
	}
	if(n==2)
	{
		char strAux[101] = "Visita a alguien que este enfermo o que hace mucho que no veas. Ayuda a alguien que lo    necesite";
		for(i=0;i<101;i++)
			strAux2[i] = strAux[i];
	}
	if(n==3)
	{
		char strAux[115] = "Te encontraste a alguien que no te cae muy   bien? * Hace a los demas lo que te gustaria  que te hagan a vos * ";
		for(i=0;i<115;i++)
			strAux2[i] = strAux[i];
	}
	if(n==4)
	{
		char strAux[82] = "Saluda al colectivero, dale el asiento al    otro, estemos atentos a los demas.";
		for(i=0;i<82;i++)
			strAux2[i] = strAux[i];
	}
	if(n==5)
	{
		 
		char strAux[134] = "Preocupado por el medio ambiente? Vos        tambien podes ayudar! Cuida el agua cuando   te banas, tira la basura en donde se debe!";
		for(i=0;i<134;i++)
			strAux2[i] = strAux[i];
	}
	if(n==6)
	{
		char strAux[100] =  "Y por casa como andamos? Empeza en lo        cotidiano con un gesto de amor hacia los     demas.";
		for(i=0;i<100;i++)
			strAux2[i] = strAux[i];
	}
	if(n==7)
	{
		char strAux[80] = "El odio no puede eliminarse con mas odio:    solo el amor puede hacerlo";
		for(i=0;i<80;i++)
			strAux2[i] = strAux[i];
	}
	if(n==8)
	{
		char strAux[65] = "No pidas a otros que hagan lo que tu         no puedes hacer";
		for(i=0;i<65;i++)
			strAux2[i] = strAux[i];
	}
	if(n==9)
	{
		char strAux[124] = "Se tolerante y respeta las ideas de los      demas, aunque no las compartas no seran      razon de discusion ni de division";
		for(i=0;i<124;i++)
			strAux2[i] = strAux[i];
	}
	if(n==10)
	{
		char strAux[70] = "Regla de ORO: Haz al otro lo que te gustaria que te hicieran a ti.";
		for(i=0;i<70;i++)
			strAux2[i] = strAux[i];
	}
	
	printf("%s \n", strAux2);
 
	return 0;
}
