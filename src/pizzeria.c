#include "pizzeria.h"
#include "queue.h"
#include "helper.h"
#include "cliente.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

pthread_mutex_t mutex_pegar_mesas, mutex_indice_cliente, mutex_indice_pizzaiolo;
sem_t mesas_desocupadas, deck_livres, deck_ocupados;

pedido_t* deck;

int indice_pizzaiolo, indice_cliente, tam_deck_;

void pizzeria_init(int tam_forno, int n_pizzaiolos, int n_mesas,
                   int n_garcons, int tam_deck, int n_grupos) {

	deck = malloc(sizeof(pedido_t) * tam_deck);

	tam_deck_ = tam_deck;

	pthread_mutex_init(&mutex_pegar_mesas, NULL);
	pthread_mutex_init(&mutex_indice_cliente, NULL);
	pthread_mutex_init(&mutex_indice_pizzaiolo, NULL);

	sem_init(&mesas_desocupadas, 0, n_mesas);
	sem_init(&deck_livres, 0, tam_deck);
	sem_init(&deck_ocupados, 0, 0);
}

void pizzeria_close() {
}

void pizzeria_destroy() {
	free(deck);

	pthread_mutex_destroy(&mutex_pegar_mesas);
	pthread_mutex_destroy(&mutex_indice_cliente);
	pthread_mutex_destroy(&mutex_indice_pizzaiolo);

	sem_destroy(&mesas_desocupadas);
	sem_destroy(&deck_livres);
	sem_destroy(&deck_ocupados);
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

	// pthread_t cliente;

	// int a = 78;
	// pthread_create(&cliente, NULL, cliente_thread, (void *) &a);

	// pthread_join(cliente, NULL);

    return 0;
}

void garcom_tchau(int tam_grupo) {
	int mesas = ceil((double) tam_grupo / 4.0);
	for(int i = 0; i < mesas; i++) {
		sem_post(&mesas_desocupadas);
	}
	printf("Grupo de %d pessoas deu tchau\n", tam_grupo);
}

void garcom_chamar() {
}

void fazer_pedido(pedido_t* pedido) {
	sem_wait(&deck_livres);
	pthread_mutex_lock(&mutex_indice_cliente);
	indice_cliente = (indice_cliente + 1) % tam_deck_;
	deck[indice_cliente] = *pedido;
	pthread_mutex_unlock(&mutex_indice_cliente);
	sem_post(&deck_ocupados);
}

int pizza_pegar_fatia(pizza_t* pizza) {
    return -1; // erro: não fui implementado (ainda)!
}
