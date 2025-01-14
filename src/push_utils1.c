/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <marcambuehl4@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:33:59 by maambuhl          #+#    #+#             */
/*   Updated: 2025/01/14 17:18:46 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	find_place(int *stack, int *b, t_stack_info *stack_i)
{
	int	to_place;
	int	i;

	i = *b;
	to_place = stack[(*b) + 1];
	if (to_place >= stack[stack_i->max] || to_place <= stack[stack_i->min])
		return (stack_i->max);
	while (i)
	{
		if (to_place > stack[i - 1] && to_place < stack[i])
			return (i - 1);
		if (to_place > stack[*b] && stack[(*b) + 1] < stack[0])
			return (*b);
		i--;
	}
	return (i);
}

int	find_place_i(t_stack_info *stack_i, int to_place)
{
	int	i;
	int	*stack;
	int	*b;
	
	stack = stack_i->stack;
	b = stack_i->b;
	i = *b;
	if (to_place > stack[stack_i->max] || to_place < stack[stack_i->min])
		return (stack_i->max);
	while (i)
	{
		if (to_place > stack[i - 1] && to_place < stack[i])
			return (i - 1);
		if (to_place > stack[*b] && to_place < stack[0])
			return (*b);
		i--;
	}
	return (i);
}

int	offset_a(t_stack_info *stack_i, int tmp_b)
{
	int	size_a;
	
	tmp_b = tmp_b - (*stack_i->b + 1);
	size_a = stack_i->size - (*stack_i->b + 1);
	if (tmp_b < (size_a / 2))
		return (tmp_b);
	else
		return (size_a - tmp_b);
}

int	offset_b(t_stack_info *stack_i, int place)
{
	if (place < ((*stack_i->b) / 2))
		return (place + 1);
	else
		return (*stack_i->b - place);
}

int	find_best_i(t_stack_info *stack_i, int init_min_mv)
{
	int place;
	int	nb_mv;
	int	nb_mv_a;
	int	to_place;
	int	best_i;
	int	min_mv;
	int	tmp_b;
	int	nb_mv_b;
	int	size_a;
	
	size_a = stack_i->size - (*stack_i->b + 1);
	min_mv = init_min_mv;
	tmp_b = *stack_i->b + 1;
	best_i = 0;
	while (tmp_b < stack_i->size)
	{
		nb_mv = 0;
		nb_mv_a = offset_a(stack_i, tmp_b);
		to_place = stack_i->stack[tmp_b];
		place = find_place_i(stack_i, to_place);
		if (place < (*stack_i->b / 2))
		{
			//rrb
			nb_mv_b = place + 1;
			if (tmp_b - (*stack_i->b + 1) > (size_a / 2))
			{ // rra
				if (nb_mv_a > nb_mv_b)
					nb_mv = nb_mv_a;
				else
					nb_mv = nb_mv_b;
			}
			else
				nb_mv += (nb_mv_b + nb_mv_a);
		}
		else
		{
			//rb
			// nb_mv += *stack_i->b - place;
			nb_mv_b = *stack_i->b - place;
			if (tmp_b - (*stack_i->b + 1) < (size_a / 2))
			{ // ra
				if (nb_mv_a > nb_mv_b)
					nb_mv = nb_mv_a;
				else
					nb_mv = nb_mv_b;
			}
			else
				nb_mv += (nb_mv_b + nb_mv_a);
		}
		if (nb_mv < min_mv)
		{
			min_mv = nb_mv;
			best_i = tmp_b;
			stack_i->nb_mv_b = nb_mv_b;
			stack_i->nb_mv_a = nb_mv_a;
			stack_i->min_mv = nb_mv;
			stack_i->place = place;
		}
		tmp_b++;
	}
	stack_i->best_index = best_i;
	stack_i->best_index_a = best_i;
	return (best_i);
}

int	initiate_mv_a(t_stack_info *stack_i, int index_to_mv, int nb)
{
	int	size_a;
	int	nb_rr;
	int	nb_rrr;
	int	i;
	
	nb_rr = 0;
	nb_rrr = 0;
	i = 0;
	size_a = stack_i->size - (*stack_i->b + 1);
	index_to_mv = index_to_mv - (*stack_i->b + 1);
	if (stack_i->place > (*stack_i->b / 2) && index_to_mv < (size_a / 2))
	{
		i = 1;
		if (stack_i->nb_mv_a > stack_i->nb_mv_b)
			nb_rr = stack_i->nb_mv_b;
		else
			nb_rr = stack_i->nb_mv_a;
	}
	else if (stack_i->place < (*stack_i->b / 2) && index_to_mv > (size_a / 2))
	{
		i = 1;
		if (stack_i->nb_mv_a > stack_i->nb_mv_b)
			nb_rrr = stack_i->nb_mv_b;
		else
			nb_rrr = stack_i->nb_mv_a;
	}
	make_rr_rrr(stack_i, nb_rr, nb_rrr);
	make_mv_a(stack_i, index_to_mv, nb);
	return (i);
}
