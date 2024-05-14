#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void absolute(int x, int* y) {
    if (x >= 0)
        *y = x;
    else
        *y = -x;
}

int main(void) {
    int a = 0, res = 0;  // No modificar esta declaración
    // --- No se deben declarar variables nuevas ---
    a = -10;
    absolute(a, &res);
    printf("%d\n", res);
    assert(res >= 0 && (res == a || res == -a));
    return EXIT_SUCCESS;
}

/*
c)
int *y es similar a un parámetro de tipo in/out, ya que puede tanto modificarse
con asignaciones del tipo *y = ..., como leerse con expresiones del tipo *y. En
este caso particular, la variable nunca se lee, por lo que se la puede
considerar como un parámetro de tipo out.

En general, la sintaxis de C solo nos ofrece variables de tipo in, y de tipo
in/out (pasando punteros).
*/
