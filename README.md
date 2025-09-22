# Calculadora Gráfica em C com GTK4

![Calculadora](https://imgur.com/cFr4NXT) Projeto de uma calculadora totalmente funcional com interface gráfica (GUI) desenvolvida em linguagem C pura e a biblioteca moderna GTK4. Este projeto foi criado como um exercício prático para aprender sobre desenvolvimento de aplicações desktop, separação de lógica e interface, e compilação com bibliotecas externas.

---

## 🚀 Funcionalidades

* Operações aritméticas básicas: Adição, Subtração, Multiplicação e Divisão.
* Suporte para números decimais.
* Interface gráfica intuitiva e responsiva.
* Tratamento de erro para divisão por zero.
* Lógica de cálculo separada da camada de apresentação (interface).

---

## 🛠️ Tecnologias Utilizadas

* **Linguagem:** C
* **Biblioteca Gráfica:** GTK4
* **Interface Builder:** Glade / Cambalache (para o arquivo `interface.ui`)
* **Compilador:** GCC (através do ambiente MinGW-w64 no Windows)

---

## ⚙️ Como Compilar e Executar

Este projeto foi desenvolvido e testado no Windows utilizando o ambiente MSYS2, mas pode ser compilado em Linux com pequenas adaptações.

### Pré-requisitos

* **No Windows:**
    * [MSYS2](https://www.msys2.org/) instalado.
    * No terminal MSYS2 MinGW x64, instale as dependências:
        ```bash
        pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-gtk4
        ```

* **No Linux (Debian/Ubuntu):**
    ```bash
    sudo apt update
    sudo apt install build-essential libgtk-4-dev
    ```

### Compilação

1.  Clone o repositório:
    ```bash
    git clone [https://github.com/](https://github.com/)[SEU USUARIO DO GITHUB]/[NOME-DO-SEU-REPOSITORIO].git
    ```
2.  Navegue até a pasta do projeto:
    ```bash
    cd [NOME-DO-SEU-REPOSITORIO]
    ```
3.  Compile o programa usando o `gcc` e o `pkg-config`:
    ```bash
    gcc main.c calculadora_logica.c -o minha_calculadora $(pkg-config --cflags --libs gtk4)
    ```

### Execução

Após a compilação, execute o programa gerado:

```bash
./minha_calculadora
