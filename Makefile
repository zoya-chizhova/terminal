# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -Wall -g

# Имя исполняемого файла
TARGET = my_project

# Исходные файлы
SRCS = Directory.cpp \
       Entry.cpp \
       MultiLineFile.cpp \
       SingleLineFile.cpp \
       Terminal.cpp \
       main.cpp

# Объектные файлы
OBJS = $(SRCS:.cpp=.o)

# Цель по умолчанию
all: $(TARGET)

# Правило сборки исполняемого файла
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Правило компиляции .cpp в .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(TARGET) $(OBJS)

# Пересборка
rebuild: clean all

.PHONY: all clean rebuild
