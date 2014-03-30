/*--------------------------------------
// TIPOS PROPIOS
// Para el Launchpad
--------------------------------------*/
typedef struct {
	int		str;	// Elementos que había al principio
	int		mov;	// Elementos movidos
	int		del;	// Elementos eliminados
	} stats;

typedef struct {
	char	name_ext[125];	// Nombre del archivo + ext
	} archive;

typedef struct {
	int			n_arch;	// Número de archivos
	archive*	a_list;	// Lista de archivos
	} arch_list;
/*--------------------------------------
// END OF FILE
--------------------------------------*/