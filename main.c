/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 14:09:23 by qhonore           #+#    #+#             */
/*   Updated: 2017/10/21 19:12:43 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "include/malloc.h"

int		main()
{
	int* test = ft_malloc(1);
	printf("test: %p\n", test);
	test = ft_malloc(1);
	printf("test: %p\n", test);
	return (0);
}
