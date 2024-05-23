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
    graph.add_edge("A", "B", 2.5);
    graph.add_edge("A", "C", 2.5);
    graph.add_edge("B", "C", 3.0);
    graph.add_edge("C", "D", 4.0);
    graph.add_edge("D", "E", 5.0);
    graph.add_edge("E", "A", 1.0);

    // Удаление вершины
    if (graph.remove_vertex("B")) {
        std::cout << "Vertex B has been removed" << std::endl;
    }

    // Проверка наличия ребра
    if (graph.has_edge("A", "B")) {
        std::cout << "Edge (A, B) exists" << std::endl;
    }
    else {
        std::cout << "Edge (A, B) does not exist" << std::endl;
    }

    // Получение списка исходящих ребер из вершины
    std::cout << "Edges exiting from A: ";
    for (const auto& edge : graph.exiting_edges("A")) {
        std::cout << "(" << edge.from << ", " << edge.to << ", " << edge.distance << ") ";
    }
    std::cout << std::endl;

    // Получение списка входящих ребер в вершину
    std::cout << "Edges incoming to D: ";
    for (const auto& edge : graph.incoming_edges("D")) {
        std::cout << "(" << edge.from << ", " << edge.to << ", " << edge.distance << ") ";
    }
    std::cout << std::endl;

    // Удаление ребра
    graph.remove_edge("E", "A");
    std::cout << "Edge (E, A) has been removed" << std::endl;
    

    // Получение количества вершин
    std::cout << "Order of the graph: " << graph.order() << std::endl;

    // Получение степени вершины
    std::cout << "Degree of vertex A: " << graph.degree("A") << std::endl;


    // Создание экземпляра графа
    Graph<std::string, double> graph2;

    // Добавление вершин
    graph2.add_vertex("A");
    graph2.add_vertex("B");
    graph2.add_vertex("C");
    graph2.add_vertex("D");
    graph2.add_vertex("E");

    // Добавление ребер
    graph2.add_edge("A", "B", 5.0);
    graph2.add_edge("A", "C", 3.0);
    graph2.add_edge("B", "D", 2.0);
    graph2.add_edge("B", "E", 4.0);
    graph2.add_edge("C", "D", 6.0);
    graph2.add_edge("D", "E", 1.0);

    // Вывод списка вершин
    graph2.print_vertices();

    std::cout << std::endl;
    // Вывод списка ребер
    graph2.print_edges();

    // Поиск кратчайшего пути
    std::vector<typename Graph<std::string, double>::Edge> path = graph2.shortest_path("A", "E");
    std::cout << "Shortest path from A to E: ";
    for (const auto& edge : path) {
        std::cout << edge.from << " -> " << edge.to << " (" << edge.distance << ") ";
    }
    std::cout << std::endl;

    // Определение самой удаленной вершины
    std::string farthest_vertex = graph2.find_farthest_vertex();
    std::cout << "The farthest vertex is: " << farthest_vertex << std::endl;



    return 0;
}