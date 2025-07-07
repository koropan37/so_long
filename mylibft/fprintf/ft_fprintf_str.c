/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:25:32 by skimura           #+#    #+#             */
/*   Updated: 2025/07/05 19:45:49 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_fprintf_put_c(int fd, char c)
{
	ssize_t	bytes;

	bytes = write(fd, &c, 1);
	if (bytes == -1)
		return (-1);
	return ((int)bytes);
}

int	ft_fprintf_put_s(int fd, char *s)
{
	ssize_t	bytes;

	if (!s)
		bytes = write(fd, "(null)", 6);
	else
		bytes = write(fd, s, ft_strlen(s));
	if (bytes == -1)
		return (-1);
	return ((int)bytes);
}
