/*--------------------------------------
// TIPOS PROPIOS
// Base de datos de tags
--------------------------------------*/
typedef struct {
	char		f_addr[200];	// Direcci�n de carpeta
	char		f_tag[50];		// Tag
	//int		num_tags;			// N�mero de tags
	} folder;

typedef struct {
	int			n_fol;		// N�mero de carpetas
	folder*		f_list;		// Vector con todas las carpetas
	} folder_list;
/*--------------------------------------
// END OF FILE
--------------------------------------*/