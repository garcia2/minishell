/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:39:00 by nigarcia          #+#    #+#             */
/*   Updated: 2023/09/14 13:53:54 by jileroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_wrong_arg_error(char *arg)
{
	print_error("minishell: export : `");
	print_error(arg);
	print_error("': not a valid identifier\n");
	g_error = 1;
}
