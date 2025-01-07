/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <marcambuehl4@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:33:59 by maambuhl          #+#    #+#             */
/*   Updated: 2025/01/07 21:54:51 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	find_max(int *stack, int b)
{
	int	max;
	int	i;

	i = b;
	max = stack[b--];
	while (b >= 0)
	{
		if (stack[b] > max)
		{
			max = stack[b];
			i = b;
		}
		b--;
	}
	return (i);
}

int	find_min(int *stack, int b)
{
	int	min;
	int	i;

	i = b;
	min = stack[b--];
	while (b >= 0)
	{
		if (stack[b] < min)
		{
			min = stack[b];
			i = b;
		}
		b--;
	}
	return (i);
}

int	push_basic(t_stack_info *stack_i)
{
	int	a;

	a = *(stack_i->b) + 1;
	stack_i->min = find_min(stack_i->stack, *stack_i->b);
	stack_i->max = find_max(stack_i->stack, *stack_i->b);
	if (stack_i->stack[a] > stack_i->stack[stack_i->max])
	{
		// stack_i->max = a;
		if (*stack_i->b == stack_i->max)
		{
			pb(stack_i->b, stack_i->size, 1);
			return (-1);
		}
		// find_best_index(stack, b, max, size);
		return (stack_i->max);
	}
	if (stack_i->stack[a] < stack_i->stack[stack_i->min])
	{
		// find_best_index(stack, b, max, size);
		stack_i->min = a;
		return (stack_i->max);
	}
	return (-2);
}

int	find_place(int *stack, int *b)
{
	int	to_place;
	int	i;

	i = *b;
	to_place = stack[(*b) + 1];
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

int	find_place_i(t_stack_info *stack_i, int to_place, int tmp_b)
{
	int	i;
	int	*stack;
	int	*b;
	(void)tmp_b;
	
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
	
	size_a = stack_i->size - (*stack_i->b + 1);
	if (tmp_b < (size_a / 2))
		return (tmp_b - (*stack_i->b + 1));
	else
		return (stack_i->size - tmp_b);
}

int	offset_b(t_stack_info *stack_i, int place)
{
	if (place < ((*stack_i->b) / 2))
		return (place + 1); //rrb
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
		place = find_place_i(stack_i, to_place, tmp_b);
		if (place < (*stack_i->b / 2))
		{
			//rrb
			nb_mv_b = place + 1;
			if (tmp_b > (size_a / 2))
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
			if (tmp_b < (size_a / 2))
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

int	make_mv_a(t_stack_info *stack_i, int index_to_mv)
{
	int	size_a;
	int	nb;
	int	head;
	int	i;
	int	nb_rr;
	int	nb_rrr;
	
	nb_rr = 0;
	nb_rrr = 0;
	size_a = stack_i->size - (*stack_i->b + 1);
	head = stack_i->stack[(*stack_i->b) + 1];
	nb = stack_i->stack[index_to_mv];

	if (stack_i->place > (*stack_i->b / 2) && index_to_mv < (size_a / 2))
	{ // rb
		if (stack_i->nb_mv_a > stack_i->nb_mv_b)
			nb_rr = stack_i->nb_mv_b;
		else
			nb_rr = stack_i->nb_mv_a;
	}
	else if (stack_i->place < (*stack_i->b / 2) && index_to_mv > (size_a / 2))
	{ // rrb
		if (stack_i->nb_mv_a > stack_i->nb_mv_b)
			nb_rrr = stack_i->nb_mv_b;
		else
			nb_rrr = stack_i->nb_mv_a;
	}
	i = -1;
	while (++i < nb_rr)
	{
		rr(stack_i->stack, stack_i->size, stack_i->b);
		if (stack_i->place == *stack_i->b)
			stack_i->place = 0;
		else
			stack_i->place++;
	}
	i = -1;
	while (++i < nb_rrr)
	{
		rrr(stack_i->stack, stack_i->size, stack_i->b);
		if (stack_i->place == 0)
			stack_i->place = *stack_i->b;
		else
			stack_i->place--;
	}
	i = 0;
	while (head != nb)
	{
		if (index_to_mv < (size_a / 2))
		{
			ra(stack_i->stack, stack_i->size, stack_i->b, 1);
		}
		else
		{
			rra(stack_i->stack, stack_i->size, stack_i->b, 1);
		}
		head = stack_i->stack[(*stack_i->b) + 1];
		i++;
	}
	return (i);
}

int	find_best_index(int *stack, int *b, int place, int size)
{
	int	nb;
	int	head;
	int	i;

	(void)size;
	nb = stack[place];
	head = stack[*b];
	i = 0;
	while (head != nb)
	{
		if (place < (*b / 2))
			rrb(stack, b, 1);
		else
			rb(stack, b, 1);
		head = stack[*b];
		i++;
	}
	return (i);
}
