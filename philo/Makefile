# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/02 13:13:30 by ngordobi          #+#    #+#              #
#    Updated: 2024/09/02 14:02:15 by ngordobi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	philo

CC					=	gcc
CC_FLAGS			=	-Wall -Wextra -Werror

SOURCES				=	philo.c \
						check_args.c \

OBJECTS				= 	$(SOURCES:%.c=%.o)

INCLUDE				=	philo.h

define PHILOSOPHERS
\033[0;33m

 ██▓███   ██░ ██  ██▓ ██▓     ▒█████    ██████  ▒█████   ██▓███   ██░ ██ ▓█████  ██▀███    ██████ 
▓██░  ██▒▓██░ ██▒▓██▒▓██▒    ▒██▒  ██▒▒██    ▒ ▒██▒  ██▒▓██░  ██▒▓██░ ██▒▓█   ▀ ▓██ ▒ ██▒▒██    ▒ 
▓██░ ██▓▒▒██▀▀██░▒██▒▒██░    ▒██░  ██▒░ ▓██▄   ▒██░  ██▒▓██░ ██▓▒▒██▀▀██░▒███   ▓██ ░▄█ ▒░ ▓██▄   
▒██▄█▓▒ ▒░▓█ ░██ ░██░▒██░    ▒██   ██░  ▒   ██▒▒██   ██░▒██▄█▓▒ ▒░▓█ ░██ ▒▓█  ▄ ▒██▀▀█▄    ▒   ██▒
▒██▒ ░  ░░▓█▒░██▓░██░░██████▒░ ████▓▒░▒██████▒▒░ ████▓▒░▒██▒ ░  ░░▓█▒░██▓░▒████▒░██▓ ▒██▒▒██████▒▒
▒▓▒░ ░  ░ ▒ ░░▒░▒░▓  ░ ▒░▓  ░░ ▒░▒░▒░ ▒ ▒▓▒ ▒ ░░ ▒░▒░▒░ ▒▓▒░ ░  ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒▓ ░▒▓░▒ ▒▓▒ ▒ ░
░▒ ░      ▒ ░▒░ ░ ▒ ░░ ░ ▒  ░  ░ ▒ ▒░ ░ ░▒  ░ ░  ░ ▒ ▒░ ░▒ ░      ▒ ░▒░ ░ ░ ░  ░  ░▒ ░ ▒░░ ░▒  ░ ░
░░        ░  ░░ ░ ▒ ░  ░ ░   ░ ░ ░ ▒  ░  ░  ░  ░ ░ ░ ▒  ░░        ░  ░░ ░   ░     ░░   ░ ░  ░  ░  
          ░  ░  ░ ░      ░  ░    ░ ░        ░      ░ ░            ░  ░  ░   ░  ░   ░           ░  

$(END)
endef
export PHILOSOPHERS

.SILENT:

all:				$(NAME)

$(NAME):			$(OBJECTS) $(INCLUDE)
					$(CC) $(CC_FLAGS) $(OBJECTS) -o $(NAME)
					mkdir ./objects/
					mv $(OBJECTS) ./objects/
					echo "\n······································ Compilation complete ······································"
					echo "$$PHILOSOPHERS"

clean:
					rm -rf ./objects/
					rm -rf *.o
					echo "\n·······························"
					echo "\n· Objects correctly removed."
					
fclean:				clean
					rm -rf $(NAME)
					echo "· Executable correctly removed.\n"

re:					fclean all
.PHONY:				all clean fclean re