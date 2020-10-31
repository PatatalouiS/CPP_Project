
# This Makefile assume that you want to put your OBJ files in an OBJ folder.
# And all your sources must be in src/ folder, change in consequences if not.
# And your exec will be created on the same level of the Makefile.

GCC       = g++
FLAGS     = -Wall -Wextra -std=c++17
LIBS      =
MAIN_RULE = ExprApp

OBJ       = obj/
SRC       = src/
O_X       = .o
C_X       = .cpp
H_X       = .hpp

# take *.cpp in $(SRC), add parent folder $(OBJ) and replace .cpp to .o
OBJ_FILES = $(patsubst %$(C_X), $(OBJ)%$(O_X), $(notdir $(wildcard $(SRC)*$(C_X))))

# Main rule
all : mkdir_folders $(MAIN_RULE)

# ld rule
$(MAIN_RULE) : $(OBJ_FILES) 
	$(GCC) $(FLAGS) $(LIBS) $^ -o $@

# for all the .cpp with a related .hpp
$(OBJ)%$(O_X) : $(SRC)%$(C_X) $(SRC)%.$(H_X)
	$(GCC) $(FLAGS) -c $< -o $@

# for all the .cpp without related .hpp
$(OBJ)%$(O_X) : $(SRC)%$(C_X)
	$(GCC) $(FLAGS) -c $< -o $@

mkdir_folders :
	@mkdir -p $(OBJ)

clean :
	rm -rvf $(OBJ)

veryclean : clean
	rm -rvf $(MAIN_RULE)

.PHONY : clean veryclean
