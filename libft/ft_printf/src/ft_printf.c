/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:12:17 by akhossan          #+#    #+#             */
/*   Updated: 2019/11/24 21:00:36 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Gets the precision, either from va_arg if a '*' flag is set,
**	or from format string using ft_atoll function
*/

static void	va_arg_precision(t_args *args, t_vars *var)
{
	if (var->str[var->j] == '*')
	{
		args->precision = va_arg(var->types_list, int);
		if (args->spec == 'f')
			args->precision = args->precision < 0 ? 6 : args->precision;
	}
	else
	{
		args->precision = ft_atoll(&var->str[var->j]);
		if (args->precision < 0)
		{
			if (args->spec == 'f')
				args->precision = 6;
			else
			{
				args->flag = (args->flag & MASK_MINUS) ? \
							args->flag : args->flag + 1;
				args->width = args->precision * -1;
			}
		}
	}
}

/*
**	Handles precision and unsets '0' flag for certain
**	type conversions (diouxXpb).
*/

void		get_precision(t_args *args, t_vars *var)
{
	if (var->str[var->j] == '.')
	{
		args->precision = 0;
		var->j++;
		va_arg_precision(args, var);
		while (ft_isdigit(var->str[var->j]))
			var->j++;
		if ((args->flag & MASK_ZERO) && args->precision >= 0 \
				&& ft_contains(DIOUXXPB, args->spec))
			args->flag ^= MASK_ZERO;
	}
	else if (args->spec == 'f')
		args->precision = 6;
}

/*
**	Function to dispatch printing according the appropriate
**	conversion specifier given in the format string.
*/

void		manage_args(t_args *args, t_vars *var)
{
	if (ft_contains("id", args->spec))
		ft_print_d(args, var);
	else if (ft_contains("poubxX", args->spec))
		ft_print_poubx(args, var);
	else if (args->spec == 's')
		ft_print_s(args, var);
	else if (args->spec == 'f')
		ft_print_f(args, var);
	else
		ft_print_c(args, var);
}

/*
**	Escape 42 Norminette shit rules 😎
*/

static void	ft_printf_helper(t_args *args, t_vars *var)
{
	while (var->str[++var->i])
	{
		if (var->str[var->i] == '%')
		{
			initialize_args(args);
			var->j = var->i + 1;
			if (!var->str[var->j])
				break ;
			if (!get_specifier(args, var))
			{
				var->i = var->j;
				continue ;
			}
			var->j = var->i + 1;
			get_flags(args, var);
			get_width(args, var);
			get_precision(args, var);
			get_modifier(args, var);
			manage_args(args, var);
			var->i = args->spec_index;
		}
		else
			set_color(var);
	}
}

/*
**	Our evil ft_printf trying to imitate printf monster 😈
*/

int			ft_printf(const char *format, ...)
{
	t_args args;
	t_vars var;

	if (!format)
		exit(1);
	va_start(var.types_list, format);
	var.counter = 0;
	var.str = (char *)format;
	var.i = -1;
	ft_printf_helper(&args, &var);
	va_end(var.types_list);
	return (var.counter);
}

/*
**	we forgot to handle this case:
**	printf(" heello %.2147483647d\n", 45);
*/
