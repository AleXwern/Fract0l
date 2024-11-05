/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 14:24:04 by anystrom          #+#    #+#             */
/*   Updated: 2024/10/24 19:57:50 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.hpp"

/*
** Color stuff
** Function is spread to four parts
** A * B * C * D
** Basically B and C are the most important factors.
** Rising pow(currIter) power makes the graph lean on right.
** Likewise pow(1 - currIter) has the opposite effect.
** 0-point of X+1 is half of X, where X is power.
** Removing B or C or setting power as 0 is the key to filling valid area.
*/

/*
** Creates, sets and returns a color palette based on ITER
** T is a double value between 0 and 1.
*/

uint32_t		get_color(double currIter, int set, SDL_PixelFormat *format)
{
	t_color		colour;

	switch (set)
	{
	case 0:
		colour.red = (12 * pow((1 - currIter), 0) * pow(currIter, 3) * 255);
		colour.blue = (13 * pow((1 - currIter), 2) * pow(currIter, 2) * 255);
		colour.green = (14 * pow((1 - currIter), 2) * pow(currIter, 1) * 255);
		break;
	case 1:
		colour.red = (16 * pow((1 - currIter), 2) * pow(currIter, 2) * 240);
		colour.blue = (16 * pow((1 - currIter), 2) * pow(currIter, 2) * 240);
		colour.green = (16 * pow((1 - currIter), 2) * pow(currIter, 2) * 240);
		break;
	case 2:
		colour.red = (16 * pow((1 - currIter), 1) * 255);
		colour.blue = (16 * pow((1 - currIter), 4) + pow(currIter, 1) * 255);
		colour.green = (16 * pow((1 - currIter), 4) + pow(currIter, 1) * 255);
		break;
	case 3:
		colour.red = 255 / currIter;
		colour.blue = 255 / currIter;
		colour.green = 255 / currIter;
		break;
	}
	colour.alpha = 0xff;
	return SDL_MapRGBA(format, colour.red, colour.green, colour.blue, colour.alpha);
}
