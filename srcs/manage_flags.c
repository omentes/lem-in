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
#define USAGE "%s%s%s%s", USAGE1, USAGE2, USAGE3, USAGE4
#define USAGE1 "usage: ./lemin [flag1] [flagN] [redirect file, use '<']\n"
#define USAGE2 "               -e       Error managment\n"
#define USAGE3 "               -s       Print input string if error in data\n"
#define USAGE4 "               -algo    Best algo enable\n"

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
		else if (ft_strequ(argv[i], "-algo"))
			data->algo = 1;
		else
		{
			ft_printf(USAGE);
			cleaning(data);
			exit(-42);
		}
		i++;
	}
}

// void			init_nrm(t_tout *nrm, int flag)
// {
// 	if (flag)
// 	{
// 		if (flag == 1)
// 		{
// 			nrm->check = 0;
// 			nrm->cc = 0;
// 		}
// 		else if (flag == 2)
// 		{
// 			// nrm->k++;
// 			nrm->i += nrm->cc;
// 		}
// 	}
// 	else
// 	{
// 		nrm->i = 0;
// 		nrm->k = 0;
// 		nrm->check = 0;
// 		nrm->cc = 0;
// 	}
// }

static void		clean_lst_out(t_prnt *show, int i)
{
	t_prnt	*temp;

	while (show)
	{
		if (show->pathshow)
		{
			i = 0;
			while (show->pathshow[i])
				free(show->pathshow[i++]);
			free(show->pathshow);
		}
		if (show->next)
		{
			temp = show;
			show = show->next;
			free(temp);
		}
		else
		{
			free(show);
			break ;
		}
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
	ft_printf("steps [%i]\n", steps);
	return (steps);
}
void			norme_output_first(t_tout *nrm, t_lem *data,
	t_prnt *test);
void			manage_output2(t_lem *data, int *ants)
{
	t_tout	nrm;
	int		j;

	if (ants)
		;
	// if ((int)data->how_ants < data->how_path)
	// 	data->how_path = data->how_ants;
	ft_bzero(&nrm, sizeof(t_tout));
	nrm.out = ft_new_char_arr(search_max_steps(data) *
		search_max_steps(data));
	// nrm.roomcount = search_max_steps2(data);
	nrm.linecount = search_max_steps(data);
	if (data->algo == 0)
		data->how_path = 1;
	norme_output_first(&nrm, data, data->toout);
	j = 0;
	// ft_printf("%s\n", data->input);
	while (nrm.out[j])
	{
		ft_printf("%s\n", nrm.out[j]);
		free(nrm.out[j]);
		j++;
	}
	clean_lst_out(data->toout, 0);
	free(nrm.out);
}

static t_prnt	*returntestlist(t_prnt *show, int *i)
{
	while ((*i)-- && show->next->howa)
		show = show->next;
	return (show);
}

void			norme_output_first(t_tout *nrm, t_lem *data, t_prnt *test)
{
	int mod;

	nrm->ant = 0;
	nrm->correct = 0;
	nrm->path = 0;
	while (nrm->ant < (int)data->how_ants)
	{
		mod = nrm->ant % data->how_path;
		test = returntestlist(data->toout, &mod);
		ft_printf("mod|%i|\n",mod);
		if (mod > 0)
			nrm->correct++;
		nrm->line = 0 + nrm->correct;
		nrm->name = 0;
		while (nrm->line < nrm->linecount)
		{
			ft_printf("boom!\n");
			if (test->pathshow[nrm->name])
			{
				if (nrm->name == 0)
				{
					nrm->path++;
					test->howa--;
				}
				if (nrm->out[nrm->line] == NULL)
					nrm->out[nrm->line] = ft_strdup("L");
				else
					nrm->out[nrm->line] = ft_strjoin_free(nrm->out[nrm->line], ft_strdup(" L"));
				nrm->out[nrm->line] = ft_strjoin_free(nrm->out[nrm->line], ft_itoa(nrm->ant + 1));
				nrm->out[nrm->line] = ft_strjoin_free(nrm->out[nrm->line], ft_strdup("-"));
				nrm->out[nrm->line] = ft_strjoin_free(nrm->out[nrm->line], ft_strdup(test->pathshow[nrm->name]));
			}
			nrm->line++;
			nrm->name++;
		}
		ft_printf("HERAK!%i!\n",nrm->path);
		if (nrm->path == data->how_path)
		{
			nrm->path = 0;
			nrm->correct++;
		}
		nrm->ant++;
	}
}

