#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\headers\main_aux.h"
#include "..\headers\all_direct.h"
/*--------------------------------------
// ORGANIZACIÓN DE CARPETAS Y TAGS
--------------------------------------*/

/*--------------------------------------
// Función: show_info
// Muestra la info de una carpeta
--------------------------------------*/
void show_info (folder FOLD)
{
	light_line(LAT_SIZE);
	printf("Address:\n  %s\n\n", FOLD.f_addr);
	printf("Tag:\n  %s\n\n", FOLD.f_tag);
	light_line(LAT_SIZE);
}
/*--------------------------------------
// Función: show_info_small
// Muestra la info de una carpeta
// de forma reducida
--------------------------------------*/
void show_info_small (folder FOLD)
{
	printf("Address: %s\n", FOLD.f_addr);
	printf("Tag: %s\n", FOLD.f_tag);
}
/*--------------------------------------
// Función: list_folders
// Enseña una lista con todas carpetas
--------------------------------------*/
void list_folders (folder_list LIST)
{
	int i;

	if (LIST.n_fol==0){
		printf("There aren't any folders yet.");
		return;
	}

	for(i=0 ; i<LIST.n_fol ; i++) {
		list_number(i+1);
		show_info_small (LIST.f_list[i]);
		if ((i+1)%4==0) {
			pause(0);
			system("cls");
			launchsetup_list_menu_v();
		}
	}
	printf("\nNUMBER OF FOLDERS LISTED: %i", LIST.n_fol);
}
/*--------------------------------------
// Función: add_folders
// Añade una carpeta con sus tags
--------------------------------------*/
void add_folders (folder* FOLD)
{
	printf("\nEnter address\n-> ");
	fflush(stdin);
	gets(FOLD->f_addr);
	printf("Enter tag (alpha ver: just one)\n-> ");
	fflush(stdin);
	gets(FOLD->f_tag);
}
/*--------------------------------------
// Función: remove_folders
// Quita carpetas de la lista
--------------------------------------*/
void remove_folders (folder_list* LIST, int i)
{
	int k;

	LIST->n_fol--;
	for (k=i; k<LIST->n_fol; k++)
	{
		strcpy(LIST->f_list[k].f_addr, LIST->f_list[k+1].f_addr);
		strcpy(LIST->f_list[k].f_tag,	  LIST->f_list[k+1].f_tag);
	}
	LIST->f_list = (folder*) realloc(LIST->f_list, LIST->n_fol*sizeof(folder));
}
/*--------------------------------------
// Función: modif_folders
// Quita carpetas de la lista
--------------------------------------*/
int modif_folders (folder* FOLD, int mode)
{
	switch (mode) {
		case 1:
			erase_this_line();
			printf("Modifying address\n-> ");
			fflush(stdin);
			gets(FOLD->f_addr);
			return 1;
		case 2:
			erase_this_line();
			printf("Modifying tag\n-> ");
			fflush(stdin);
			gets(FOLD->f_tag);
			return 1;
		case 0:
			return -1;
		default:
			opt_error();
			return -1;
	}
}
/*--------------------------------------
// Función: search
// Hace una búsqueda
--------------------------------------*/
int search (folder_list LIST, char keyword[100])
{
	int i;

	for (i=0; i<LIST.n_fol; i++) {
		if (strcmp(LIST.f_list[i].f_addr, keyword)==0
		||  strcmp(LIST.f_list[i].f_tag,	 keyword)==0 ){
			return i; }
	}
	return -1;
}
/*--------------------------------------
// Función: read_folder_list
// Lee de archivo la lista de carpetas
--------------------------------------*/
folder_list read_folder_list ()
{
	FILE* datafile = fopen ("..\\database\\tag_database.txt", "rt");
	int i;
	folder_list LIST;
	create_folder_list(&LIST);

	if ((datafile==NULL)) {
		fatal_error(
			"Couldn't open \"tag_database.txt\"");
	}

	while (!feof(datafile))
	{
		i = LIST.n_fol;
		LIST.f_list = (folder*) realloc( LIST.f_list, (i+1)*sizeof(folder));
		fgets(LIST.f_list[i].f_addr, 200 ,datafile);
		if (strcmp(LIST.f_list[i].f_addr, "_EMPTY_FILE")==0) {
			system("cls");
			printf("\n( There aren't any folders listed yet )\n");
			pause(23);
			fclose(datafile);
			return LIST;
		}
		if (strcmp(LIST.f_list[i].f_addr, "_EOF")==0) {
			break;
		}
		strcpy(LIST.f_list[i].f_addr, remove_n(LIST.f_list[i].f_addr));
		fgets(LIST.f_list[i].f_tag, 50 ,datafile);
		strcpy(LIST.f_list[i].f_tag, remove_n(LIST.f_list[i].f_tag));
		LIST.n_fol++;
	}
	fclose(datafile);
	return LIST;
}
/*--------------------------------------
// Función: write_folder_list
// Guarda la lista de carpetas en
// un archivo
--------------------------------------*/
void write_folder_list (folder_list SAVE)
{
	FILE* datafile = fopen ("..\\database\\tag_database.txt", "w");
	int i;
	
	if ((datafile==NULL)) {
		fatal_error(
			"Couldn't open \"tag_database.txt\"");
	}

	if (SAVE.n_fol==0) {
		fprintf(datafile, "_EMPTY_FILE");
	}
	else {
		for (i=0; i<SAVE.n_fol; i++) {
			fprintf(datafile, "%s\n", SAVE.f_list[i].f_addr);
			fprintf(datafile, "%s\n", SAVE.f_list[i].f_tag);
		}
		fprintf(datafile, "_EOF");
	}
	fclose(datafile);
}
/*--------------------------------------
// Función: create_folder
// "Pone a cero" una carpeta
--------------------------------------*/
void create_folder (folder* FOLD)
{
	strcpy (FOLD->f_addr, " ");
	strcpy (FOLD->f_tag, " ");
}
/*--------------------------------------
// Función: create_folder_list
// "Pone a cero" una lista de carpetas
--------------------------------------*/
void create_folder_list (folder_list* LIST)
{
	LIST->n_fol	= 0;
	LIST->f_list	= 0x0;
}
/*--------------------------------------
// Función: copy_folder
// Copia los datos de una carpeta
// a otra
--------------------------------------*/
void copy_folder (folder* dest, folder source)
{
	strcpy(dest->f_addr, source.f_addr);
	strcpy(dest->f_tag,	  source.f_tag);
}
/*--------------------------------------
// END OF FILE
--------------------------------------*/