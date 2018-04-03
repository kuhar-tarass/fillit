/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 17:28:29 by tkuhar            #+#    #+#             */
/*   Updated: 2018/04/03 10:02:00 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "valid.h"


//##############################################
#include <stdio.h>
//##############################################


t_elem	*ft_elemnew(int *content)
{
	t_elem *new;

	if (!(new = malloc(sizeof(t_elem))))
		return (0);
	new->pos = content;
	new->next = 0;
	new->prev = 0;
	return (new);
}

void	ft_elempush_back(t_elem **begin_list, int *content)
{
	t_elem	*tmp;

	if (!*begin_list)
	{
		*begin_list = ft_elemnew(content);
		return ;
	}
	if (!(tmp = *begin_list))
		return ;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = ft_elemnew(content);
	tmp->next->prev = tmp;
}

int	*cutkey(int *k)
{
	int minc;
	int minr;
	int i;

	i = 8;
	minr = 3;
	minc = 3;
	while(i--)
		if (i % 2)
			minr = minr > k[i] ? k[i] : minr;
		else
			minc = minc > k[i] ? k[i] : minc;
	i = 8;
	while (i--)
		if (i % 2)
			k[i] = k[i] - minr;
		else
			k[i] = k[i] - minc;
	return (k);
}


int *key(int *map, int *k)
{
	int i;
	int b;
	int max;

	i = -1;
	b = 0;
	max = 0;
	while (++i < 16)
	{
		b += map[i];
		map[i] += (i - 4 > 0 && map[i] > 0) ? map[i - 4] : 0;
		map[i] += (i - 1 > 0 && map[i] > 0) ? map[i - 1] : 0;
		map[i] += (i + 4 < 16 && map[i] > 0) ? map[i + 4] : 0;
		map[i] += (i + 1 < 16 && map[i] > 0) ? map[i + 1] : 0;
		max = map[i] > max ? map[i] : max;
	}
	if (b != 4 || max < 3)
		return (0);
	while(i--)
		if (map[15 - i])
		{
			*(k++) = (15 - i) % 4; 
			*(k++) = (15 - i) / 4;
		}
	return (k - 8);
}

int	checkvalid_input(int fd, int *map, t_elem **elem, char *s)
{
	char buf[21];
	int i;
	int j;
	int *k;

	fd = open(s, O_RDONLY);
	while (read (fd, buf, 20))
	{
		i = 0;
		j = 20;
		while(buf[4] == '\n' && buf[9] == '\n' && buf[14] == '\n' &&
			buf[19] == '\n' && buf[20] == '\n' && j--)
			if (buf[20 - j] == '.' || buf[20 - j] == '#')
				map[i++] = (buf[20 - j] == '.') ? 0 : 1;
			else if (buf[20 - j] != '\n')
				break;
		if (j != -1)
			break ;
		if ((k = malloc(sizeof(int) * 8)))
			ft_elempush_back(elem, cutkey(key(map,k)));
	}
	printf("!!!!");
	//write(1,buf, 21);
	return ((buf[0] == '\0') ? 0 : 1);
}

int	main(int argc, char **argv)
{
	int *map;
	int fd;
	t_elem *elem;
	int b;

	if (argc != 2)
		return (0);
	if (!(map = malloc(sizeof(int) * 16)))
		return (0);
	elem = 0;
//	int i  = 2;
	if (checkvalid_input(fd, map, &elem, argv[1]))
		printf ("§§§§§§§\n");
	// t_elem *tmp = elem;
	// while (tmp)
	// {
	// 	b = 0;
	// 	while (b < 8)
	// 		printf ("%i %i	", tmp->pos[b++], tmp->pos[b++]);
	// 	printf("\n");
	// 	tmp = tmp->next;
	// }
	return (0);
}
