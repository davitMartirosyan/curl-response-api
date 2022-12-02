all:
	cd libft/ && make re
	cd ../
	gcc curl.c gnl/get_next_line.c gnl/get_next_line_utils.c libft/libft.a -lcurl -o curl