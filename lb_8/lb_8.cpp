#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <deque>
using namespace std;
struct node_queue {
	int index;
	struct node_queue* next;
};

struct node {
	int index;
	struct node* next_node;
};

struct Graph {
	vector<node*>vertexes;
};

struct node_queue* head_queue = NULL;
struct node_queue* last_queue = NULL;
void BFS_list_struct(Graph* G, int start);
void BFS_list(Graph* G, int start);
void add_el_queue(int index);
void del_queue();
void BFS_struct(vector<vector<int>>& M, int start);
void BFS(vector<vector<int>>& M, int start);
void print_G(Graph* G);
void add_el(struct Graph* G, int vertex, int new_index);

int main()
{
	clock_t start, end;
	setlocale(LC_ALL, "Russian");
	Graph G;
	int sizeM = 0, number = 0;
	cout << "Введите количество вершин у графа:\n";
	cin >> sizeM;
	G.vertexes.resize(sizeM, nullptr);
	cout << "Матрица смежности:\n";
	vector <vector<int>> M(sizeM, vector<int>(sizeM, 0));
	for (int i = 0; i < sizeM; i++) {
		for (int j = 0; j < sizeM; j++) {
			if (i == j) {
				M[i][j] = 0;
			}
			else {
				M[i][j] = rand() % 2;
			}
			printf("%3d ", M[i][j]);
			if (M[i][j]) {
				if (i == j) {
					continue;
				}
				add_el(&G, i, j);
			}
		}
		cout << '\n';
	}
	cout << "Список смежности:\n";
	print_G(&G);
	do {
		cout << "Введите номер вершины(-1 - выйти):\n";
		cin >> number;
		number--;

		cout << "Обход графа в ширину с использованием библиотеки очереди:\n";
		cout << "Для матрицы:\n";
		start = clock();
		BFS(M, number);
		end = clock();
		double time_spend = (double)(end - start) / CLOCKS_PER_SEC;
		cout << "\nВремя работы: " << time_spend << "\n";

		cout << "Для списка смежности:\n";
		start = clock();
		BFS_list(&G, number);
		end = clock();
		time_spend = (double)(end - start) / CLOCKS_PER_SEC;
		cout << "\nВремя работы: " << time_spend << "\n\n";


		cout << "Обход графа в ширину с использованием структуры очереди:\n";
		cout << "Для матрицы:\n";
		start = clock();
		BFS_struct(M, number);
		end = clock();
		time_spend = (double)(end - start) / CLOCKS_PER_SEC;
		cout << "\nВремя работы: " << time_spend << "\n";

		cout << "Для списка смежности:\n";
		start = clock();
		BFS_list_struct(&G, number);
		end = clock();
		time_spend = (double)(end - start) / CLOCKS_PER_SEC;
		cout << "\nВремя работы: " << time_spend << "\n\n";

	} while (number != -1);



}

void BFS_struct(vector<vector<int>>& M, int start) {
	vector<bool> visited(M.size(), false);
	add_el_queue(start);
	visited[start] = true;

	while (head_queue != NULL) {
		int current = head_queue->index;
		del_queue();
		cout << current + 1 << " ";

		for (int i = 0; i < M.size(); i++) {
			if (M[current][i] == 1 && !visited[i]) {
				add_el_queue(i);
				visited[i] = true;
			}
		}
	}
}
void BFS(vector<vector<int>>& M, int start) {
	vector<bool> visited(M.size(), false);
	deque<int> q;

	q.push_back(start);
	visited[start] = true;

	while (!q.empty()) {
		int current = q.front();
		q.pop_front();
		cout << current + 1 << " ";
		for (int i = 0; i < M.size(); i++) {
			if (M[current][i] == 1 && !visited[i]) {
				q.push_back(i);
				visited[i] = true;
			}
			int counter = 0;
		}
	}
}

void BFS_list_struct(Graph* G, int start) {
	vector <bool> visited(G->vertexes.size(), false);
	head_queue = nullptr;
	last_queue = nullptr;
	add_el_queue(start);
	visited[start] = true;
	while (head_queue != nullptr) {
		int current = head_queue->index;
		del_queue();
		cout << current + 1 << " ";
		node* tmp = G->vertexes[current];
		while (tmp != nullptr) {
			if (visited[tmp->index] == false) {
				add_el_queue(tmp->index);
				visited[tmp->index] = true;
			}
			tmp = tmp->next_node;
		}
	}
}
void BFS_list(Graph* G, int start) {
	vector<bool> visited(G->vertexes.size(), false);
	deque<int> q;

	q.push_back(start);
	visited[start] = true;

	while (!q.empty()) {
		int current = q.front();
		q.pop_front();
		cout << current + 1 << " ";

		node* tmp = G->vertexes[current];
		while (tmp != nullptr) {
			if (!visited[tmp->index]) {
				q.push_back(tmp->index);
				visited[tmp->index] = true;
			}
			tmp = tmp->next_node;
		}
	}
}

void add_el(struct Graph* G, int vertex, int new_index) {
	node* p = (node*)malloc(sizeof(node));
	p->index = new_index;
	if (G->vertexes[vertex] == nullptr) {
		G->vertexes[vertex] = p;
		p->next_node = nullptr;
	}
	else {
		node* tmp = G->vertexes[vertex];
		while (tmp->next_node != nullptr) {
			tmp = tmp->next_node;
		}
		tmp->next_node = p;
		p->next_node = nullptr;
	}
}
void print_G(Graph* G) {
	for (int i = 0; i < G->vertexes.size(); i++) {
		node* tmp = G->vertexes[i];
		cout << "Вершина " << i + 1 << ": ";
		while (tmp != nullptr) {
			cout << tmp->index + 1 << " ";
			tmp = tmp->next_node;
		}
		cout << '\n';
	}
}

/* Последовательное добавление в список элемента (в конец) */
void add_el_queue(int index) {
	struct node_queue* pointer = NULL;
	if ((pointer = (node_queue*)malloc(sizeof(struct node_queue))) == NULL) {
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}
	pointer->index = index;
	pointer->next = NULL;

	if (head_queue == NULL && pointer != NULL) { // если списка нет, то устанавливаем голову списка
		head_queue = pointer;
		last_queue = pointer;
	}
	else if (head_queue != NULL && pointer != NULL) { // список уже есть, то вставляем в конец
		last_queue->next = pointer;
		last_queue = pointer;
	}
	return;
}

/* Удаление элемента с начала очереди */
void del_queue() {
	if (head_queue == NULL) {
		printf("Список пуст\n");
		return;
	}
	struct node_queue* struc = head_queue;
	head_queue = head_queue->next;
	free(struc);
}