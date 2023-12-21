NAME	= main
PT1		= 
PT2		= 
CC		= g++ -Wfatal-errors -Wall -Wextra -Werror -fsanitize=address
ARGV1	= files/input.txt
ARGV2	= files/input2.txt

run: pt1

pt2:
	$(CC) $(PT2) -o $(NAME) 
	@./$(NAME) $(ARGV1)
pt1:
	$(CC) $(PT1) -o $(NAME) 
	@./$(NAME) $(ARGV1)
pt2_2:
	$(CC) $(PT2) -o $(NAME) 
	@./$(NAME) $(ARGV2)
pt1_2:
	$(CC) $(PT1) -o $(NAME) 
	@./$(NAME) $(ARGV2)
clean:
	@rm -rf $(NAME)
