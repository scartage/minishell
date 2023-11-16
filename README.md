# Minishell

## Descripción
Minishell es un proyecto que imita funcionalidades básicas de un shell UNIX. Este shell personalizado permite la ejecución de comandos, manejo de redirecciones, pipes, señales, y más, proporcionando una experiencia similar a la de shells como bash.

## Características
- **Prompt Interactivo:** Espera la entrada de comandos del usuario.
- **Historial de Comandos:** Mantiene un historial de los comandos ejecutados.
- **Ejecución de Comandos:** Busca y ejecuta el ejecutable correcto basado en la variable PATH o mediante rutas relativas o absolutas.
- **Manejo de Señales:** Implementa el manejo de ctrl-C, ctrl-D y ctrl-\.
- **Redirecciones y Pipes:**
  - `<` para redirigir la entrada.
  - `>` para redirigir la salida.
  - `<<` para el input hasta encontrar un delimitador.
  - `>>` para redirigir la salida en modo append.
  - `|` para conectar la salida de un comando con la entrada del siguiente.
- **Variables de Entorno:** Gestiona la expansión de variables de entorno.
- **Estado de Salida:** `$?` se expande al estado de salida del último comando en la pipeline.
- **Built-ins Implementados:**
  - `echo` con opción `-n`.
  - `cd` con rutas relativas o absolutas.
  - `pwd` sin opciones.
  - `export` sin opciones.
  - `unset` sin opciones.
  - `env` sin opciones o argumentos.
  - `exit` sin opciones.

## Beneficios Educativos
Este proyecto es una excelente oportunidad para:
- **Entender el Funcionamiento Interno de los Shells:** Aprender cómo los shells interpretan y ejecutan comandos, manejan el entorno de usuario y comunican con el sistema operativo.
- **Practicar Programación en C:** Mejorar habilidades en C, especialmente en áreas como manejo de memoria, procesos, y señales.
- **Gestión de Procesos y Señales:** Aprender sobre la creación y gestión de procesos, así como el manejo de señales en un entorno UNIX.
- **Desarrollo de Habilidades de Depuración y Resolución de Problemas:** Resolver desafíos complejos relacionados con la interpretación de comandos y la gestión de estados.

## Uso
Para utilizar Minishell, clona el repositorio y compila el código:

1- Descargar/clonar el repositorio

```git clone https://github.com/scartage/minishell.git```

2- Acceder al repositorio

```cd Minishell```

3- Compilar

```make```

4- Ya podrás ejecutar el programa

```./minishell```

