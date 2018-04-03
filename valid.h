/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 18:21:44 by tkuhar            #+#    #+#             */
/*   Updated: 2018/04/01 18:21:45 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_elem
{
	struct s_elem	*next;
	struct s_elem	*prev;
	int		*pos;
}				t_elem;

#endif
