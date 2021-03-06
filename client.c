/*
 * client.c
 * 
 * Copyright 2018 Alvarito050506 <donfrutosgomez@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

int main(int argc, char *argv[])
{
	int stsocket, stport;
	struct sockaddr_in address;
	char buffer[2048];
	if (argc == 2 && strcmp(argv[1], "-h") == 0 || argc == 2 && strcmp(argv[1], "--help") == 0)
	{
		printf("Uso: %s [opciones] host\nOpciones:\n\t-h, --help\tMuestra esta ayuda.\n\nEl argumento <host> es el nombre del host a conectarse. El cliente se conectará al puerto 3890 de este.\n\nEstado de salida:\n\t0 si todo fue bien.\n\t1 si no se pudo crear el socket.\n\t2 si no se especificó un host.\n\t3 si el host no es válido.\n", argv[0]);
		return 0;
	}
	stport = 3890;
	stsocket = socket(AF_INET, SOCK_STREAM, 0);
	if (argc < 2)
	{
		printf("300 - No se especificó un host.\n");
		return 1;
	}
	if (stsocket < 0)
	{
		printf("201 - No se pudo crear el socket.\n");
		return 2;
	}
	bzero((char *) &address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(argv[1]);
	if (address.sin_addr.s_addr < 0)
	{
		printf("301 - El host %s no es válido.\n", argv[1]);
		return 3;
	}
	address.sin_port = htons(stport);
	connect(stsocket, (struct sockaddr *) &address, sizeof(address));
	printf("101 - Conectado. (STTP/1.0)\n");
	printf("Ingrese el mesaje a enviar al servidor: ");
	bzero(buffer, 2048);
	fgets(buffer, 2047, stdin);
	write(stsocket, buffer, strlen(buffer));
	bzero(buffer, 2048);
	read(stsocket, buffer, 2047);
	printf("%s\n", buffer);
	close(stsocket);
	return 0;
}
