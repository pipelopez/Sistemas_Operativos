#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHARS 255
#define MAXCHARSNUM 10



struct materiam{
	char nombre[MAXCHARS];
	float nota;
	int creditos;
};

int contar(FILE *in_file);
void leer(struct materiam *mats, FILE *in_file, int cantMaterias);
void escribir(struct materiam *mats, FILE *out_file, int cantMaterias);
float promPond(struct materiam *mats, int cantMaterias);
int cantMateriasPerdidas(struct materiam *mats, int cantMaterias);

int main(int argc, char *argv[]){

	int cantMaterias = 0;
	FILE *in_file;
	FILE *out_file;
	struct materiam *mats;
	if (argc != 3){
		fprintf(stderr,"uso: %s <maresEntrada.txt> <maresProcesado.txt>\n",argv[0]);
		fprintf(stderr, "ejemplo:\n%s materias.txt formateado.txt\n",argv[0] );
		exit(-1);
	}

	in_file = fopen(argv[1], "r");
	out_file = fopen(argv[2],"w");
	if(in_file == NULL){
		printf("cannot open %s\n",argv[1] );
		exit(8);
	}
	if(out_file == NULL){
		printf("cannot open %s\n",argv[2] );
		exit(8);
	}

	if((cantMaterias = contar(in_file)) == -1){
		fprintf(stderr, "Error: Formato de archivo incorrecto\n");
		fclose(out_file);
		fclose(in_file);
		exit(EXIT_FAILURE);
	}

	mats = malloc(sizeof(struct materiam)*cantMaterias);

	leer(mats,in_file,cantMaterias);
	escribir(mats,out_file,cantMaterias);
	printf("%s ha sido leido y procesado correctamente en %s\n",argv[1],argv[2]);
	free(mats);
	fclose(in_file);
	fclose(out_file);
	return 0;
}


int contar(FILE *in_file){
	char inBuf[MAXCHARS];
	int cantMaterias;
	while(fgets(inBuf,MAXCHARS,in_file)){
		cantMaterias++;
	}
	rewind(in_file);
	return cantMaterias;
}

void leer(struct materiam *mats, FILE *in_file, int cantMaterias){
	int actual = 0;
	char inBuf[MAXCHARS];

	char *resto;
	char *token;
	while( actual < cantMaterias && fgets(inBuf,MAXCHARS,in_file) ){
		//Strtok_R -> Thread safe

		//Primera llamada se le pasa el String como primer parámetro
		token = strtok_r(inBuf, ";", &resto); //OJO: Modifica el string original!!!!
		//En este punto inBuf fue modificado, donde habían ';'' ahora hay '\0' (caracter nulo)
		//de esta manera, strtok_r la próxima vez retornará el texto que hay entre 
		// los dos siguiente '\0' o en su defecto entre el siguiente '\0' y el fin de linea

		strcpy((mats+actual)->nombre, token); //Guardamos el nombre

		//En las llamadas consecuentes solo se le pasa NULL como primer parámetro y &resto como
		//el tercer parámetro, en resto se tendrá la direccion asociada al punto en el que
		//inicia el token (substring). El final de dicho substring se encuentra en el siguiente'\0'
		token = strtok_r(NULL, ";", &resto);
		(mats+actual)->nota = atof(token); //Guaramos la nota


		token = strtok_r(NULL, ";", &resto);
		(mats+actual)->creditos = atoi(token); //Guardamos los créditos
		actual++;
	}
}

void escribir(struct materiam *mats, FILE *out_file, int cantMaterias){

	int materiasPerdidas = cantMateriasPerdidas(mats,cantMaterias);
	float promedioPond = promPond(mats,cantMaterias);
	fprintf(out_file,"%-30s%-10s%-10s\n","Materia","Nota","Créditos" );
	for(int i = 0; i < cantMaterias ; i++){
		fprintf(out_file,"%-31.30s%-11.2f%-10d\n",(mats+i)->nombre,(mats+i)->nota,(mats+i)->creditos );
	}

	fprintf(out_file, "\nTotal de materias: %d\n", cantMaterias);
	fprintf(out_file, "Materias ganadas: %d\n", (cantMaterias-materiasPerdidas));
	fprintf(out_file, "Materias perdidas: %d\n", materiasPerdidas);
	fprintf(out_file, "Promedio ponderado: %1.2f\n", promedioPond);
}

float promPond(struct materiam *mats, int cantMaterias){
		int sumCreditos = 0;
	float sumNota = 0;
	for(int i = 0; i < cantMaterias ; i++){
		sumNota += (mats+i)->nota * (mats+i)->creditos;
		sumCreditos += (mats+i)->creditos;
	}
	return sumNota/sumCreditos;
}

int cantMateriasPerdidas(struct materiam *mats, int cantMaterias){
	int perdidas = 0;
	for(int i = 0; i < cantMaterias ; i++){
		if((mats+i)->nota < 3){
			++perdidas;
		}
	}
	return perdidas;
}