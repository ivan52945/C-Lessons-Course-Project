TARGET = course-project

RELEASE_PREF = release
SRC_PREF = sources
OBJ_PREF = objects

SRC = $(wildcard $(SRC_PREF)/*.c)
OBJ = $(patsubst $(SRC_PREF)/%.c, $(OBJ_PREF)/%.o, $(SRC))

all: $(RELEASE_PREF)/$(TARGET)

$(RELEASE_PREF)/$(TARGET): $(OBJ)
	gcc $(OBJ) -o $(RELEASE_PREF)/$(TARGET)

$(OBJ_PREF)/%.o: $(SRC_PREF)/%.c
	gcc -c $< -o $@

#я не знаю как тут нормально экранировать слеши для windows

clean:
	del $(RELEASE_PREF)\\*.exe
	del $(OBJ_PREF)\\*.o