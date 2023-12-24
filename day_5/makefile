NAME	= main
PT1		= seeds_loc.cpp
PT2		= seeds_loc2.cpp
CC		= g++ -Wfatal-errors -Wall -Wextra -Werror -fsanitize=address
ARGV	= files/input2.txt

run: pt2

pt2:
	$(CC) $(PT2) -o $(NAME) 
	@./$(NAME) $(ARGV)
pt1:
	$(CC) $(PT1) -o $(NAME) 
	@./$(NAME) $(ARGV)
clean:
	@rm -rf $(NAME)
