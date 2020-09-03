/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdebbie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 03:27:02 by bdebbie           #+#    #+#             */
/*   Updated: 2019/09/23 21:32:25 by bdebbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_list(t_lst **list, char **line, int fill_ans)
{
	char	*buff;
	size_t	index;

	index = 0;
	if ((*list)->str != NULL)
		while ((*list)->str[index] != '\n' && (*list)->str[index] != '\0')
			index++;
	if (((*list)->str != NULL && (*list)->str[index] == '\n') || fill_ans == 0)
	{
		*line = (char*)malloc(sizeof(char) * (index + 1));
		index = -1;
		while ((*list)->str[++index] != '\n' && (*list)->str[index] != '\0')
			(*line)[index] = (*list)->str[index];
		(*line)[index] = '\0';
		buff = (*list)->str;
		if ((*list)->str[index] != '\0')
			index++;
		(*list)->str = ft_strdup(&(buff[index]));
		free(buff);
		return (1);
	}
	else
		return (0);
}

static int		fill_list(t_lst **fd_list, int fd)
{
	char	buff[BUFF_SIZE + 1];
	int		answer;
	char	*tmp;

	answer = read(fd, buff, BUFF_SIZE);
	if (answer == 0)
		return (0);
	if (answer == -1)
		return (-1);
	buff[answer] = '\0';
	if ((*fd_list)->str == NULL)
	{
		(*fd_list)->str = (char*)malloc(sizeof(char) * answer);
		while (answer >= 0)
			(*fd_list)->str[answer--] = '\0';
	}
	tmp = (*fd_list)->str;
	(*fd_list)->str = ft_strjoin(tmp, buff);
	free(tmp);
	tmp = NULL;
	return (1);
}

static t_lst	*find_fd(t_lst **fd_list, int fd)
{
	t_lst *local_list;

	if (*fd_list == NULL)
	{
		if (!(*fd_list = (t_lst*)malloc(sizeof(t_lst))))
			return (NULL);
		(*fd_list)->fd = fd;
		(*fd_list)->next = NULL;
		(*fd_list)->str = NULL;
		return (*fd_list);
	}
	local_list = *fd_list;
	while (local_list->next != NULL)
		if (local_list->fd == fd)
			return (local_list);
		else
			local_list = local_list->next;
	if (local_list->fd == fd)
		return (local_list);
	if (!(local_list->next = (t_lst*)malloc(sizeof(t_lst))))
		return (NULL);
	local_list->next->fd = fd;
	local_list->next->str = NULL;
	local_list->next->next = NULL;
	return (local_list->next);
}

static void		clean_last(t_lst **fd_list, t_lst **buff)
{
	char	*to_clean_str;
	t_lst	*local_list;

	to_clean_str = (*buff)->str;
	free(to_clean_str);
	if ((*fd_list)->fd == (*buff)->fd)
	{
		local_list = *fd_list;
		*fd_list = (*fd_list)->next;
		free(local_list);
		local_list = NULL;
		return ;
	}
	local_list = *fd_list;
	while (local_list->next->fd != (*buff)->fd)
		local_list = local_list->next;
	local_list->next = (*buff)->next;
	free(*buff);
}

int				get_next_line(const int fd, char **line)
{
	static t_lst	*fd_list;
	t_lst			*buff;
	int				fill_answer;
	int				check_answer;

	if (!line || fd < 0 || fd > 10240 || BUFF_SIZE <= 0 ||
		read(fd, NULL, 0) == -1 || !(buff = find_fd(&fd_list, fd)))
		return (-1);
	while (!(check_answer = check_list(&buff, line, 1)))
	{
		if ((fill_answer = fill_list(&buff, fd)) == -1)
			return (-1);
		if (fill_answer == 0 && buff->str == NULL)
			return (0);
		if (fill_answer == 0 && buff->str != NULL)
		{
			check_list(&buff, line, 0);
			break ;
		}
	}
	if (buff->str[0] == '\0')
		clean_last(&fd_list, &buff);
	return (1);
}
