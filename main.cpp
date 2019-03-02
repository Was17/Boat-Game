#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/*
Author: Jesus Gutierrez Lopez
Github: https://github.com/Was17/Boat-Game
Year: 2017
Description: Boat game to play in a computer console.
*/

//CONST
const int NUMBOAT = 10;
//STRUCTS
struct Barcos
{
    int casillasfila[4];
    int casillascolumna[4];
    int longitud;
    int restantes;
};
//VARIABLES
Barcos barcosUsuario[NUMBOAT];
Barcos barcosMaquina[NUMBOAT];
int longitudBarcos[NUMBOAT] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
int fila;
int columna;
int tableroUsuario[10][10];
int tableroMaquina[10][10];
int vistaUsuario[10][10];
int vistaMaquina[10][10];
int i, j;
char usuario[20];
int jugada = 1;
char orientacion;
char carac;
int filaAnterior, filaPosterior, columnaAnterior, columnaPosterior;
int error;

//INICIALIZAR BARCOS
void inicializarTableros()
{
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            vistaMaquina[i][j] = -1;
            vistaUsuario[i][j] = -1;
            tableroMaquina[i][j] = 0;
            tableroUsuario[i][j] = 0;
        }
    }
    for (i = 0; i < NUMBOAT; i++)
    {
        barcosUsuario[i].longitud = longitudBarcos[i];
        barcosUsuario[i].restantes = longitudBarcos[i];
        barcosMaquina[i].longitud = longitudBarcos[i];
        barcosMaquina[i].restantes = longitudBarcos[i];
    }
};

void inscribirBarcosUsuario()
{

    int opcion;
    i = 0;
    while (i < NUMBOAT)
    {
        do
        {
            error = 0;
            printf("Seleciona opcion: 1)Insertar Barco 2)Consultar tablero\n");
            scanf("%i", &opcion);
            switch (opcion)
            {
            case 1:
                break;
            case 2:
                for (fila = 0; fila < 10; fila++)
                {
                    for (columna = 0; columna < 10; columna++)
                    {
                        printf("%i ", tableroUsuario[fila][columna]);
                    }
                    printf("\n");
                }
                error = 1;
                break;
            default:
                printf("Hubo un problema introduzca de nuevo la accion");
                error = 1;
                break;
            }
        } while (error);
        do
        {
            error = 0;
            printf("\n BARCO %i\n", barcosUsuario[i].longitud);
            printf("Introduce la fila\n");
            scanf("%s", &carac);
            fila = (int)(carac - 65);
            if (fila < 0 || fila > 9)
            {
                printf("Error al introducir la linea\n");
                error = 1;
            }
        } while (error);
        do
        {
            error = 0;
            printf("introduce la columna\n");
            scanf("%i", &columna);
            if (columna < 0 || columna > 9)
            {
                printf("Error al introducir la columna\n");
                error = 1;
            }
        } while (error);
        do
        {
            error = 0;
            printf("Introduce la orientacion (H=Horizontal V=Vertical)\n");
            scanf("%s", &orientacion);
            if (orientacion != 'H' && orientacion != 'V')
            {
                printf("Error al introducir la orientacion\n");
                error = 1;
            }
            if (orientacion == 'H' && ((columna + longitudBarcos[i]) - 1) > 9)
            {
                printf("Error al introducir la orientacion\n");
                error = 1;
            }
            if (orientacion == 'V' && (fila + longitudBarcos[i] - 1) > 9)
            {
                printf("Error al introducir la orientacion\n");
                error = 1;
            }
        } while (error);
        //comprobar si es posible
        if (fila > 0)
        {
            filaAnterior = fila - 1;
        }
        else
        {
            filaAnterior = fila;
        }
        if (columna > 0)
        {
            columnaAnterior = columna - 1;
        }
        else
        {
            columnaAnterior = columna;
        }

        if (fila < 9)
        {

            filaPosterior = fila + longitudBarcos[i];
        }
        else
        {
            filaPosterior = 9;
        }

        if (columna < 9)
        {
            columnaPosterior = columna + longitudBarcos[i];
        }
        else
        {
            columnaPosterior = 9;
        }

        int ocupado = 0;
        int aux;
        for (aux = filaAnterior; aux <= filaPosterior; aux++)
            for (j = columnaAnterior; j <= columnaPosterior; j++)
            {
                if (tableroUsuario[aux][j] != 0)
                {
                    ocupado = 1;
                }
            }
        int casilla = 0;
        if (!ocupado)
        {
            if (orientacion == 'H')
            {
                if (columna == columnaPosterior)
                {
                    for (j = columna; j <= columnaPosterior; j++)
                    {
                        tableroUsuario[fila][j] = 1;
                        barcosUsuario[i].casillascolumna[casilla] = j;
                        barcosUsuario[i].casillasfila[casilla] = fila;
                        casilla++;
                    }
                }
                else
                {
                    for (j = columna; j < columnaPosterior; j++)
                    {
                        tableroUsuario[fila][j] = 1;
                        barcosUsuario[i].casillascolumna[casilla] = j;
                        barcosUsuario[i].casillasfila[casilla] = fila;
                        casilla++;
                    }
                }
            }
            else if (orientacion == 'V')
            {
                if (fila == filaPosterior)
                {
                    for (j = fila; j <= filaPosterior; j++)
                    {
                        tableroUsuario[j][columna] = 1;
                        barcosUsuario[i].casillascolumna[casilla] = columna;
                        barcosUsuario[i].casillasfila[casilla] = j;
                        casilla++;
                    }
                }
                else
                {
                    for (j = fila; j < filaPosterior; j++)
                    {
                        tableroUsuario[j][columna] = 1;
                        barcosUsuario[i].casillascolumna[casilla] = columna;
                        barcosUsuario[i].casillasfila[casilla] = j;
                        casilla++;
                    }
                }
            }

            i++; //CONFIRMADO QUE SE PUEDE COLOCAR
        }
        else
        {
            printf("Es imposible colocar el barco en dicha posicion, compruebe el tablero introduciendo un 2\n");
        }
    }
}
void maquinaGeneraBarquitos()
{
    i = 0;
    int error;
    srand(time(NULL));
    while (i < NUMBOAT)
    {
        do
        {
            error = 0;
            fila = rand() % 10;
            columna = rand() % 10;
            int aux1;
            aux1 = rand() % 2;
            if (aux1)
            {
                orientacion = 'H';
                if (columna + longitudBarcos[i] > 10)
                {
                    error = 1;
                }
            }
            else
            {
                orientacion = 'V';
                if (fila + longitudBarcos[i] > 10)
                {
                    error = 1;
                }
            }
        } while (error);
        //comprobar si es posible
        if (fila > 0)
        {
            filaAnterior = fila - 1;
        }
        else
        {
            filaAnterior = fila;
        }
        if (columna > 0)
        {
            columnaAnterior = columna - 1;
        }
        else
        {
            columnaAnterior = columna;
        }
        if (fila < 9)
        {

            filaPosterior = fila + longitudBarcos[i];
        }
        else
        {
            filaPosterior = 9;
        }

        if (columna < 9)
        {
            columnaPosterior = columna + longitudBarcos[i];
        }
        else
        {
            columnaPosterior = 9;
        }

        int ocupado = 0;
        int aux;
        for (aux = filaAnterior; aux <= filaPosterior; aux++)
            for (j = columnaAnterior; j <= columnaPosterior; j++)
            {
                if (tableroMaquina[aux][j] != 0)
                {
                    ocupado = 1;
                }
            }
        int casilla = 0;
        if (!ocupado)
        {
            if (orientacion == 'H')
            {
                if (columna == columnaPosterior)
                {
                    for (j = columna; j <= columnaPosterior; j++)
                    {
                        tableroMaquina[fila][j] = 1;
                        barcosMaquina[i].casillascolumna[casilla] = j;
                        barcosMaquina[i].casillasfila[casilla] = fila;
                        casilla++;
                    }
                }
                else
                {
                    for (j = columna; j < columnaPosterior; j++)
                    {
                        tableroMaquina[fila][j] = 1;
                        barcosMaquina[i].casillascolumna[casilla] = j;
                        barcosMaquina[i].casillasfila[casilla] = fila;
                        casilla++;
                    }
                }
            }
            else if (orientacion == 'V')
            {
                if (fila == filaPosterior)
                {
                    for (j = fila; j <= filaPosterior; j++)
                    {
                        tableroMaquina[j][columna] = 1;
                        barcosMaquina[i].casillascolumna[casilla] = columna;
                        barcosMaquina[i].casillasfila[casilla] = j;
                        casilla++;
                    }
                }
                else
                {
                    for (j = fila; j < filaPosterior; j++)
                    {
                        tableroMaquina[j][columna] = 1;
                        barcosMaquina[i].casillascolumna[casilla] = columna;
                        barcosMaquina[i].casillasfila[casilla] = j;
                        casilla++;
                    }
                }
            }

            i++;
        }
    }
}

//------------------------------------------------------------------------------------------------
///METODOS AUXILIARES DE JUEGO
int shootMaquina(int linea, int cola)
{
    int i, casilla = 0;
    for (i = 0; i < NUMBOAT; i++)
    {
        for (j = 0; j < barcosUsuario[i].longitud; j++)
        {
            if (barcosUsuario[i].casillasfila[j] == linea)
            {
                if (barcosUsuario[i].casillascolumna[j] == cola)
                {
                    barcosUsuario[i].restantes--;
                    return barcosUsuario[i].restantes;
                }
            }
        }
    }
}

int maquinaRealizaMovimiento(int linea, int cola)
{

    int disparo = tableroUsuario[linea][cola];
    vistaUsuario[linea][cola] = disparo;

    char c = (char)(linea + 65);
    printf("DISPARO DE LA MAQUINA A LA FILA:");
    ;
    printf(" %c COLUMNA: %i\n", c, columna);
    switch (disparo)
    {
    case 0:
        printf("DISPARO AL AGUA\n");
        tableroUsuario[linea][cola] = -1;
        return 1;

    case 1:
        tableroUsuario[linea][cola] = 2;
        printf("DISPARO:");
        if (shootMaquina(linea, cola) > 0)
        {
            printf("TOCADO\n");

            return 0;
        }
        else
        {
            printf("HUNDIDO\n");
            return 0;
        }
    }
}

int finalPartida(int x)
{
    int i, casilla = 0;
    for (i = 0; i < NUMBOAT; i++)
    {
        if (barcosUsuario[i].restantes != 0 && x)
        {
            return 1;
        }
        if (barcosMaquina[i].restantes != 0 && !x)
        {
            return 1;
        }
    }
    return casilla;
}

int shootUsuario(int linea, int cola)
{
    int i, casilla = 0;
    for (i = 0; i < NUMBOAT; i++)
    {
        for (j = 0; j < barcosMaquina[i].longitud; j++)
        {
            if (barcosMaquina[i].casillasfila[j] == linea)
            {
                if (barcosMaquina[i].casillascolumna[j] == cola)
                {
                    barcosMaquina[i].restantes--;
                    return barcosMaquina[i].restantes;
                }
            }
        }
    }
}

int UsuarioRealizaMovimiento(int linea, int cola)
{
    int disparo = tableroMaquina[linea][cola];
    vistaMaquina[linea][cola] = disparo;
    switch (disparo)
    {
    case 0:
        printf("DISPARO AL AGUA\n");
        return 1;

    case 1:
        printf("DISPARO AL BARCO: ");
        disparo = shootUsuario(linea, cola);
        if (disparo > 0)
        {
            printf("TOCADO\n");
            return 0;
        }
        else
        {
            printf("HUNDIDO\n");
            return 0;
        }
    default:
        return 1;
    }
}

//-----------------------------------------------------------------------------
///JUEGO PRINCIPAL
int aux = -1;
void movimientos()
{
    int turno = 1;
    int var;
    error;
    int final = 1;
    while (final)
    {
        int fallado = 0;
        aux++;
        if (aux == 2)
        {
            jugada++;
            aux = 0;
        }
        if (turno)
        {
            while (!fallado)
            {
                printf("JUGADA %i, TURNO DE %s\n", jugada, usuario);
                int disparar = 1;
                while (disparar)
                {
                    printf("SELECIONE OPCION\n");
                    printf("1)DISPARAR 2)CONSULTAR TABLERO USUARIO 3)CONSULTAR TABLERO ENEMIGO\n");
                    scanf("%i", &var);
                    switch (var)
                    {
                    case 1:
                        do
                        {
                            error = 0;
                            disparar = 0;
                            do
                            {
                                error = 0;
                                printf("Introduce la fila\n");
                                scanf("%s", &carac);
                                fila = (int)(carac - 65);
                                if (fila < 0 || fila > 9)
                                {
                                    printf("Error al introducir la fila\n");
                                    error = 1;
                                }
                            } while (error);
                            do
                            {
                                error = 0;
                                printf("introduce la columna\n");
                                scanf("%i", &columna);
                                if (columna < 0 || columna > 9)
                                {
                                    printf("Error al introducir la columna\n");
                                    error = 1;
                                }
                            } while (error);
                            if (vistaMaquina[fila][columna] != -1)
                            {
                                error = 1;
                                printf("YA HA DISPARADO EN DICHA POSICION; PRUEBE DE NUEVO\n");
                            }
                        } while (error);
                        fallado = UsuarioRealizaMovimiento(fila, columna);
                        break;
                    case 2:
                        for (i = 0; i < 10; i++)
                        {
                            for (j = 0; j < 10; j++)
                            {
                                if (tableroUsuario[i][j] != -1)
                                    printf("%i ", tableroUsuario[i][j]);
                                else
                                    printf("* ");
                            }
                            printf("\n");
                        }
                        break;
                    case 3:
                        for (i = 0; i < 10; i++)
                        {
                            for (j = 0; j < 10; j++)
                            {
                                if (vistaMaquina[i][j] != -1)
                                    printf("%i ", vistaMaquina[i][j]);
                                else
                                    printf("* ");
                            }
                            printf("\n");
                        }
                        break;
                    }
                    final = finalPartida(0);
                    if (final == 0)
                    {
                        fallado = 1;
                        turno = 2;
                    }
                }
            }

            turno = 0;
        }
        else if (turno == 0)
        {
            int anterior = 0;
            int x = 1;
            int y = 0;
            error = 0;
            int contador = 0;
            fallado = 0;
            while (!fallado)
            {
                printf("JUGADA %i,TURNO DE LA MAQUINA\n", jugada);
                do
                {
                    error = 0;
                    fila = rand() % 10;
                    columna = rand() % 10;
                    if (vistaUsuario[fila][columna] != -1)
                    {
                        error = 1;
                    }
                } while (error);
                fallado = maquinaRealizaMovimiento(fila, columna);
                final = finalPartida(1);
                if (final == 0)
                {
                    fallado = 1;
                    turno = 2;
                }
            }
            turno = 1;
        }
    }
    if (!finalPartida(1))
    {
        printf("Victoria de la Maquina en %i jugadas\n", jugada);
        printf("Han quedado en pie los siguientes barcos de la maquina: \n");
        for (i = 0; i < NUMBOAT; i++)
        {
            if (barcosMaquina[i].restantes != 0)
            {
                printf("un barco de longuitud %i\n", barcosMaquina[i].longitud);
            }
        }
    }
    else
    {
        printf("Victoria del usario en %i jugadas\n", jugada);
        printf("Han quedado en pie los siguientes barcos de %s\n", usuario);
        for (i = 0; i < NUMBOAT; i++)
        {
            if (barcosUsuario[i].restantes != 0)
            {
                printf("un barco de longuitud %i\n", barcosUsuario[i].longitud);
            }
        }
    }
}

//Main Program
int main()
{
    printf("==============================\n"
           "====JUEGO DE LOS BARQUITOS====\n"
           "==============================\n"
           "===******* ***** *******======\n"
           "==============================\n"
           "Bienvenido al juego de los barquitos!\n"
           "Este juego es un simulador del juego de los barquitos!\n"
           "Para algunas personas, es un simple juego.\n Otras los usan para mejorar su velocidad mental y desarrollar su conocimiento de lo desconocido.");
    printf("Ahora dejame conocerte un poco mas. Cual es tu nombre?: \n");
    scanf("%s", usuario);
    printf("Es hora de comenzar tu aventura, pero \n No te gustaria  conocer las reglas antes de empezar?\n Introduce el numero de la opcion que quieres seleccionar 1)Si 2)No\n");
    int opcion;
    do
    {
        scanf("%i", &opcion);
    } while (opcion != 2 && opcion != 1);
    if (opcion == 1)
    {
        printf("Es muy sencillo jugar.\n "
               "Tendras que colocar tus barcos de forma que esten separados en una unidad en todas las direcciones.\n"
               "Y posteriormente intentar adivinar donde la maquina tiene escondidos los suyos.\n"
               "Es facil, a que si? pues venga pongamonos en marcha.\n");
    }
    inicializarTableros();
    inscribirBarcosUsuario();
    maquinaGeneraBarquitos();
    movimientos();
    return 0;
}
