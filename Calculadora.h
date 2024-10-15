#ifndef CALCULADORA_H_INCLUDED
#define CALCULADORA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
typedef struct
{
    char usuario[30];
    char contrasenia[30];
} Usuario;
typedef struct {
	int dni;
	char nombre[30];
	int telefono;
	char direccion[30];
	char rol;
} Persona;
typedef struct {
	char letras[4];
	int numeros;
} Patente;
typedef struct {
	Patente patente;
	char marca[30];
	char modelo[30];
	int anio;
	int kms;
	Persona Titular;
	float precioDeAdquisicion;
} Auto;

typedef struct {
	int dia;
	int mes;
	int anio;

} Fecha;

typedef struct {
	Fecha fecha;
	Patente autoAVender;
	float precioVenta;
	float ganancia;
	int dniComprador;
	int dniVendedor;
} Venta;

typedef struct {
	Patente patente;
	char marca[30];
	char modelo[30];
	int anio;
	int kms;
	int dniTitular;
	float precioDeAdquisicion;
} AutoArchivo;

void registrarse (char[],Usuario);
int iniciarsesion (char[]);
int RecorrerUsuario(char[], Usuario,Usuario);
int MostrarMenuYSeleccionarOpcion (int,char[],Usuario);
void AgregarAuto(Auto,char[]);
void AgregarPersonas (char[],Persona);
void ModificarPersona (char[]);
void ListadoPersonas(char[]);
void ListadoPersonasRecursivo(FILE *);
void MostrarPersonaElegida (char []);
void ListadoPersonasRecursivo(FILE*);
void ListadoAutos(char[],int);
void ListadoAutoRecursivo(FILE*,int);
void VerAutosEnVenta(char[]);
void MostrarAutoElegido (char[]);
void RegistrarVenta (char[],char[],char[]);
void AutosEnVenta(char[],char[]);
void VerVentas (char[]);
void VerUnaVenta (char[]);
void RecaudacionMes (char Ventas[]);
void MayorGanancia (char Ventas[]);
int CargarDimensionDinamico (char [],int);
void CargarArregloDinamico (Auto **,char[]);
int posicionMenor(Auto**,int);
void ordenacionSeleccion(Auto**,int);
void MostrarArreglodeAntiguedad (Auto **,int);



#endif // CALCULADORA_H_INCLUDED
