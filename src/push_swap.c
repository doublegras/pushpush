
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <marcambuehl4@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:33:29 by maambuhl          #+#    #+#             */
/*   Updated: 2025/01/06 16:09:51 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	*create_stack(char **strs, int size)
{
	int		i;
	int		*stack;
	long	temp;

	stack = malloc(sizeof(int) * size);
	if (!stack)
		err("Error\nCannot malloc stack");
	i = 0;
	while (i < size)
	{
		temp = ft_atoi(strs[i]);
		if (temp > INT_MAX || temp < INT_MIN)
		{
			free(stack);
			err("Error\nProvide number that fit 32bit integer");
		}
		stack[i] = temp;
		i++;
	}
	return (stack);
}

void	print_a(int *b, int *stack, int size)
{
	int	i;

	i = *b + 1;
	printf("A = [ ");
	while (i < size)
		printf("%d ", stack[i++]);
	printf("]\n");
}

void	print_b(int *b, int *stack)
{
	int	i;

	i = *b;
	printf("B = [ ");
	if (i >= 0)
	{
		while (i >= 0)
			printf("%d  ", stack[i--]);
	}
	printf("]\n");
}

void	print_s(int *b, int *stack, int size)
{
	print_a(b, stack, size);
	print_b(b, stack);
}

void	algo(t_stack_info *stack_i)
{
	int	place;
	int	i;
	int	min;
	int	best_index;
	int	init_min_mv;

	while ((*stack_i->b + 1) < stack_i->size)
	{
		place = push_basic(stack_i);
		best_index = 0;
		if (place == -1)
		{
			/*print_s(b, stack, size);*/
			continue ;
		}
		if (place == -2)
		{
			place = find_place(stack_i->stack, stack_i->b);
			stack_i->best_index_b = place;
			init_min_mv = offset_b(stack_i, place);
			best_index = find_best_i(stack_i, init_min_mv);
		}
		if (best_index && best_index == *stack_i->b + 1)
			i = find_best_index(stack_i->stack, stack_i->b, place, stack_i->size);
		else
		{
			if (best_index)
			{
				make_mv_a(stack_i, best_index);
				place = stack_i->place;
			}
			i = find_best_index(stack_i->stack, stack_i->b, place, stack_i->size);
		}
		pb(stack_i->b, stack_i->size, 1);
		/*print_s(b, stack, size);*/
	}
	i = 0;
	while (i < stack_i->size)
	{
		pa(stack_i->b, 1);
		i++;
	}
	i = 0;
	min = stack_i->stack[find_min(stack_i->stack, stack_i->size - 1)];
	while (*stack_i->stack != min)
		ra(stack_i->stack, stack_i->size, stack_i->b, 1);
	print_s(stack_i->b, stack_i->stack, stack_i->size);
}

int	main(int ac, char **av)
{
	int				*stack;
	int				b;
	t_stack_info	stack_i;

	if (ac < 2)
		err("Error\nYou should provide stack a as arguments");
	check_input(av + 1, ac - 1);
	stack = create_stack(av + 1, ac - 1);
	b = -1;
	pb(&b, ac - 1, 1);
	pb(&b, ac - 1, 1);
	stack_i.stack = stack;
	stack_i.b = &b;
	stack_i.max = 0;
	stack_i.min = 0;
	stack_i.size = ac - 1;
	stack_i.nb_mv_b = 0;
	stack_i.nb_mv_a = 0;
	algo(&stack_i);
}
