# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/26 18:50:16 by skoh              #+#    #+#              #
#    Updated: 2021/11/27 18:10:45 by skoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	:= philo
# LDFLAGS	= -fsanitize=address -g3
CFLAGS 	= -Wall -Wextra -Werror $(LDFLAGS)
objs 	:= main.o ft_atoi_try.o utils.o

.phony: all clean fclean re test check

all: $(NAME)

$(objs): philo.h

$(NAME): $(objs)
	$(LINK.o) $^ -o $@

clean:
	rm -f $(objs)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(NAME)
	@read -p "philos: " P && read -p "min eats: " E \
	&& D=`echo "$$P%2*60+130"|bc` \
	&& echo excuting... \
	&& zsh -c "time ./philo $$P $$D 60 60 $$E &> log"
	@make check

check:
	@echo searching unordered lines && awk '{c=$$1; if(c<a)print NR,a,$$0; a=c}' log
	@awk 'BEGIN{max=e=a=d=t=s=mean=0}{ \
	if($$2>max){max=$$2} \
	if($$3=="died"){++d} \
	else if($$4=="eating"){e=e+1;if($$2=="1"){++a}} \
	else if($$4=="sleeping"){++s} \
	else if($$4=="thinking"){++t} \
	} END{mean=e/max; \
	print "thinks: "t"\neats found: " e " / " max " philos = " mean "\nsleeps: "s"\ndied found: " d}' log
	@echo tail.. && tail log
