/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkingsbl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 15:31:53 by pkingsbl          #+#    #+#             */
/*   Updated: 2020/07/22 14:57:41 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "libft.h"

# define NONDEC spec.type == 'x' || spec.type == 'X' || spec. type == 'o'
# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define BWN   "\x1B[37m"
# define RESET "\x1B[0m"

typedef union	u_ptr
{
	void			*ptr;
	unsigned long	mem;
}				t_memory_ptr;

typedef struct	s_specif
{
	int			sharp;
	int			zero;
	int			minus;
	int			plus;
	int			space;
	int			l;
	int			h;
	long long	wide;
	long long	precision;
	char		*res;
	size_t		len;

	char		size[3];

	char		type;
}				t_specif;

void			type(char *point);
void			ft_spec_new(t_specif *spec);
char			*ft_for_string(va_list ap, t_specif spec);
int				ft_for_char(va_list ap, t_specif *spec);
char			*ft_type_to_str(va_list ap, t_specif spec);
char			*ft_for_decimal(__int128_t dec, t_specif spec, int base);
char			*ft_for_unsigned(long long dec, t_specif spec);
char			*ft_for_haxedecimal(__int128_t llhex, t_specif spec);
char			*ft_for_haxedecimal_up(__int128_t arg, t_specif spec);
char			*ft_for_octal(__int128_t llhex, t_specif spec);
char			*ft_for_percent(t_specif spec);
char			*ft_strleft(char **str, int wide, char c);
char			*ft_strright(char **str, int wide, char c);
char			*ft_itoa_base(__int128_t n, int base);
char			*ft_for_p(va_list ap, t_specif spec);
char			*ft_for_ld(va_list ap, t_specif spec);
char			*print_float(long double n, long long afterdot);
const char		*search_flags(const char *str, t_specif *spec);
const char		*search_wide(const char *str, t_specif *spec, va_list ap);
const char		*search_precision(const char *str, t_specif *spec, va_list ap);
const char		*search_size(const char *str, t_specif *spec);
const char		*search_type(const char *str, t_specif *spec);
const char		*ft_search_spec(const char *format, t_specif *spec, va_list ap);
int				ft_solve_type(va_list ap, int fd, t_specif spec);
void			str_wide(char **str, t_specif spec);
void			str_flags(char **str, char *s1);
void			set_colour(const char *str, int fd);
int				print_not_percent(const char *str, int *i, int fd);

#endif
