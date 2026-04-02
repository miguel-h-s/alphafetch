TARGET = alphafetch

# Compilador padrão 
CXX ?= g++


CXXFLAGS = -std=c++20 -Wall -Wextra -Os -s -Iinclude


SRC_DIR = src
OBJ_DIR = obj


PREFIX = /usr/local


VERDE = \033[32m
RESET = \033[0m


SRC = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/modules/*.cpp)


OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))


all: $(TARGET)


$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "$(VERDE)[✓] $(TARGET) compilado com sucesso!$(RESET)"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@


$(OBJ_DIR)/modules/%.o: $(SRC_DIR)/modules/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@


$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)


clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "$(VERDE)[✓] Limpeza concluída.$(RESET)"


install: $(TARGET)
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f $(TARGET) $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/$(TARGET)
	@echo "$(VERDE)[✓] O alphafetch foi instalado com sucesso em $(PREFIX)/bin/ !$(RESET)"

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(TARGET)
	@echo "$(VERDE)[✓] O alphafetch foi removido do sistema.$(RESET)"

.PHONY: all clean install uninstall