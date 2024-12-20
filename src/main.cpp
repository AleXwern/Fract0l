/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 13:18:02 by anystrom          #+#    #+#             */
/*   Updated: 2024/11/13 22:03:16 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.hpp"
#include "value.hpp"

#include <stdio.h>
#include <string.h>
#include <SDL3/SDL_main.h>

/*
** Initialize image into t_image struct and pull needed data out of it.
** Different t_image parts are (shortly) explained in fractol.h file.
** FRC is given in case something goes terribly wrong.
*/

static void	init_image(t_fractol *frc)
{
	if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO))
		error_out("Init error!");
	if (!(frc->window = SDL_CreateWindow("Fract01s", WINX, WINY, 0)))
		error_out("Window creation error!");
	if (!(frc->renderer = SDL_CreateRenderer(frc->window, NULL)))
		if (!(frc->renderer = SDL_GetRenderer(frc->window)))
			error_out("Renderer creation error!");
	if (!(frc->surface = SDL_GetWindowSurface(frc->window)))
		error_out("Could not get window surface!");
	if (!(frc->texture = SDL_CreateTextureFromSurface(frc->renderer, frc->surface)))
		error_out("Could not make ui texture!");
	SDL_ShowWindow(frc->window);
}

void			setDefaultFractalValues(s_fractal *fractal)
{
	fractal->min = set_complex(-2.0, -2.0);
	fractal->max.real = 2.0;
	fractal->max.imaginary = fractal->min.imaginary +
			(fractal->max.real - fractal->min.real) *
			static_cast<double>(WINY) / static_cast<double>(WINX);
	fractal->jul = set_complex(-0.4, 0.6);
	fractal->iter = 30;
}

void			set_default(t_fractol *frc)
{
	frc->threads = 100;
	setDefaultFractalValues(&frc->fractal);
	frc->colourset = 0;
	frc->currPixel = 0;
	frc->donePixel = 0;
	frc->redefine = 0xff;
	frc->fractol = 0;
}

/*
** Program ALWAYS exits trough this function.
** In no case whatsoever should it exit trough main.
** MSG is feedback message and FRC is toolbox that need to be handled.
*/

void			error_out(const char *msg)
{
	printf("%s\n", msg);
	exit(0);
}

/*
** Function main. Sets up some core features that are never modified in future.
** fractol_main(frc) puts program in set loop
** ft_putendl(OOPS) should never run.
** ac != 2 exits program with USAGE and incorrect 1 with B_ARG.
*/

int main(int argc, char *argv[])
{
	t_fractol	frc;

	if (argv && argc) {}
	init_image(&frc);
	fractol_main(&frc);
	printf(OOPS);
	return (0);
}
