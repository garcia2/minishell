/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 20:19:39 by nigarcia          #+#    #+#             */
/*   Updated: 2022/05/24 11:36:20 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_di(int n)
{
	char	*str_n;
	int		len;

	str_n = ft_itoa(n);
	ft_putstr_fd(str_n, 1);
	len = ft_strlen(str_n);
	free(str_n);
	return (len);
}
