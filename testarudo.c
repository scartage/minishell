#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void signal_handler(int signal) {
    if (signal == SIGINT) {
        printf("haha, fuck you, I wont close.\n");
    }
}

int main() {
    signal(SIGINT, signal_handler);
    while (1)
        sleep(10000);
}





// Función para intercambiar los datos de dos nodos en la lista enlazada
void swapNodes(t_list *node1, t_list *node2) {
    t_env_var *temp_env_var = (t_env_var *)node1->content;
    node1->content = node2->content;
    node2->content = temp_env_var;
}

// Función para ordenar una lista enlazada de estructuras t_env_var por nombre
void ordenarListaPorNombre(t_list *head) {
    t_list *actual = head;

    while (actual != NULL) {
        t_list *siguiente = actual->next;

        while (siguiente != NULL) {
            t_env_var *env_var_actual = (t_env_var *)actual->content;
            t_env_var *env_var_siguiente = (t_env_var *)siguiente->content;

            // Compara los nombres y actualiza si es necesario
            if (strcmp(env_var_actual->name, env_var_siguiente->name) > 0) {
                swapNodes(actual, siguiente);
            }

            siguiente = siguiente->next;
        }

        actual = actual->next;
    }
}

int main() {
    // Crear una lista enlazada con estructuras t_env_var
    t_list *envs = NULL;

    // Agregar nodos a la lista (t_env_var)
    // ...

    // Llamar a la función para ordenar la lista por nombre
    ordenarListaPorNombre(envs);

    // Ahora "envs" está ordenada alfabéticamente según los nombres de las variables de entorno.

    // Puedes iterar sobre la lista y hacer lo que necesites.
    
    return 0;
}