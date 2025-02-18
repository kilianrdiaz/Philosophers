/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroyo-di <kroyo-di@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:39:32 by kroyo-di          #+#    #+#             */
/*   Updated: 2025/01/23 15:47:49 by kroyo-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9') 
		return (1);
	return (0);
}

long	ft_atol(const char *s)
{
	int		i;
	long	res;
	long	neg;

	i = 0;
	res = 0;
	neg = 1;
	while (s[i] && s[i] == ' ')
		i++;
	if (!s[i])
		return (0);
	if (s[i] == '+')
		i++;
	else if (s[i] == '-')
	{
		neg = -1;
		i++;
	}
	while (s[i] && ft_isdigit(s[i]))
	{
		res = res * 10 + s[i] - '0';
		i++;
	}
	return (res * neg);
}
