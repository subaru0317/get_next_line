#!/bin/bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=$1 get_next_line.c libft.a