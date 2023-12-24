NAME	= main
PT1		= margin_error.cpp
PT2		= margin_error_2.cpp
CC		= g++ -Wfatal-errors -Wall -Wextra -Werror -fsanitize=address
ARGV	= files/input.txt

run: pt1

pt2:
	$(CC) $(PT2) -o $(NAME) 
	@./$(NAME) $(ARGV)
pt1:
	$(CC) $(PT1) -o $(NAME) 
	@./$(NAME) $(ARGV)
clean:
	@rm -rf $(NAME)
