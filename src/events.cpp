/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:01:55 by AleXwern          #+#    #+#             */
/*   Updated: 2024/11/11 19:35:01 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.hpp"
#include "fractol.hpp"
#include "value.hpp"
#include <stdio.h>

int			FractolEventHandler::eventThreadMain(void)
{
	int ret = SDL_WaitEventTimeout(&events, 10);
	if (ret)
	{
		switch (events.type)
		{
		case SDL_EVENT_KEY_DOWN:
		case SDL_EVENT_KEY_UP:
			handle_keyboard(events.key, evFrc);
			break;
		case SDL_EVENT_MOUSE_MOTION:
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
		case SDL_EVENT_MOUSE_BUTTON_UP:
			handle_mouse(&events, evFrc);
			break;
		case SDL_EVENT_MOUSE_WHEEL:
			handle_mousewheel(&events.wheel, evFrc);
			break;
		case SDL_EVENT_QUIT:
			error_out("This is fine");
			break;
		default:
			break;
		}
	}
	return 1;
}

void		FractolEventHandler::handle_keyboard(SDL_KeyboardEvent event, t_fractol *frc)
{
	int		direction;
	double	delta;
	
	if (event.down)
		return;
	
	#pragma GCC diagnostic push		// Disable GCC freaking out for not having every single key here
	#pragma GCC diagnostic ignored "-Wswitch"
	switch (event.scancode)
	{
	case SDL_SCANCODE_ESCAPE:
		error_out("This is fine");
		break;
	case SDL_SCANCODE_F:
		frc->fractol = (frc->fractol + 1) % 4;
		break;
	case SDL_SCANCODE_C:
		frc->colourset = (frc->colourset + 1) % 4;
		break;
	case SDL_SCANCODE_KP_PLUS:
		frc->fractal.iter++;
		printf("Iterations %d\n", frc->fractal.iter);
		break;
	case SDL_SCANCODE_KP_MINUS:
		frc->fractal.iter--;
		printf("Iterations %d\n", frc->fractal.iter);
		break;
	case SDL_SCANCODE_UP:
	case SDL_SCANCODE_DOWN:
		direction = (event.scancode - 81) * 2 - 1;
		delta = frc->fractal.max.imaginary - frc->fractal.min.imaginary;
		frc->fractal.min.imaginary += delta * 0.05 * -direction;
		frc->fractal.max.imaginary += delta * 0.05 * -direction;
		break;
	case SDL_SCANCODE_LEFT:
	case SDL_SCANCODE_RIGHT:
		direction = (event.scancode - 79) * 2 - 1;
		delta = frc->fractal.max.real - frc->fractal.min.real;
		frc->fractal.min.real += delta * 0.05 * direction;
		frc->fractal.max.real += delta * 0.05 * direction;
		break;
	case SDL_SCANCODE_R:
		set_default(frc);
		break;
	case SDL_SCANCODE_E:
		frc->fractal.iter = 0xffff;
		printf("Iterations %d\n", frc->fractal.iter);
		break;
	case SDL_SCANCODE_J:
		frc->fixjulia = frc->fixjulia ? false : true;
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
		frc->fractal.iter = (event.scancode - 29) * 10;
		printf("Iteratiuns %d\n", frc->fractal.iter);
		break;
	default:
		break;
	}
	#pragma GCC diagnostic pop
}

void	FractolEventHandler::handle_mouse(SDL_Event *event, t_fractol *frc)
{
	static bool			isPressed = false;
	t_complex			delta;

	isPressed = event->button.button == 1 ? true : false;
	if (isPressed)
	{
		delta = {(frc->fractal.max.real - frc->fractal.min.real) * ((oldpos.real - event->motion.x) / WINX),
				 (frc->fractal.max.imaginary - frc->fractal.min.imaginary) * ((oldpos.imaginary - event->motion.y) / WINY)};
		frc->fractal.min.real += delta.real;
		frc->fractal.max.real += delta.real;
		frc->fractal.min.imaginary -= delta.imaginary;
		frc->fractal.max.imaginary -= delta.imaginary;
	}
	if (frc->fixjulia)
	{
		frc->fractal.jul = set_complex(4 * ((double)event->motion.x / WINX - 0.5),
								4 * ((double)(WINY - event->motion.x) / WINY - 0.5));
	}
	oldpos = {static_cast<double>(event->motion.x), static_cast<double>(event->motion.y)};
}

void	FractolEventHandler::handle_mousewheel(SDL_MouseWheelEvent *event, t_fractol *frc)
{
	double		zoom;
	t_complex	target;

	if (event->y > 0)
		zoom = 1.0 * 0.9;
	else
		zoom = 1.0 / 0.9;
	target = {1.00 * oldpos.real / (WINX / (frc->fractal.max.real - frc->fractal.min.real)) + frc->fractal.min.real,
			-1.0 * oldpos.imaginary / (WINY / (frc->fractal.max.imaginary - frc->fractal.min.imaginary)) + frc->fractal.max.imaginary};
	frc->fractal.min.real = ((frc->fractal.min.real - target.real) * zoom) + target.real;
	frc->fractal.min.imaginary = ((frc->fractal.min.imaginary - target.imaginary) * zoom) + target.imaginary;
	frc->fractal.max.real = ((frc->fractal.max.real - target.real) * zoom) + target.real;
	frc->fractal.max.imaginary = ((frc->fractal.max.imaginary - target.imaginary) * zoom) + target.imaginary;
}
