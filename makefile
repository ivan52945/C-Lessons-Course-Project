TARGET = course-project

FLAGS = -Wall -std=c99

RELEASE_PREF = release
SRC_PREF = sources
OBJ_PREF = objects

SRC = $(wildcard $(SRC_PREF)/*.c)
OBJ = $(patsubst $(SRC_PREF)/%.c, $(OBJ_PREF)/%.o, $(SRC))

all: $(RELEASE_PREF)/$(TARGET)

$(RELEASE_PREF)/$(TARGET): $(OBJ)
	gcc $(FLAGS) $(OBJ) -o $(RELEASE_PREF)/$(TARGET)

$(OBJ_PREF)/%.o: $(SRC_PREF)/%.c
	gcc $(FLAGS) -c $< -o $@

clean:
	del $(RELEASE_PREF)\\*.exe
	del $(OBJ_PREF)\\*.o