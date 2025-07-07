/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:46:31 by skimura           #+#    #+#             */
/*   Updated: 2025/07/05 19:47:09 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef DIGITS_10
#  define DIGITS_10 "0123456789"
# endif

# ifndef DIGITS_16
#  define DIGITS_16 "0123456789abcdef"
# endif

# ifndef DIGITS_16X
#  define DIGITS_16X "0123456789ABCDEF"
# endif

int	ft_fprintf(int fd, const char *format, ...);
int	ft_fprintf_put_c(int fd, char c);
int	ft_fprintf_put_s(int fd, char *s);
int	ft_fprintf_put_u_hex(int fd, unsigned long long n, char spec);
int	ft_fprintf_put_p(int fd, void *p);
int	ft_fprintf_put_d_i(int fd, long long n);
int	ft_fprintf_unsigned_nbr_base(int fd, unsigned long long n, int base,
		const char *digits);

#endif
