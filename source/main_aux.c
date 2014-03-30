#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\headers\main_aux.h"
/*--------------------------------------
// FUNCIONES AUXILIARES
--------------------------------------*/

/*--------------------------------------
// Función: pause
// Establece un alto en el camino
--------------------------------------*/
void pause (int a)
{
	switch(a) {
		case 0:
			printf("\n\nNext ... ");
			break;
		case 1:
			printf("\n\nEnd of file.");
			break;
		case 2:
			printf("\n\nPress any key to\n"
				"return to previous menu.");
			break;
		case 8:
			printf("\n\nPROGRAM WILL BE TERMINATED.");
			break;
		case 9:
			printf("\n\nPROGRAM IS GOING TO TERMINATE"
				"\n\nPRESS ANY KEY TO END IT AT ONCE");
			break;
		default:
			printf("\n\nPress any key to continue.");
			break;
	}
	fflush(stdin);
	getch();
	system("cls");
}
/*--------------------------------------
// Función: error
// Cuando se produce un error que
// termina el programa
--------------------------------------*/
void error (char* mes)
{
	fprintf (stderr, "\n\nProgram has crashed unexpectedly."
		"\nReason: %s", mes);
	pause(2);
}
/*--------------------------------------
// Función: opt_error
// Error de opción equivocada
--------------------------------------*/
void opt_error ()
{
	printf("\n\nThat's not an option!");
	pause(23);
}
/*--------------------------------------
// Función: fatal_error
// Cuando se produce un error que
// termina el programa
--------------------------------------*/
void fatal_error (char* mes)
{
	fprintf (stderr, "\n\nProgram has crashed unexpectedly."
		"\nReason: %s", mes);
	pause(8);
	exit(-1);
}
/*--------------------------------------
// Función: list_number
// Da un formato chulo a los números
// que indexan una lista
--------------------------------------*/
void list_number (int num)
{
	printf( "\xDB\xDB"
			" %i "
			"\xDB\xDB\xDB"
			"\xDB\xB2\xB2"
			"\xB1\xB0\n", num);
}
/*--------------------------------------
// Función: light_line
// Crea una línea
--------------------------------------*/
void light_line (int size)
{
	int i;
	for( i=0 ; i<=size ; i++) printf("\xCD");
	printf("\n");
}
/*--------------------------------------
// Función: bold_line
// Crea una línea
--------------------------------------*/
void bold_line (int size)
{
	int i;
	for( i=0 ; i<=size ; i++) printf("\xDB");
}
/*--------------------------------------
// Función: center_title
// Centra el título
--------------------------------------*/
void center_title (int size, char* mes)
{
	int i;
	int mes_size = strlen(mes);
	int blank_size;

	size -= 2;
	blank_size = (size-mes_size)/2;

	printf("\xDB");
	for(i=0;i<=size;i++) { printf(" ");}
	printf("\xDB\xDB");
	for(i=0;i<=blank_size;i++) { printf(" ");}
	printf("%s", mes);
	if (mes_size%2==0) blank_size++;
	for(i=0;i<blank_size;i++) { printf(" ");}
	printf("\xDB\xDB");
	for(i=0;i<=size;i++) { printf(" ");}
	printf("\xDB");
}
/*--------------------------------------
// Función: title
// Crea cabeceras para los menús
--------------------------------------*/
void title (int size, char* mes)
{
	bold_line(size);
	center_title(size, mes);
	bold_line(size);
	printf("\n");
}
/*--------------------------------------
// Función: erase_this_line
// Elimina el contenido de la línea
// sobre la que se situa el cursor
--------------------------------------*/
void erase_this_line ()
{
	int i;
	printf("\r");
	for (i=0;i<LAT_SIZE;i++) {
		printf(" ");}
	printf("\r");
}
/*--------------------------------------
// Función: opt_elect
// Lee una opción a introducir
--------------------------------------*/
int opt_elect (char* mes)
{
	int opt;
	char* string;

	string = (char*) malloc(strlen(mes)+1);
	strcpy(string, mes);
	printf("%s", string);

	opt = _getche();
	opt = toupper(opt);

	return opt-48;
}
/*--------------------------------------
// Función: opt_yesno
// Lee una opción a introducir de sí/no
--------------------------------------*/
int opt_yesno (char* mes)
{
	int opt;

	printf("%s", mes);
	do{
		printf("\b");
		opt = _getche();
		opt = toupper(opt);
	} while ( (opt!='Y') && (opt!='N') );

	return opt;
}
/*--------------------------------------
// Función: opt_yesno_exit
// Sí/no especial para salir
--------------------------------------*/
int opt_yesno_exit (char* mes)
{
	int opt;

	printf("%s", mes);

	opt = _getche();
	opt = toupper(opt);

	return opt;
}
/*--------------------------------------
// Función: remove_n
// Quita el caracter de "\n"
--------------------------------------*/
char* remove_n (char* str_n)
{
	int i, size_no;
	char* str_no;
	size_no = strlen(str_n);
	str_no = (char*) calloc(size_no, sizeof(char));
	for (i=0;i<size_no-1;i++) {	str_no[i] = str_n[i]; }
	return str_no;
}
// dir /b > "F:\COMPLEX CODING\archivo.txt"
// Hace un dir de formato simple y lo guarda en archivo
// dir /o:n
// Organiza por nombre (n) o por fecha (d)
// 
// cd "route" & dir *.jpg *.jpeg *.bmp *.png *.gif /b /o:d > "archive_list"
// Cambia a la carpeta indicada en "route"
// y hace un dir de formato simple
// que tenga las extensiones indicadas
// y estén ordenadas por fecha (opcional)
// Dicha lista de archivos la guarda en
// un archivo temporal que luego se borra
/*--------------------------------------
// END OF FILE
--------------------------------------*/