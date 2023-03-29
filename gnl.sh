#!/bin/bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=$1 get_next_line.c get_next_line_utils.c libft.a