NAME	= main
PT1		= cards_value.cpp
PT2		= cards_copy.cpp
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
