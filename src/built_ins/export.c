/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:13:11 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/05/24 17:50:02 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_export_function_only_once(char **env)
{
	int			i;
	const char	*key;
	const char	*value;

	i = 0;
	while (env[i])
	{
		key = env[i];
		value = ft_strchr(env[i], '=');
		if (value)
		{
			printf("declare -x %.*s=\"%s\"\n", (int)(value - key), key, value
				+ 1);
		}
		i++;
	}
}

static char	**get_key_value_pair(char *arg)
{
	char	**temp;
	char	*position;

	position = ft_strchr(arg, '=');
	temp = malloc(sizeof * temp * (2 + 1));
	temp[0] = ft_substr(arg, 0, position - arg);
	temp[1] = ft_substr(position, 1, ft_strlen(position));
	temp[2] = NULL;
	return (temp);
}

int	call_no_arguments(char **args, int i, int result)
{
	if (!args[i])
	{
		print_export_function_only_once(g_data.env);
		return (result);
	}
	return (result);
}

int	ft_export_built_in(t_data *data, char **args)
{
	int		i;
	char	**temp;
	int		result;

	result = EXIT_SUCCESS;
	i = 1;
	result = call_no_arguments(args, i, result);
	while (args[i])
	{
		if (!check_for_the_env_key(args[i]))
		{
			error_msg_commad(COLOR_RED "export:", args[i],
				"not a valid identifier", false);
			result = (EXIT_FAILURE);
		}
		else if (ft_strchr(args[i], '=') != NULL)
		{
			temp = get_key_value_pair(args[i]);
			create_the_new_env_var(data, temp[0], temp[1]);
			free_str_tab(temp);
		}
		i++;
	}
	return (result);
}
