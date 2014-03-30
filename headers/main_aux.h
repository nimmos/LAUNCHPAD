/*--------------------------------------
// PROTOTIPOS
// Para funciones auxiliares
--------------------------------------*/
#define LAT_SIZE	79
#define MAX_OPT		3

void pause			(int);
void error			(char*);
void opt_error		();
void fatal_error	(char*);
void list_number	(int);
void light_line		(int);
void bold_line		(int);
void center_title	(int, char*);
void title			(int, char*);
void erase_this_line();
int  opt_elect		(char*);
int  opt_yesno		(char*);
int  opt_yesno_exit	(char*);
char*remove_n		(char*);
/*--------------------------------------
// END OF FILE
--------------------------------------*/