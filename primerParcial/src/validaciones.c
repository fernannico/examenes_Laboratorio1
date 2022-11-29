/*
 * validaciones.c
 *
 *  Created on: 1 oct. 2022
 *      Author: User
 */

#include "validaciones.h"

int esNumerica(char * cadena, int limite)
{
    int retorno = -1; //error
    int i;

    if(cadena != NULL && limite > 0)
    {
        retorno = 1; //verdadero
        for(i = 0; i<limite && cadena [i] != '\0'; i++)
        {
            if(i== 0 && (cadena[i] == '+' || cadena[i] == '-'))
            {
                continue;
            }
            if(cadena[i] > '9' || cadena[i] < '0')
            {
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}

int getInt(int * pResultado)
{
    int retorno = -1;
    char bufferString[50];
    if( pResultado != NULL && myGets(bufferString,sizeof(bufferString)) == 0 && esNumerica(bufferString, sizeof(bufferString)))
    {
       retorno = 0;
       *pResultado = atoi(bufferString);
    }
    return retorno;
}

int myGets(char * cadena, int longitud)
{
	int retorno = -1;
	char bufferString[4096];

	if(cadena != NULL && longitud > 0)
	{
		fflush(stdin);
		if(fgets(bufferString, sizeof(bufferString), stdin) != NULL)
		{
			if(bufferString[strnlen(bufferString, sizeof(bufferString))-1] == '\n')
			{
				bufferString[strnlen(bufferString, sizeof(bufferString))-1] = '\0';
			}
			if(strnlen(bufferString, sizeof(bufferString)) <= longitud)
			{
				strncpy(cadena, bufferString, longitud);
				retorno  = 0;
			}
		}
	}
    return retorno;
}

int utn_getNumero(int * pResultado, char* mensaje, char * mensajeError, int minimo, int maximo, int reintentos)
{
    int retorno = -1;
    int bufferInt;

    do
    {
        reintentos--;
        printf("%s", mensaje);
        if( getInt(&bufferInt) == 0 && bufferInt >= minimo && bufferInt <= maximo)
        {
            *pResultado = bufferInt;
            retorno = 0;
            break;
        }
        printf("%s", mensajeError);
    }while(reintentos >= 0);

    return retorno;
}

///entero
//---------------------------------------------------------------------------------------------------
///flotante

int esFlotante(char* cadena)
{
	int i=0;
	int retorno = 1;
	int contadorPuntos=0;

	if(cadena != NULL && strlen(cadena) > 0)
	{
		for(i=0 ; cadena[i] != '\0'; i++)
		{
			if(i==0 && (cadena[i] == '-' || cadena[i] == '+'))
			{
				continue;
			}
			if(cadena[i] < '0' || cadena[i] > '9' )
			{
				if(cadena[i] == '.' && contadorPuntos == 0)
				{
					contadorPuntos++;
				}
				else
				{
					retorno = 0;
					break;
				}
			}
		}
	}
	return retorno;
}

int getFloat(float* pResultado)
{
    int retorno=-1;
    char buffer[64];

    if(pResultado != NULL)
    {
    	if(myGets(buffer,sizeof(buffer))==0 && esFlotante(buffer))
    	{
			*pResultado = atof(buffer);
			retorno = 0;
		}
    }
    return retorno;
}

int utn_getNumeroFlotante(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos)
{
	float bufferFloat;
	int retorno = -1;
	while(reintentos>=0)
	{
		reintentos--;
		printf("%s",mensaje);
		if(getFloat(&bufferFloat) == 0)
		{
			if(bufferFloat >= minimo && bufferFloat <= maximo)
			{
				*pResultado = bufferFloat;
				retorno = 0;
				break;
			}
		}
		printf("%s",mensajeError);
	}
	return retorno;
}

///flotante
//---------------------------------------------------------------------------------------------------
///abc

char validarSeguirNoSeguir(char * mensaje, char * mensajeError, int repeticiones){
	char letra = 'S';
	char letraNoSeguir = 'N';
	char opcion;

	do{
		printf("%s", mensaje);
		fflush(stdin);
		scanf("%c", &opcion);
		opcion = toupper(opcion);
		if(opcion != letra && opcion != letraNoSeguir){
			printf("%s", mensajeError);
			repeticiones--;
		}
	}while((opcion != letra && opcion != letraNoSeguir) && repeticiones >= 0);

	return opcion;
}

int utn_getCaracter(char* pResultado, char* mensaje,char* mensajeError, char minimo,char maximo,int reintentos)
{
	int retorno = -1;
	char buffer;
	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf("%s",mensaje);
			fflush(stdin);
			scanf("%c",&buffer);
			buffer = toupper(buffer);
			if(buffer >= minimo && buffer <= maximo)
			{
				*pResultado = buffer;
				retorno = 0;
				break;
			}
			printf("%s",mensajeError);
			reintentos--;
		}while(reintentos>=0);

	}
	return retorno;
}

int pedirCadena(char cadena[],int len,char mensaje[])
{
	int retorno;
	char buffer[1024];
	int largoBuffer;

	retorno = 0;

	printf("%s",mensaje);
	fflush(stdin);
	scanf("%[^\n]",buffer);

	largoBuffer = (int)strlen(buffer);

	if(len > largoBuffer)
	{
		strcpy(cadena,buffer);
		retorno = 1;
	}


	return retorno;
}
