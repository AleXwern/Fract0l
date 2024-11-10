/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 15:33:27 by anystrom          #+#    #+#             */
/*   Updated: 2024/11/10 23:35:27 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.hpp"
#include "value.hpp"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
**	THIS FINE IS NOT USED FOR NOW
*/

/*
** Builds the needed string+number string that will be shown.
** NUM is freed here, DUMMY is freed on stats.
*/

char		*create_stats(int num, const char *str)
{
	char	*strnum;
	char	*dummy;

	strnum = itoa(num);
	dummy = ft_strjoin(str, strnum);
	free(strnum);
	return (dummy);
}

/*
** DUMMY is a dummy string that temprarily stores created strings
** that need to be shown on screen.
** Author hasn't done ft_printf so we'll go trough a bit more
** convoluted process.
*/

static void	stats(t_fractol *frc)
{
	char	*dummy;

	printf("DATA");
	dummy = create_stats(frc->iter, "Iterations: ");
	printf(dummy);
	free(dummy);
	dummy = create_stats(frc->threads, "Threads: ");
	printf(dummy);
	free(dummy);
	if (frc->fractol == 1)
	{
		if (frc->fixjulia)
			printf(DATA_O);
		else
			printf(DATA_F);
	}
}

/*
** Writes a quick reference of keys to upleft corner.
** Position is based on window size but text size cannot be changed
** which may cause severe clipping on smaller windows.
*/

void		help_window(t_fractol *frc)
{
	if (frc->ishelp)
	{
		printf(HLP);
		printf(HLP_A);
		printf(HLP_B);
		printf(HLP_C);
		printf(HLP_D);
		printf(HLP_E);
		printf(HLP_F);
		printf(HLP_G);
		printf(HLP_H);
		printf(HLP_I);
		printf(HLP_J);
		stats(frc);
	}
}
