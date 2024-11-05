/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 13:12:21 by anystrom          #+#    #+#             */
/*   Updated: 2024/11/05 22:59:06 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <math.h>
# include <SDL.h>
# include <fcntl.h>
# include <stdint.h>

/*
** Struct for complex number presentation.
** r is real part.
** i is imaginary part.
*/
typedef struct		s_complex
{
	double			real;
	double			imaginary;
}					t_complex;

/*
** Colors!!
** int set	= what the current set is
** int 1-4  = color
*/
typedef struct		s_color
{
	unsigned int	set;
	union
	{
		uint32_t	colour;
		struct
		{
			uint8_t	red;
			uint8_t	blue;
			uint8_t	green;
			uint8_t alpha;
		};
		
	};
}					t_color;

/*
** General toolbox for handling information.
** void *mlx	= generic mlx pointer.
** void *win	= generil mlx window pointer.
** int threads	= number of threads used to render image. Default 10.
** int start	= start Y pos for thread.
** int end		= end Y pos for thread.
** t_image img	= image data.
** t_color color= color data.
** int fractol	= id of fractol type.
** 0 Mandelbrot
** 1 Julia
** 2 Bship
** double zoom	= is exponent for zoom modifer.
** int iter		= how many times value is iterated. Default 30.
** int ishelp	= 0 or -1 if help window is shown.
** int fixjulia	= 0 or -1 if julia follows mouse.
** t_complex max = maximum complex number value.
** t_complex min = minimum complex number value.
*/
typedef struct		s_fractol
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	uint8_t			threads;
	int				start;
	t_color			color;
	int				fractol;
	double			zoom;
	int				iter;
	int				colourset;
	int				ishelp;
	int				fixjulia;
	t_complex		max;
	t_complex		min;
	t_complex		factor;
	t_complex		c;
	t_complex		jul;
}					t_fractol;

void				error_out(const char *msg);
void				fractol_main(t_fractol *frc);
void				help_window(t_fractol *frc);
void				set_default(t_fractol *frc);
void				thread_core(t_fractol *frc);

int					define_set(t_fractol *frc);
int					julia_move(int x, int y, t_fractol *frc);
int					key_main(int key, t_fractol *frc);
int					mouse_main(int key, int x, int y, t_fractol *frc);

uint32_t			get_color(double currIter, int set, SDL_PixelFormat *format);
t_complex			set_complex(double rn, double in);

void				handle_keyboard(SDL_KeyboardEvent event, t_fractol *frc);
void				handle_mouse(SDL_MouseButtonEvent event, SDL_MouseMotionEvent position, t_fractol *frc);

#endif
