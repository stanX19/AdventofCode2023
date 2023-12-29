NAME	= main
PT1		= beam_reflection.cpp
PT2		= max_energy.cpp
CC		= g++ -Wfatal-errors -Wall -Wextra -Werror -fsanitize=address -g3 -std=c++17
INPUT1	= files/input.txt
INPUT2	= files/input2.txt

run: pt1

pt2:
	$(CC) $(PT2) -o $(NAME) 
	@./$(NAME) $(INPUT1)
pt1:
	$(CC) $(PT1) -o $(NAME) 
	@./$(NAME) $(INPUT1)
pt2_2:
	$(CC) $(PT2) -o $(NAME) 
	@./$(NAME) $(INPUT2)
pt1_2:
	$(CC) $(PT1) -o $(NAME) 
	@./$(NAME) $(INPUT2)
clean:
	@rm -rf $(NAME)
