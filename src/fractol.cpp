/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 15:52:31 by anystrom          #+#    #+#             */
/*   Updated: 2024/11/13 22:03:32 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.hpp"
#include "value.hpp"
#include "events.hpp"
#include <stdio.h>

constexpr int threads = 8;

Fractol::Fractol(t_fractol *frc) :
	colourset(frc->colourset), currPixel(frc->currPixel), donePixel(frc->donePixel)
{
	mutex = frc->mutex;
	surfacedata = (uint32_t*)frc->surface->pixels;
	format = SDL_GetPixelFormatDetails(frc->surface->format);
	id = SDL_GetCurrentThreadID();
	redefine_fracal(frc);
}

void	Fractol::redefine_fracal(t_fractol *frc)
{
	fractal = frc->fractal;
	fractal.factor = set_complex((fractal.max.real - fractal.min.real) / WINX,
			(fractal.max.imaginary - fractal.min.imaginary) / WINY);
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

void		Fractol::frc_draw(t_fractol *frc)
{
	SDL_LockMutex(mutex);
	pixel = currPixel;
	currPixel++;
	SDL_UnlockMutex(mutex);
	if (pixel >= WINY)
	{
		redefine_fracal(frc);
		return;
	}
	fractal.c.imaginary = fractal.max.imaginary - pixel * fractal.factor.imaginary;
	for (uint32_t x = 0; x < WINX; x++)
	{
		fractal.c.real = fractal.min.real + x * fractal.factor.real;
		surfacedata[WINX * pixel + x] = get_color(fractolDef(&fractal) / static_cast<double>(fractal.iter));
	}
	SDL_LockMutex(mutex);
	donePixel++;
	SDL_UnlockMutex(mutex);
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
	SDL_Thread*	thread;

	for (int i = 0; i < threads; i++)
	{
		thread = SDL_CreateThread(frc_draw_entry, "Render Thread", frc);
		if (thread == NULL)
			error_out(T_ERROR);
		SDL_DetachThread(thread);
		i++;
	}
}

void			fractol_main(t_fractol *frc)
{
	SDL_Mutex	*mutex = SDL_CreateMutex();
	SDL_Mutex	*eventLock = SDL_CreateMutex();
	s_fractal	fractal;
	FractolEventHandler	handler(eventLock, frc, &fractal);

	set_default(frc);
	setDefaultFractalValues(&fractal);
	frc->mutex = mutex;
	thread_core(frc);
	while (1)
	{
		handler.eventThreadMain();
		SDL_LockMutex(mutex);
		if (frc->donePixel >= WINY)
		{
			SDL_UpdateWindowSurface(frc->window);
			SDL_LockMutex(eventLock);
			frc->fractal = fractal;
			SDL_UnlockMutex(eventLock);
			frc->currPixel = 0;
			frc->donePixel = 0;
		}
		SDL_UnlockMutex(mutex);
	}
}
