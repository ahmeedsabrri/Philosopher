/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <asabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:47:54 by asabri            #+#    #+#             */
/*   Updated: 2023/05/28 14:02:47 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include<sys/wait.h>
pid_t wait(int *wstatus);
int main(int argc, char const *argv[])
{
    int id = fork();
    int n;
    int i;

    
    if (id != 0)
        n = 1;
    else 
        n = 6;
    if (id != 0)
    {
        wait(NULL);
    }
    i = n;
    while (++i < n + 5)
    {
        if (id == 0)
            printf("child proccess {i}-> %d \n",i);
        else
            printf("main proccess %d\n",i);
        fflush(stdout);
    }
    printf("\n");
    return 0;
}