/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 17:28:29 by tkuhar            #+#    #+#             */
/*   Updated: 2018/04/02 20:18:05 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "valid.h"


//##############################################
#include <stdio.h>
//##############################################



int	*mapalloc()
{
	int *map;

	if((map = (int *)malloc(sizeof(int) * 16)))
		return (map);

	return (0);
}

int *key(int *map)
{
	int i;
	int b;
	
	i = -1;
	while (++i < 16)
	{
		b += map[i];
		map[i] += (i - 4 > 0 && map[i] > 0) ? map[i - 4] : 0;
		map[i] += (i - 1 > 0 && map[i] > 0) ? map[i - 1] : 0;
		map[i] += (i + 4 < 16 && map[i] > 0) ? map[i + 4] : 0;
		map[i] += (i + 1 < 16 && map[i] > 0) ? map[i + 1] : 0;
	}
	if (b != 4)
		return (0);
	b = 16;
	while (b--)
	{
		printf ("%i	", map[15 - b]);
		if (!((16 - b)%4))
			printf ("\n");
	}
	return (0);
}

int	*checkvalid_input(int fd, int *map)
{
	char buf[22];
	int i;
	int j;


	j = 21;
	i = 0;
	read (fd, buf, 21);
	while(buf[4] == '\n' && buf[9] == '\n' && buf[14] == '\n' &&
		buf[19] == '\n' && buf[20] == '\n' && j--)
		if (buf[20 - j] == '.' || buf[20 - j] == '#')
			map[i++] = (buf[20 - j] == '.') ? 0 : 1;
		else if (buf[20 - j] != '\n')
			return (0);
	buf[21] = '\0';
	if (j != -1)
		return (0);
	key(map);
	return (map);
}

int	main(int argc, char **argv)
{
	int *map;
	int fd;

	if (argc != 2)
		return (0);
	fd = open(argv[1],O_RDONLY);
	//printf("#####\n");
	map = mapalloc();
	checkvalid_input(fd, map);
	return (0);
}
