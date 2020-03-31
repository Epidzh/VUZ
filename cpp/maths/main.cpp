#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <exception>
#include <algorithm>
#include <queue>
#include <list>
// #include "Structs.h"
// #include "Graph.h"
// #include "Label_struct.h"
#include <iostream>
struct flight_edge

{

    int cost;

    int duration;

    flight_edge(int c = 0, int d = 0) : cost(c), duration(d) {}

    friend std::ostream &operator<<(std::ostream &stream, const flight_edge &edge);
};

struct airport

{

    std::string name;

    std::string abr;

    double lon;

    double lat;

    airport(std::string name_ = "", std::string abr_ = "",

            double lon_ = 0, double lat = 0)

        : name(name_), abr(abr_), lon(lon_), lat(lat)
    {
    }

    friend std::ostream &operator<<(std::ostream &stream,

                                    const airport &a);
};

std::ostream &operator<<(std::ostream &stream, const flight_edge &edge)

{

    stream << edge.cost << ' ' << edge.duration << '\n';

    return stream;
}

std::istream &operator>>(std::istream &stream, flight_edge &edge)

{

    stream >> edge.cost >> edge.duration;

    return stream;
}

std::ostream &operator<<(std::ostream &stream, const airport &a)

{

    stream << a.abr << ' ' << a.lon << ' ' << a.lat << ' ' << a.name;

    return stream;
}

std::istream &operator>>(std::istream &stream, airport &a)

{

    std::string str;

    stream >> a.abr >> a.lon >> a.lat;

    std::getline(stream, str);

    a.name = str;

    return stream;
}

namespace Graph
{

template <typename D, typename E>
class graph;

template <typename D, typename E, typename Tmember>
struct string_functor;

template <typename D, typename E>
class vertex
{
public:
    using edge = std::pair<size_t, E>;
    using iterator = typename std::vector<edge>::iterator;
    template <typename A, typename B>
    friend class graph;

private:
    std::vector<edge> edges;
    size_t id_;
    D data_;

public:
    vertex(size_t i, D d) : edges{}, id_{i}, data_{d} {}
    D &data() { return data_; }
    size_t id() const { return id_; }
    size_t size() const { return edges.size(); }
    edge &operator[](size_t n) { return edges[n]; }
    edge operator[](size_t n) const { return edges[n]; }
    void add_edge(const edge &edge) { edges.push_back(edge); }

    void print_edges()
    {
        for (auto it = edges.begin(); it != edges.end(); ++it)
            std::cout << it->second << '\n';
    }
    friend inline std::ostream &operator<<(std::ostream &stream,
                                           const vertex &v)
    {
        return stream << v.data_;
    }
    size_t find_adj_vertex(size_t index)
    {
        for (size_t j = 0; j < edges.size(); ++j)
        {
            if (index == edges[j].first)
                return j;
        }
        throw std::exception();
    }

    template <typename Tmember>
    auto weight(Tmember member) -> decltype(data_.*member)
    {
        return data_.*member;
    }

    template <typename Tmember>
    auto e_weight(Tmember member, size_t i) -> decltype((edges[i].second).*member)
    {
        return (edges[i].second).*member;
    }
};

template <typename D, typename E>
class graph
{
public:
    const int INF = 0x3f3f3f3f;
    using iterator = typename std::vector<vertex<D, E>>::iterator;

    vertex<D, E> &operator[](size_t i) { return adj_list[i]; }
    vertex<D, E> operator[](size_t i) const { return adj_list[i]; }
    void add_vertex(vertex<D, E> v) { adj_list.push_back(v); }
    void add_edge(E edge, vertex<D, E> &from, vertex<D, E> &to);

    size_t findVertexById(size_t id);

    size_t size() const { return adj_list.size(); }
    void read(const std::string &s, const std::string &t);
    void write(std::string s);
    void print_path(const std::vector<size_t> &v);

    void sort()
    {
        std::sort(adj_list.begin(), adj_list.end(),
                  [](const vertex<D, E> &v1, const vertex<D, E> &v2) { return v1.id() < v2.id(); });
    }
    size_t findMaxVertex()
    {
        auto i = std::max_element(adj_list.begin(), adj_list.end(),
                                  [](const vertex<D, E> &v1, const vertex<D, E> &v2) { return v1.size() < v2.size(); });
        if (size() == 0)
            throw std::exception();
        return i->size();
    }
    template <typename Tmember1, typename Tmember2>
    void print_results(Tmember1 vertexField, Tmember2 edgeField);

    template <typename Tmember>
    size_t findVertexByData(const std::string s, Tmember member);

    template <typename Tmember>
    std::vector<size_t> shortest_path(size_t s, size_t t, Tmember member)
    {
        std::vector<int> dist(size(), INF);
        std::vector<size_t> pred(size());
        dist[s] = 0;
        std::vector<char> pset(size());
        for (size_t i = 0; i < size(); ++i)
        {
            int minimum = INF;
            size_t minv;
            for (size_t j = 0; j < size(); ++j)
            {
                if (!pset[j] && dist[j] <= minimum)
                {
                    minimum = dist[j];
                    minv = j;
                }
            }

            if (minimum == INF || minv == t)
                break;
            pset[minv] = 1;
            for (size_t k = 0; k < adj_list[minv].size(); ++k)
            {
                size_t m = adj_list[minv][k].first;
                if (!pset[m] && dist[m] >
                                    dist[minv] + adj_list[minv].e_weight(member, k))
                {
                    dist[m] = dist[minv] + adj_list[minv].e_weight(member, k);
                    pred[m] = minv;
                }
            }
        }
        std::vector<size_t> pa;
        if (dist[t] == INF)
        {
            std::cout << "Пути нет." << std::endl;
            return pa;
        }
        std::cout << "Результат выполнения алгоритма Дейкстры:" << std::endl;
        for (size_t i = t; i != s; i = pred[i])
        {
            pa.push_back(i);
        }
        pa.push_back(s);
        std::reverse(pa.begin(), pa.end());
        for (int i = 0; i < pa.size() - 1; ++i)
        {
            size_t k = adj_list[pa[i]].find_adj_vertex(pa[i + 1]);
            std::cout << adj_list[pa[i]].e_weight(member, k) << std::endl;
        }
        std::cout << "Суммарный вес оптимального пути: " << dist[t] << std::endl;
        return pa;
    }

    template <typename Tmember>
    void bellman_ford(size_t s, size_t t, Tmember member)
    {
        std::vector<int> dist(adj_list.size(), INF);
        dist[s] = 0;

        while (true)
        {
            bool temp = false;
            for (int j = 0; j < adj_list.size(); ++j)
            {
                for (int k = 0; k < adj_list[j].size(); ++k)
                {
                    size_t m = adj_list[j][k].first;
                    if (dist[j] < INF)
                    {
                        if (dist[m] > dist[j] + adj_list[j].e_weight(member, k))
                        {
                            dist[m] = dist[j] + adj_list[j].e_weight(member, k);
                            temp = true;
                        }
                    }
                }
            }
            if (!temp)
                break;
        }
        std::cout << "Результат выполнения алгоритма Беллмана - Форда:" << std::endl;
        std::cout << "Суммарный вес оптимального пути: ";
        if (dist[t] >= INF)
            std::cout << 0 << std::endl;
        else
            std::cout << dist[t] << std::endl;
    }

private:
    std::vector<vertex<D, E>> adj_list;
    void add_edge(E edge, size_t i, size_t j);
};

template <typename D, typename E>
void graph<D, E>::write(std::string s)
{
    std::ofstream out(s);
    for (auto it = adj_list.begin(); it != adj_list.end(); ++it)
    {
        if (it->size())
        {
            out << it->id() << ' ' << it->size() << '\n';
            for (auto i = it->edges.begin(); i != it->edges.end(); ++i)
            {
                out << adj_list[i->first].id() << ' ' << i->second;
            }
        }
    }
    out.close();
}

template <typename D, typename E>
void graph<D, E>::print_path(const std::vector<size_t> &v)
{
    if (v.size() > 0)
    {
        std::cout << "Длина оптимального пути: " << v.size() - 1 << std::endl;
        std::cout << "Кратчайший путь:" << std::endl;
    }
    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cout << adj_list[v[i]] << std::endl;
    }
}

template <typename D, typename E>
void graph<D, E>::read(const std::string &s, const std::string &t)
{
    std::ifstream in(s);
    size_t id{};
    D data{};
    while (in >> id)
    {
        in >> data;
        vertex<D, E> v(id, data);
        add_vertex(v);
    }

    in.close();
    in.open(t);
    size_t from{}, to{}, count{};
    E e{};
    while (in >> from)
    {
        size_t index = findVertexById(from);
        in >> count;
        for (size_t i = 0; i < count; ++i)
        {
            in >> to;
            in >> e;
            add_edge(e, index, findVertexById(to));
        }
    }
    in.close();
}

template <typename D, typename E>
void graph<D, E>::add_edge(E eVal, vertex<D, E> &from, vertex<D, E> &to)
{
    size_t fromIndex = findVertexById(from.id());
    if (fromIndex == adj_list.size())
        throw std::exception();
    size_t toIndex = findVertexById(to.id());
    if (toIndex == adj_list.size())
        throw std::exception();
    typename vertex<D, E>::edge e;
    e.first = toIndex;
    e.second = eVal;
    adj_list[fromIndex].add_edge(e);
}

template <typename D, typename E>
void graph<D, E>::add_edge(E eVal, size_t i, size_t j)
{
    typename vertex<D, E>::edge e;
    e.first = j;
    e.second = eVal;
    adj_list[i].add_edge(e);
}

template <typename D, typename E>
size_t graph<D, E>::findVertexById(size_t id)
{
    for (size_t i = 0; i < adj_list.size(); ++i)
        if (adj_list[i].id() == id)
            return i;
    return adj_list.size();
}

template <typename D, typename E>
template <typename Tmember>
size_t graph<D, E>::findVertexByData(const std::string s, Tmember member)
{
    string_functor<D, E, Tmember> find_s{};
    iterator i{adj_list.end()};
    for (auto it = adj_list.begin(); it != adj_list.end(); ++it)
    {
        if (find_s(*it, member, s))
            i = it;
    }
    if (i != adj_list.end())
    {
        return std::distance(adj_list.begin(), i);
    }
    else
    {
        throw std::exception();
    }
}

template <typename D, typename E, typename Tmember>
struct string_functor
{
    bool operator()(vertex<D, E> &v, Tmember member, std::string s)
    {
        auto a = v.weight(member);
        std::string::size_type n = a.find(s);
        return n != std::string::npos;
    }
};

template <typename D, typename E>
template <typename Tmember1, typename Tmember2>
void graph<D, E>::print_results(Tmember1 vertexField, Tmember2 edgeField)
{
    std::string s{}, t{};
    std::cout << "Введите начало маршрута: " << std::endl;
    std::getline(std::cin, s);
    std::cout << "Введите конечный пункт назначения: " << std::endl;
    std::getline(std::cin, t);
    auto i = findVertexByData(s, vertexField);
    auto j = findVertexByData(t, vertexField);
    std::vector<size_t> v = shortest_path(i, j, edgeField);
    print_path(v);
    bellman_ford(i, j, edgeField);
}
} // namespace Graph

struct label;
using p_label = std::shared_ptr<label>;
using edge = std::pair<size_t,flight_edge>;
using namespace Graph;

struct label
{
    label(const flight_edge& sum, const p_label pr = nullptr,
           const size_t res = 0, int num = 0):
        sum_of_res{sum},
        p_pred_label{pr},
        resident_vertex{res},
        n{num},
        is_dominated{false},
        is_processed{false} {}
    flight_edge sum_of_res;
    p_label p_pred_label;
    size_t resident_vertex;
    bool is_dominated;
    bool is_processed;
    int n;
};

class p_greater{
    public:
        bool operator()( const std::shared_ptr<label> l1,
                        const std::shared_ptr<label> l2 )
        {
          if( l1->sum_of_res.cost < l2->sum_of_res.cost )
            return false;
          if( l1->sum_of_res.cost == l2->sum_of_res.cost )
            return l1->sum_of_res.duration > l2->sum_of_res.duration;
          return true;
        }
};



bool dominance(const label& label1, const label& label2)
{
        return label1.sum_of_res.cost <= label2.sum_of_res.cost
         && label1.sum_of_res.duration <= label2.sum_of_res.duration;
};

bool ref_function(const graph<airport, flight_edge>& g, label& new_label,
                   const label& old_label,const edge& ed, const int max_duration)
{
        new_label.sum_of_res.cost = old_label.sum_of_res.cost + ed.second.cost;
        new_label.sum_of_res.duration = old_label.sum_of_res.duration +
                             ed.second.duration;
        return new_label.sum_of_res.duration <= max_duration ? true : false;
};

void shortest_path_rc(const graph<airport, flight_edge>& g, size_t s,
                      size_t t, int max_duration,
                      std::vector<std::vector<size_t>>& pareto_optimal_solutions,
                      std::vector<flight_edge>& optimal_resource_containers)
{
std::priority_queue<p_label, std::vector<p_label>, p_greater> unprocessed_labels;
int label_num = 0;
bool feasible = true;
flight_edge start(0, 0);
p_label first_label{new label(start, nullptr, s, label_num++)};
unprocessed_labels.push(first_label);
std::vector<std::list<p_label>> vec_of_labels( g.size() );
vec_of_labels[s].push_back(first_label);
std::vector<typename std::list<p_label>::iterator>
                vec_last_valid_pos_for_dominance( g.size() );
for( size_t i = 0; i <  g.size(); ++i )
    vec_last_valid_pos_for_dominance[i] = vec_of_labels[i].begin();
std::vector<bool> b_vec_vertex_already_checked_for_dominance( g.size(), false );
while( unprocessed_labels.size() ){
    p_label cur_label = unprocessed_labels.top();
    unprocessed_labels.pop();
    if( !cur_label->is_dominated )
    {
        int i_cur_resident_vertex_num = cur_label->resident_vertex;
        std::list<p_label>& list_labels_cur_vertex =
        vec_of_labels[i_cur_resident_vertex_num];
        if(list_labels_cur_vertex.size() >=2  )
        {
            typename std::list<p_label>::iterator outer_iter =
            list_labels_cur_vertex.begin();
            bool outer_iter_at_or_beyond_last_valid_pos_for_dominance = false;
            while( outer_iter != list_labels_cur_vertex.end() )
            {
                p_label cur_outer_plabel = *outer_iter;
                typename std::list<p_label>::iterator inner_iter = outer_iter;
                if( !outer_iter_at_or_beyond_last_valid_pos_for_dominance &&
                   outer_iter ==
            vec_last_valid_pos_for_dominance[i_cur_resident_vertex_num])
                {
                    outer_iter_at_or_beyond_last_valid_pos_for_dominance = true;
                }


                if(
    !b_vec_vertex_already_checked_for_dominance[i_cur_resident_vertex_num] ||
          outer_iter_at_or_beyond_last_valid_pos_for_dominance)
                {
                    ++inner_iter;
                }
                else
                {
                    inner_iter =
            vec_last_valid_pos_for_dominance[i_cur_resident_vertex_num];
                    ++inner_iter;
                }
                bool outer_iter_erased = false;
                while( inner_iter != list_labels_cur_vertex.end() )
                {
                    p_label cur_inner_plabel = *inner_iter;
                    if(dominance( cur_outer_plabel->sum_of_res,
                                 cur_inner_plabel->sum_of_res))
                    {
                        typename std::list<p_label>::iterator buf = inner_iter;
                        ++inner_iter;
                        list_labels_cur_vertex.erase( buf );
                        if(cur_inner_plabel->is_processed)
                        {
                            cur_inner_plabel.reset();
                        }
                        else
                            cur_inner_plabel->is_dominated = true;
                        continue;
                    }
                    else
                        ++inner_iter;
                    if(dominance(cur_inner_plabel->sum_of_res,
                                 cur_outer_plabel->sum_of_res))
                    {
                        typename std::list<p_label>::iterator buf = outer_iter;
                        ++outer_iter;
                        list_labels_cur_vertex.erase( buf );
                        outer_iter_erased = true;
                        if( cur_outer_plabel->is_processed )
                        {
                            cur_outer_plabel.reset();
                        }
                        else
                            cur_outer_plabel->is_dominated = true;
                        break;
                    }
                }
                if( !outer_iter_erased )
                    ++outer_iter;

            }
        if( list_labels_cur_vertex.size() > 1 )
                vec_last_valid_pos_for_dominance[i_cur_resident_vertex_num]=
                (--(list_labels_cur_vertex.end()));
            else
                vec_last_valid_pos_for_dominance[i_cur_resident_vertex_num]=
                list_labels_cur_vertex.begin();    b_vec_vertex_already_checked_for_dominance[i_cur_resident_vertex_num]=true;
        }
    }

    if( !cur_label->is_dominated )
    {
        cur_label->is_processed = true;
        size_t cur_vertex = cur_label->resident_vertex;
        size_t  v_size = g[cur_vertex].size();
        for( size_t i = 0; i < v_size; ++i )
        {
            feasible = true;
            edge e = g[cur_vertex][i];
            p_label new_label{new label(start, cur_label, e.first, label_num++)};
            feasible = ref_function(g, *new_label, *cur_label, e, max_duration);
            if( feasible )
            {
              vec_of_labels[new_label->resident_vertex].push_back(new_label);
              unprocessed_labels.push( new_label );
            }
        }
    }
}

std::list<p_label> labels = vec_of_labels[t];
typename std::list<p_label>::const_iterator csi = labels.begin();
typename std::list<p_label>::const_iterator csi_end = labels.end();

if( labels.size() )
{
    for(; csi != csi_end; ++csi)
    {
        std::vector<size_t> cur_pareto_optimal_path;
        p_label p_cur_label = *csi;
        optimal_resource_containers.push_back(p_cur_label->sum_of_res);
        while( p_cur_label->n != 0 )
        {
           cur_pareto_optimal_path.push_back( p_cur_label->resident_vertex );
           p_cur_label = p_cur_label->p_pred_label;
        }
        cur_pareto_optimal_path.push_back(p_cur_label->resident_vertex);
        std::reverse(cur_pareto_optimal_path.begin(),
                               cur_pareto_optimal_path.end());
        pareto_optimal_solutions.push_back( cur_pareto_optimal_path );
    }
}

}

using namespace Graph;

void menu()

{

    std::cout << "1. Поиск маршрута по названию пунктов назначения." << std::endl;
    std::cout << "2. Поиск маршрута по аббревиатуре." << std::endl;
    std::cout << "3. Поиск оптимального маршрута по времени." << std::endl;
    std::cout << "4. Поиск оптимального маршрута по стоимости." << std::endl;
    std::cout << "5. Поиск оптимального маршрута по обоим параметрам спомощью priority_queue." << std::endl;
    std::cout << "6. Выход из программы." << std::endl;
}

int main()

{

    setlocale(0, "Russian");

    graph<airport, flight_edge> g{};

    g.read("1.txt", "2.txt");

    std::string s{}, t{};

    int var{};

    do
    {

        var = 0;

        menu();

        do
        {

            std::cout << "Выберите пункт меню:";

            std::string temp;

            std::getline(std::cin, temp);

            try
            {

                var = std::stoi(temp);
            }

            catch (std::invalid_argument)

            {

                std::cout << "Ошибка. Введите правильный пункт." << std::endl;
            }

        } while (var < 1 || var > 6);

        switch (var)
        {

        case 1:

        {

            try
            {
                g.print_results(&airport::name, &flight_edge::cost);
            }

            catch (std::exception)
            {

                std::cout << "Такого пункта не существует!" << std::endl;

                break;
            }

            break;
        }

        case 2:

        {

            try
            {
                g.print_results(&airport::abr, &flight_edge::cost);
            }

            catch (std::exception)
            {

                std::cout << "Такого пункта не существует!" << std::endl;

                break;
            }

            break;
        }

        case 3:

        {

            try
            {
                g.print_results(&airport::name, &flight_edge::duration);
            }

            catch (std::exception)
            {

                std::cout << "Такого пункта не существует!" << std::endl;

                break;
            }

            break;
        }

        case 4:

        {

            try
            {
                g.print_results(&airport::name, &flight_edge::cost);
            }

            catch (std::exception)
            {

                std::cout << "Такого пункта не существует!" << std::endl;

                break;
            }

            break;
        }

        case 5:

        {

            try
            {

                std::string s{}, t{}, tmp{};

                int time{0};

                std::cout << "Введите начало маршрута: " << std::endl;

                std::getline(std::cin, s);

                std::cout << "Введите конечный пункт назначения: " << std::endl;

                std::getline(std::cin, t);

                std::cout << "Введите ограничение по времени: " << std::endl;

                std::getline(std::cin, tmp);

                time = std::stoi(tmp);

                std::vector<std::vector<size_t>> v;

                std::vector<flight_edge> rc;

                shortest_path_rc(g, g.findVertexByData(s, &airport::name),

                                 g.findVertexByData(t, &airport::name), time, v, rc);

                if (v.size() == 0)

                    std::cout << "Пути, удовлетворяющего ограничениям не найдено." << std::endl;

                for (int i = 0; i < v.size(); ++i)

                {

                    std::cout << "Длина оптимального пути: " << v[i].size() - 1 << std::endl;

                    std::cout << "Кратчайший путь:" << std::endl;

                    for (size_t j = 0; j < v[i].size(); ++j)

                    {

                        std::cout << g[v[i][j]] << std::endl;
                    }

                    std::cout << "Длительность пути: " <<

                        rc[i].duration << std::endl;

                    std::cout << "Цена пути: " << rc[i].cost << std::endl;
                }
            }

            catch (std::exception)

            {

                std::cout << "Такого пункта не существует!" << std::endl;

                break;
            }

            catch (std::invalid_argument)

            {

                std::cout << "Ошибка. Введите правильное время." << std::endl;

                break;
            }
        }

        break;
        }

    } while (var != 6);

    return 0;
}
