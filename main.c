#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <locale.h> // Não precisamos mais desta com a função custom_atof

#include "calculadora_logica.h"

// Função "força-bruta" para converter string para double, ignorando o sistema
double custom_atof(const char *s) {
    double resultado = 0.0;
    int apos_ponto = 0;
    double divisor = 10.0;
    int sinal = 1;

    if (*s == '-') {
        sinal = -1;
        s++;
    }

    while (*s) {
        if (*s >= '0' && *s <= '9') {
            if (apos_ponto) {
                resultado = resultado + (*s - '0') / divisor;
                divisor *= 10.0;
            } else {
                resultado = resultado * 10.0 + (*s - '0');
            }
        } else if (*s == '.') {
            apos_ponto = 1;
        }
        s++;
    }
    return resultado * sinal;
}


// Variáveis globais
static char buffer_display[100] = "0";
static double primeiro_numero = 0;
static char operacao_pendente = '\0';
static gboolean resetar_display = TRUE;

// --- Funções de Callback (Handlers dos botões) ---

void on_button_numero_clicked(GtkButton *button, gpointer user_data) {
    GtkLabel *display_label = GTK_LABEL(user_data);
    const char *texto_botao = gtk_button_get_label(button);

    if (resetar_display) {
        strcpy(buffer_display, "");
        resetar_display = FALSE;
    }
    if (strcmp(buffer_display, "0") == 0 && strcmp(texto_botao, ".") != 0) {
        strcpy(buffer_display, "");
    }
    if (strcmp(texto_botao, ".") == 0 && strchr(buffer_display, '.') != NULL) {
        return;
    }
    strcat(buffer_display, texto_botao);
    gtk_label_set_text(display_label, buffer_display);
}

void on_button_operacao_clicked(GtkButton *button, gpointer user_data) {
    primeiro_numero = custom_atof(buffer_display); // Usando nossa função
    operacao_pendente = gtk_button_get_label(button)[0];
    resetar_display = TRUE;
}

void on_button_clear_clicked(GtkButton *button, gpointer user_data) {
    GtkLabel *display_label = GTK_LABEL(user_data);
    strcpy(buffer_display, "0");
    primeiro_numero = 0;
    operacao_pendente = '\0';
    resetar_display = TRUE;
    gtk_label_set_text(display_label, buffer_display);
}

void on_button_equals_clicked(GtkButton *button, gpointer user_data) {
    GtkLabel *display_label = GTK_LABEL(user_data);
    if (operacao_pendente == '\0') return;

    double segundo_numero = custom_atof(buffer_display); // Usando nossa função
    double resultado = 0;

    switch (operacao_pendente) {
        case '+': resultado = somar(primeiro_numero, segundo_numero); break;
        case '-': resultado = subtrair(primeiro_numero, segundo_numero); break;
        case '*': resultado = multiplicar(primeiro_numero, segundo_numero); break;
        case '/': 
            if (segundo_numero == 0) {
                sprintf(buffer_display, "Erro");
                gtk_label_set_text(display_label, buffer_display);
                operacao_pendente = '\0';
                resetar_display = TRUE;
                return;
            }
            resultado = dividir(primeiro_numero, segundo_numero); 
            break;
    }
    
    sprintf(buffer_display, "%.6g", resultado);
    gtk_label_set_text(display_label, buffer_display);
    operacao_pendente = '\0';
    resetar_display = TRUE;
}

// --- Função de Ativação da Aplicação ---
static void activate(GtkApplication *app, gpointer user_data) {
    GtkBuilder *builder = gtk_builder_new_from_file("interface.ui");
    GtkWindow *window = GTK_WINDOW(gtk_builder_get_object(builder, "main_window"));
    GtkLabel *display_label = GTK_LABEL(gtk_builder_get_object(builder, "display_label"));

    GtkButton *btn;
    for (int i = 0; i <= 9; i++) {
        char btn_id[20];
        sprintf(btn_id, "button_%d", i);
        btn = GTK_BUTTON(gtk_builder_get_object(builder, btn_id));
        if (btn) g_signal_connect(btn, "clicked", G_CALLBACK(on_button_numero_clicked), display_label);
    }
    btn = GTK_BUTTON(gtk_builder_get_object(builder, "button_dot"));
    if (btn) g_signal_connect(btn, "clicked", G_CALLBACK(on_button_numero_clicked), display_label);
    btn = GTK_BUTTON(gtk_builder_get_object(builder, "button_plus"));
    if (btn) g_signal_connect(btn, "clicked", G_CALLBACK(on_button_operacao_clicked), display_label);
    btn = GTK_BUTTON(gtk_builder_get_object(builder, "button_minus"));
    if (btn) g_signal_connect(btn, "clicked", G_CALLBACK(on_button_operacao_clicked), display_label);
    btn = GTK_BUTTON(gtk_builder_get_object(builder, "button_multiply"));
    if (btn) g_signal_connect(btn, "clicked", G_CALLBACK(on_button_operacao_clicked), display_label);
    btn = GTK_BUTTON(gtk_builder_get_object(builder, "button_divide"));
    if (btn) g_signal_connect(btn, "clicked", G_CALLBACK(on_button_operacao_clicked), display_label);
    btn = GTK_BUTTON(gtk_builder_get_object(builder, "button_clear"));
    if (btn) g_signal_connect(btn, "clicked", G_CALLBACK(on_button_clear_clicked), display_label);
    btn = GTK_BUTTON(gtk_builder_get_object(builder, "button_equals"));
    if (btn) g_signal_connect(btn, "clicked", G_CALLBACK(on_button_equals_clicked), display_label);

    gtk_window_set_application(window, app);
    gtk_window_present(window);
    g_object_unref(builder);
}

// --- Função Principal ---
int main(int argc, char *argv[]) {
    // TESTE DE DEBUG DEFINITIVO
    //printf("\n>>> MODO DE DEBUG ATIVADO! SE ESTA MENSAGEM APARECEU, O CODIGO NOVO ESTA RODANDO. <<<\n\n");

    GtkApplication *app;
    int status;
    app = gtk_application_new("com.exemplo.calculadora", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}