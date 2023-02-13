/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:58:15 by nigarcia          #+#    #+#             */
/*   Updated: 2022/05/24 14:43:16 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_next(char type, va_list ptr)
{
	if (type == 's')
		return (ft_printf_s((char *) va_arg(ptr, char *)));
	else if (type == 'c')
		return (ft_printf_c((char) va_arg(ptr, int)));
	else if (type == 'p')
		return (ft_printf_p((unsigned long long int)
				va_arg(ptr, unsigned long long int)));
	else if (type == 'x' || type == 'X')
		return (ft_printf_x((int) va_arg(ptr, int), type));
	else if (type == 'd' || type == 'i')
		return (ft_printf_di((int) va_arg(ptr, int)));
	else if (type == 'u')
		return (ft_printf_u((unsigned int) va_arg(ptr, unsigned int)));
	else if (type == '%')
		return (ft_printf_c('%'));
	return (0);
}

static int	is_good_type(char c)
{
	char	*types;

	types = "csdiupxX%";
	while (*types)
	{
		if (*types == c)
			return (1);
		types++;
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		size_write;
	va_list	ptr;

	size_write = 0;
	i = 0;
	va_start(ptr, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] && is_good_type(format[i + 1]))
		{
			size_write += print_next(format[i + 1], ptr);
			i++;
		}
		else
		{
			ft_putchar_fd(format[i], 1);
			size_write++;
		}
		i++;
	}
	va_end(ptr);
	return (size_write);
}
