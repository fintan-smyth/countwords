/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countwords.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:47:54 by fsmyth            #+#    #+#             */
/*   Updated: 2025/02/22 14:58:56 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

typedef struct s_wc
{
	char	*word;
	int		count;
}	t_wc;

t_wc	*new_wc(char *word)
{
	t_wc	*new;

	new = ft_calloc(1, sizeof(*new));
	new->word = ft_strdup(word);
	new->count = 1;
	return (new);
}

void	free_wc(void *wcptr)
{
	t_wc *wc;

	wc = (t_wc *)wcptr;
	free(wc->word);
	free(wc);
}

int	count_digits(int num)
{
	int	digits;

	if (num == 0)
		return (1);
	digits = 0;
	while (num != 0)
	{
		num /= 10;
		digits++;
	}
	return (digits);
}

void	print_wc_node(t_wc *wordcount, void *digitsptr)
{
	int		digits;
	
	digits = *(int *)digitsptr;
	printf("%*d\t%s\n", digits, wordcount->count, wordcount->word);
}

void	add_word(t_tree **tree, char *word, int *max)
{
	int	cmp;

	(void)max;
	if (*tree == NULL)
	{
		*tree = ft_tree_new(new_wc(word));
		return ;
	}
	cmp = ft_strcmp(word, ((t_wc *)(*tree)->content)->word);
	if (cmp == 0)
	{
		((t_wc *)(*tree)->content)->count++;
		// if (((t_wc *)(*tree)->content)->count > *max)
		// 	*max = ((t_wc *)(*tree)->content)->count;
	}
	else if (cmp < 0)
		add_word(&(*tree)->left, word, max);
	else if (cmp > 0)
		add_word(&(*tree)->right, word, max);
}

void	process_line(t_tree **tree, char *line, int *max)
{
	char		buf[255];
	size_t		i;
	size_t		j;

	i = 0;
	while (line[i] != 0)
	{
		ft_memset(buf, 0, 255);
		while (!ft_isalnum(line[i]) && line[i] != 0 && line[i] != '_')
			i++;
		j = 0;
		while (ft_isalnum(line[i]) || line[i] == '_')
		{
			buf[j++] = line[i++];
		}
		if (buf[0] != 0)
			add_word(tree, buf, max);
	}
}

int	process_args(int argc, char **argv)
{
	int	fd;

	if (argc > 2)
		return (-1);
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			return (-1);
	}
	else
		fd = 0;
	return (fd);
}

int	wc_cmp_num(void *node1, void *node2)
{
	t_wc	*wc1;
	t_wc	*wc2;

	wc1 = (t_wc *)node1;
	wc2 = (t_wc *)node2;
	return (wc2->count - wc1->count);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_tree		*tree;
	t_wc		**wc_arr;
	char		*buf;
	int			max;
	int			digits;
	int			no_words;
	size_t		size;
	struct stat	statbuf;

	fd = process_args(argc, argv);
	if (fd < 0)
		return (1);
	fstat(fd, &statbuf);
	size = statbuf.st_size;
	buf = ft_calloc(1, size + 1);
	read(fd, buf, size);
	tree = NULL;
	max = 0;
	process_line(&tree, buf, &max);
	free(buf);
	digits = count_digits(max);
	no_words = ft_treesize(tree);
	wc_arr = (t_wc **)ft_tree_to_arr(tree);
	ft_qsort((void **)wc_arr, 0, no_words - 1, wc_cmp_num);
	ft_printf("Count\tWord\n------------\n");
	int i = 0;
	while (wc_arr[i] != NULL)
		print_wc_node(wc_arr[i++], &digits);
	ft_printf("No. words:\t%d\n", no_words);
	ft_tree_clear(tree, free_wc);
	free(wc_arr);
}
