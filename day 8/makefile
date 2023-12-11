NAME	= main
PT1		= nav_steps.cpp
PT2		= nav_steps_2.cpp
CC		= g++ -Wfatal-errors -Wall -Wextra -Werror -std=c++17 -fsanitize=address
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
