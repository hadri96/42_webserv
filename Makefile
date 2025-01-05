NAME= webserv

MAKEFLAGS= --no-print-directory

INCLUDES = includes

CC= c++

CFLAGS= -Wall -Wextra -Werror -I$(INCLUDES) -std=c++98

UNAME_S := $(shell uname -s)

#ifeq ($(UNAME_S),Linux)
#	SRCS+= ...
#else ifeq ($(UNAME_S),Darwin)
#	SRCS+= ...
#endif

# Source File names:
MAIN = main
PARSING = HTTPResponse HTTPRequest HTMLParser ResponseHeader
SERVER = Eventloop ClientConnection
UTILS = getCurrentTime
CONFIG =

# Source directory
SRCS_DIR = srcs

# Source Subdirectories:
PARS_DIR = parsing
SERVER_DIR = server
CONFIG_DIR = config
UTILS_DIR = utils
# Source Files
SRCS = $(addprefix $(SRCS_DIR)/$(UTILS_DIR)/, $(addsuffix .cpp, $(UTILS)))\
	$(addprefix $(SRCS_DIR)/, $(addsuffix .cpp, $(MAIN)))\
	$(addprefix $(SRCS_DIR)/$(PARS_DIR)/, $(addsuffix .cpp, $(PARSING)))\
	$(addprefix $(SRCS_DIR)/$(SERVER_DIR)/, $(addsuffix .cpp, $(SERVER))) \
	$(addprefix $(SRCS_DIR)/$(CONFIG_DIR)/, $(addsuffix .cpp, $(CONFIG)))


# Convert source file names to object file names in the OBJ_DIRS directory
OBJ_DIR = obj
OBJ_DIRS = $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(PARS_DIR)) \
	$(addprefix $(OBJ_DIR)/, $(SERVER_DIR)) \
	$(addprefix $(OBJ_DIR)/, $(CONFIG_DIR)) \
	$(addprefix $(OBJ_DIR)/, $(UTILS_DIR))

OBJS = $(SRCS:$(SRCS_DIR)/%.cpp=$(OBJ_DIR)/%.o)

#SANITIZE= -g3 -fsanitize=address
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

# Compilation rule for the final executable
$(NAME): $(OBJ_DIRS) $(OBJS) header
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(SANITIZE)
	@echo "$(YELLOW)\no------------------------------------o$(RESET)"
	@echo "$(GREEN)|           WEBSERV COMPILED          |$(RESET)"
	@echo "$(YELLOW)o------------------------------------o\n$(RESET)"

# Create object directories if they do not exist
$(OBJ_DIRS):
	@mkdir -p $(OBJ_DIR) \
		$(addprefix $(OBJ_DIR)/, $(PARS_DIR)) \
		$(addprefix $(OBJ_DIR)/, $(SERVER_DIR)) \
		$(addprefix $(OBJ_DIR)/, $(CONFIG_DIR)) \
		$(addprefix $(OBJ_DIR)/, $(UTILS_DIR))

# Rule to compile object files from source files
$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.cpp | $(OBJ_DIRS)
	@$(CC) $(CFLAGS) -o $@ -c $<

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
		@echo "$(RED)|__/     \__/ \_______/|_______/ |_______/  \_______/|__/          \_/$(RESET)"
		@echo "\n\n";

clean: header
	@echo "${RED}\nCleaning up...${RESET}"
	@rm -f $(OBJS)
	@echo "${GREEN}Cleanup done.${RESET}"

fclean: 	clean
		@rm -f $(NAME)
		@rm -rf $(OBJ_DIR)
		@echo "$(YELLOW)\no------------------------------------o$(RESET)"
		@echo "$(RED)|           WEBSERV CLEARED           |$(RESET)"
		@echo "$(YELLOW)o------------------------------------o\n$(RESET)"

re: 			fclean all
