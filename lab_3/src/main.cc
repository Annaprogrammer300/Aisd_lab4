//#include "../include/graf.h"
#include "graf.cc"



int main() {
    // Создание экземпляра графа
    Graph<std::string, double> graph;

    // Добавление вершин
    graph.add_vertex("A");
    graph.add_vertex("B");
    graph.add_vertex("C");
    graph.add_vertex("D");
    graph.add_vertex("E");

    // Добавление ребер
    graph.add_edge("A", "B", 5.0);
    graph.add_edge("A", "C", 3.0);
    graph.add_edge("B", "D", 2.0);
    graph.add_edge("B", "E", 4.0);
    graph.add_edge("C", "D", 6.0);
    graph.add_edge("D", "E", 1.0);

    // Вывод списка вершин
    graph.print_vertices();
    std::cout << std::endl;
    // Вывод списка ребер
    graph.print_edges();

    // Поиск кратчайшего пути
    std::vector<typename Graph<std::string, double>::Edge> path = graph.shortest_path("A", "E");
    std::cout << "Shortest path from A to E: ";
    for (const auto& edge : path) {
        std::cout << edge.from << " -> " << edge.to << " (" << edge.distance << ") ";
    }
    std::cout << std::endl;

    // Определение самой удаленной вершины
    std::string farthest_vertex = graph.find_farthest_vertex();
    std::cout << "The farthest vertex is: " << farthest_vertex << std::endl;

	

    return 0;
}