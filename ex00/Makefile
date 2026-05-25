NAME = fixed

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic -MMD -MP

SRCS = main.cpp Fixed.cpp

OBJDIR = objs
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)
RM = rm -rf

all: $(NAME)

-include $(OBJS:.o=.d)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
