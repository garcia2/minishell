/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:39:13 by jileroux          #+#    #+#             */
/*   Updated: 2023/09/14 17:04:59 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_args(char **lex)
{
	if (lex[1][0] != '0' && ft_atoi(lex[1]) == 0)
	{
		print_error("minishell: exit: ");
		print_error(lex[1]);
		print_error(": numeric argument required\n");
		return (2);
	}
	return (0);
}

int	check_digit(char **lex)
{
	if (lex[1][0] != '0' && ft_atoi(lex[1]) == 0)
	{
		print_error("minishell: exit: ");
		print_error(lex[1]);
		print_error(": numeric argument required\n");
		return (2);
	}
	return (print_error("minishell: exit: too many arguments\n"), 1);
}

int	exit_calcul(int err_code)
{
	if (err_code < 0)
	{
		while (err_code < 0)
			err_code += 256;
	}
	else if (err_code > 0)
	{
		while (err_code > 0)
			err_code -= 256;
		err_code += 256;
	}
	printf("err_code : %d\n", err_code);
	return (err_code);
}

int	exit_value(char **lex)
{
	int		err_code;

	err_code = ft_atoi(lex[1]);
	printf("atoi : %d\n", err_code);
	if (!lex[1])
		return (free(lex), 2);
	else if (lex[1] && lex[2])
	{
		err_code = check_digit(lex);
		return (err_code);
	}
	else if (lex[1])
	{
		err_code = check_args(lex);
		if (err_code == 2)
			return (err_code);
	}
	err_code = ft_atoi(lex[1]);
	err_code = exit_calcul(err_code);
	return (err_code);
}
