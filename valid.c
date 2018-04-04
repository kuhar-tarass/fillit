/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <tkuhar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 17:28:29 by tkuhar            #+#    #+#             */
/*   Updated: 2018/04/04 21:54:04 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "valid.h"


//############################################################
// УЖс, куча говнокода, переписал очень почти всё :)
//
//	не отличаю в конце файла 
//	 ...#$
//	 ...#$
//	 ...#$
//	 ...#$
//	 от 
//	 ...#$
//	 ...#$
//	 ...#$
//	 ...#$
//	 $
// хз как починить не ломая всё.
//###########################################################
#include <stdio.h>
//###########################################################

void	ft_elemdel(t_elem **alst)
{
	t_elem	*temp;

	if (alst && *alst)
	{
		while (*alst)
		{
			temp = (*alst)->next;
			free((*alst)->pos);
			free(*alst);
			*alst = temp;
		}
		*alst = 0;
	}
}

t_elem	*ft_elemnew(int *content)
{
	t_elem	*new;
	int		i;

	if (!(new = malloc(sizeof(t_elem))))
		return (0);
	i = -1;
	while (++i < 8)
		new->pos = content;
	new->next = 0;
	return (new);
}

int	ft_elempush_back(t_elem **begin_list, int *content)
{
	t_elem	*tmp;

	if (content == 0)
		return (1);
	if (!*begin_list)
	{
		*begin_list = ft_elemnew(content);
		return (0);
	}
	if (!(tmp = *begin_list))
		return (1);
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = ft_elemnew(content);
	return (0);
}

int	*key(int *map)
{
	int minc;
	int minr;
	int i;
	int *k;
	int j;

	if (!map || !(k = malloc(8 * 4)))
		return (0);
	j = 16;
	minr = 3;
	minc = 3;
	i = 0;
	while (j--)
		if (map[15 - j])
		{
			k[i] = (15 - j) % 4;
			minc = minc > k[i] ? k[i] : minc;
			k[++i] = (15 - j) / 4;
			minr = minr > k[i] ? k[i] : minr;
			i++;
		}
	while (i--)
		k[i] = (i % 2) ? k[i] - minr : k[i] - minc;
	return (k);
}

int	*checkmap(int *map)
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
		if (map[i] == 1)
			return (0);
	}
	if (b != 4 || max < 4)
		return (0);
	return (map);
}

int	checkvalid_input(int *map, t_elem **elem, char *s)
{
	char	buf[20];
	int		j;
	int		*k;
	int		fd;
	int		i;

	fd = open(s, O_RDONLY);
	while ( (i = read(fd, buf, 20)) == 20)
	{
		j = 20;
		while (buf[4] == '\n' && buf[9] == '\n' && buf[14] == '\n' &&
			buf[19] == '\n' && j--)
			if (buf[19 - j] == '.' || buf[19 - j] == '#')
				*map++ = (buf[19 - j] == '.') ? 0 : 1;
			else if (buf[19 - j] != '\n')
				return (1);
		if (ft_elempush_back(elem, key(checkmap(map = map - 16))))
				return (1);
		if (read(fd, buf, 1) && buf[0] != '\n')
			return (1);
	}
	if (!(read(fd, buf, 1)) && !(i % 20))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	int		*map;
	t_elem	*elem;
	int		b;

	if (argc != 2 )
		return (0);
	if (!(map = malloc(sizeof(int) * 16)))
		return (0);
	elem = 0;
	if (checkvalid_input(map, &elem, argv[1]))
	{
		printf ("§§§§§§§		MAP_ERROR		§§§§§§§\n");
		ft_elemdel(&elem);
	}
		//////////////////////print/////////////////////////
	else
	{
		t_elem *tmp = elem;
		if (!tmp)
			printf("#######		gg emptyfile	#######\n");
		while (tmp)
		{
			b = 0;
			while (b < 8)
				printf ("%i %i	", tmp->pos[b++], tmp->pos[b++]);
			printf("\n");
			tmp = tmp->next;
		}
	}
	return (0);
}
