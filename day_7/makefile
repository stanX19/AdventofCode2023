NAME	= main
PT1		= hand_val.cpp
PT2		= hand_val_2.cpp
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
