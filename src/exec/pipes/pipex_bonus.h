/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:39:02 by mthibaul          #+#    #+#             */
/*   Updated: 2023/01/16 18:12:57 by mthibaul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		cmd_nb;
	int		pipe_nb;
	int		index;
	int		here_doc;
	int		*pipe;
	char	*cmd;
	char	**cmd_args;
	char	**cmd_path;
	pid_t	pid;
}	t_pipex;

void	free_pipex(t_pipex *p);
void	do_pipes(t_pipex *pipex);
void	error(char *err);
void	close_pipes(t_pipex *pipex);
void	child(t_pipex pipex, char **av, char **envp);
void	get_infile(char **av, t_pipex *pipex);
void	get_outfile(char *file, t_pipex *pipex);
void	here_doc(char *av, t_pipex *pipex);
int		err_msg(char *err);
int		check_arg(char *arg, t_pipex *pipex);
char	*find_cmd(char **envp, char *cmd_args);
char	**cmd_path(char **envp);
char	**ft_freesplit(char **dst);

#endif
