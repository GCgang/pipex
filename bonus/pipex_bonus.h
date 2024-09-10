/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:48:43 by hyeoan            #+#    #+#             */
/*   Updated: 2023/03/05 12:16:38 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_argument
{
	int		in_file;
	int		out_file;
	int		here_doc;
	int		odd_fd[2];
	int		even_fd[2];
	int		cmd_cnt;
	int		tot_pipe_cnt;
	char	**path;
	char	***cmds;
}	t_arg;

typedef struct s_node
{
	int				fd;
	char			*back_up;
	struct s_node	*next;
}	t_file_node;

typedef struct s_list
{
	t_file_node	*tail;
	t_file_node	*before;
	t_file_node	*current;
	size_t		total_fd;
}	t_list;

/* main */
void	initialize(t_arg *pipex, int argc, char **argv, char **envp);
void	excute(t_arg *pipex, int argc, char **argv);
void	finalize(t_arg *pipex);
void	exit_ctl(t_arg *pipex, char *errmsg, int exit_flag);

/* initialize */
char	**get_path(t_arg *pipex, char **envp);
char	***get_cmds(t_arg *pipex, int argc, char **argv);
int		ft_strncmp(char *s1, char *s2, int n);

/* excute */
void	parent_process(t_arg *pipex, int idx);
void	child_process(t_arg *pipex, int idx, int argc, char **argv);
void	run_execve(t_arg *pipex, int idx);
char	*check_cmd(t_arg *pipex, int idx);
void	close_pipe(int *pipe);

/* free */
void	free_3d(char ***cmds, int alloc_space);
void	free_path(char **path);
void	free_cmds(char ***cmds);

/* init_file */
void	here_document(t_arg *pipex, char **argv);
void	init_infile(t_arg *pipex, int idx, char **argv);
void	init_outfile(t_arg *pipex, int idx, int argc, char **argv);

/* split */
char	**ft_split(char *str, char charset);
char	*put_word(char *str, char charset);
size_t	get_word_len(char *str, char charset);
size_t	ft_word_cnt(char *str, char charset);
void	*free_2d(char **str_arr);

/* strjoin */
size_t	ft_strlen(char *s);
char	*ft_strcat(char *dest, char *src);
char	*ft_strjoin(char *s1, char *s2);

/* get_next_line */
char	*get_next_line(int fd);
int		find_node(t_list *file_list, int fd);
int		add_node(t_list *file_list, int fd);
char	*read_file(t_list *file_list, char *buf);
char	*make_line(t_list *file_list);

/* get_next_line_utils */
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strchr(char *s, int c);
char	*gnl_strjoin(char *s1, char *s2);
void	remove_list(t_list *file_list);

/* putstr */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

#endif