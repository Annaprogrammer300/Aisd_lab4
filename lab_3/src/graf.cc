#include "../include/graf.h"


template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_vertex(const Vertex& v) const {
    return std::find(_vertices.begin(), _vertices.end(), v) != _vertices.end();
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::add_vertex(const Vertex& v) {
    if (has_vertex(v)) throw std::invalid_argument("[add_vertex] the vertex already exists");
    _vertices.push_back(v);
    _edges[v] = { };
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_vertex(const Vertex& v) {
    auto& it = std::find(_vertices.begin(), _vertices.end(), v);
    if (it == _vertices.end()) return false;
    _vertices.erase(it);
    _edges.erase(v);
    for (auto& vertex : _vertices) {
        auto& edges = _edges.at(vertex);
        edges.erase(std::remove_if(edges.begin(), edges.end(), [v](const Edge& e) {return e.to == v; }), edges.end());
    }
    return true;
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::add_edge(const Vertex& from, const Vertex& to, const Distance& dist) {
    if (has_edge({ from, to, dist })) throw std::invalid_argument("[add_edge] the edge already exists");

    auto& edges = _edges[from];
    edges.push_back({ from, to, dist });
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_edge(const Edge& e) {
    if (!has_edge(e)) return false;
    auto& edges = _edges.at(e.from);

    edges.erase(std::remove_if(edges.begin(), edges.end(), [e](const Edge& edge)
        { return (e.from == edge.from) && (e.to == edge.to) && (e.distance == edge.distance); }), edges.end());

    return true;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_edge(const Vertex& from, const Vertex& to) {
    if (!has_edge(from, to)) return false;
    auto& edges = _edges.at(from);

    edges.erase(std::remove_if(edges.begin(), edges.end(), [&](const Edge& e) { return (e.from == from) && (e.to == to); }), edges.end());

    return false;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_edge(const Edge& e) const {
    auto& edges = _edges.at(e.from);
    for (const auto& edge : edges) {
        if (edge.to == e.to && (abs(e.distance - edge.distance) < DBL_EPSILON)) return true;
    }
    return false;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_edge(const Vertex& from, const Vertex& to) const {
    auto& edges = _edges.at(from);
    for (const auto& edge : edges) {
        if (edge.to == to) return true;
    }
    return false;
}

//Получаем итераторы, указывающие на начало и конец вектора вершин графа.
template<typename Vertex, typename Distance>
std::pair<typename std::vector<Vertex>::iterator, typename std::vector<Vertex>::iterator> Graph<Vertex, Distance>::vertices() {
    return { _vertices.begin(), _vertices.end() };
}

//возвращает пару итераторов, указывающих на начало и конец вектора ребер, исходящих из заданной вершины
template<typename Vertex, typename Distance>
std::pair<typename std::vector<Vertex>::iterator, typename std::vector<Vertex>::iterator> Graph<Vertex, Distance>::edges(const Vertex& v) {
    return { exiting_edges(v).begin(), exiting_edges(v).end() };
}

template<typename Vertex, typename Distance>
std::vector<typename Graph<Vertex, Distance>::Edge> Graph<Vertex, Distance>::exiting_edges(const Vertex& v) const {
    if (!has_vertex(v)) throw std::invalid_argument("[exiting_edges] there is no such vertex in the graph");

    return _edges.at(v);
}

//возвращает вектор всех ребер, входящих в заданную вершину
template<typename Vertex, typename Distance>
std::vector<typename Graph<Vertex, Distance>::Edge> Graph<Vertex, Distance>::incoming_edges(const Vertex& v) const {
    if (!has_vertex(v)) throw std::invalid_argument("[incoming_edges] there is no such vertex in the graph");
    std::vector<Edge> edges;
    for (auto& vertex : _vertices) {
        for (auto& edge : _edges.at(vertex))
            if (edge.to == v) edges.push_back(edge);
    }

    return edges;
}

template<typename Vertex, typename Distance>
size_t Graph<Vertex, Distance>::order() const {
    return _vertices.size();
}

//(количество ребер) для заданной вершины
template<typename Vertex, typename Distance>
size_t Graph<Vertex, Distance>::degree(const Vertex& v) const {
    if (!has_vertex(v)) throw std::invalid_argument("[degree] there is no such vertex in the graph");

    return incoming_edges(v).size() + exiting_edges(v).size();
}

template<typename Vertex, typename Distance> // поиск кратчайшего пути Алгоритм Дейкстры
std::vector<typename Graph<Vertex, Distance>::Edge> Graph<Vertex, Distance>::shortest_path(const Vertex& start, const Vertex& end) const {
    if (!has_vertex(start) || !has_vertex(end)) throw std::invalid_argument("[shortest_path] one or two vertices do not exist in the graph");

    std::unordered_map<Vertex, Distance> distance;
    std::unordered_map<Vertex, Vertex> prev;

    for (const Vertex& vertex : _vertices) {
        distance[vertex] = std::numeric_limits<Distance>::max();
    }
    distance[start] = 0;

    std::priority_queue<std::pair<Distance, Vertex>, std::vector<std::pair<Distance, Vertex>>, std::greater<std::pair<Distance, Vertex>>> pq;
    pq.push(std::make_pair(0, start));

    while (!pq.empty()) {
        Vertex current = pq.top().second;
        pq.pop();

        if (current == end) {
            // Восстановление пути
            std::vector<Edge> result;
            Vertex current_vertex = end;
            while (current_vertex != start) {
                auto it = std::find_if(_edges.at(prev[current_vertex]).begin(), _edges.at(prev[current_vertex]).end(),
                    [&](const Edge& e) { return e.to == current_vertex; });
                result.push_back(*it);
                current_vertex = prev[current_vertex];
            }
            std::reverse(result.begin(), result.end());
            return result;
        }

        for (const auto& edge : exiting_edges(current)) {
            Distance new_distance = distance[current] + edge.distance;
            if (new_distance < distance[edge.to]) {
                distance[edge.to] = new_distance;
                prev[edge.to] = current;
                pq.push(std::make_pair(new_distance, edge.to));
            }
        }
    }

    // Если конечная вершина недостижима
    throw std::runtime_error("[shortest_path] no path found");
}

template<typename Vertex, typename Distance>
std::vector<Vertex> Graph<Vertex, Distance>::walk(const Vertex& start_vertex) const { // обход в ширину
    if (!has_vertex(start_vertex)) throw std::invalid_argument("[walk] there is no such vertex in the graph");

    std::vector<Vertex> result;//посещенные вершины
    std::unordered_map<Vertex, Color> colors;

    for (const auto& vertex : _vertices) {
        colors[vertex] = Color::White;
    }

    std::queue <Vertex> queue;
    queue.push(start_vertex);
    colors[start_vertex] = Color::Gray;

    while (!queue.empty()) {
        Vertex current_vertex = queue.front();
        queue.pop();

        for (auto& edge : _edges.at(current_vertex)) {
            if (colors[edge.to] == Color::White) {
                queue.push(edge.to);
                colors[edge.to] = Color::Gray;
            }
        }
        result.push_back(current_vertex);
        colors[current_vertex] = Color::Black;

    }
    return result;
}

template<typename Vertex, typename Distance>
Distance Graph<Vertex, Distance>::length_shortest_path(const Vertex& start, const Vertex& end) const {
    std::vector<Edge> edges = shortest_path(start, end);
    Distance len = 0;
    for (const auto& edge : edges) {
        len += edge.distance;
    }
    return len;
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::print_vertices() const {
    std::cout << "Vertices: [ ";
    for (const Vertex& vertex : _vertices) {
        if (vertex != _vertices.back()) std::cout << vertex << ", ";
        else std::cout << vertex << " ]";
    }
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::print_edges() const {
    std::cout << "Edges: " << std::endl;
    for (const Vertex& vertex : _vertices) {
        for (const Edge& edge : _edges.at(vertex)) {
            std::cout << edge.from << " -> " << edge.to << "(" << edge.distance << ")" << std::endl;
        }
    }
}

template<typename Vertex, typename Distance>
Vertex Graph<Vertex, Distance>::find_farthest_vertex() {
    Vertex farthest_vertex{};//Вершина, наиболее удалённая от других вершин.
    Distance max_avg_distance = 0;//Максимальное среднее расстояние от какой-либо вершины до её соседей.

    for (const auto& vertex : _vertices) {
        // Вычисляем среднее расстояние от текущей вершины до её соседей
        Distance avg_distance = 0;
        size_t num_neighbors = 0;
        for (const auto& edge : exiting_edges(vertex)) {
            avg_distance += length_shortest_path(vertex, edge.to);
            num_neighbors++;
        }
        if (num_neighbors > 0) {
            avg_distance /= num_neighbors;
        }

        // Обновляем максимальное среднее расстояние и запоминаем текущую вершину
        if (avg_distance > max_avg_distance) {
            max_avg_distance = avg_distance;
            farthest_vertex = vertex;
        }
    }

    return farthest_vertex;
}