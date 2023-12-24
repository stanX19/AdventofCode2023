NAME	= main
PT1		= map_steps.cpp
PT2		= enclosed_area.cpp
CC		= g++ -Wfatal-errors -Wall -Wextra -Werror -fsanitize=address
INPUT1	= files/input.txt
INPUT2	= files/input2.txt

run: pt2

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
special:
	$(CC) map_convert_to_ber.cpp
	./a.out $(INPUT2) files/output_2.txt
clean:
	@rm -rf $(NAME)
