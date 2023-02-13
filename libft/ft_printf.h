/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:13:49 by nigarcia          #+#    #+#             */
/*   Updated: 2022/06/03 16:02:24 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"
# include <limits.h>

int	ft_printf(const char *format, ...);
int	ft_printf_s(char *s);
int	ft_printf_c(char c);
int	ft_printf_di(int n);
int	ft_printf_u(unsigned int n);
int	ft_printf_p(unsigned long long int ptr);
int	ft_printf_x(int n, char type);

#endif
