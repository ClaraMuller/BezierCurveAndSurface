SHELL	=	bash
CPPFLAGS	+=	-Wextra -Wall -Werror -I./include -std=c++11
INCLDEP	=	-Y./include

# School
LDFLAGS += -L ~/.brew/lib
CPPFLAGS += -I ~/.brew/include/glm -I ~/.brew/include
#home
LDFLAGS	+=	-L/usr/local/lib
CPPFLAGS	+= -I/usr/local/include

LDFLAGS	+=	-L./lib -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lglew
DEBUG	=	-g3 -fno-inline
CC		=	g++

OBJDIR	=	.objs
LISTDIR	=	src

DIRSRC	=	src

NAME	=	a.out
SRC		=	$(DIRSRC)/main.cpp		\
			$(DIRSRC)/Bezier2D.cpp		\
			$(DIRSRC)/Color.cpp		\
			$(DIRSRC)/Engine.cpp		\
			$(DIRSRC)/EngineDrawing.cpp	\
			$(DIRSRC)/EngineMap.cpp		\
			$(DIRSRC)/EngineStatic.cpp	\
			$(DIRSRC)/EngineGetterSetter.cpp\
			$(DIRSRC)/Scene.cpp		\
			$(DIRSRC)/Shader.cpp

OBJ		=	$(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))
DEPS	=	$(OBJDIR)/Makefile.deps

.SILENT:

all		:	$(OBJDIR) $(DEPS) $(NAME)

$(addprefix $(OBJDIR)/, %.o)	:	%.cpp
		$(CC) $(CPPFLAGS) -o $@ -c $<
		echo -e '\033[0;32mBuilding C Object $@\033[0m'

$(NAME)	:	$(OBJ)
	$(CC) $(CPPFLAGS) -o $@ $(OBJ) $(LDFLAGS)
	echo -ne '\033[1;31mC executable \033[1;35m$(NAME) '
	echo -e '\033[1;33m$(CC)\033[0m'

ifneq ("$(wildcard $(DEPS))", "")
-include $(DEPS)
endif

$(DEPS)		:
	$(eval RETURN_VAL := $(shell makedepend 2>/dev/null; echo $$?))
	if [ $(RETURN_VAL) -eq 0 ]; then												\
		makedepend -- $(CPPFLAGS) -- $(SRC) -p $(OBJDIR)/ $(INCLDEP) -f- > $(DEPS) 2> /dev/null;	\
	fi

clean	:
		/bin/rm	-fr $(OBJDIR)
		echo -e '\033[1;34mClean executable $(NAME)\033[0m'

fclean	:	clean
		/bin/rm -fr $(NAME)
		echo -e '\033[1;34mFclean executable $(NAME)\033[0m'

re		:	fclean
		make

debug	:	CPPFLAGS += $(DEBUG)
debug	:	fclean all
		echo -e '\033[1;31mDebug version \033[1;35m$(DEBUG)\033[0m'

analyze	:
		clang --analyze -Xanalyzer -analyzer-output=html $(SRC) -I./include

every	:	CPPFLAGS += -Weverything
every	:	fclean all
		echo -e '\033[1;33mGood job !\033[0m'

$(OBJDIR)	:
		/bin/mkdir $(OBJDIR);			\
		for DIR in $(LISTDIR);			\
		do								\
			/bin/mkdir $(OBJDIR)/$$DIR;	\
		done							\

help	:
		echo -e '\033[1;34mclean\t\033[0m⇒ Cleaning all object'
		echo -e '\033[1;34mfclean\t\033[0m⇒ Cleaning all object and libraries'
		echo -e '\033[1;34mdebug\t\033[0m⇒ Add debug flags'
		echo -e '\033[1;34mre\t\033[0m⇒ Deleting all object and build'
		echo -e ""
		echo -e '\033[1;34mevery\t\033[0m⇒ God code'

.PHONY:	clean fclean re debug every
# DO NOT DELETE
