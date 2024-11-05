/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 15:52:31 by anystrom          #+#    #+#             */
/*   Updated: 2024/11/05 23:59:05 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.hpp"
# include "value.hpp"
#include <stdio.h>

constexpr int threads = 12;

/*
** Creates and sets DOUBLE values into complex number presentation.
*/

t_complex		set_complex(double rn, double in)
{
	t_complex	cn;

	cn.real = rn;
	cn.imaginary = in;
	return (cn);
}

/*
** I determines a current XY position since DATA is 1D array.
** Gets color palette based on iteration and sets the palette into pixel.
*/

static void		set_pixel(t_fractol *frc, SDL_Surface *surface, int x, int y)
{
	uint32_t endCol = get_color(define_set(frc) / 50.0f, frc->colourset, surface->format);
	uint32_t *surfacedata = (uint32_t*)surface->pixels;
	surfacedata[WINX * y + x] = endCol;
}

/*
** Bread and butter fratal calculation.
** First sets a set FACTOR which is then used to calculate
** C with every single pixel that is analyzed (aka all 1M in 1000x1000)
*/

static void		frc_draw(t_fractol *frc)
{
	int			x;

	frc->factor = set_complex((frc->max.real - frc->min.real) / WINX,
			(frc->max.imaginary - frc->min.imaginary) / WINY);
	while (frc->start < WINY)
	{
		x = 0;
		frc->c.imaginary = frc->max.imaginary - frc->start * frc->factor.imaginary;
		while (x < WINX)
		{
			frc->c.real = frc->min.real + x * frc->factor.real;
			set_pixel(frc, frc->surface, x, frc->start);
			x++;
		}
		frc->start += threads;
	}
}

static int		frc_draw_entry(void *frc)
{
	frc_draw(static_cast<t_fractol*>(frc));
	return (0);
}

/*
** Heart of the system.
** PTHREAD is a bonus.
** makes X amount of threads and copies of FRC, set's an area they are
** responsible for.
** THREAD and FRAC are malloced and then freed after everything is done.
** Malloc was the easiest way of doing this since thread amount was
** to be made modifiedable.
*/
void			thread_core(t_fractol *frc)
{
	SDL_Thread*	thread[threads];
	t_fractol	frac[threads];
	int			i;

	i = 0;
	while (i < threads)
	{
		frac[i] = *frc;
		frac[i].start = i;
		thread[i] = SDL_CreateThread(frc_draw_entry, "Render Thread", (void*)&frac[i]);
		if (thread[i] == NULL)
			error_out(T_ERROR);
		i++;
	}
	while (i-- > 0)
		SDL_WaitThread(thread[i], NULL);
	SDL_UpdateWindowSurface(frc->window);
	//help_window(frc);
}

/*
** Readies input methods, gets and sets the image trough thread_core and
** then shows the image in window.
*/

void			fractol_main(t_fractol *frc)
{
	SDL_Event	events;

	set_default(frc);
	//mlx_key_hook(frc->win, key_main, frc);
	//mlx_hook(frc->win, 6, 0, julia_move, frc);
	//mlx_mouse_hook(frc->win, mouse_main, frc);
	while (1)
	{
		if (SDL_WaitEvent(&events))
		{
			switch (events.type)
			{
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				handle_keyboard(events.key, frc);
				break;
			case SDL_MOUSEMOTION:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				handle_mouse(&events, frc);
				break;
			case SDL_MOUSEWHEEL:
				handle_mousewheel(&events.wheel, frc);
				break;
			default:
				break;
			}
		}
		thread_core(frc);
	}
}
