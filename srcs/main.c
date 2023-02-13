/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:00:04 by nigarcia          #+#    #+#             */
/*   Updated: 2023/02/12 16:57:49 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*result;
	char	**lex;

	(void) lex;
	result = readline("minishell: ");
	lexer(result);
	printf("%s\n", getenv("PATH"));
}