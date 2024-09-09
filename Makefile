NAME= webserv

MAKEFLAGS= --no-print-directory

INCLUDES = includes

SRCS= srcs/main.cpp


CC= c++

CFLAGS= -Wall -Wextra -Werror -I$(INCLUDES) -std=c++98

UNAME_S := $(shell uname -s)

#ifeq ($(UNAME_S),Linux)
#	SRCS+= ...
#else ifeq ($(UNAME_S),Darwin)
#	SRCS+= ...
#endif

# SANITIZE= -g3 -fsanitize=address
SANITIZE= -g

# Color Variables
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
MAGENTA=\033[0;35m
CYAN=\033[0;36m
WHITE=\033[0;37m
RESET=\033[0m

.PHONY: all clean fclean re header

all: $(NAME)

header:

		@echo "$(BLUE)                                 . ....";
		@echo "$(BLUE)                            .@@@@@@@@%@@@@@";
		@echo "$(BLUE)                          %@@. @:  @@  .@..@@%";
		@echo "$(BLUE)                        .@@@%.@.   @@   .@.%@@@.";
		@echo "$(BLUE)                       %@    @@@@@@@@@@@@@@    @@";
		@echo "$(BLUE)                      #@    .@     @@     @.    @#";
		@echo "$(BLUE)                      @     @@     @@     @@    .@.";
		@echo "$(BLUE)                     -@     @*     @@     *@     @=";
		@echo "$(BLUE)                     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
		@echo "$(BLUE)                     =@     @*     @@     *@     @=";
		@echo "$(BLUE)                      @.    @@     @@     @@    .@.";
		@echo "$(BLUE)                      #@    .@     @@     @.    @#";
		@echo "$(BLUE)                       @@    @@@@@@@@@@@@@@    @%";
		@echo "$(BLUE)                        .@@@%.@.   @@   .@.%@@@.";
		@echo "$(BLUE)                          %@@ .@:  @@  :@. @@%";
		@echo "$(BLUE)                             @@@@@%@@%@@@@@";
		@echo "$(BLUE)                                  ...\n";
		@echo "$(CYAN) /SS      /SS           /SS";
		@echo "$(RED)| SS  /S | SS          | SS";
		@echo "$(CYAN)| SS /SSS| SS  /SSSSSS | SSSSSSS   /SSSSSSS  /SSSSSS   /SSSSSS  /SS    /SS";
		@echo "$(RED)| SS/SS SS SS /SS__  SS| SS__  SS /SS_____/ /SS__  SS /SS__  SS|  SS  /SS/";
		@echo "$(CYAN)| SSSS_  SSSS| SSSSSSSS| SS  \ SS|  SSSSSS | SSSSSSSS| SS  \__/ \  SS/SS/";
		@echo "$(RED)| SSS/ \  SSS| SS_____/| SS  | SS \____  SS| SS_____/| SS        \  SSS/";
		@echo "$(CYAN)| SS/   \  SS|  SSSSSSS| SSSSSSS/ /SSSSSSS/|  SSSSSSS| SS         \  S/";
		@echo "$(RED)|__/     \__/ \_______/|_______/ |_______/  \_______/|__/          \_/$(RESET)";


$(NAME) : $(SRCS)
			@$(MAKE) header
			@$(CC) $(CFLAGS) -o $@ $^ $(SANITIZE)
			@echo "$(YELLOW)\no------------------------------------o$(RESET)"
			@echo "$(GREEN)|           WEBSERV COMPILED          |$(RESET)"
			@echo "$(YELLOW)o------------------------------------o\n$(RESET)"

clean:
	@$(MAKE) header
	@echo "${RED}\nCleaning up...${RESET}"
	@rm -f $(NAME)
	@echo "${GREEN}Cleanup done.${RESET}"

fclean: 	clean
		@rm -f $(NAME)
		@rm -rf objs
		@echo "$(YELLOW)\no------------------------------------o$(RESET)"
		@echo "$(RED)|           WEBSERV CLEARED           |$(RESET)"
		@echo "$(YELLOW)o------------------------------------o\n$(RESET)"

re: 			fclean all
