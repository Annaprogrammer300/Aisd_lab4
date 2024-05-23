#ifndef LAB3_INCLUDE_GRAPH_H
#define LAB3_INCLUDE_GRAPH_H

#include <algorithm>
#include <cfloat>
#include <iostream>
#include <iterator>
#include <memory>
#include <queue>
#include <unordered_map>
#include <vector>

enum class Color { White, Gray, Black };

template<typename Vertex, typename Distance = double>
class Graph {
public:
    struct Edge {
        Vertex from, to;
        Distance distance;
    };

    bool has_vertex(const Vertex& v) const;
    void add_vertex(const Vertex& v);
    bool remove_vertex(const Vertex& v);

    bool has_edge(const Edge& e) const;
    bool has_edge(const Vertex& from, const Vertex& to) const;
    void add_edge(const Vertex& from, const Vertex& to, const Distance& dist);
    bool remove_edge(const Edge& e);
    bool remove_edge(const Vertex& from, const Vertex& to);

    std::pair<typename std::vector<Vertex>::iterator, typename std::vector<Vertex>::iterator> vertices();
    std::pair<typename std::vector<Vertex>::iterator, typename std::vector<Vertex>::iterator> edges(const Vertex& v);
    std::vector<Edge> exiting_edges(const Vertex& v) const;
    std::vector<Edge> incoming_edges(const Vertex& v) const;

    size_t order() const;
    size_t degree(const Vertex& v) const;

    std::vector<Edge> shortest_path(const Vertex& start, const Vertex& end) const;
    std::vector<Vertex> walk(const Vertex& start_vertex) const;
    Distance length_shortest_path(const Vertex& start, const Vertex& end) const;

    void print_vertices() const;
    void print_edges() const;
    Vertex find_farthest_vertex();

private:
    std::vector<Vertex> _vertices;
    std::unordered_map<Vertex, std::vector<Edge>> _edges;
};

#endif