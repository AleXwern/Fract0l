/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:22:56 by AleXwern          #+#    #+#             */
/*   Updated: 2024/11/13 21:43:17 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <SDL3/SDL.h>

#include "fractol.hpp"

class	FractolEventHandler
{
public:
	FractolEventHandler(SDL_Mutex *mutex, t_fractol *frc, s_fractal *fractal) :
		evMutex(mutex), evFrc(frc), evFractal(fractal)
	{
	}

	int	eventThreadMain(void);

private:

	void	handle_keyboard(SDL_KeyboardEvent event);
	void	handle_mouse(SDL_Event *event);
	void	handle_mousewheel(SDL_MouseWheelEvent *event);

	SDL_Event	events;
	SDL_Mutex	*evMutex;
	t_fractol	*evFrc;
	t_complex	oldpos;
	s_fractal	*evFractal;
};
