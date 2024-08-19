/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:07:19 by rgiambon          #+#    #+#             */
/*   Updated: 2024/08/15 11:25:11 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include "../libft/libft.h"

void	parent_process(char *cmd2, int file_fd, int *pipe_fds, char **env);
void	child_process(char *cmd1, int file_fd, int *pipe_fds, char **env);
void	open_and_check(int argc, char *argv[], int *fd1, int *fd2);
void	execution(char *cmd, char **env);
char	**create_cmd_tab(char *cmd);
char	*path_finder(char *cmd, char **env);
char	*find_path_string(char **env);
char	*path_checker(char **all_path, char *cmd);
void	free_all(char **tab);

#endif
