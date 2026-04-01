# Nome do executável final
TARGET = alphafetch

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Os -s -Iinclude

# Pastas
SRC_DIR = src
OBJ_DIR = obj

# Caminho de instalação padrão no Linux
PREFIX = /usr/local

# --- CORES PARA O TERMINAL ---
VERDE = \033[32m
RESET = \033[0m

# Busca todos os arquivos .cpp na pasta src e em src/modules/
SRC = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/modules/*.cpp)

# Gera a lista de arquivos .o dentro da pasta obj/ mantendo a estrutura
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

# Regra padrão
all: $(TARGET)

# Regra para linkar os arquivos objetos e gerar o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "$(VERDE)[✓] $(TARGET) compilado com sucesso!$(RESET)"

# Regra para compilar os arquivos .cpp da raiz de src
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para compilar os arquivos .cpp que estão dentro de src/modules
$(OBJ_DIR)/modules/%.o: $(SRC_DIR)/modules/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cria a pasta obj/ se ela não existir
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpa os arquivos gerados pela compilação
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "$(VERDE)[✓] Limpeza concluída.$(RESET)"

# Regra para instalar o binário no sistema
install: $(TARGET)
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f $(TARGET) $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/$(TARGET)
	@echo "$(VERDE)[✓] O alphafetch foi instalado com sucesso em $(PREFIX)/bin/ !$(RESET)"

# Regra para remover o binário do sistema
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(TARGET)
	@echo "$(VERDE)[✓] O alphafetch foi removido do sistema.$(RESET)"

.PHONY: all clean install uninstall