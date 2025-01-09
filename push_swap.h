/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <marcambuehl4@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:56:46 by maambuhl          #+#    #+#             */
/*   Updated: 2025/01/09 13:49:00 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "./libft/libft.h"
# include <stdio.h>
# include <errno.h>
# include <limits.h>

typedef struct s_stack_info
{
	int	*stack;
	int	*b;
	int	size;
	int	min;
	int	max;
	int	best_index;
	int	place;
	int	min_mv;
	int	nb_mv_a;
	int	nb_mv_b;
	int	best_index_b;
	int	best_index_a;
	int	tmp_max;
	int	tmp_min;
}	t_stack_info;

void	err(char *str);
void	check_input(char **str, int ac);
void	pb(int *b, int size, int print);
void	pa(int *b, int print);
void	sa(int *stack, int size, int *b, int print);
void	sb(int *stack, int *b, int print);
void	ra(int *stack, int size, int *b, int print);
void	rb(int *stack, int *b, int print);
void	rr(int *stack, int size, int *b);
void	rra(int *stack, int size, int *b, int print);
void	rrb(int *stack, int *b, int print);
void	rrr(int *stack, int size, int *b);
int		find_max(int *stack, int b);
int		find_min(int *stack, int b);
int		find_best_index(int *stack, int *b, int a, int size);
int		find_best_i(t_stack_info *stack_i, int init_min_mv);
int		push_basic(t_stack_info *stack_i);
int		find_place(int *stack, int *b, t_stack_info *stack_i);
int		make_mv_a(t_stack_info *stack_i, int index_to_mv);
int		offset_b(t_stack_info *stack_i, int place);

#endif
