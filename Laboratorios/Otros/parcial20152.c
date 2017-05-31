/*
 * PLANTILLA VACIA, VERSION 1.
 * Name         : evalX_ApellidoNombre.c
 * Compilation  : gcc -Wall evalX_ApellidoNombre.c -o 1.out
 * Execution    : ./1.out
*/

/* Incluir cabeceras o bibliotecas. */
#include <stdio.h>// printf, scanf, setbuf, fflush
#include <stdlib.h>//malloc
#include <string.h>

/* Definicion de macros y constantes. */
#define MAX_PRODUCT_CANT 100

/* Declaracion de funciones. */
void getOption(char *_option);
void addItem (int *_codigo, char (*_descripcion)[12], float *_valor);
void Consultar(int *_codigo, char (*_descripcion)[12], float *_valor, char *_option, int *_posiciones);
void getOptionBuscar(char *_option);
void buscaCodigo(int *_codigo, int *_posiciones);
void buscaDescripcion(char (*_descripcion)[12], int *_posiciones);
void facturar(char *_option, int *_codigo, int *_posiciones, float *_valor, char (*_descripcion)[12]);

/* Variables globales. */
int enlisted_items =0;
int enLista=0;
int cant=0;
int enFactura=0;

/* Main function. */
int main() {
    /* Variables locales. */
    char option = 'x';
    int *codigo;
    char (*descripcion)[12];
    float *valor;
    int *posiciones;

    /* Obtener espacio dinámico en memoria. */
    codigo = (int *) malloc(sizeof(int)*MAX_PRODUCT_CANT);
    descripcion = (char (*)[12]) malloc(sizeof(char[12]) * MAX_PRODUCT_CANT);
    valor = (float *) malloc(sizeof(float) * MAX_PRODUCT_CANT);
    posiciones = (int *) malloc(sizeof(int) * MAX_PRODUCT_CANT);

    /* Obtener informacion. */
    do{
            getOption(&option);
            printf("La opción escogida fue %c\n", option);
            switch (option){
                case 'a':
                facturar(&option, codigo, posiciones, valor, descripcion);
                break;
                case 'b':
                Consultar(codigo, descripcion, valor, &option, posiciones);
                break;
                case 'c':
                addItem (codigo, descripcion, valor);
                break;
                case 'q':
                printf("\nSaliendo del programa..\n\n");
                break;
                default:
                printf("La opción %c escogida no es válida, seleccione de nuevo.\n", option);
            }
        }while(option !='q');
    /* Hacer operaciones. */

    /* Mostrar resultados. */

    return 0;
}

/* Implementacion de funciones. */
//Punto 1 (20%) Función Menú
void getOption(char *_option){
    printf("\nMENÚ DE OPCIONES\n");
    printf("\ta) Nueva factura.\n");
    printf("\tb) Consultar artículo.\n");
    printf("\tc) Ingresar artículo.\n");
    printf("\tq) Salir.\n");
    printf("Seleccione una opción: ");
    setbuf(stdin, NULL); //limpiar el bufer
    scanf("\n%c", _option);
}

//Punto 3 (20%) adicionar artículos
void addItem (int *_codigo, char (*_descripcion)[12], float *_valor){
  int i;
    int num_new_items=0;
    printf("\nIngrese el número de productos a registrar: ");
    setbuf(stdin, NULL);

    // Obtengo el argumento y lo convierto a número
    scanf("%d", &num_new_items);
    if(num_new_items<=0){
        printf("\nEl valor ingresado no es válido, \ndebe ser un número entero mayor a cero.\n");
        return;
    }

    //Verificar que los existentes + los nuevos < maximo permitido
    if(num_new_items + enlisted_items > MAX_PRODUCT_CANT){
        printf("No es posible registrar %d productos.\n", num_new_items);
        printf("La capacidad máxima es %d y actualmente están registrados %d.\n", MAX_PRODUCT_CANT, enlisted_items);
        return;
    }

    //Enlistar items
    for(i=enlisted_items; i<enlisted_items+num_new_items; i++){
        /* Obtener información del empleado. */
        printf("\nNombre del producto N°%d: ", i + 1);
        setbuf(stdin, NULL);
        scanf("%s", (char *)(_descripcion+i));
        printf("Código: ");//Verifica que el salario sea un número
        setbuf(stdin, NULL);
        scanf("%d", _codigo+i);
        while(*(_codigo+i)<=0){
            printf("\nEl valor ingresado no es válido.\nIngrese de nuevo el código:");
            setbuf(stdin, NULL);
            scanf("%d", _codigo+i);
        }
        printf("Valor: ");//Verifica que el salario sea un número
        setbuf(stdin, NULL);
        scanf("%f", _valor+i);
        while(*(_valor+i)<=0){
            printf("\nEl valor ingresado no es válido.\nIngrese de nuevo el valor:");
            setbuf(stdin, NULL);
            scanf("%f", _valor+i);
        }
    }

    //Actualizar valores e informar al usuario
   enlisted_items += num_new_items;
   printf("\nSe han registrado %d productos en la lista.\n", num_new_items);
   printf("El número total de productos en la lista es %d.\n", enlisted_items);
}

//Punto 2 (20%) Consultar articulo
void Consultar(int *_codigo, char (*_descripcion)[12], float *_valor, char *_option, int *_posiciones){
        getOptionBuscar(_option);
          printf("\nLa opción escogida fue %c\n", *_option);
          switch (*_option){
              case 'a':
              _posiciones = (int *) malloc(sizeof(int) * MAX_PRODUCT_CANT);
              buscaCodigo(_codigo, _posiciones);
              break;
              case 'b':
              _posiciones = (int *) malloc(sizeof(int) * MAX_PRODUCT_CANT);
              buscaDescripcion(_descripcion, _posiciones);
              break;
              default:
              printf("La opción %c escogida no es válida, seleccione de nuevo.\n", *_option);
              getOption(_option);
          }

          //Imprimir inforación
          if(*(_posiciones)==101){
            printf("\nEl código no existe!!!\n" );
          }else{
          printf("|%-15s|%-15s|%-15s|\n", "Código", "Descripcion", "Valor");
          printf("|%-14d|%-15s|%-15.2f|\n", *(_codigo+(*_posiciones)), *(_descripcion+(*_posiciones)),*(_valor+(*_posiciones)) );
          }
          free(_posiciones);
}

//Submenú de búsqueda
void getOptionBuscar(char *_option){
    printf("\nMÉTODO DE BÚSQUEDA\n");
    printf("\ta) Buscar por código.\n");
    printf("\tb) Buscar por descripcion (Nombre).\n");
    printf("Seleccione una opción: ");
    setbuf(stdin, NULL); //limpiar el bufer
    scanf("\n%c", _option);
}

//Buscar por código
void buscaCodigo(int *_codigo, int *_posiciones){
  int posicion=0;
  int i=0;
  int cod=0;
  printf("\nIngrese el código del producto: " );
  setbuf(stdin, NULL); //limpiar el bufer
  scanf("\n%d", &cod);

  while(cod<=0){
      printf("\nEl valor ingresado no es válido.\nIngrese de nuevo el código:");
      setbuf(stdin, NULL);
      scanf("%d", &cod);
  }

  while((posicion < MAX_PRODUCT_CANT) & (cod != *(_codigo+posicion))) {
      posicion++;
  }

  if ((posicion==MAX_PRODUCT_CANT) & (cod != *(_codigo+posicion)) ){
    posicion= 101;
  }

if(cant !=0){
  for (i = enFactura; i < cant; i++) {
    *(_posiciones+i)=posicion;
    enFactura++;
  }
}

*(_posiciones) = posicion;
}

void buscaDescripcion(char (*_descripcion)[12], int *_posiciones){
  int posicion=0, iguales=1;
  char (*desc)[12];
  desc = (char (*)[12]) malloc(sizeof(char[12]) * 1);
  printf("\nIngrese el nombre del producto: " );
  setbuf(stdin, NULL); //limpiar el bufer
  scanf("\n%s", (char *)desc);

  iguales= strcmp(*desc , *(_descripcion+posicion));
  while((posicion < MAX_PRODUCT_CANT) & (iguales != 0)) {
      posicion++;
      iguales= strcmp(*desc , *(_descripcion+posicion));
  }

  if ((posicion==MAX_PRODUCT_CANT) & (iguales != 0) ){
    posicion= 101;
  }
        *(_posiciones) = posicion;

  free(desc);
}

//Punto 2 (40%) facturar
void facturar(char *_option, int *_codigo, int *_posiciones, float *_valor, char (*_descripcion)[12]){
  int i;
  int *cuantos;
  float *totales, total=0;
  printf("\nIngrese el número de productos a facturar: " );
  setbuf(stdin, NULL); //limpiar el bufer
  scanf("\n%d", &cant);
  if(cant <=0){
    printf("\nLa cantidad ingresada debe ser mayor a cero.\n" );
    cant=0;
    return;
  }

  if (cant > enlisted_items && enlisted_items!=0) {
    printf("\nLa cantidad ingresada es mayor que la cantidad de produc en el sistema.\n");
    cant=0;
    return;
  }

  if (cant > enlisted_items && enlisted_items==0) {
    printf("\nAún no hay productos en el sistema.\n");
    cant=0;
    return;
  }

  cuantos = (int *) malloc(sizeof(int) * cant);
  totales = (float *) malloc(sizeof(float) * cant);

  for (i = 0; i < cant; i++) {
    buscaCodigo(_codigo, _posiciones);
    while(*(_posiciones+i)==101){
      printf("\n El código no existe !!!\n");
      enFactura--;
      buscaCodigo(_codigo, _posiciones);
    }
    printf("Ingrese la cantidad de este producto: ");
    setbuf(stdin, NULL); //limpiar el bufer
    scanf("\n%d", (cuantos+i));
    if(*cuantos <=0){
      printf("\nEl valor debe ser mayor a cero, \nIngrese de nuevo la cantidad: ");
      setbuf(stdin, NULL); //limpiar el bufer
      scanf("\n%d", (cuantos+i));
    }
  }

  //Imprimir inforación
  printf("\n|\t\t\t%15s\t\t\t|\n", "Factura de venta");
  printf("|%-31s|%-31s|\n","Emprendedor S:A", "Nit: 80808080");
  printf("|%-15s|%-15s|%-15s|%-15s|\n", "Cantidad", "Descripcion", "Valor", "Total");

  for (i = 0; i < cant; i++) {
    *(totales+i)=(*(cuantos+i)) * (*(_valor+(*(_posiciones+i))));//multiplica la cantidad por el valor.
    printf("|%-15d|%-15s|%-15.2f|%-15.2f|\n", *(cuantos+i),  *(_descripcion+(*(_posiciones+i))), *(_valor+(*(_posiciones+i))), *(totales+i));
    total = total+*(totales+i);
  }
  printf("|%31s|%-31.2f|\n", "Total", total);
  cant =0;
  enFactura=0;
  free(cuantos);
  free(totales);
  free(_posiciones);
}
