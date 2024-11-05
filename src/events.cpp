/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:01:55 by AleXwern          #+#    #+#             */
/*   Updated: 2024/11/06 00:17:53 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.hpp"
#include "value.hpp"
#include <stdio.h>

t_complex	oldpos;

void			handle_keyboard(SDL_KeyboardEvent event, t_fractol *frc)
{
	int		direction;
	double	delta;
	
	if (event.state == SDL_PRESSED)
		return;
	
	#pragma GCC diagnostic push		// Disable GCC freaking out for not having every single key here
	#pragma GCC diagnostic ignored "-Wswitch"
	switch (event.keysym.scancode)
	{
	case SDL_SCANCODE_ESCAPE:
		error_out("This is fine");
		return;
	case SDL_SCANCODE_F:
		frc->fractol = (frc->fractol + 1) % 4;
		return;
	case SDL_SCANCODE_C:
		frc->colourset = (frc->colourset + 1) % 4;
		return;
	case SDL_SCANCODE_KP_PLUS:
		frc->iter = frc->iter+1 < 100 ? frc->iter+1 : 100;
		printf("Iteratiuns %d\n", frc->iter);
		return;
	case SDL_SCANCODE_KP_MINUS:
		frc->iter = frc->iter-1 > 1 ? frc->iter-1 : 1;
		printf("Iteratiuns %d\n", frc->iter);
		return;
	case SDL_SCANCODE_UP:
	case SDL_SCANCODE_DOWN:
		direction = (event.keysym.scancode - 81) * 2 - 1;
		delta = frc->max.imaginary - frc->min.imaginary;
		frc->min.imaginary += delta * 0.05 * -direction;
		frc->max.imaginary += delta * 0.05 * -direction;
		return;
	case SDL_SCANCODE_LEFT:
	case SDL_SCANCODE_RIGHT:
		direction = (event.keysym.scancode - 79) * 2 - 1;
		delta = frc->max.real - frc->min.real;
		frc->min.real += delta * 0.05 * direction;
		frc->max.real += delta * 0.05 * direction;
		return;
	case SDL_SCANCODE_R:
		set_default(frc);
		break;
	case SDL_SCANCODE_1:
	case SDL_SCANCODE_2:
	case SDL_SCANCODE_3:
	case SDL_SCANCODE_4:
	case SDL_SCANCODE_5:
	case SDL_SCANCODE_6:
	case SDL_SCANCODE_7:
	case SDL_SCANCODE_8:
	case SDL_SCANCODE_9:
	case SDL_SCANCODE_0:
		frc->iter = (event.keysym.scancode - 29) * 10;
		printf("Iteratiuns %d\n", frc->iter);
		break;
	default:
		return;
	}
	#pragma GCC diagnostic pop
}

void	handle_mouse(SDL_Event *event, t_fractol *frc)
{
	static bool			isPressed = false;
	t_complex			delta;

	isPressed = event->button.button == 1 ? true : false;
	if (isPressed)
	{
		delta = {(frc->max.real - frc->min.real) * ((oldpos.real - event->motion.x) / WINX),
				 (frc->max.imaginary - frc->min.imaginary) * ((oldpos.imaginary - event->motion.y) / WINY)};
		frc->min.real += delta.real;
		frc->max.real += delta.real;
		frc->min.imaginary -= delta.imaginary;
		frc->max.imaginary -= delta.imaginary;
	}
	oldpos = {static_cast<double>(event->motion.x), static_cast<double>(event->motion.y)};
}

void	handle_mousewheel(SDL_MouseWheelEvent *event, t_fractol *frc)
{
	double		zoom;
	t_complex	target;

	if (event->y > 0)
		zoom = 1.0 * 0.9;
	else
		zoom = 1.0 / 0.9;
	target = {1.00 * oldpos.real / (WINX / (frc->max.real - frc->min.real)) + frc->min.real,
			-1.0 * oldpos.imaginary / (WINY / (frc->max.imaginary - frc->min.imaginary)) + frc->max.imaginary};
	frc->min.real = ((frc->min.real - target.real) * zoom) + target.real;
	frc->min.imaginary = ((frc->min.imaginary - target.imaginary) * zoom) + target.imaginary;
	frc->max.real = ((frc->max.real - target.real) * zoom) + target.real;
	frc->max.imaginary = ((frc->max.imaginary - target.imaginary) * zoom) + target.imaginary;
}
