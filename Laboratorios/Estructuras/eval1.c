/*
 * PLANTILLA VACIA, VERSION 1.
 * Name         : eval1_LopezFelipe.c
 * Compilation  : gcc -Wall eval1_LopezFelipe.c -o 1.out
 * Execution    : ./1.out
*/

/* Incluir cabeceras o bibliotecas. */
#include <stdio.h>// printf, scanf, setbuf, fflush
#include <stdlib.h>//malloc
#include <string.h>

/* Definicion de macros y constantes. */
#define MAX_CHARACTER_NAME 50
#define MAX_CHARS_LINE 20

/* Definition of structures. */
typedef struct {
    char name[MAX_CHARACTER_NAME];
    float salary;
    int extraHours;
    float valorExtras;
    float salaryTotal;
} employee;

/* Declaración de funciones. */
void getOption(char *_option);
int getNumEmployees(FILE *f);
void registerEmployeesInFile(employee *emp, FILE *f);
void registerEmployees(employee *emp);
void getSalaryEmploye(employee *emp, float *_total);
void showList(employee *emp);
void generateFile(employee *emp, FILE *f, float *_total);

/* Variables globales. */
int max_employees = 0;
float extra_value = 0;
int enlisted_employees =0;
int numEmployeesInFIle = 0;
int registrarDesdeArchivo =0;

/* Main function. */
int main(int argc, char *argv[]) {

    /* Variables locales. */
    char option = 'x';
    int exitValue;
    float total =0;
    char *fileEntrada;
    FILE *employeeFile;
    char *fileSalida;
    FILE *salida;
    employee *employees;

    // Validación: Número de argumentos traídos de consola.
    if (argc != 5) {
            printf("\nError: Numero de parametros invalido.\nDebe iniciar asi: ./1.out <entrada.csv> <salida.txt> <numero maximo de trabajadores> <valor hora extra>\n");
    		exit(0);
        }

    fileEntrada = argv[1];
    fileSalida = argv[2];

    employeeFile = fopen(fileEntrada, "r");
    if(employeeFile == NULL) {
          printf("No se pudo abrir el archivo\n");
          exit(0);
      }

    salida = fopen(fileSalida, "w+");
    if(salida == NULL) {
          printf("No se pudo abrir el archivo\n");
          exit(0);
      }

    numEmployeesInFIle = getNumEmployees(employeeFile);

    if (numEmployeesInFIle <= 0) {
        printf("Error: No hay trabajadores en el archivo\n");
        exit(0);
      }

    printf("Hay %d trabajadores en el archivo\n", numEmployeesInFIle);

    // Obtengo el argumento y lo convierto a número
    max_employees = atoi(argv[3]);//convierte lo que recibe a número
    setbuf(stdin, NULL); //limpiar el bufer
    printf("El número máximo de empleados es %d\n", max_employees);

    extra_value = atof(argv[4]);
    setbuf(stdin, NULL); //limpiar el bufer
    printf("El valor de la hora extra es %f\n", extra_value);

      /* Obtener espacio dinámico en memoria. */
    employees = (employee *)malloc(sizeof(employee) * max_employees);

        //Validar que el número ingresado sea positivo
    if(max_employees<=0){
        printf("\nError: El número de empleados ingresado no es válido,\ndebe ser un número mayor a cero.\n");
        exit(0);
    }else{
        printf("La lista tendrá una cantidad máxima de %d trabajadores\n", max_employees);
        do{
          getOption(&option);
          printf("\nLa opción escogida fue %c\n", option);
          switch (option){
            case 'a':
              if(registrarDesdeArchivo == 0){
                registerEmployeesInFile(employees, employeeFile);
              }else{
                registerEmployees(employees);
              }
            break;
            case 'b':
              showList(employees);
            break;
            case 'c':
              getSalaryEmploye(employees, &total);
            break;
            case 'd':
              generateFile(employees, salida, &total);
            break;
            case 'q':
              printf("\nSaliendo del programa..\n\n");
            break;
            default:
              printf("La opción %c escogida no es válida, seleccione de nuevo.\n", option);
            }
          }while(option !='q');
        }

    exitValue = fclose(employeeFile);
    if(exitValue == 0) {
        printf("se cerró el archivo employees.\n");
    }

    exitValue = fclose(salida);
    if(exitValue == 0) {
        printf("se cerró el archivo salida.\n");
    }

    /* Free memory. */
    free(employees);

    return 0;
}

/* Implementacion de funciones. */

int getNumEmployees(FILE *f) {
    int num = 0;
    char buffer[MAX_CHARS_LINE];
    while(!feof(f)) {
        fgets(buffer, MAX_CHARS_LINE, f);
        num++;
    }
    rewind(f);
    return num - 1;
}

//Punto 1 (20%) Función Menú
void getOption(char *_option){
    printf("\nMENÚ DE OPCIONES\n");
    printf("\ta) Registrar trabajadores.\n");
    printf("\tb) Ver lista de trabajadores.\n");
    printf("\tc) Calcular nómina.\n");
    printf("\td) Generar archivo.\n");
    printf("\tq) Salir del programa.\n");
    printf("Seleccione una opción: ");
    setbuf(stdin, NULL); //limpiar el bufer
    scanf("\n%c", _option);
}

//Punto 2 (20%) Registrar empleados
void registerEmployees(employee *emp){
    int i;
    int num_new_employees=0;
    printf("\nIngrese el número de empleados a registrar: ");
    setbuf(stdin, NULL);

    // Obtengo el argumento y lo convierto a número
    scanf("%d", &num_new_employees);
    if(num_new_employees<=0){
        printf("\nEl valor ingresado no es válido, \ndebe ser un número entero mayor a cero.\n");
        return;
    }

    printf("El valor ingresado fue: %d\n", num_new_employees);

    //Verificar que los existentes + los nuevos < maximo permitido
    if(num_new_employees + enlisted_employees > max_employees){
        printf("No es posible registrar %d trabajadores.\n", num_new_employees);
        printf("La capacidad máxima es %d y actualmente están registrados %d.\n", max_employees, enlisted_employees);
        return;
    }

    for(i=enlisted_employees; i<enlisted_employees+num_new_employees; i++){
        printf("\nNombre del empleado N°%d: ", i + 1);
        setbuf(stdin, NULL);
        scanf("%s", (char *)&(emp+i)->name);
        printf("Salario: ");
        setbuf(stdin, NULL);
        scanf("%f", &(emp+i)->salary);
        while((emp+i)->salary<=0){
            (emp+i)->salary = 0;
            printf("\nEl valor ingresado no es válido, el salario debe ser mayor a cero.\nIngrese de nuevo el salario:");
            setbuf(stdin, NULL);
            scanf("%f", &(emp+i)->salary);
        }
        printf("Horas extra: ");
        setbuf(stdin, NULL);
		    scanf("%d", &(emp+i)->extraHours);
        while((emp+i)->extraHours<0){
            printf("\nEl valor ingresado no es válido debe ser un número igual o mayor a cero.\nIngrese de nuevo las horas extra: ");
            setbuf(stdin, NULL);
            scanf("%d", &(emp+i)->extraHours);
        }
    }
    //Actualizar valores e informar al usuario
    enlisted_employees += num_new_employees;
    printf("\nSe han registrado %d empleados en la lista.\n", num_new_employees);
    printf("El número total de empleados en la lista es %d.\n", enlisted_employees);
}

void registerEmployeesInFile(employee *emp, FILE *f) {
    /* Local variables. */
    int i = 0;
    char *token;
    char lines[MAX_CHARS_LINE];

    for (i = 0; i < numEmployeesInFIle; i++) {
        fgets(lines, MAX_CHARS_LINE, f);
        token = strtok(lines, ";");
        while(token!=NULL) {
            strcpy((char *)emp->name,token);
            token = strtok(NULL, ";");
            emp->salary = atof(token);
            token = strtok(NULL, ";");
            emp->extraHours = atoi(token);
            token = strtok(NULL, ";");
            emp->valorExtras = extra_value*(emp->extraHours);
        }
        emp++;
        enlisted_employees++;
    }
    registrarDesdeArchivo = 1;
    printf("Los usuarios del archivo de entrada fueron registrados exitosamente.\n");
}

//Punt0 3 (20) mostrar la lista
void showList(employee *emp){
    int i=0;
    if(enlisted_employees==0){
        printf("No se han ingresado datos aún.\n");
        return;
    }

    //Listar empleados
   printf("\n\tLista de trabajadores\n");
   printf("%-15s%-15s%-15s\n", "Nombre", "Salario base", "Horas extra");
   for(i=0; i<enlisted_employees; i++){
       printf("%-15s%-15.2f%-15d\n", emp->name, emp->salary, emp->extraHours);
       emp++;
   }
}


//Punto 4 (40%) Calcular salarios
void getSalaryEmploye(employee *emp, float *_total){
    int i;
    //Verificar que hayan datos
    if(enlisted_employees==0){
        printf("Aún no se ha ingresado ningún salario\n");
        return;
    }

    *_total = 0;
    printf("\n\t\tLista de trabajadores\n");
    printf("%-30s%-30s\n","Nombre de la empresa: XXX S:A", "Nit: 80808080");
    printf("%-15s%-15s%-15s%-15s\n", "Nombre", "Salario base", "Salario extra", "Total");
    for(i=0; i<enlisted_employees; i++){
      emp->valorExtras = emp->extraHours * extra_value;//salario extra de cada uno
      emp->salaryTotal = emp->salary + emp->valorExtras;//total de cada uno
      *_total += emp->salaryTotal; //total de todos
      printf("%-15s%-15.2f%-15.2f%-15.2f\n", emp->name, emp->salary, emp->valorExtras, emp->salaryTotal);
      emp++;
    }
    printf("%-45s%-15.2f\n", "Total", *_total);
}

void generateFile(employee *emp, FILE *f, float *_total) {
    int i = 0;
    fprintf(f, "\n\t\tLista de trabajadores\n");
    fprintf(f, "%-30s%-30s\n","Nombre de la empresa: XXX S:A", "Nit: 80808080");
    fprintf(f, "%-15s%-15s%-15s%-15s\n", "Nombre", "Salario base", "Horas extra", "Total");
    for (i = 0; i < enlisted_employees; i++) {
        fprintf(f, "%-15s%-15.2f%-15d%-15.2f\n", emp->name, emp->salary, emp->extraHours, emp->salaryTotal);
        emp++;
    }
    fprintf(f, "%-45s%-15.2f\n", "Total", *_total);
    printf("Los datos se almacenaron correctamente en el archivo.\n");
}
