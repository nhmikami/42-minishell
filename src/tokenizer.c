/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:14:10 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/11 15:56:42 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	identify_keyword(char *keyword)
// {
	
// }

// t_token	**tokenizer(char *input)
// {
// 	int		i;
// 	int		len;
// 	char	**arr;
// 	t_token	**token;
// 	int		identifier;

// 	i = 0;
// 	arr = ft_split(input, " ");
// 	len = ft_arrlen(arr);
// 	token = maloc((len + 1) * sizeof(token));
// 	while (arr[i])
// 	{
// 		identifier = identify_keyword(arr[i]);
// 		if (identifier)
// 		{
// 			token[i]->keyword = arr[i];
// 			token[i]->identifier = identifier;
// 		}
// 		i++;
// 	}
// 	return (token);
// }