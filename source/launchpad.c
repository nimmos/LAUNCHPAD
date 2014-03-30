#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\headers\main_aux.h"
#include "..\headers\all_direct.h"
/*--------------------------------------
// TAG LAUNCHPAD
--------------------------------------*/

/*--------------------------------------
// Función: comm_archive_list
// Ejecuta un comando que introduce
// la lista de archivos deseados de
// cierta ruta a un fichero temporal
--------------------------------------*/
int comm_archive_list (char orig[200], arch_list* A_LIST)
{
	char order[500];

	strcpy(order, "cd \"");
	strcat(order, orig);
	strcat(order, "\" & dir");
	strcat(order, " *.jpg *.jpeg *.JPEG");
	strcat(order, " *.bmp *.gif *png");
	strcat(order, " /b /o:d");
	strcat(order, " > \"C:\\file_temp.txt\"");
	system(order);

	return read_archive_list (orig, A_LIST);
}
/*--------------------------------------
// Función: read_archive_list
// Abre la lista de archivos en el
// fichero temporal y los mete en
// memoria dinámica
--------------------------------------*/
int read_archive_list (char route[200], arch_list* A_LIST)
{
	FILE* datafile = fopen ("C:\\file_temp.txt", "r+t");
	int i;

	if ((datafile==NULL)) {
		fatal_error(
			"Couldn't open \"C:\\file_temp.txt\"");
	}

	fseek(datafile, 0, SEEK_END);
	fputs("_EOF", datafile);
	fseek(datafile, 0, SEEK_SET);

	while (!feof(datafile))
	{
		i = A_LIST->n_arch;
		A_LIST->a_list = (archive*) realloc( A_LIST->a_list, (i+1)*sizeof(archive));
		fgets(A_LIST->a_list[i].name_ext, 125 ,datafile);
		if (strcmp(A_LIST->a_list[i].name_ext, "_EOF")==0) {
			if (i==0) {
				system("cls");
				printf( "\nThere aren't any a_list in\n"
						"%s", route);
				pause(2);
				fclose(datafile);
				return -1;
			}
			break;
		}
		strcpy(A_LIST->a_list[i].name_ext, remove_n(A_LIST->a_list[i].name_ext));
		A_LIST->n_arch++;
	}
	fclose(datafile);
	return 1;
}
/*--------------------------------------
// Función: remove_archive_list
// Borra esa lista de archivos temporal
--------------------------------------*/
void remove_archive_list ()
{
	system("del \"C:\\file_temp.txt\"");
}
/*--------------------------------------
// Función: execute
// Abre un archivo
--------------------------------------*/
void execute (char orig[200], char file[125])
{
	char order[500];

	strcpy(order, "start \"new\" \"");
	strcat(order, orig);
	strcat(order, "\\");
	strcat(order, file);
	strcat(order, "\"");
	strcat(order, " & cd scripts & change_window.vbs");
	system(order);
}
/*--------------------------------------
// Función: move
// Mueve un archivo de una carpeta a otra
--------------------------------------*/
void move (char orig[200], char dest[200], char file[125])
{
	char order[500];

	strcpy(order, "move \"");
	strcat(order, orig);
	strcat(order, "\\");
	strcat(order, file);
	strcat(order, "\" \"");
	strcat(order, dest);
	strcat(order, "\\");
	strcat(order, file);
	strcat(order, "\"");
	system(order);
}
/*--------------------------------------
// Función: create_bin
// Crea una carpeta donde se borraran
// los archivos
--------------------------------------*/
void create_bin ()
{
	system("md \"C:\\Launchpad Bin\"");
}
/*--------------------------------------
// Función: search_tags
// Busca el tag en la lista de tags
// y devuelve la dirección de destino
--------------------------------------*/
int search_tags(char t_dest[50], folder_list DATA, char* dest[200])
{
	int i;

	for (i=0;i<DATA.n_fol;i++) {
		if ( strcmp(t_dest, DATA.f_list[i].f_tag)==0) {
			strcpy(dest, DATA.f_list[i].f_addr);
			return 1;	}
	} return -1;
}
/*--------------------------------------
// Función: show_stats
// Muestra las estadísticas de una
// sesión
--------------------------------------*/
void show_stats (stats info)
{
	double per;
	int tr = info.mov + info.del;

	system("cls");
	title(LAT_SIZE, "STATISTICS");
	printf("Session stadistics:\n");
	light_line(LAT_SIZE);
	printf("Files at start:\t\t%i\n", info.str);
	printf("Files moved:\t\t%i\n", info.mov);
	printf("Files deleted:\t\t%i\n", info.del);
	printf("Files remaining:\t%i\n\n", info.str - tr);
	per = ((double)tr)/(double)info.str*100;
	printf("Percentage of files deleted: %.2f %c\n\n", per, 37);
	light_line(LAT_SIZE);
}
/*--------------------------------------
// END OF FILE
--------------------------------------*/