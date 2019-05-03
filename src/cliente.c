#include "cliente.h"

#include <stdlib.h>
#include <stdio.h>

void* cliente_thread(void* arg) {
	printf("%d", *(int *)arg);
	return NULL;
}