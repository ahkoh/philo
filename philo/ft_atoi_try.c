/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_try.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 23:01:45 by skoh              #+#    #+#             */
/*   Updated: 2021/11/26 23:01:46 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

static int	ft_isspace(int c)
{
	return (c == ' ' || ('\t' <= c && c <= '\r'));
}

static int	ft_atoi(const char *str)
{
	int	sum;
	int	is_negative;
	int	prev;

	prev = (is_negative = (sum = 0));
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		is_negative = (*str++ == '-');
	while (ft_isdigit(*str))
	{
		if (is_negative)
			sum = sum * 10 - (*str++ - '0');
		else
			sum = sum * 10 + (*str++ - '0');
		if (sum / 10 == prev)
			prev = sum;
		else
			return (-!is_negative);
	}
	return (sum);
}

int	ft_atoi_try(const char *str, int *out)
{
	*out = ft_atoi(str);
	while (ft_isspace(*str))
		str++;
	if (*out == -(*str != '-'))
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	if (!ft_isdigit(*str))
		return (0);
	while (ft_isdigit(*str))
		str++;
	return (*str == '\0');
}
