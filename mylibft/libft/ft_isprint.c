/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:39:22 by skimura           #+#    #+#             */
/*   Updated: 2025/05/05 13:15:26 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (' ' <= c && c <= '~');
}

// #include <stdio.h>
// #include <ctype.h>

// int main()
// {
// printf("%d\n", ft_isprint('1'));
// printf("%d\n", isprint('1'));
// printf("%d\n", ft_isprint(1));
// printf("%d\n", isprint(1));
// return 0;
// }
