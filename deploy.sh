#!/bin/bash

# --- Configuração ---
# O nome do seu executável final
EXE_NAME="calculadora.exe"
# O nome da pasta de destino que será criada
# Linha nova e correta
DEST_DIR="/c/Users/Enzo/Desktop/Calculadora_Portatil"

# --- Início do Script ---
echo "🚀 Iniciando o processo de deploy da Calculadora..."

# Limpa a pasta de destino antiga, se existir
if [ -d "$DEST_DIR" ]; then
    echo "🧹 Limpando a pasta de destino antiga..."
    rm -rf "$DEST_DIR"
fi

# Cria a pasta de destino limpa
echo "📁 Criando a pasta de destino: $DEST_DIR"
mkdir -p "$DEST_DIR"

# Compila o executável com a flag -mwindows (opcional, mas recomendado)
echo "👨‍💻 Compilando a versão final do executável..."
gcc main.c calculadora_logica.c -o "$EXE_NAME" $(pkg-config --cflags --libs gtk4) -mwindows

# Copia o executável principal para a pasta de destino
echo "➡️  Copiando $EXE_NAME para $DEST_DIR..."
cp "$EXE_NAME" "$DEST_DIR/"

# A mágica acontece aqui: encontra e copia todas as DLLs necessárias
echo "🔍 Encontrando e copiando as DLLs necessárias..."
ldd "$EXE_NAME" | grep "/mingw64/bin" | awk '{print $3}' | xargs -I {} cp {} "$DEST_DIR/"

# Copia as pastas de recursos essenciais do GTK
echo "🎨 Copiando recursos do GTK (temas, ícones, esquemas)..."
# Cria a estrutura de pastas dentro do diretório de destino
mkdir -p "$DEST_DIR/lib"
mkdir -p "$DEST_DIR/share"

# Copia as pastas de forma recursiva (-r)
cp -r /mingw64/share/glib-2.0 "$DEST_DIR/share/"
cp -r /mingw64/share/gtk-4.0 "$DEST_DIR/share/"
cp -r /mingw64/share/icons "$DEST_DIR/share/"
cp -r /mingw64/lib/girepository-1.0 "$DEST_DIR/lib/"

echo "✅ Processo concluído com sucesso!"
echo "Sua calculadora portátil está pronta na pasta: $DEST_DIR"