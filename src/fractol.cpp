/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 15:52:31 by anystrom          #+#    #+#             */
/*   Updated: 2024/11/10 00:42:12 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.hpp"
#include "value.hpp"
#include "events.hpp"
#include <stdio.h>

constexpr int threads = 8;

Fractol::Fractol(t_fractol *frc)
{
	id = 1 << SDL_GetThreadID(NULL);
	redefine_fracal(frc);
}

void	Fractol::redefine_fracal(t_fractol *frc)
{
	fractal.iter = frc->iter;
	fractal.max = frc->max;
	fractal.min = frc->min;
	fractal.jul = frc->jul;
	switch (frc->fractol)
	{
	case 0:
		fractolDef = frc_mandelbrot;
		break;
	case 1:
		fractolDef = frc_julia;
		break;
	case 2:
		fractolDef = frc_bship;
		break;
	default:
		fractolDef = frc_tricorn;
		break;
	}
}

t_complex		set_complex(double rn, double in)
{
	t_complex	cn;

	cn.real = rn;
	cn.imaginary = in;
	return (cn);
}

void		Fractol::set_pixel(t_fractol *frc, SDL_Surface *surface, int x, int y)
{
	uint32_t endCol = get_color(fractolDef(&fractal) / 50.0f, frc->colourset, surface->format);
	uint32_t *surfacedata = (uint32_t*)surface->pixels;
	surfacedata[WINX * y + x] = endCol;
}

void		Fractol::frc_draw(t_fractol *frc)
{
	int			x = 0;
	int			pixel;

	SDL_LockMutex(frc->mutex);
	pixel = frc->currPixel;
	frc->currPixel++;
	SDL_UnlockMutex(frc->mutex);
	if (pixel >= WINY)
	{
		redefine_fracal(frc);
		SDL_Delay(10);
		return;
	}
	fractal.factor = set_complex((fractal.max.real - fractal.min.real) / WINX,
			(fractal.max.imaginary - fractal.min.imaginary) / WINY);
	fractal.c.imaginary = fractal.max.imaginary - pixel * fractal.factor.imaginary;
	while (x < WINX)
	{
		fractal.c.real = fractal.min.real + x * fractal.factor.real;
		set_pixel(frc, frc->surface, x, pixel);
		x++;
	}
	SDL_LockMutex(frc->mutex);
	frc->donePixel++;
	SDL_UnlockMutex(frc->mutex);
}

static int		frc_draw_entry(void *data)
{
	t_fractol	*frc = static_cast<t_fractol*>(data);
	Fractol		fractol(frc);

	while (1)
	{
		fractol.frc_draw(frc);
	}
	return (0);
}

void			thread_core(t_fractol *frc)
{
	SDL_Thread*	thread[threads];
	int			i;

	i = 0;
	while (i < threads)
	{
		thread[i] = SDL_CreateThread(frc_draw_entry, "Render Thread", frc);
		if (thread[i] == NULL)
			error_out(T_ERROR);
		i++;
	}
}

void			fractol_main(t_fractol *frc)
{
	SDL_mutex	*mutex = SDL_CreateMutex();
	FractolEventHandler	handler(mutex, frc);

	set_default(frc);
	frc->mutex = mutex;
	//SDL_CreateThread(event_thread, "Events", &handler);
	thread_core(frc);
	while (1)
	{
		handler.eventThreadMain();
		SDL_LockMutex(frc->mutex);
		if (frc->donePixel >= WINY)
		{
			SDL_UpdateWindowSurface(frc->window);
			frc->currPixel = 0;
			frc->donePixel = 0;
		}
		SDL_UnlockMutex(frc->mutex);
		//thread_core(frc);
	}
}
