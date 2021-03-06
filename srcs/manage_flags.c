/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#define USAGE "%s%s%s%s%s%s", USAGE1, USAGE2, USAGE3, USAGE4, USAGE5, USAGE6
#define USAGE1 "usage: ./lemin [flag1] [flagN] [redirect file, use '<']\n"
#define USAGE2 "               -e       Error managment\n"
#define USAGE3 "               -s       Print input string if error in data\n"
#define USAGE4 "               -one     Use one shortest path\n"
#define USAGE5 "               -info    Show information\n"
#define USAGE6 "               -h       Show this is message\n"
#define MAXINTVALUE 2147483647

void			set_flags(t_lem *data, char **argv, int flags)
{
	int i;

	i = 0;
	while (i < flags)
	{
		if (ft_strequ(argv[i], "-e"))
			data->error = 1;
		else if (ft_strequ(argv[i], "-s"))
			data->showinput = 1;
		else if (ft_strequ(argv[i], "-one"))
			data->oneway = 1;
		else if (ft_strequ(argv[i], "-info"))
			data->info = 1;
		else
		{
			ft_printf(USAGE);
			cleaning(data);
			exit(-42);
		}
		i++;
	}
}

int				search_max_steps2(t_lem *data)
{
	int		i;
	int		steps;
	t_prnt	*show;

	steps = 0;
	show = data->toout;
	ft_printf("");
	while (show)
	{
		i = 0;
		while (show->pathshow[i])
			i++;
		if (i > steps)
			steps = i;
		if (show->next)
			show = show->next;
		else
			break ;
	}
	return (steps);
}

int				search_min_steps(t_lem *data)
{
	int		i;
	int		steps;
	t_prnt	*show;

	steps = MAXINTVALUE;
	show = data->toout;
	while (show)
	{
		i = 0;
		while (show->pathshow[i])
			i++;
		if (i < steps)
			steps = i;
		if (show->next)
			show = show->next;
		else
			break ;
	}
	return (steps);
}
