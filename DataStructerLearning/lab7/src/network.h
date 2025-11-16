#ifndef NETWORK
#define NETWORK
#include <hash_map>
#include <iostream>
#include <limits>
#include <map>
#include <list>
#include <queue>
#include <unordered_map>

using namespace std;

//template<class vertex, class Compare = less<vertex> >
// vertex是顶点的类型，比如string，int等
template<class vertex>
class network {
    //node in the adjacency list, a to-vetex, an associated weight
    // 定义了一个目标顶点to和他的权重weight的一对关系
    // 实质上是定义了一个边
    // 此结构体用于表示到某个顶点的边的权重
    struct vertex_weight_pair {
        vertex to;
        double weight;

        // Postcondition: this vertex_weight_pair has been initialized
        //                from x and y.
        vertex_weight_pair(const vertex &x, const double &y) {
            to = x;
            weight = y;
        } // two-parameter constructor

        // Postcondition: true has been returned if this
        //                vertex_weight_pair is less than x.
        //                Otherwise, false has been returned.
        bool operator>(const vertex_weight_pair &p) const {
            return weight > p.weight;
        } // operator>
    }; // class vertex_weight_pair
    // 将这种一对的关系存入一个链表中
    typedef typename std::list<vertex_weight_pair> adj_list;
    typedef typename adj_list::iterator adj_list_itr; //adjacency list iterotor
    typedef typename std::map<vertex, adj_list> ver_adj_map; // 表示了一个顶点和他的邻接顶点的关系
    typedef typename ver_adj_map::iterator ver_adj_map_itr;

protected:
    ver_adj_map ver_adj; // {vertex, adj_list} // 顶点和邻接顶点的关系


public:
    // Postcondition: this network is empty.
    network() {
    }

    // Postcondition: the number of vertices in this network has been
    //                returned.
    unsigned int size() {
        return ver_adj.size();
    } // method size


    // Postcondition: true has been returned if this network contains no
    //                vertices.  Otherwise, false has been returned.
    bool empty() {
        return size() == 0;
    } // method empty


    // Postcondition: true has been returned if this network contains the
    //                edge <v1, v2>.  Otherwise, false has been returned.
    // 用于判断两点之间是否有边
    bool contains_edge(const vertex &v1, const vertex &v2) {
        ver_adj_map_itr itr = ver_adj.find(v1);
        if (itr == ver_adj.end() || ver_adj.find(v2) == ver_adj.end()) //not both exist
            return false;

        adj_list_itr list_itr;

        for (list_itr = ((*itr).second).begin(); //itr points to a pair in ver_adj_map: first:vertex, second:adj_list
             list_itr != ((*itr).second).end();
             list_itr++)
            if ((*list_itr).to == v2) //vertex-weight-struct
                return true;
        return false;
    } // method contains_edge


    // Postcondition: if v is already in this network, false has been
    //                returned. Otherwise, the map with v and an empty list
    //                has been added to this network and true has been
    //                returned.
    // 添加一个顶点，这个顶点对象需要在外部创建好，然后用这个函数添加到网络中
    // 这个顶点对象需要定义和哪些顶点有边的关系，以及这些边的权重
    // 网络中所有的顶点都是由顶点及其邻接顶点的关系组成的
    bool insert_vertex(const vertex &v) {
        return ver_adj.insert(
            pair<vertex, list<vertex_weight_pair> > // 若v已经存在，返回false，不会初始化该顶点
            (v, list<vertex_weight_pair>()) //empty list // 将(一个顶点，一个空的邻接顶点链表)插入到网络中
        ).second; //map insert returns pair<iterator,bool>
    } // method insert_vertex


    // Postcondition: if the edge <v1, v2> is already in this network false
    //                has been returned. Otherwise, that edge with the
    //                given weight has been inserted in this network and
    //                true has been returned.
    bool insert_edge(const vertex &v1, const vertex &v2, const double &weight) {
        if (contains_edge(v1, v2))
            return false;
        insert_vertex(v1); //may already exist
        insert_vertex(v2); //may already exist
        (*ver_adj.find(v1)).second.push_back(vertex_weight_pair(v2 /* to */, weight));
        // ver_adj.find(v1)返回的是一个pair，pair的第二个元素表示的是一个邻接顶点链表，将v2和权重插入到这个链表中
        return true;
    } // method insert_edge

    /*=======================================DIJKSTRA'S ALGORITHM==========================================================*/
    // Postcondition: the shortest path from v1 to v2 and its total weight
    //                have been returned; if such a path is found,
    //				  returns the list of vertices on the shortest path
    //				  and the total weight of the shortest path;
    //				  otherwise, returns an empty list and the value -1.0
    pair<list<vertex>, double> get_shortest_path(const vertex &v1, const vertex &v2) {
        const int size = this->size();
        // 最短距离数组 <节点编号，距离>
        unordered_map<vertex, double> distance;
        // 前驱节点数组 <当前节点，前驱节点>
        unordered_map<vertex, vertex> prev;
        // 已经确定的节点集合
        unordered_map<vertex, bool> S;
        // 初始化，将所有节点的距离设置为无穷大
        for (auto &it: ver_adj) {
            distance[it.first] = numeric_limits<double>::max();
            // distance[it.first] = numeric_limits<double>::max();
        }
        // 起点到自己的距离为0
        distance[v1] = 0;
        // 工具函数，获取最小距离的节点
        auto const get_shortest_vertex = [&distance,&S]() -> vertex {
            // 最小堆：{当前距离, 节点编号}
            std::priority_queue<pair<double, vertex>, vector<pair<double, vertex> >, greater<> > heap;
            // 添加所有未确定的节点到heap中
            for (auto &it: distance) {
                if (!S[it.first]) {
                    heap.push({it.second, it.first});
                }
            }
            return heap.top().second;
        };
        // 工具函数，更新节点
        auto update_vertex = [&distance, &prev, &S](const auto &vf,
                                                    list<network<vertex>::vertex_weight_pair> update_list) {
            S[vf] = true;
            // std::cout << vf << "节点开始更新，其邻接节点有：";
            // for (auto edge: update_list) {
            //     std::cout << edge.to << " ";
            // }
            // std::cout << std::endl;
            for (auto edge: update_list) {
                // todo fix. prev[vf] == edge.to
                // 如果prev为edge.to,则跳过
                if (prev[vf] == edge.to) {
                    continue;
                }
                // 如果新的距离较小
                if (distance[vf] + edge.weight < distance[edge.to]) {
                    std::cout << "Update distance of " << edge.to << " from " << distance[edge.to] << " to " << distance
                            [vf] + edge.weight << std::endl;
                    distance[edge.to] = distance[vf] + edge.weight;
                    // 更新prev
                    std::cout << "更新prev：" << edge.to << "->" << vf << std::endl;
                    prev[edge.to] = vf;
                }
            }
        };
        // 循环直到所有节点都被确定
        auto vf = v1; // vf为当前节点
        while (true) {
            update_vertex(vf, ver_adj.find(vf)->second);
            // 更新当前节点的毗邻节点的距离，除了当前的prev节点
            // 更新vf为最小的
            vf = get_shortest_vertex();
            if (vf == v2) {
                update_vertex(vf, ver_adj.find(vf)->second);
                break;
            }
        }
        auto ve = v2;
        auto vs = v1;
        list<vertex> path;
        while (ve != vs) {
            path.push_back(ve);
            ve = prev[ve];
            // cout << "寻址：" << prev[v2] << endl;
        }
        path.push_back(v1);
        return make_pair(path, distance[v2]);
        // 每次从未确定的顶点中选择距离起点最近的一个顶点，将其加入 S，并更新与其相邻顶点的最短距离。
    } // method get_shortest_path
}; // class network

#endif
