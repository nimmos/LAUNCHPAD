/*--------------------------------------
// TIPOS PROPIOS
// Base de datos de tags
--------------------------------------*/
typedef struct {
	char		f_addr[200];	// Dirección de carpeta
	char		f_tag[50];		// Tag
	//int		num_tags;			// Número de tags
	} folder;

typedef struct {
	int			n_fol;		// Número de carpetas
	folder*		f_list;		// Vector con todas las carpetas
	} folder_list;
/*--------------------------------------
// END OF FILE
--------------------------------------*/