#include "tTagDB.h"
#include "tLaunchpad.h"
/*--------------------------------------
// PROTOTIPOS
// Hacia todas las funciones de:
// tag_setup.c
--------------------------------------*/
void main_menu				();
void launchsetup_menu		();
void launchsetup_list_menu	(folder_list);
void launchsetup_add_menu	(folder_list*);
void launchsetup_rem_menu	(folder_list*);
void launchsetup_mod_menu	(folder_list*);
void launchroute_menu		(char* [200]);
void launch_menu			(char  [200]);

void main_menu_v			(char [200]);
void launchsetup_menu_v		();
void launchsetup_list_menu_v();
void launchsetup_add_menu_v	();
void launchsetup_rem_menu_v	();
void launchsetup_mod_menu_v	();
void launchroute_menu_v		(char [200], int);
void launch_menu_v			();

void show_info			(folder);
void show_info_small	(folder);
void list_folders		(folder_list);
void add_folders		(folder*);
void remove_folders		(folder_list*, int);
int  modif_folders		(folder*, int);

int				search				(folder_list, char [100]);
folder_list		read_folder_list	();
void			write_folder_list	(folder_list);
void			create_folder		(folder*);
void			create_folder_list	(folder_list*);
void			copy_folder			(folder*, folder);
/*--------------------------------------
// PROTOTIPOS
// Hacia todas las funciones de:
// launchpad.c
--------------------------------------*/
int			comm_archive_list	(char [200], arch_list*);
int			read_archive_list	(char [200], arch_list*);
void		remove_archive_list	();
void		execute				(char [200], char [125]);
void		move				(char [200], char [200],  char [125]);
void		create_bin			();
int			search_tags			(char [50],  folder_list, char*[200]);
void		show_stats			(stats);
/*--------------------------------------
// END OF FILE
--------------------------------------*/