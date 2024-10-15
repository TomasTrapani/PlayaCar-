#include "Calculadora.h"

void registrarse (char Registros[],Usuario UsuariosRegistrados)
{
    Usuario UsuarioExistente;
    char ConfirmacionContrasenia[30];
    int flag=0,i=0;
    char seguir='s';
    printf("\nREGISTRARSE\n");
    printf("-------------\n");
    while(seguir=='s' || flag==0)
    {
        printf("\nIngrese un nombre de usuario: ");
        fflush(stdin);
        scanf("%s",&UsuariosRegistrados.usuario);
        printf("Estas seguro de que este sea tu nombre de usuario?\nSi queres cambiar tu nombre ejecuta la letra S");
        fflush(stdin);
        scanf("%c",&seguir);
        if(seguir!='s')
        {
            flag = RecorrerUsuario(Registros,UsuarioExistente,UsuariosRegistrados);
        }
    }
    FILE *Usuarios=fopen(Registros,"ab");
    if(Usuarios!=NULL)
    {
        flag=1;
        seguir='s';
        while(seguir=='s' && flag==1)
        {
            printf("Ingrese una contrasenia: ");
            fflush(stdin);
            scanf("%s",&UsuariosRegistrados.contrasenia);
            printf("Ingrese de nuevo su contrasenia: ");
            fflush(stdin);
            scanf("%s",&ConfirmacionContrasenia);
            printf("Si no estas seguro de la eleccion de tu contraseña ejecuta la letra s. ");
            fflush(stdin);
            scanf("%c",&seguir);
            while(seguir=='s')
            {
                printf("Ingrese una contrasenia: ");
                fflush(stdin);
                scanf("%s",&UsuariosRegistrados.contrasenia);
                printf("Ingrese de nuevo su contrasenia: ");
                fflush(stdin);
                scanf("%s",&ConfirmacionContrasenia);
                printf("¿Ahora estas seguro de tu nueva eleccion, si no estas seguro ejecuta la letra 's'?");
                fflush(stdin);
                scanf("%c",&seguir);
            }
            while(flag==1)
            {
                if (strcmpi(UsuariosRegistrados.contrasenia,ConfirmacionContrasenia)==0)
                {
                    printf("¡Su usuario se ha creado correctamente!. ");
                    flag=0;
                }
                else
                {
                    printf("Su contrasenias no son iguales, ingrese nuevamente: \n");
                    printf("Ingrese una contrasenia: ");
                    fflush(stdin);
                    scanf("%s",&UsuariosRegistrados.contrasenia);
                    fflush(stdin);
                    printf("Ingrese de nuevo su contrasenia: ");
                    scanf("%s",&ConfirmacionContrasenia);
                }
            }

        }

        fwrite(&UsuariosRegistrados,sizeof(Usuario),1,Usuarios);
        fclose(Usuarios);

    }

}
int iniciarsesion (char Registros[])
{
    int flagU=0;
    char seguir='s';
    char usuario[30];
    char contrasenia[30];
    Usuario usuarioaux;
    printf("\n INICIAR SESION\n");
    printf("----------------\n");
    while(seguir=='s')
    {
        printf("Nombre de usuario: ");
        fflush(stdin);
        scanf("%s",&usuario);
        printf("Contrasenia: ");
        fflush(stdin);
        scanf("%s",&contrasenia);
        printf("Para cambiar su eleccion ejecute la letra 's'. ");
        fflush(stdin);
        scanf("%c",&seguir);

    }

    FILE* Usuarios=fopen(Registros,"rb");
    if(Usuarios!= NULL)
    {

        while(fread(&usuarioaux,sizeof(Usuario),1,Usuarios)>0 && flagU==0)
        {
            if(strcmpi(usuario,usuarioaux.usuario)==0 && strcmpi(contrasenia,usuarioaux.contrasenia)==0)
            {
                flagU=1;
            }
        }
        if(flagU==1)
        {
            printf("\n!Ha ingresado a su cuenta de manera correcta!\n");
            printf("--------------------------------------------\n");
        }
        else
        {
            printf("Usuario o contrasenia incorrecta. =( .\n");
        }
        fclose(Usuarios);
    }
    return flagU;
}
int RecorrerUsuario(char Registros[], Usuario UsuarioExistente,Usuario UsuariosRegistrados )
{
    int flag=1;
    FILE *Usuarios=fopen(Registros,"rb");
    if(Usuarios!=NULL)
    {
        while(fread(&UsuarioExistente,sizeof(Usuario),1,Usuarios)>0 && flag==1)
        {
            if(strcmp(UsuariosRegistrados.usuario,UsuarioExistente.usuario)==0)
            {
                printf("\n!Ese nombre ya esta registrado elija otro!");
                flag=0;

            }
        }
        fclose(Usuarios);
    }
    return flag;
}
int MostrarMenuYSeleccionarOpcion (int opcion,char Registros[],Usuario UsuariosRegistrados)
{
    int flag=0;
    printf("\n!Buenas bienvenido a nuestro menu!\n",UsuariosRegistrados.usuario);
    printf("\nQue estabas buscando...\n\n");
    printf ("  1- Agregar / modificar un auto.\n");
    printf ("  2- Agregar / modificar una persona.\n");
    printf("  3- Ver listado de personas (nombre, telefono y dni).\n");
    printf ("  4- Ver info de una persona (toda la info).\n");
    printf("  5- Ver listado de autos (marca, modelo, patente).\n");
    printf ("  6- Ver autos en venta (marca, modelo, patente y anio).\n");
    printf ("  7- Ver info de un auto (toda la info).\n");
    printf ("  8- Ver listado de ventas (fecha y patente).\n");
    printf ("  9- Ver una venta en particular(toda la info).\n");
    printf (" 10- Registrar una venta.\n");
    printf(" 11- Calcular cuanto se recaudo en determinado mes, de determinado anio.\n");
    printf(" 12- Calcular cual fue la venta que genero mayor ganancia hasta el momento.\n");
    printf(" 13- Ver los autos que tengan menos de 10 anios, por orden de antiguedad.\n");
    scanf("%d",&opcion);
    while(flag==0)
    {
        if(opcion<=13 && opcion>0)
        {
            flag=1;
        }
        else
        {
            printf("!Opcion incorrecta, elija nuevamente su numero!\n");
            fflush(stdin);
            scanf("%d",&opcion);
        }
    }
    return opcion;
}
void AgregarAuto (Auto autos,char ArchivoAuto[])
{
    int i=0,flag=0;
    char seguir='n';
    Auto aux;
    FILE* ArchiAuto=fopen(ArchivoAuto,"r+b");
    if(ArchiAuto!=NULL)
    {
        while(seguir=='n')
        {
            int letras;
            printf("Escriba las letras de tu patente: \n");
            fflush(stdin);
            scanf("%s",&autos.patente.letras);
            while(flag==0)
            {
                if((letras=strlen(autos.patente.letras))==3)
                {
                   flag=1;
                }
                else
                {
                    printf("Tu patente es incorrecta.\n");
                    printf("Escriba las letras de tu patente: \n");
                    fflush(stdin);
                    scanf("%s",&autos.patente.letras);

                }

            }
            flag=0;

            while(flag==0)
            {
            printf("Escriba los tres numeros de tu patente: \n");
            scanf("%d",&autos.patente.numeros);
                if(autos.patente.numeros>=1000 || autos.patente.numeros<0)
                {
                    printf("Tus numeros son incorrectos.\n");
                    printf("Escriba los tres numeros de tu patente: \n");
                    scanf("%d",&autos.patente.numeros);
                }
                else
                {
                    flag=1;
                }

            }
            flag=0;
            printf("¿Estas seguro que esta es la patente que queres cargar (S/N): %s %d ?\n",autos.patente.letras,autos.patente.numeros);
            fflush(stdin);
            scanf("%c",&seguir);
            while(fread(&aux,sizeof(Auto),1,ArchiAuto)>0 && flag==0)
                        {
                            if(strcmpi(autos.patente.letras,aux.patente.letras)==0 && autos.patente.numeros==aux.patente.numeros )
                                {
                                    printf("Esa patente ya esta cargada. Cargue nuevamente la patente.\n");
                                    flag=1;
                                }
                        }
            if(flag==1)
                {
                    seguir='n';
                }
        }
        flag=0;
        while(flag==0)
        {
            printf("¿Cual es la marca del auto que vas a agregar? \n");
            fflush(stdin);
            scanf("%s",autos.marca);
            printf("¿Estas seguro que esta es la marca que queres cargar (S/N): %s ?\n",autos.marca);
            fflush(stdin);
            scanf("%c",&seguir);
            if(seguir=='s')
                {
                    flag=1;
                }
        }
        flag=0;
        while(flag==0)
        {
            printf("¿Cual es el modelo del auto? ");
            fflush(stdin);
            scanf("%s",&autos.modelo);
            printf("¿Estas seguro que tu modelo del auto es (s/n): %s ?\n",autos.modelo);
            fflush(stdin);
            scanf("%c",&seguir);
            if(seguir=='s')
                {
                    flag=1;
                }
        }
        flag=0;
        while(flag==0)
        {
            printf("¿Cual es el anio del auto que vas a agregar? \n");
            fflush(stdin);
            scanf("%d",&autos.anio);
            printf("¿Estas seguro que esta es el anio que queres cargar (s/n): %d ?\n",autos.anio);
            fflush(stdin);
            scanf("%c",&seguir);
            if(seguir=='s')
                {
                    if(autos.anio>1990 || autos.anio<=2024)
                        {
                            flag=1;
                        }
                    else
                        {
                            printf("\nEse anio es incorrecto, verifique porfavor su eleccion.\n");

                        }
                }

        }
        flag=0;
        while(flag==0)
        {
            printf("¿Cuantos KM tiene el auto que vas agregar? \n");
            fflush(stdin);
            scanf("%d",&autos.kms);
            printf("¿Estas seguro que estos son los KMS que queres cargar (s/n): %d ?\n",autos.kms);
            fflush(stdin);
            scanf("%c",&seguir);
            if(seguir=='s')
                {
                    if(autos.kms<300000 && autos.kms>=0)
                    {
                    flag=1;
                    }
                    else
                    {
                    printf("\nEsos KM son incorrectos,verifique porfavor su eleccion.\n");
                    }


                }
        }
        flag=0;
        while(flag==0)
        {
            printf("¿Cual es el DNI de la persona?\n");
            fflush(stdin);
            scanf("%d",&autos.Titular.dni);
            printf("¿Estas seguro de que este es tu DNI (S/N): %d ?\n",autos.Titular.dni);
            fflush(stdin);
            scanf("%c",&seguir);
            if(seguir=='s')
                {
                        if(autos.Titular.dni<=99999999 && autos.Titular.dni>=999999)
                        {
                            flag=1;

                        }
                        else
                        {
                            printf("\nEse DNI esta mal escrito o no es valido.\n");
                        }
                }

        }
        flag=0;
        while(flag==0)
        {
            printf("¿Cual es el nombre de la persona?\n");
            fflush(stdin);
            scanf("%s",&autos.Titular.nombre);
            printf("¿Estas seguro de que es el nombre (s/n): %s ?\n",autos.Titular.nombre);
            fflush(stdin);
            scanf("%c",&seguir);
            if(seguir=='s')
                {
                    flag=1;
                }
        }
        flag=0;
        while(flag==0)
        {
            printf("¿Cual es el numero de telefono (sin codigo de area)?\n");
            fflush(stdin);
            scanf("%d",&autos.Titular.telefono);
            printf("¿Estas seguro que el telefono correspondiente es (s/n): %d ?\n",autos.Titular.telefono);
            fflush(stdin);
            scanf("%c",&seguir);
            if(seguir=='s')
                {
                    if(autos.Titular.telefono<10000000 && autos.Titular.telefono>999999)
                        {
                            flag=1;
                        }
                    else
                        {
                    printf("\nEse telefono esta mal escrito o no es valido. \n");
                        }
                }
        }
        flag=0;
        while(flag==0)
        {
            printf("¿Cual es la direccion (solo calle) ?\n");
            fflush(stdin);
            scanf("%s",&autos.Titular.direccion);
            printf("¿Estas seguro de que esta es tu dirrecion (S/N): %s ?\n",autos.Titular.direccion);
            fflush(stdin);
            scanf("%c",&seguir);
            if(seguir=='s')
                {
                    flag=1;
                }
        }
        flag=0;
        while(flag==0)
        {
            printf("¿Cual es el precio de adquisicion? ");
            fflush(stdin);
            scanf("%f",&autos.precioDeAdquisicion);
            printf("Estas seguro que este fue el precio de adquisicion el vehiculo (S/N): %.2f ?\n",autos.precioDeAdquisicion);
            fflush(stdin);
            scanf("%c",&seguir);
            if(seguir=='s')
                {
                    if(autos.precioDeAdquisicion<3000000 || autos.precioDeAdquisicion>50000000)
                    {
                    printf("Ese valor es erroneo, ingrese nuevamente el valor del vehiculo.\n");
                    fflush(stdin);
                    scanf("%f",&autos.precioDeAdquisicion);
                    }
                    else
                    {
                    flag=1;
                    }
                }
        }
          flag=0;
                while(flag==0)
                {
                    printf("Que Rol cumple usted? (C=comprador / V=Vendedor) \n");
                    fflush(stdin);
                    scanf("%c",&autos.Titular.rol);
                    if(autos.Titular.rol=='c')
                        {
                            printf("¿Estas seguro que el rol elegido es (S/N): %c ='comprador' ?\n",autos.Titular.rol);
                        }else if(autos.Titular.rol=='v')
                        {
                            printf("¿Estas seguro que el rol elegido es (S/N): %c = 'vendedor' ?\n",autos.Titular.rol);
                        }

                    fflush(stdin);
                    scanf("%c",&seguir);
                   if(seguir=='s')
                    {
                     if(autos.Titular.rol=='c' || autos.Titular.rol=='v')
                    {
                        flag=1;
                    }
                    else
                    {
                        printf("\nEse Rol no es valido o esta mal escrto. \n");

                    }
                    }

                }
        fwrite(&autos,sizeof(Auto),1,ArchiAuto);
        fclose(ArchiAuto);
    }

}

void ModificarAuto (char ArchivoAuto[])
{

    Auto Aux;
    Auto Patente;
    int flag=0;
    while(flag==0)
    {
        printf("¿Que letras tenia la patente del auto que queres modificarle su registro?\n" );
        fflush(stdin);
        scanf("%s",&Patente.patente.letras);
        FILE*ArchiAuto=fopen(ArchivoAuto,"rb");
        if(ArchiAuto!=NULL)
        {
            while(fread(&Aux,sizeof(Auto),1,ArchiAuto)>0 && flag==0)
            {
                if(strcmp(Aux.patente.letras,Patente.patente.letras)==0)
                {
                    flag=1;
                }
            }
            if(flag==0)
            {
                printf("Esa patente buscada no esta cargado en su registro porfavor verifique su eleccion.\n ");
            }
            fclose(ArchiAuto);
        }
    }
    char seguir='s';
    FILE* ArchiAuto=fopen(ArchivoAuto,"r+b");
    if(ArchiAuto!=NULL)
    {
        while(fread(&Aux,sizeof(Auto),1,ArchiAuto)>0)
        {
            if(strcmpi(Patente.patente.letras,Aux.patente.letras)==0)
            {
                printf("¿Queres modificarle sus letras en su patente (s/n)?\n");
                fflush(stdin);
                scanf("%c",&seguir);
                if(seguir=='s')
                {
                    printf("Cuales letras queres ponerle?\n");
                    fflush(stdin);
                    scanf("%s",&Aux.patente.letras);
                    int flag=0;
                    while(flag==0)
                    {
                        int letras=strlen(Aux.patente.letras);
                        if(letras!=3)
                        {
                            printf("Esa patente es incorrecta ingrese nuevamente su patente.\n");
                            fflush(stdin);
                            scanf("%s",&Aux.patente.letras);
                        }
                        else
                        {
                            flag=1;
                        }

                    }
                }
                printf("Queres modificarle su numero de patente (s/n)?\n");
                fflush(stdin);
                scanf("%c",&seguir);
                if(seguir=='s')
                {
                    printf("Cual numero de patente queres ponerle?\n");
                    fflush(stdin);
                    scanf("%d",&Aux.patente.numeros);
                    int flag=0;
                    while(flag==0)
                    {
                        if(Aux.patente.numeros<1000 && Aux.patente.numeros>=0)
                        {
                            flag=1;
                        }
                        else
                        {
                            printf("Ese numero de patente es incorrecta ingrese nuevamente sus numeros. \n");
                            fflush(stdin);
                            scanf("%d",&Aux.patente.numeros);
                        }
                    }
                }
                printf("Queres modificarle su marca de vehiculo (s/n)?\n");
                fflush(stdin);
                scanf("%c",&seguir);
                if(seguir=='s')
                {
                    printf("Cual marca queres ponerle?\n");
                    fflush(stdin);
                    scanf("%s",&Aux.marca);
                }
                printf("Queres mofidicarle su modelo (s/n)? \n");
                fflush(stdin);
                scanf("%c",&seguir);
                if(seguir=='s')
                {
                    printf("Cual modelo queres ponerle? \n");
                    fflush(stdin);
                    scanf("%s",&Aux.modelo);
                }
                printf("Queres modificarle su anio (s/n)?  \n");
                fflush(stdin);
                scanf("%c",&seguir);
                if(seguir=='s')
                {
                    printf("Cual anio queres ponerle?\n");
                    fflush(stdin);
                    scanf("%d",&Aux.anio);
                    int flag=0;
                    while(flag==0)
                    {
                        if(Aux.anio>1990 && Aux.anio<=2024)
                        {
                            flag=1;
                        }
                        else
                        {
                            printf("Ese numero de patente es incorrecta ingrese nuevamente sus numeros. \n");
                            fflush(stdin);
                            scanf("%d",&Aux.anio);

                        }
                    }

                }
                printf("Queres modificarle sus km (s/n)?\n");
                fflush(stdin);
                scanf("%c",&seguir);
                if(seguir=='s')
                {
                    printf("Cuantos km queres ponerle?\n");
                    fflush(stdin);
                    scanf("%d",&Aux.kms);
                    int flag=0;
                    while(flag==0)
                    {
                        if(Aux.kms<300000 && Aux.kms>=0)
                        {
                            flag=1;
                        }
                        else
                        {
                            printf("Esos kms son incorrectos ingrese nuevamente. \n");
                            fflush(stdin);
                            scanf("%d",&Aux.kms);
                        }
                    }
                }
                printf("Queres modificar su DNI del titular (s/n)?\n");
                fflush(stdin);
                scanf("%c",&seguir);
                if(seguir=='s')
                {
                    printf("Cual va a ser su nuevo DNI?\n");
                    fflush(stdin);
                    scanf("%d",&Aux.Titular.dni);
                    int flag=0;
                    while(flag==0)
                    {
                        if(Aux.Titular.dni<=99999999 && Aux.Titular.dni>=999999)
                        {
                            flag=1;

                        }
                        else
                        {
                            printf("\nEse DNI esta mal escrito o no es valido.\n");
                            printf("¿Cual es el DNI de la persona?\n");
                            fflush(stdin);
                            scanf("%d",&Aux.Titular.dni);
                        }
                    }
                }
                    printf("¿Queres cambiar el nombre del titular de este auto(s/n)?\n");
                    fflush(stdin);
                    scanf("%c",&seguir);
                        if(seguir=='s')
                        {
                        printf("¿Cual va a ser su nuevo nombre?\n");
                        fflush(stdin);
                        scanf("%s",Aux.Titular.nombre);
                        }
                    printf("Queres modificar la dirrecion (s/n)?\n");
                    fflush(stdin);
                    scanf("%c",&seguir);
                        if(seguir=='s')
                            {
                            printf("Cual va a ser su nueva dirrecion (solo calle)?\n");
                            fflush(stdin);
                            scanf("%s",&Aux.Titular.direccion);
                            }
                    printf("Queres modificar su numero de telefono(s/n)?\n");
                    fflush(stdin);
                    scanf("%c",&seguir);
                        if(seguir=='s')
                            {
                                printf("Cual queres que sea su nuevo telefono del titular (sin codigo de area)?\n");
                                fflush(stdin);
                                scanf("%d",&Aux.Titular.telefono);
                                int flag=0;
                                while(flag==0)
                                    {
                                        if(Aux.Titular.telefono<10000000 && Aux.Titular.telefono>999999)
                                            {
                                                flag=1;
                                            }else
                                            {
                                                printf("Numero incorrecto, recuerde no colocar su numero de area.\n");
                                                fflush(stdin);
                                                scanf("%d",&Aux.Titular.telefono);
                                            }
                                    }
                            }
                        printf("Queres cambiar su precio de adquisicion (s/n)?\n");
                        fflush(stdin);
                        scanf("%c",&seguir);
                        if(seguir=='s')
                        {
                            printf("Cual valor queres ponerle?\n");
                            fflush(stdin);
                            scanf("%f",&Aux.precioDeAdquisicion);
                            int flag=0;
                            while(flag==0)
                            {
                                if(Aux.precioDeAdquisicion>2500000 && Aux.precioDeAdquisicion<50000000)
                                {
                                    flag=1;
                                }
                                else
                                {
                                    printf("Ese precio es incorrecto ingrese nuevamente. \n");
                                    fflush(stdin);
                                    scanf("%d",&Aux.precioDeAdquisicion);
                                }
                            }
                        }
                    }
                     flag=0;
                 while(flag==0)
                {

                    printf("Que Rol cumple usted? (C=comprador / V=Vendedor) \n");
                    fflush(stdin);
                    scanf("%c",&Aux.Titular.rol);
                    if(Aux.Titular.rol=='c')
                        {
                             printf("¿Estas seguro que el rol elegido es (S/N): %c = 'Comprador' ?\n",Aux.Titular.rol);
                        }else if(Aux.Titular.rol=='v')
                        {
                            printf("¿Estas seguro que el rol elegido es (S/N): %c = 'Vendedor' ?\n",Aux.Titular.rol);
                        }
                    fflush(stdin);
                    scanf("%c",&seguir);
                    if(seguir=='s')
                    {
                       if(Aux.Titular.rol=='c' || Aux.Titular.rol=='v')
                    {
                        flag=1;
                    }
                    else
                    {
                        printf("\nEse Rol no es valido o esta mal escrto. \n");
                    }
                    }

                }

                    fseek(ArchiAuto,-sizeof(Auto),SEEK_CUR);
                    fwrite(&Aux,sizeof(Auto),1,ArchiAuto);
                    fseek(ArchiAuto,sizeof(Auto),SEEK_CUR);
                }
            fclose(ArchiAuto);
        }

}




void AgregarPersonas (char ArchivoPersonas[],Persona personas)
        {
            int flag=0;
            char seguir;
            FILE *ArchiPersonas=fopen(ArchivoPersonas,"ab");
            if(ArchiPersonas!=NULL)
            {
                while(flag==0)
                {
                    printf("¿Cual es el DNI de la persona?\n");
                    fflush(stdin);
                    scanf("%d",&personas.dni);
                    printf("¿Estas seguro de que este es tu DNI (s/n): %d ?\n",personas.dni);
                    fflush(stdin);
                    scanf("%c",&seguir);
                    if(seguir=='s')
                        {
                         if(personas.dni<=99999999 && personas.dni>=999999)
                            {
                                flag=1;

                            }
                        else
                            {
                                printf("\nEse DNI esta mal escrito o no es valido.\n");
                            }
                        }

                }
                flag=0;
                while(flag==0)
                {
                    printf("¿Cual es el nombre de la persona?\n");
                    fflush(stdin);
                    scanf("%s",&personas.nombre);
                    printf("¿Estas seguro de que es el nombre (s/n): %s ?\n",personas.nombre);
                    fflush(stdin);
                    scanf("%c",&seguir);
                    if(seguir=='s')
                        {
                            flag=1;
                        }
                }
                flag=0;
                while(flag==0)
                {
                    printf("¿Cual es el numero de telefono (sin codigo de area)?\n");
                    fflush(stdin);
                    scanf("%d",&personas.telefono);
                    printf("¿Estas seguro que el telefono correspondiente es (s/n): %d ?\n",personas.telefono);
                    fflush(stdin);
                    scanf("%c",&seguir);
                    if(seguir=='s')
                        {
                            if(personas.telefono<10000000 && personas.telefono>999999)
                                {
                                    flag=1;
                                }
                            else
                                {
                                    printf("\nEse telefono esta mal escrito o no es valido. \n");

                                }
                        }

                }
                flag=0;
                while(flag==0)
                {
                    printf("¿Cual es la direccion (solo calle) ?\n");
                    fflush(stdin);
                    scanf("%s",&personas.direccion);
                    printf("¿Estas seguro de que esta es tu dirrecion (s/n): %s ?\n",personas.direccion);
                    fflush(stdin);
                    scanf("%c",&seguir);
                    if(seguir=='s')
                        {
                            flag=1;
                        }
                }
                flag=0;
                 while(flag==0)
                {
                    printf("Que Rol cumple usted? (c=comprador / v=Vendedor) \n");
                    fflush(stdin);
                    scanf("%c",&personas.rol);

                    if(personas.rol=='c')
                        {
                            printf("¿Estas seguro que el rol elegido es (s/n): %c = 'Comprador' ?\n",personas.rol);
                        }
                    else if(personas.rol=='v')
                        {
                            printf("¿Estas seguro que el rol elegido es (s/n): %c = 'Vendedor' ?\n",personas.rol);
                        }

                    fflush(stdin);
                    scanf("%c",&seguir);
                   if(seguir=='s')
                    {
                      if(personas.rol=='c' || personas.rol=='v')
                    {
                        flag=1;
                    }
                    else
                    {
                        printf("\nEse Rol no es valido o esta mal escrto. \n");

                    }
                    }


                }
                fwrite(&personas,sizeof(Persona),1,ArchiPersonas);
                fclose(ArchiPersonas);
            }

        }

void ModificarPersona (char ArchivoPersonas[])
{
            char nombre[10];
            Persona aux;
            int flag=0;
            while(flag==0)
            {
                printf("¿Cual es el nombre de la persona que queres modificarle su registro?" );
                fflush(stdin);
                scanf("%s",&nombre);
                FILE*ArchiPersonas=fopen(ArchivoPersonas,"rb");
                if(ArchiPersonas!=NULL)
                {
                    while(fread(&aux,sizeof(Persona),1,ArchiPersonas)>0 && flag==0)
                    {
                        if(strcmp(nombre,aux.nombre)==0)
                        {
                            flag=1;
                        }
                    }
                    if(flag==0)
                    {
                        printf("Esa persona que estas buscando no esta cargado en su registro porfavor verifique su eleccion. ");
                    }
                    fclose(ArchiPersonas);
                }
            }
            char seguir='s';
            FILE* ArchiPersonas=fopen(ArchivoPersonas,"r+b");
            if(ArchiPersonas!=NULL)
            {
                while(fread(&aux,sizeof(Persona),1,ArchiPersonas)>0)
                {
                    if(strcmpi(nombre,aux.nombre)==0)
                    {
                        printf("¿Queres modificarle su nombre (s/n)?\n");
                        fflush(stdin);
                        scanf("%c",&seguir);
                        if(seguir=='s')
                        {
                            printf("Cual nombre queres ponerle?\n");
                            fflush(stdin);
                            scanf("%s",&aux.nombre);
                        }
                        printf("Queres modificarle su DNI? (s/n) \n");
                        fflush(stdin);
                        scanf("%c",&seguir);
                        if(seguir=='s')
                        {
                            printf("Cual DNI queres ponerle?\n");
                            fflush(stdin);
                            scanf("%d",&aux.dni);
                            int flag=0;
                            while(flag==0)
                            {
                                if(aux.dni<=99999999 && aux.dni>=999999)
                                {
                                    flag=1;
                                }
                                else
                                {
                                    printf("Ese numero de documento es invalido. Ingrese nuevamente el DNI\n");
                                    fflush(stdin);
                                    scanf("%d",&aux.dni);
                                }
                            }
                        }
                        printf("Queres modificarle su numero de telefono? \n");
                        fflush(stdin);
                        scanf("%c",&seguir);
                        if(seguir=='s')
                        {
                            printf("Cual numero de telefono queres ponerle (sin codigo de area)?\n");
                            fflush(stdin);
                            scanf("%d",&aux.telefono);
                            int flag=0;
                            while(flag==0)
                            {
                                if(aux.telefono<10000000 && aux.telefono>999999)
                                {
                                    flag=1;
                                }
                                else
                                {
                                    printf("Ese numero es incorrecto. Ingrese nuevamente su numero.\n");
                                    fflush(stdin);
                                    scanf("%d",&aux.telefono);
                                }
                            }
                        }
                        printf("Queres mofidicarle su direccion? \n");
                        fflush(stdin);
                        scanf("%s",&aux.direccion);
                        if(seguir=='s')
                        {
                            printf("Cual direccion queres ponerle? \n");
                            fflush(stdin);
                            scanf("%s",&aux.direccion);
                        }
                         printf("Queres modificarle el Rol a la persona? \n");
                        fflush(stdin);
                        scanf("%c",&seguir);
                        if(seguir=='s')
                        {
                            printf("Cual es el rol que deseas asignar? (C=comprador / V=vendedor) \n");
                            fflush(stdin);
                            scanf("%d",&aux.rol);
                            if(aux.rol=='c')
                                {
                                    printf("Estas  seguro que quieres asignarle el rol: %c 'Comprador'",aux.rol);
                                }else if(aux.rol=='v')
                                {
                                    printf("Estas seguro que quiere asignarle el rol: %c 'Vendedor'",aux.rol);
                                }
                                fflush(stdin);
                                scanf("%c",&seguir);
                            int flag=0;
                            while(flag==0)
                            {
                                if(aux.rol=='c' || aux.rol=='v')
                                {
                                    flag=1;
                                }
                                else
                                {
                                    printf("Ese rol es incorrecto. Ingreselo nuevamente.\n");
                                    fflush(stdin);
                                    scanf("%d",&aux.rol);
                                }
                            }
                        }
                        fseek(ArchiPersonas,-sizeof(Persona),SEEK_CUR);
                        fwrite(&aux,sizeof(Persona),1,ArchiPersonas);
                        fseek(ArchiPersonas,sizeof(Persona),SEEK_CUR);
                    }

                }
                fclose(ArchiPersonas);
            }
        }
void ListadoPersonas(char ArchivoPersonas[])
{
            FILE *ArchiPersonas=fopen(ArchivoPersonas,"rb");
            if(ArchiPersonas!=NULL)
            {
                ListadoPersonasRecursivo(ArchiPersonas);
                fclose(ArchiPersonas);
            }
}
void ListadoPersonasRecursivo(FILE *ArchiPersonas)
{
            Persona aux;
            if(fread(&aux,sizeof(Persona),1,ArchiPersonas)>0)
            {
                ListadoPersonasRecursivo(ArchiPersonas);
                printf("DNI: %d \n",aux.dni);
                printf("Nombre: %s \n",aux.nombre);
                printf("Telefono: %d \n",aux.telefono);
            }
}

void MostrarPersonaElegida (char ArchivoPersonas[])
{
            Persona aux;
            int dniabuscar=0,flag=0;
            char seguir;
            while(flag==0)
            {
                printf("Ingrese un DNI para buscar a la persona: \n");
                scanf("%i",&dniabuscar);
                printf("¿Estas seguro de que este es tu DNI %i (S=SI/N=NO):?\n",dniabuscar);
                fflush(stdin);
                scanf("%c",&seguir);
                if(seguir=='s')
                    {
                        if(dniabuscar<=99999999 && dniabuscar>=999999)
                            {
                            flag=1;
                            }
                        else
                            {
                    printf("\nEse DNI esta mal escrito o no es valido.\n");
                            }
                    }

            }
            flag=0;
            FILE*ArchiPersonas=fopen(ArchivoPersonas,"rb");
            if(ArchiPersonas!=NULL)
            {
                while(fread(&aux,sizeof(Persona),1,ArchiPersonas)>0 && flag==0)
                {
                    if (aux.dni==dniabuscar)
                    {
                        printf("DNI: %d \n",aux.dni);
                        printf("Nombre: %s \n",aux.nombre);
                        printf("Telefono: %d \n",aux.telefono);
                        printf("Direccion: %s \n",aux.direccion);
                        if(aux.rol=='c')
                            {
                                printf("Rol: Comprador\n");
                            }else if (aux.rol=='v')
                            {
                                printf("Rol: Vendedor\n");
                            }
                        flag=1;
                    }

                }
                if(flag==0)
                {
                    printf("La persona buscada no se encuentra registrada.\n");
                }
                fclose(ArchiPersonas);
            }
}

void ListadoAutos(char ArchivoAuto[],int i)
{
            printf("\nListado de autos:\n");
            printf("---------\n");
            FILE *ArchiAuto=fopen(ArchivoAuto,"rb");
            if(ArchiAuto!=NULL)
            {
                ListadoAutoRecursivo(ArchiAuto,+1);
                fclose(ArchiAuto);
            }
}

void ListadoAutoRecursivo(FILE *ArchiAuto,int i)
{
            Auto aux;
            if(fread(&aux,sizeof(Auto),1,ArchiAuto)>0)
            {

                printf("\n Auto n %d\n",i);
                printf(".........\n");
                printf("Patente: %s %d \n",aux.patente.letras, aux.patente.numeros);
                printf("Marca: %s \n",aux.marca);
                printf("Modelo: %s \n",aux.modelo);
                printf("Anio: %d\n",aux.anio);
                printf("KM: %d\n",aux.kms);
                printf("Nombre: %s\n",aux.Titular.nombre);
                printf("DNI: %d\n",aux.Titular.dni);
                printf("Telefono: %d\n",aux.Titular.telefono);
                printf("Direccion: %s\n",aux.Titular.direccion);
                printf("Precio de adquisicion: %.2f\n",aux.precioDeAdquisicion);
                ListadoAutoRecursivo(ArchiAuto,i+1);
            }
}

void VerAutosEnVenta (char AutosAlaVenta[])
{
            Auto aux;
            int i=1;
            FILE* ArchiAlaVenta=fopen(AutosAlaVenta,"rb");
            if(ArchiAlaVenta!=NULL)
            {
                while(fread(&aux,sizeof(Auto),1,ArchiAlaVenta)>0)
                {
                    printf(" Auto en venta nº: %d\n",i);
                    printf("---------------------\n");
                    printf("Patente: %s %d \n",aux.patente.letras, aux.patente.numeros);
                    printf("Marca: %s \n",aux.marca);
                    printf("Modelo: %s\n",aux.modelo);
                    printf("Anio: %d\n",aux.anio);
                    i++;
                }
                fclose(ArchiAlaVenta);
            }
}

void MostrarAutoElegido (char ArchivoAuto[])
{
            Auto aux;
            char patente[4];
            int numeros;
            int flag=0;
            char seguir='s';
            while(flag==0)
            {
                printf("Ingrese las letras de la patente para buscar al auto correspondiente: \n");
                scanf("%s",&patente);
                printf("¿Estas seguro de que estas son las letras de tu patente: %s (S=SI/N=NO)?\n",patente);
                fflush(stdin);
                scanf("%c",&seguir);
                if(seguir=='s')
                        {
                            int letras=strlen(patente);
                            if(letras==3)
                                {
                                flag=1;
                                }
                            else
                                {
                                    printf("\nEsa patente esta mal escrito o no es valida asegurate de que sean 3 letras.\n");
                                }
                        }
            }
            flag=0;
            while(flag==0)
            {
                printf("Por ultimo ingrese los numeros de la patente.\n");
                fflush(stdin);
                scanf("%d",&numeros);
                printf("Estas seguro que los numeros de tu patente son: %d (S=SI/N=NO)? \n",numeros);
                fflush(stdin);
                scanf("%c",&seguir);
                if(seguir=='s')
                    {
                        if(numeros<1000 && numeros>=0)
                            {
                                flag=1;
                            }else
                            {
                                printf("Esos numeros de patente son invalidos.\n");
                            }
                    }
            }
            flag=0;
            FILE*ArchiAuto=fopen(ArchivoAuto,"rb");
            if(ArchiAuto!=NULL)
            {
                while(fread(&aux,sizeof(Auto),1,ArchiAuto)>0 && flag==0)
                {
                    if (strcmpi(aux.patente.letras,patente)==0)
                    {
                        printf("\n!Hemos encontrado el auto que estabas buscando!\n");
                        printf("----------------------------------------------\n");
                        printf("Patente: %s %d \n",aux.patente.letras, aux.patente.numeros);
                        printf("Marca: %s \n",aux.marca);
                        printf("Modelo: %s \n",aux.modelo);
                        printf("Anio: %d \n",aux.anio);
                        printf("KM: %d\n",aux.kms);
                        printf("Precio de adquisicion: %f\n",aux.precioDeAdquisicion);
                        printf("Nombre del propietario: %s\n",aux.Titular.nombre);
                        printf("DNI del propietario: %d\n",aux.Titular.dni);
                        printf("Telefono del propietario: %d\n",aux.Titular.telefono);
                        flag=1;
                    }

                }
                if(flag==0)
                {
                    printf("La patente buscada no se encuentra registrada.\n");
                }
                fclose(ArchiAuto);
            }
}
void RegistrarVenta (char Ventas[],char ArchivoAuto [],char ArchivoPersonas[])
{
    Venta aux;
    char seguir;
    int flag=0;
    FILE*ArchivoVentas=fopen(Ventas,"ab");
    if(ArchivoVentas!=NULL)
    {
        printf("\nRegistro de ventas\n");
        printf("--------------------\n");
        while(flag==0)
        {
            printf("Ingrese el dia de la venta: \n");
            fflush(stdin);
            scanf("%d",&aux.fecha.dia);
            printf("Estas seguro que es %d? (S/N) \n",aux.fecha.dia);
            fflush(stdin);
            scanf("%c",&seguir);
            if(seguir=='s')
            {
                if(aux.fecha.dia>0 && aux.fecha.dia <= 31)
                {
                    flag=1;
                }
                else
                {
                    printf("El dia ingresado no es correcto o invalido ");
                }
            }
        }
        flag=0;
        while(flag==0)
        {
            printf("Ingrese el mes de la venta: \n");
            fflush(stdin);
            scanf("%d",&aux.fecha.mes);
            printf("Estas seguro que es %d? (S/N) \n",aux.fecha.mes);
            fflush(stdin);
            scanf("%c",&seguir);
            if(seguir=='s')
            {
                if(aux.fecha.mes>0 && aux.fecha.mes <= 12)
                {
                    flag=1;
                }
                else
                {
                    printf("El mes ingresado no es correcto o invalido ");
                }
            }
        }
        flag=0;
        while(flag==0)
        {
            printf("Ingrese el anio de la venta: \n");
            fflush(stdin);
            scanf("%d",&aux.fecha.anio);
            printf("Estas seguro que el anio que se realiza la venta es %d? (S/N) \n",aux.fecha.anio);
            fflush(stdin);
            scanf("%c",&seguir);
            if(seguir=='s')
            {
                if(aux.fecha.anio>1990 && aux.fecha.anio <= 2024)
                {
                    flag=1;
                }
                else
                {
                    printf("El anio ingresado no es correcto o invalido ");
                }

            }
        }
            printf("Fecha de la venta: %d/%d/%d\n",aux.fecha.dia,aux.fecha.mes,aux.fecha.anio);
            flag=0;
            while(flag==0)
            {
                int letras;
                printf("Escriba las letras de tu patente: \n");
                fflush(stdin);
                scanf("%s",&aux.autoAVender.letras);
                if((letras=strlen(aux.autoAVender.letras))!=3)
                {
                    printf("Tu patente es incorrecta.\n");
                }
                else
                {
                    flag=1;
                }
            }
            flag=0;
            while(flag==0)
            {
                printf("Escriba los tres numeros de tu patente: \n");
                fflush(stdin);
                scanf("%d",&aux.autoAVender.numeros);
                printf("Estas seguro que los numeros de su patente son: %d ?\n",aux.autoAVender.numeros);
                fflush(stdin);
                scanf("%c",&seguir);
                if(seguir=='s')
                    {
                     if(aux.autoAVender.numeros<1000 && aux.autoAVender.numeros>=0 )
                        {
                            flag=1;
                        }
                    else
                        {
                            printf("Tus numeros son incorrectos.\n");

                        }
                    }

            }
            flag=0;
            while(flag==0)
                {
                printf("Escriba su DNI (vendedor): ");
                fflush(stdin);
                scanf("%d",&aux.dniVendedor);
                printf("Quieres confirmar tu DNI: %d (s/n)?\n",aux.dniVendedor);
                fflush(stdin);
                scanf("%c",&seguir);
                    if(seguir=='s')
                        {
                          if(aux.dniVendedor <=99999999 && aux.dniVendedor>=999999)
                            {
                                FILE*ArchiPersonas=fopen(ArchivoPersonas,"rb");
                                Persona aux2;
                                if(ArchiPersonas!=NULL)
                                {
                                    while(fread(&aux2,sizeof(Persona),1,ArchiPersonas)>0 && flag==0)
                                    {
                                        if(aux2.dni==aux.dniVendedor && aux2.rol =='v')
                                        {
                                            printf("!El DNI del vendedor esta registrado!\n");
                                            flag=1;
                                        }

                                    }
                                    if(flag==0)
                                        {
                                            printf("Su DNI no esta registrado!!\n");
                                        }
                                    fclose(ArchiPersonas);
                                }

                            }
                            else
                            {
                    printf("\nEse DNI esta mal escrito o no es valido.\n");

                            }
                        }
                }
                flag=0;
            while(flag==0)
                {
                printf("Escriba el DNI del Comprador: ");
                fflush(stdin);
                scanf("%d",&aux.dniComprador);
                printf("Quieres confirmar su DNI: %d ?\n",aux.dniComprador);
                fflush(stdin);
                scanf("%c",&seguir);
                    if(seguir=='s')
                        {
                          if(aux.dniComprador <=99999999 && aux.dniComprador>=999999)
                            {
                                FILE*ArchiPersonas=fopen(ArchivoPersonas,"rb");
                                Persona aux3;
                                if(ArchiPersonas!=NULL)
                                {
                                    while(fread(&aux3,sizeof(Persona),1,ArchiPersonas)>0 && flag==0)
                                    {
                                        if(aux3.dni==aux.dniComprador && aux3.rol=='c')
                                        {
                                            printf("!El DNI comprador esta registrado!\n");
                                            flag=1;
                                        }

                                    }
                                    if(flag==0)
                                        {
                                            printf("Su DNI no esta registrado!! \n");
                                        }
                                    fclose(ArchiPersonas);
                                }

                            }
                            else
                            {
                    printf("\nEse DNI esta mal escrito o no es valido.\n");

                            }
                        }
                }
            MostrarAutoElegido(ArchivoAuto);
            printf("\n");
            FILE*ArchiAuto=fopen(ArchivoAuto,"rb");
            Auto autos;
            if(ArchiAuto!=NULL)
            {
                printf("Ingrese el precio de venta: ");
                fflush(stdin);
                scanf("%f",&aux.precioVenta);
                int flag=0;
                while(fread(&autos,sizeof(Auto),1,ArchiAuto)>0 )
                {
                    while(strcmp(aux.autoAVender.letras,autos.patente.letras)==0 && flag==0)
                    {

                        if(aux.precioVenta>autos.precioDeAdquisicion)
                        {
                            aux.ganancia=aux.precioVenta - autos.precioDeAdquisicion;
                            flag=1;
                        }
                        else
                        {
                            printf("Ese monto ingresado generaria una perdida en su venta. Ingrese nuevamente el valor de su venta.\n");
                            fflush(stdin);
                            scanf("%f",&aux.precioVenta);
                        }
                    }

                }
                fclose(ArchiAuto);
            }
        printf("Su auto ya ha sido Vendido!\n");
        fwrite(&aux,sizeof(Venta),1,ArchivoVentas);
        fclose(ArchivoVentas);
        }
        Auto AuxCambiarTitular;
        FILE*ArchiAuto=fopen(ArchivoAuto,"r+b");
        if(ArchiAuto!=NULL)
            {
                while(fread(&AuxCambiarTitular,sizeof(Auto),1,ArchiAuto)>0)
                    {
                        if(strcmpi(aux.autoAVender.letras,AuxCambiarTitular.patente.letras)==0 && aux.autoAVender.numeros==AuxCambiarTitular.patente.numeros)
                            {
                                fseek(ArchiAuto,-sizeof(Auto),SEEK_CUR);
                                AuxCambiarTitular.Titular.dni=aux.dniComprador;
                                AuxCambiarTitular.Titular.rol='c';
                                fwrite(&AuxCambiarTitular,sizeof(Auto),1,ArchiAuto);
                            }
                    }
                fclose(ArchiAuto);
            }
    }

void AutosEnVenta(char ArchivoAuto [],char AutosAlaVenta[])
{
    Auto aux;
    FILE*ArchiAuto=fopen(ArchivoAuto,"rb");
    if(ArchiAuto!=NULL)
    {
        fseek(ArchiAuto,-sizeof(Auto),SEEK_END);
        while(fread(&aux,sizeof(Auto),1,ArchiAuto)>0)
        {
            if(aux.Titular.rol =='v')
            {
                FILE* ArchiAlaVenta=fopen(AutosAlaVenta,"wb");
                if(ArchiAlaVenta!=NULL)
                    {
                        fwrite(&aux,sizeof(Auto),1,ArchiAlaVenta);
                        fclose(ArchiAlaVenta);
                    }
            }
        }
    fclose(ArchiAuto);
    }
}

void VerVentas (char Ventas[])
{
    Venta aux;
    int i=1;
    FILE* ArchivoVentas=fopen(Ventas,"rb");
    if(ArchivoVentas!=NULL)
        {
            while(fread(&aux,sizeof(Venta),1,ArchivoVentas)>0)
                {
                    printf("\nListado de ventas\n");
                    printf("--------------------\n");
                    printf("Venta n %d\n",i);
                    printf("Fecha: %d/%d/%d\n",aux.fecha.dia,aux.fecha.mes,aux.fecha.anio);
                    printf("Patente: %s %d",aux.autoAVender.letras,aux.autoAVender.numeros);
                    i++;
                }
        fclose(ArchivoVentas);
        }
}

void VerUnaVenta (char Ventas[])
{
    Venta aux;
    char patente[4];
    char seguir;
    int numeros,flag=0;
            while(flag==0)
            {
                printf("Ingrese las letras de la patente para buscar al auto correspondiente: \n");
                scanf("%s",&patente);
                printf("¿Estas seguro de que estas son las letras de tu patente: %s (S=SI/N=NO)?\n",patente);
                fflush(stdin);
                scanf("%c",&seguir);
                if(seguir=='s')
                        {
                            int letras=strlen(patente);
                            if(letras==3)
                                {
                                flag=1;
                                }
                            else
                                {
                                    printf("\nEsa patente esta mal escrito o no es valida asegurate de que sean 3 letras.\n");
                                }
                        }
            }
            flag=0;
            while(flag==0)
            {
                printf("Por ultimo ingrese los numeros de la patente.\n");
                fflush(stdin);
                scanf("%d",&numeros);
                printf("Estas seguro que los numeros de tu patente son: %d (S=SI/N=NO)? \n",numeros);
                fflush(stdin);
                scanf("%c",&seguir);
                if(seguir=='s')
                    {
                        if(numeros<1000 && numeros>=0)
                            {
                                flag=1;
                            }else
                            {
                                printf("Esos numeros de patente son invalidos.\n");
                            }
                    }
            }
    flag=0;
    FILE *ArchivoVentas=fopen(Ventas,"rb");
    if(ArchivoVentas!=NULL)
        {
            while(fread(&aux,sizeof(Venta),1,ArchivoVentas)>0 && flag==0)
                {
                    if(strcmpi(patente,aux.autoAVender.letras)==0 && aux.autoAVender.numeros==numeros)
                        {
                                printf("\n!Este auto ha sido vendido!\n");
                                printf("Fecha de venta: %d/%d/%d \n",aux.fecha.dia,aux.fecha.mes,aux.fecha.anio);
                                printf("DNI del comprador: %d \n",aux.dniComprador);
                                printf("DNI del vendedor: %d \n",aux.dniVendedor);
                                printf("Precio de venta: %.2f \n",aux.precioVenta);
                                printf("Patente del auto vendido: %s %d \n",aux.autoAVender.letras,aux.autoAVender.numeros);
                                printf("Ganancia de venta del auto: %.2f \n",aux.ganancia);
                        }
                }

        }
}
void RecaudacionMes (char Ventas[])
{
    Venta aux;
    int flag=0;
    int anio,mes;
    float gananciatotal=0;
    char seguir='s';

    while(flag==0)
    {
        printf("Ingrese el anio que desea ver su recaudacion \n");
        fflush(stdin);
        scanf("%d",&anio);
        if(anio<2024 && anio>1990)
        {
            printf("El anio ingresado no es valido!!\n");

        }
        else
        {
            printf("Estas seguro que queres ver el anio de recaudacion (s/n): %d \n",anio);
            fflush(stdin);
            scanf("%c",&seguir);
            if(seguir=='s')
            {
                if(anio>1990 && anio<2025)
                {
                    flag=1;
                }
                else
                {
                    printf("El anio ingresado no es valido!!\n");
                }
            }
        }
    }

    flag=0;
     while(flag==0)
    {
        printf("Ingrese el mes que desea ver su recaudacion \n");
        fflush(stdin);
        scanf("%d",&mes);
        if(mes<0 && mes>12)
        {
            printf("El anio ingresado no es valido!!\n");

        }
        else
        {
            printf("Estas seguro que queres ver el mes de recaudacion (s/n): %d \n",mes);
            fflush(stdin);
            scanf("%c",&seguir);
            if(seguir=='s')
            {
                if(mes>13 && anio<0)
                {
                   printf("El mes ingresado no es valido!!\n");
                }
                else
                {
                    flag=1;
                }
            }
        }
    }

    FILE*ArchivoVentas=fopen(Ventas,"rb");
    if(ArchivoVentas!=NULL)
    {
        while(fread(&aux,sizeof(Venta),1,ArchivoVentas)>0)
        {
            if(aux.fecha.anio==anio  && aux.fecha.mes==mes)
            {
                gananciatotal=gananciatotal+aux.ganancia;
            }
        }
        fclose(ArchivoVentas);
    }
    printf("La ganancia total del anio: %d, del mes %d fue de: %f",anio,mes,gananciatotal);

}
void MayorGanancia (char Ventas[])
{
    Venta aux,aux2;
    aux2.ganancia=0;
    FILE*ArchivoVentas=fopen(Ventas,"rb");
    if(ArchivoVentas!=NULL)
    {
        while(fread(&aux,sizeof(Venta),1,ArchivoVentas)>0)
        {
            if(aux.ganancia>aux2.ganancia)
            {
                aux2=aux;
            }
        }
        fclose(ArchivoVentas);
    }
    printf("\n!El auto que mayor ganancia nos dejo!\n");
    printf("-------------------------------------\n");
    printf("Patente: %s %d\n",aux2.autoAVender.letras,aux2.autoAVender.numeros);
    printf("DNI(comprador): %d \n",aux2.dniComprador);
    printf("DNI(Vendedor): %d \n",aux2.dniVendedor);
    printf("Fecha: %d / %d / %d \n",aux2.fecha.dia,aux2.fecha.mes,aux2.fecha.anio);
    printf("Ganancia: %.2f\n",aux2.ganancia);
    printf("Precio de venta: %.2f \n",aux2.precioVenta);
}
int CargarDimensionDinamico(char ArchivoAuto[],int validos)
{
   Auto aux;
    FILE*ArchiAuto=fopen(ArchivoAuto,"rb");
    if(ArchiAuto!=NULL)
    {
        while(fread(&aux,sizeof(Auto),1,ArchiAuto)>0)
        {
            if(aux.anio>=2014)
            {
                validos++;
            }

        }
        fclose(ArchiAuto);
    }
    return validos;
}

void CargarArregloDinamico (Auto **arrautos,char ArchivoAuto[])
{
    Auto aux;
    int i=0;
    FILE *ArchiAuto=fopen(ArchivoAuto,"rb");
    if(ArchiAuto!=NULL)
    {
            while(fread(&aux,sizeof(Auto),1,ArchiAuto)>0)
                {
                        if(aux.anio>=2014)
                            {
                                (*arrautos)[i]=aux;
                                i++;
                            }
                }
    fclose(ArchiAuto);
    }
}
int posicionMenor(Auto** arrautos,int validos)
{
    int pos=0;
    int menor=(*arrautos)[pos].anio;
    int posMenor = pos;
    int i=pos+1;
    while (i < validos){
        if(menor > (*arrautos)[i].anio){
            menor = (*arrautos)[i].anio;
            posMenor = i;
        }
        i++;
    }
    return posMenor;
}
void ordenacionSeleccion(Auto **arrautos, int validos)
{
    Auto aux;
    int posMenor;
    int i = 0;
    while(i< validos-1)
    {
        posMenor = posicionMenor(&arrautos,validos);
        aux =(*arrautos)[posMenor];
       (*arrautos)[posMenor] = (*arrautos)[i];
        (*arrautos)[i] = aux;
        i++;
    }

}
void MostrarArreglodeAntiguedad (Auto** arrautos,int validos)
{
    int i=1,f=0;
     while(f < validos)
    {
        printf("\nAuto n %d\n",i);
        printf("----------\n");
        printf("Patente: %s %d \n",(*arrautos)[f].patente.letras,(*arrautos)[f].patente.numeros);
        printf("Anio: %d \n",(*arrautos)[f].anio);
        printf("Kms: %d \n",(*arrautos)[f].kms);
        printf("Marca: %s \n",(*arrautos)[f].marca);
        printf("Modelo: %s \n",(*arrautos)[f].modelo);
        printf("Precio Adquisicion: %.2f \n",(*arrautos)[f].precioDeAdquisicion);
        printf("DNI: %d \n",(*arrautos)[f].Titular.dni);
        printf("Nombre: %s \n",(*arrautos)[f].Titular.nombre);
        i++;
        f++;
    }
}
