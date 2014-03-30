#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\headers\main_aux.h"
#include "..\headers\all_direct.h"
/*--------------------------------------
// MENUS DEL PROGRAMA : FLUJO
--------------------------------------*/

/*--------------------------------------
// Menú principal
--------------------------------------*/
void main_menu ()
{
	int  opt;
	char route[200] = {"_NO_ROUTE"};

	create_bin();
	system("title TAGLAUNCHPAD - Free beta");
	while (1) {
		main_menu_v(route);
		opt = opt_elect("\n\nSelect an option: ");
		switch (opt) {
			case 0:
				erase_this_line();
				opt = opt_yesno_exit("Are you sure "
					"you want to exit?\n(Say \"y\" "
					"to exit definitely): ");
				if ( opt==89 ) { return; }
				else { continue; }
			case 1:
				launchsetup_menu();
				continue;
			case 2:
				launchroute_menu(&route);
				continue;
			case 3:
				launch_menu (route);
				//command_test();
				continue;
			//case 4:
				// Borrar todo lo que hay en Launchpad Bin
			default:
				opt_error();
		}
	}
}
/*--------------------------------------
// Menú Tag-Launchpad setup
--------------------------------------*/
void launchsetup_menu ()
{
	folder_list LIST = read_folder_list ();

	int opt;
	while (1) {
		launchsetup_menu_v();
		opt = opt_elect("\n\nSelect an option: ");
		switch (opt) {
			case 0:
				write_folder_list(LIST);
				free(LIST.f_list);
				return;
			case 1:
				launchsetup_list_menu(LIST);
				pause(2);
				continue;
			case 2:
				launchsetup_add_menu(&LIST);
				pause(2);
				continue;
			case 3:
				launchsetup_rem_menu(&LIST);
				pause(2);
				continue;
			case 4:
				launchsetup_mod_menu(&LIST);
				pause(2);
				continue;
			default:
				opt_error();
		}
	}
}
/*--------------------------------------
// Menú Tag-Launchpad route setup
--------------------------------------*/
void launchroute_menu (char* route[200])
{
	int opt;
	if (strcmp(route, "_NO_ROUTE")==0) {
		launchroute_menu_v(route,0);
		printf("There isn't any route yet.\n");
		printf( "Enter route (DON'T PUT A \"\\\""
				" AT THE END)\n-> ");
		fflush(stdin);
		gets(route);
	}
	while (1) {
		launchroute_menu_v(route,1);
		opt = opt_elect("\n\nSelect an option: ");
		switch (opt) {
			case 0:
				return;
			case 1:
				launchroute_menu_v(route,1);
				printf( "\nEnter new route (DON'T PUT A \"\\\""
				" AT THE END)\n-> ");
				fflush(stdin);
				gets(route);
				break;
			default:
				opt_error();
		}
	}
}
/*--------------------------------------
// Menú Launch
--------------------------------------*/
void launch_menu (char orig[200])
{
	int i, exit = -1, exist = 1, found = -1;
	char			dest[200];
	char			tag_dest[50];
	stats			session;
	arch_list		A_LIST;
	folder_list		F_LIST = read_folder_list ();
	A_LIST.n_arch = 0;
	session.mov = 0;
	session.del = 0;
	
	launch_menu_v ();
	if (strcmp(orig, "_NO_ROUTE")==1) {
		printf("\nThere is no route specified yet!!");
		pause(2);
		return;
	}
	
	while ( exit==-1 && exist==1 ) {
		exist = comm_archive_list(orig, &A_LIST);
		if (exist==1) {
			session.str = A_LIST.n_arch;
			for (i=0 ; i<A_LIST.n_arch && exit==-1 ; i++) {
				execute(orig, A_LIST.a_list[i].name_ext);
				do {
					launch_menu_v (); printf("\nTAG -> ");
					fflush(stdin); gets(tag_dest);
					if ( strcmp(tag_dest, "_exit")==0 ) {
						exit = 1; break; }
					if ( strcmp(tag_dest, ".")==0 ) {
						break; }
					if ( strcmp(tag_dest, "_erase")==0 ) {
						move (orig, "C:\\Launchpad Bin.", A_LIST.a_list[i].name_ext);
						session.del++; break; }
					found = search_tags(tag_dest, F_LIST, &dest);
					if (found==1) {
						move (orig, dest, A_LIST.a_list[i].name_ext);
						session.mov++;	}
				} while (found==-1);
			}
			if (i==A_LIST.n_arch) {
				printf("\nNo more files available.");
				exist=-1;
				pause(23);
			}
			show_stats(session);
			pause(2);
		}
	}
	remove_archive_list();
}
/*--------------------------------------
// Menú Listar Carpetas
--------------------------------------*/
void launchsetup_list_menu (folder_list LIST)
{
	launchsetup_list_menu_v();
	list_folders(LIST);
}
/*--------------------------------------
// Menú Añadir Carpetas
--------------------------------------*/
void launchsetup_add_menu (folder_list* LIST)
{
	int opt, ok=0;
	folder to_add;
	create_folder(&to_add);

	do {
		launchsetup_add_menu_v();
		add_folders(&to_add);
		launchsetup_add_menu_v();
		show_info(to_add);
		opt = opt_yesno("Is it okay like this? (y/n):  ");
		switch (opt) {
			case 89: //Y
				ok = 1;
				break;
			case 78: {//N
				opt = opt_yesno("\n\nDo you want to modify it? (y/n):  ");
				switch (opt) {	case 89: continue;
								case 78: return;   }
			}
		}
		if (ok==1) {
			LIST->n_fol++;
			LIST->f_list = (folder*) realloc(LIST->f_list, LIST->n_fol*sizeof(folder));
			strcpy ( LIST->f_list[LIST->n_fol-1].f_addr, to_add.f_addr );
			strcpy ( LIST->f_list[LIST->n_fol-1].f_tag,  to_add.f_tag );
			launchsetup_add_menu_v();
		}
		opt = opt_yesno("Do you want to do another one? (y/n):  ");
		switch (opt) {	case 89: ok = 0; break;
						case 78: return;   }
	} while (ok==0);
}
/*--------------------------------------
// Menú Borrar Carpetas
--------------------------------------*/
void launchsetup_rem_menu (folder_list* LIST)
{
	char keyword[100];
	int  opt, found=-1;

	do {
		launchsetup_rem_menu_v();
		printf( "\nEnter either folder address or folder tag"
				"\nthat will be deleted:"
				"\n-> ");
		fflush(stdin);
		gets(keyword);
		if ( ( found = search(*LIST, keyword) ) != -1 ) {
			launchsetup_rem_menu_v();
			show_info (LIST->f_list[found]);
			opt = opt_yesno("Are you sure you want"
							"\nthis deleted? (y/n):  ");
			switch (opt) {
				case 89: {
					remove_folders(LIST, found);
					launchsetup_rem_menu_v();
					printf("\n");
					title(LAT_SIZE, "DATA SUCCESSFULLY REMOVED");
					break;
				}
				case 78: {
					launchsetup_rem_menu_v();
					printf("\n");
					title(LAT_SIZE, "DATA WAS NOT REMOVED");
					break;
				}
			}
		} else {
			printf( "\nNeither address nor tag were to"
					"\nbe found with the keyword: %s", keyword);
		}
		opt = opt_yesno("\nSearch again? (y/n):  ");
		switch (opt) {
			case 89: found=-1; break;
			case 78: return;   }
	} while ( found == -1 );
}
/*--------------------------------------
// Menú Modificar Carpetas
--------------------------------------*/
void launchsetup_mod_menu (folder_list* LIST)
{
	char	keyword[100];
	int		opt, found=-1;
	folder	to_modify;
	create_folder(&to_modify);

	do {
		launchsetup_mod_menu_v();
		printf( "\nEnter either folder address or folder tag"
				"\nthat will be modified:"
				"\n-> ");
		fflush(stdin);
		gets(keyword);
		if ( ( found = search(*LIST, keyword) ) != -1 ) {
			do {
				copy_folder(&to_modify, LIST->f_list[found]);
				launchsetup_rem_menu_v();
				show_info(to_modify);
				printf("1. Folder address / 2. Tag / 0. Exit\n");
				opt = opt_elect("Select what you want to modify: ");
				if ( modif_folders(&to_modify, opt) == 1 ) {
					launchsetup_rem_menu_v();
					show_info(to_modify);
					opt = opt_yesno("Is this correct? (y/n):  ");
					switch (opt) {
						case 89:
							copy_folder(&LIST->f_list[found], to_modify);
							break;
						case 78:
							break;
					}
				}
			} while ( opt!=0 );
			launchsetup_mod_menu_v();
		} else {
			printf( "\nNeither address nor tag were to"
					"\nbe found with the keyword: %s", keyword);
		}
		opt = opt_yesno("\nSearch again? (y/n):  ");
		switch (opt) {
			case 89: found=-1; break;
			case 78: return;   }
	} while ( found == -1 );
}

/*--------------------------------------
// MENUS DEL PROGRAMA : VISUAL
--------------------------------------*/

/*--------------------------------------
// Menú principal
--------------------------------------*/
void main_menu_v (char route[200])
{
	system("cls");
	title(LAT_SIZE, "TAG-LAUNCHPAD PROGRAM"
					" - MAIN MENU - Free beta");
	printf("1. Organize Tag-Launchpad\n");
	printf("2. Stablish or modify Launchpad route\n");
	printf("   ACTUAL ROUTE: %s\n\n", route);
	printf("3. Launch\n");
	printf("\n0. EXIT PROGRAM\n\n");
	bold_line(LAT_SIZE);
}
/*--------------------------------------
// Menú Tag-Launchpad setup
--------------------------------------*/
void launchsetup_menu_v ()
{
	system("cls");
	title(LAT_SIZE, "TAG-LAUNCHPAD SETUP MENU");
	printf("1. List Folders\n");
	printf("2. Add Folders\n");
	printf("3. Remove Folders\n");
	printf("4. Modify Folders\n");
	printf("\n0. Exit Menu\n\n");
	bold_line(LAT_SIZE);
}
/*--------------------------------------
// Menú Listar Carpetas
--------------------------------------*/
void launchsetup_list_menu_v ()
{
	system("cls");
	title(LAT_SIZE, "VIEWING FOLDERS LIST");
}
/*--------------------------------------
// Menú Añadir Carpetas
--------------------------------------*/
void launchsetup_add_menu_v ()
{
	system("cls");
	title(LAT_SIZE, "ADDING FOLDERS");
}
/*--------------------------------------
// Menú Borrar Carpetas
--------------------------------------*/
void launchsetup_rem_menu_v ()
{
	system("cls");
	title(LAT_SIZE, "REMOVING FOLDERS");
}
/*--------------------------------------
// Menú Modificar Carpetas
--------------------------------------*/
void launchsetup_mod_menu_v ()
{
	system("cls");
	title(LAT_SIZE, "MODIFYING FOLDERS");
}
/*--------------------------------------
// Menú Organizar Ruta Launchpad
--------------------------------------*/
void launchroute_menu_v (char route[200], int enter)
{
	system("cls");
	title(LAT_SIZE, "LAUNCHPAD ROUTE");
	if (enter==1) {
		printf("%s\n\n", route);
		bold_line(LAT_SIZE);
		printf("\n1. Modify route\n");
		printf("\n0. Exit Menu\n\n");
		bold_line(LAT_SIZE);
	}
}
/*--------------------------------------
// Menú Launch
--------------------------------------*/
void launch_menu_v ()
{
	system("cls");
	title(LAT_SIZE, "LAUNCHING FILES");
	printf( "Write \"_exit\" anytime to"
			" go back to the Main Menu.\n"
			"Write \".\" if you want to"
			" continue to the next file.\n"
			"Write \"_erase\" if you want to"
			" erase the file.\n"
			"(Files will be held in "
			"\"C:\\Launchpad Bin\")"
			"\n\n");
	bold_line(LAT_SIZE);
}
/*--------------------------------------
// END OF FILE
--------------------------------------*/