# FLAGS =  -I./headers -I./TX -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wstack-usage=8192 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
FLAGS =  -I./headers -I./TX -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

OBJECTS_ASM = asm.o mainasm.o 
OBJECTS_PROC = mainproc.o processor.o
OBJECTS_COMMON = stack.o work_with_text.o

OBJECTS_DIR = objects/

ASM_DIR = assembler/
PROC_DIR = processor/
COMMON_DIR = common/

DIRS = ASM_DIR PROC_DIR COMMON_DIR

SOURCE_DIR = source/

asm: $(addprefix $(OBJECTS_DIR)$(ASM_DIR), $(OBJECTS_ASM)) $(addprefix $(OBJECTS_DIR)$(COMMON_DIR), $(OBJECTS_COMMON))
	@echo ---------------------------------------------------------------------------------------------------------------------
	g++ $(FLAGS) $(addprefix $(OBJECTS_DIR)$(ASM_DIR), $(OBJECTS_ASM)) $(addprefix $(OBJECTS_DIR)$(COMMON_DIR), $(OBJECTS_COMMON)) -g -o asm
	@echo ----------------------------------------------------------------------------------------------------------------------------------------------------

proc: $(addprefix $(OBJECTS_DIR)$(PROC_DIR), $(OBJECTS_PROC)) $(addprefix $(OBJECTS_DIR)$(COMMON_DIR), $(OBJECTS_COMMON))
	@echo ---------------------------------------------------------------------------------------------------------------------
	g++ $(FLAGS) $(addprefix $(OBJECTS_DIR)$(PROC_DIR), $(OBJECTS_PROC)) $(addprefix $(OBJECTS_DIR)$(COMMON_DIR), $(OBJECTS_COMMON)) -g -o proc
	@echo ---------------------------------------------------------------------------------------------------------------------

$(OBJECTS_DIR)$(ASM_DIR)%.o: $(SOURCE_DIR)$(ASM_DIR)%.cpp
	g++ $(FLAGS) -c $< -o $@

$(OBJECTS_DIR)$(PROC_DIR)%.o: $(SOURCE_DIR)$(PROC_DIR)%.cpp
	g++ $(FLAGS) -c $< -o $@

$(OBJECTS_DIR)$(COMMON_DIR)%.o: $(SOURCE_DIR)$(COMMON_DIR)%.cpp
	g++ $(FLAGS) -c $< -o $@

%.o: $(SOURCE_DIR)%.cpp
	g++ $(FLAGS) -c $< -o $@


cleanasm:
	rm -f asm
	rm -f $(OBJECTS_DIR)$(ASM_DIR)*.o
	rm -f $(OBJECTS_DIR)$(COMMON_DIR)*.o

cleanproc:
	rm -f proc
	rm -f $(OBJECTS_DIR)$(PROC_DIR)*.o
	rm -f $(OBJECTS_DIR)$(COMMON_DIR)*.o

clean:
	make cleanproc
	make cleanasm