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
#include <dir.h>
#include <io.h>
#include <windows.h>


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
//extern int alphasort();
char trayectoria[TAM];
int selecc_arch(const struct dirent *entry);
struct dirent **archivos;
int contar=0;

#define NAME_MAX2 (sizeof (((struct dirent *) 0)->d_name))



int alphasort2(const struct dirent **a, const struct dirent **b)
{
  return strcmp((*a)->d_name,(*b)->d_name);
}

int
scandir3(const char *dir, struct dirent ***namelist,
        int (*select) (const struct dirent *),
        int (*compar) (const struct dirent **, const struct dirent **))
{
    DIR *d = opendir(dir);
    struct dirent *current;
    struct dirent **names;
    int count = 0;
    int pos = 0;
    int result = -1;

    if (NULL == d)
        return -1;

    while (NULL != readdir(d))
        count++;

    names = malloc(sizeof (struct dirent *) * count);

    closedir(d);
    d = opendir(dir);
    if (NULL == d)
        return -1;

    while (NULL != (current = readdir(d))) {
        if (NULL == select || select(current)) {
            struct dirent *copyentry = malloc(current->d_reclen);

            memcpy(copyentry, current, current->d_reclen);

            names[pos] = copyentry;
            pos++;
        }
    }
    result = closedir(d);

    if (pos != count)
        names = realloc(names, sizeof (struct dirent *) * pos);

    *namelist = names;

    return pos;
}




#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)scandir.c	5.10 (Berkeley) 2/23/91";
#endif /* LIBC_SCCS and not lint */

/*
 * Scan the directory dirname calling select to make a list of selected
 * directory entries then sort using qsort and compare routine dcomp.
 * Returns the number of entries and a pointer to a list of pointers to
 * struct dirent (through namelist). Returns -1 if there were any errors.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#define MAXNAMLEN 255
/*
 * The DIRSIZ macro gives the minimum record length which will hold
 * the directory entry.  This requires the amount of space in struct dirent
 * without the d_name field, plus enough space for the name with a terminating
 * null byte (dp->d_namlen+1), rounded up to a 4 byte boundary.
 */
#undef DIRSIZ
#ifdef _DIRENT_HAVE_D_NAMLEN
#define DIRSIZ(dp) \
    ((sizeof (struct dirent) - (MAXNAMLEN+1)) + (((dp)->d_namlen+1 + 3) &~ 3))
#else
#define DIRSIZ(dp) \
    ((sizeof (struct dirent) - (MAXNAMLEN+1)) + ((strlen((dp)->d_name)+1 + 3) &~ 3))
#endif

#ifndef __P
#define __P(args) ()
#endif

int
scandir2(dirname, namelist, select, dcomp)
	const char *dirname;
	struct dirent ***namelist;
	int (*select) __P((struct dirent *));
	int (*dcomp) __P((const void *, const void *));
{
	register struct dirent *d, *p, **names;
	register size_t nitems;
	struct stat stb;
	long arraysz;
	DIR *dirp;

	if ((dirp = opendir(dirname)) == NULL)
		return(-1);
//	if (fstat(dirp->dd_fd, &stb) < 0)
	//	return(-1);

	/*
	 * estimate the array size by taking the size of the directory file
	 * and dividing it by a multiple of the minimum size entry.
	 */
	arraysz = (stb.st_size / 24);
	names = (struct dirent **)malloc(arraysz * sizeof(struct dirent *));
	if (names == NULL)
		return(-1);

	nitems = 0;
	while ((d = readdir(dirp)) != NULL) {
		if (select != NULL && !(*select)(d))
			continue;	/* just selected names */
		/*
		 * Make a minimum size copy of the data
		 */
		p = (struct dirent *)malloc(DIRSIZ(d));
		if (p == NULL)
			return(-1);
		p->d_ino = d->d_ino;
		p->d_reclen = d->d_reclen;
#ifdef _DIRENT_HAVE_D_NAMLEN
		p->d_namlen = d->d_namlen;
		bcopy(d->d_name, p->d_name, p->d_namlen + 1);
#else
               strcpy(p->d_name, d->d_name);
#endif
		/*
		 * Check to make sure the array has space left and
		 * realloc the maximum size.
		 */
		if (++nitems >= arraysz) {
			//if (fstat(dirp->dd_fd, &stb) < 0)
				//return(-1);	/* just might have grown */
			arraysz = stb.st_size / 12;
			names = (struct dirent **)realloc((char *)names,
				arraysz * sizeof(struct dirent *));
			if (names == NULL)
				return(-1);
		}
		names[nitems-1] = p;
	}
	closedir(dirp);
	if (nitems && dcomp != NULL)
		qsort(names, nitems, sizeof(struct dirent *), dcomp);
	*namelist = names;
	return(nitems);
}

extern char *strrchr (const char *, int);

char *rindex2 (const char *s, int c)
{
  return strrchr (s, c);
}

void buscador()
{
	int j;

    if ( getcwd(trayectoria,TAM) == NULL )
    {
		printf("Error obteniendo la trayectoria actual\n");
        exit(0);
    }
    printf("Directorio de trabajo actual: %s\n",trayectoria);

    contar = scandir2(trayectoria, &archivos, selecc_arch, alphasort2);

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


    ptr = rindex2(entry->d_name, '.'); // Probar que tenga un punto

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

	system("PAUSE");

	return 0;
}
