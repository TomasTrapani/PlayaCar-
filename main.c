#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Calculadora.h"


int main()
{
    Usuario UsuariosRegistrados;
    Auto autos;
    Patente patentes;
    Persona personas;
    char ArchivoAuto[]= {"ArchivoAuto.bin"};
    char Registros[]= {"Usuarios.bin"};
    char ArchivoPersonas[]= {"Personas.bin"};
    char Ventas[]= {"Venta.bin"};
    char AutosAlaVenta[]={"Autosalaventa.bin"};
    int valor,flag=0,flagLogin=0,FlagCerrar=0,i=0;
    int opcion=0;
    printf("                                         !Bienvenido a PlayaCar!\n");
    printf("                                          --------------------- ");
    printf("\n \n             *Ofrecemos el mejor servicio y acompaniamiento para la compra de su vehiculo*\n");
    while(flag==0 && FlagCerrar==0)
    {
        printf("\nEjecute 0 para registrarse.\nEjecute 1 para iniciar sesion.\nEjecute 2 para salir.\n");
        fflush(stdin);
        scanf("%d",&valor);
        switch(valor)
        {
        case 0:
        {
            system("cls");
            char seguir='s';
            registrarse(Registros,UsuariosRegistrados);
            printf("\n Ahora puedes iniciar sesion!\n");
            while(flagLogin==0)
            {
                system("cls");
                flagLogin=iniciarsesion(Registros);
            }
            flag=1;
            break;
        }
        case 1:
        {
            char seguir='s';
            while(flagLogin==0)
            {
                system("cls");
                flagLogin=iniciarsesion(Registros);
                while(flagLogin==0)
                {
                    printf("\n¿Estas seguro que estas registrado? (S/N) ");
                    fflush(stdin);
                    scanf("%c",&seguir);
                    if(seguir=='s')
                    {
                        system("cls");
                        flagLogin=iniciarsesion(Registros);
                    }
                    else
                    {

                        system("cls");
                        registrarse(Registros,UsuariosRegistrados);
                    }
                }
            }

            flag=1;
            break;
        }
        case 2:
        {
           FlagCerrar=1;
           break;
        }
        default:
            printf("Su opcion no es correcta verifique su eleccion. ");
            break;
        }
        //system("pause");
        system("cls");
    }

    char seguir='s';
    while(seguir=='s' && FlagCerrar==0)
    {
        flag=1;
        opcion=MostrarMenuYSeleccionarOpcion(&opcion,Registros,UsuariosRegistrados);
        switch(opcion)
        {
        case 1:
        {
            int EleccionSobreAuto;
            printf("\nAgregar/modificar auto\n");
            printf("---------------------------");
            printf("\n1. Agregar un auto.\n2. Modificar un auto.\n3. Volver al menu/salir.\n");
            scanf("%d",&EleccionSobreAuto);
            while(flag==1)
                if(EleccionSobreAuto==1)
                {
                    AgregarAuto(autos,ArchivoAuto);

                    flag=0;

                }
                else if(EleccionSobreAuto==2)
                {
                    ModificarAuto(ArchivoAuto);
                    flag=0;
                }
                else if(EleccionSobreAuto==3)
                {
                    break;
                }
                else
                {
                    printf("Eleccion incorrecta elija nuevamente: ");
                    scanf("%d",&EleccionSobreAuto);
                }

            break;
        }
        case 2:
        {
            flag=1;
            int Eleccionpersona;
            printf("\nAgregar/modificar persona\n");
            printf("---------------------------");
            printf("\n1. Agregar una persona.\n2. Modificar una persona\n3. Volver al menu/salir.\n");
            scanf("%d",&Eleccionpersona);
            while(flag==1)
                if(Eleccionpersona==1)
                {
                    AgregarPersonas(ArchivoPersonas,personas);
                    flag=0;

                }
                else if(Eleccionpersona==2)
                {
                ModificarPersona(ArchivoPersonas);
                    flag=0;
                }
                else if(Eleccionpersona==3)
                {
                    break;
                }
                else
                {
                    printf("Eleccion incorrecta elija nuevamente: ");
                    scanf("%d",&Eleccionpersona);
                }

            break;
        }
        case 3:
        {
            printf("\n LISTADO: \n");
            ListadoPersonas(ArchivoPersonas);

            break;
        }
        case 4:
        {

            MostrarPersonaElegida(ArchivoPersonas);
            break;
        }
        case 5:
        {
            ListadoAutos(ArchivoAuto,i);
            break;
        }
        case 6:
        {
            AutosEnVenta(ArchivoAuto,AutosAlaVenta);
            VerAutosEnVenta(AutosAlaVenta);
            break;
        }
        case 7:
        {
            MostrarAutoElegido(ArchivoAuto);
            break;
        }
        case 8:
        {
            VerVentas(Ventas);
            break;
        }
        case 9:
        {
            VerUnaVenta(Ventas);
            break;

        }
        case 10:
        {
             RegistrarVenta (Ventas,ArchivoAuto,ArchivoPersonas);
            break;
        }
        case 11:
        {
            RecaudacionMes(Ventas);
            break;
        }
        case 12:
        {
            MayorGanancia(Ventas);
            break;
        }
        case 13:
        {
            int validos=0;
            validos=CargarDimensionDinamico(ArchivoAuto,validos);
            Auto *arrautos=malloc(sizeof(Auto)*(validos));
            CargarArregloDinamico (&arrautos,ArchivoAuto);
            ordenacionSeleccion(&arrautos,validos);
            MostrarArreglodeAntiguedad(&arrautos,validos);

            break;
        }
        }
    printf("\n\nDeseas voler al menu principal (s/n)...\n");
    fflush(stdin);
    scanf("%c",&seguir);
    system("cls");
    }
    return 0;
}

