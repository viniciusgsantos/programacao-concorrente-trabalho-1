#include "pizzeria.h"
#include "queue.h"
#include "helper.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

pthread_mutex_t mutex_pegar_mesas;
sem_t mesas_desocupadas;

void pizzeria_init(int tam_forno, int n_pizzaiolos, int n_mesas,
                   int n_garcons, int tam_deck, int n_grupos) {
	pthread_mutex_init(&mutex_pegar_mesas, NULL);
	sem_init(&mesas_desocupadas, 0, n_mesas);
}

void pizzeria_close() {
}

void pizzeria_destroy() {
	pthread_mutex_destroy(&mutex_pegar_mesas);
	sem_destroy(&mesas_desocupadas);
}

void pizza_assada(pizza_t* pizza) {
}

int pegar_mesas(int tam_grupo) {
	int mesas = ceil((double) tam_grupo / 4.0);

	pthread_mutex_lock(&mutex_pegar_mesas);
	for(int i = 0; i < mesas; i++) {
		sem_wait(&mesas_desocupadas);
	}
	pthread_mutex_unlock(&mutex_pegar_mesas);

    return 0;
}

void garcom_tchau(int tam_grupo) {
	int mesas = tam_grupo / 4;
	if(tam_grupo % 4 != 0) {
		mesas++;
	}
	for(int i = 0; i < mesas; i++) {
		sem_post(&mesas_desocupadas);
	}


	printf("Grupo de %d pessoas deu tchau\n", tam_grupo);
}

void garcom_chamar() {
}

void fazer_pedido(pedido_t* pedido) {
}

int pizza_pegar_fatia(pizza_t* pizza) {
    return -1; // erro: não fui implementado (ainda)!
}
