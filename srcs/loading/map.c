#include "../../includes/loading.h"

char	*create_wrapper(size_t row_nb)
{
	char	*wrapper;
	size_t	i;

	wrapper = malloc(sizeof(char) * (row_nb + 1));
	if (!wrapper)
		return (NULL);
	i = 0;
	while (i < row_nb)
	{
		wrapper[i] = ' ';
		++i;
	}
	wrapper[i] = '\0';
	return (wrapper);
}

void	add_wrappers(t_list **lst, size_t row_nb)
{
	char *wrapper1;
	char *wrapper2;
	t_list	*wrap1;
	t_list	*wrap2;
    
	// tester lst a null
	wrapper1 = create_wrapper(row_nb);
	wrapper2 = create_wrapper(row_nb);
	wrap1 = ft_lstnew(wrapper1);
	wrap2 = ft_lstnew(wrapper2);
	ft_lstadd_front(lst, wrap1);
	ft_lstadd_back(lst, wrap2);
}

t_list *load_line(t_list **lst, char *line, size_t *row_nb)
{
    size_t  size_line;
	char	*line_ok;
	t_list	*elem;

	size_line = ft_strlen(line);
	line_ok = malloc(sizeof(char) * (size_line + 2));
	if (!line_ok)
		return (NULL);
	line_ok[0] = ' ';
	ft_strlcpy(line_ok + 1, line, size_line + 1);
	line_ok[size_line] = ' ';
	size_line = ft_strlen(line_ok);
	if (size_line > *row_nb)
		*row_nb = size_line;
	elem = ft_lstnew(line_ok);
	if (elem)
		ft_lstadd_back(lst, elem);
	return (*lst);
}

t_list	*loading_map(int map_fd, size_t *row_nb)
{
	char	*line;
	t_list	*lst;
	t_list	*tempo_lst;
	int i;
	char *tempo_line;

	i = 0;
	lst = NULL;
	line = trim_backspace(map_fd);
	while (line)
	{
		if (i)
		{
			free(line);
			line = get_next_line(map_fd);
		}
		if (line)
		{
			tempo_lst = lst;
			lst = load_line(&tempo_lst, line, row_nb);
			if (!lst)
			{
				while (tempo_lst)
					ft_lstpop(&tempo_lst);
				free(line);
				return (NULL);
			}
			tempo_line = line;
		}
		++i;
	}
	
	if (ft_strlen(tempo_line) == 0)
		ft_lstpop(&lst);
	add_wrappers(&lst, *row_nb);
	return (lst);
}
