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

    return 0;
}