NAME	= main
SRCS1	= knot_simulation.cpp
SRCS2	= rope_simulation.cpp
GCC		= g++ -Wfatal-errors -Wall -Wextra -Werror -fsanitize=address
ARGV	= files/input.txt


pt2:
	$(GCC) $(SRCS2) -o $(NAME) 
	@./$(NAME) $(ARGV)
pt1:
	$(GCC) $(SRCS1) -o $(NAME) 
	@./$(NAME) $(ARGV)
clean:
	@rm -rf $(NAME)
