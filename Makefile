# Компилятор
CXX = g++

# Флаги компиляции (рекомендуется для отладки и вывода предупреждений)
CXXFLAGS = -Wall -g

# Имя исполняемого файла
TARGET = my_project

# Исходные файлы (взяты из вашего списка)
SRCS = Directory.cpp \
       Entry.cpp \
       MultiLineFile.cpp \
       SingleLineFile.cpp \
       Terminal.cpp

# Объектные файлы (автоматически генерируются из SRCS)
OBJS = \$(SRCS:.cpp=.o)

# Стандартная цель по умолчанию — "all"
all: \$(TARGET)

# Правило сборки исполняемого файла из объектных файлов
$(TARGET): $(OBJS)
  $(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Правило компиляции .cpp файлов в .o (универсальное правило)
%.o: %.cpp
  $(CXX) $(CXXFLAGS) -c $< -o $@

# Цель для очистки (удаляет исполняемый файл и объектные файлы)
clean:
	rm -f $(TARGET) $(OBJS)

# Цель для полной пересборки (очистка + сборка)
rebuild: clean all

# Указываем, что эти цели — фиктивные (чтобы make не искал файлы с такими именами)
.PHONY: all clean rebuild
