/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_list_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:08:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/05/25 11:36:41 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

char    *ft_strndup(char *s, int end);

char    *find_name(char *envp)
{
        int i;

        i = 0;
        while (envp[i])
        {
                if (envp[i] == '=')
                        return (ft_strndup(envp, i));
                i++;
        }
        return (NULL);
}

char    *find_value(char *envp)
{
        while (*envp)
        {
                if (*envp == '=')
                {
                        envp++;
                        if (*envp)
                                return (ft_strndup(envp, (int) ft_strlen(envp)));
                        else
                                return (NULL);
                }
                envp++;
        }
        return (NULL);
}

char    *ft_strndup(char *s, int end)
{
        char                    *return_string;
        int     i;

        return_string = (char *) malloc((end + 1) * sizeof(char));
        if (!return_string)
                return (NULL);
        i = 0;
        while (s[i] != '\0' && i < end)
        {
                return_string[i] = s[i];
                i++;
        }
        return_string[i] = '\0';
        return (return_string);
}