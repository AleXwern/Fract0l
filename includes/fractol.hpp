/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 13:12:21 by anystrom          #+#    #+#             */
/*   Updated: 2024/11/13 22:06:32 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <math.h>
# include <SDL3/SDL.h>
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
typedef struct	s_color
{
				uint8_t	red;
				uint8_t	blue;
				uint8_t	green;
				uint8_t alpha;
}				t_color;

struct			s_fractal
{
	uint16_t	iter;
	t_complex	max;
	t_complex	min;
	t_complex	factor;
	t_complex	c;
	t_complex	jul;
};

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
	SDL_Mutex		*mutex;
	uint8_t			threads;
	uint8_t			redefine;
	int				fractol;
	int				colourset;
	bool			fixjulia;
	s_fractal		fractal;
	uint32_t		currPixel;
	uint32_t		donePixel;
}					t_fractol;

class 				Fractol
{
public:
	Fractol(t_fractol *frc);
	
	void					redefine_fracal(t_fractol *frc);
	void					frc_draw(t_fractol *frc);
private:
	uint32_t				get_color(double currIter);

	s_fractal				fractal;
	int						(*fractolDef)(s_fractal*);
	uint8_t					id;
	uint32_t				pixel;
	int						&colourset;
	uint32_t				&currPixel;
	uint32_t				&donePixel;
	SDL_Mutex				*mutex;
	uint32_t				*surfacedata;
	const SDL_PixelFormatDetails	*format;
};



void				error_out(const char *msg);
void				fractol_main(t_fractol *frc);
void				help_window(t_fractol *frc);
void				set_default(t_fractol *frc);
void				setDefaultFractalValues(s_fractal *fractal);
void				thread_core(t_fractol *frc);

uint32_t			get_color(double currIter, int set, SDL_PixelFormat *format);
t_complex			set_complex(double rn, double in);

int					frc_tricorn(s_fractal *frc);
int					frc_mandelbrot(s_fractal *frc);
int					frc_bship(s_fractal *frc);
int					frc_julia(s_fractal *frc);

#endif
