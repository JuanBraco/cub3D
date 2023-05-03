#include <unistd.h>
#include <stdio.h>
#include "./includes/cub3d.h"

int		main(int argc, char **argv)
{
	t_data data;

    (void)data;
	if (argc == 2)
        printf("argc : %i", argc);
	else
		write(1, "Error : Arguments invalides\n", 28);
}