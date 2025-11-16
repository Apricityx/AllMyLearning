#include <iostream>
#include <string>
#include "network.h"
#include <cmath>
#pragma execution_character_set("utf-8")
#include <windows.h>
const double R = 6371.0;
// 将角度转换为弧度
double degToRad(double deg) {
    return deg * (M_PI / 180.0);
}

double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    // 将经纬度转换为弧度
    lat1 = degToRad(lat1);
    lon1 = degToRad(lon1);
    lat2 = degToRad(lat2);
    lon2 = degToRad(lon2);

    // 计算纬度和经度的差值
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    // Haversine公式
    double a = std::sin(dlat / 2) * std::sin(dlat / 2) +
               std::cos(lat1) * std::cos(lat2) *
               std::sin(dlon / 2) * std::sin(dlon / 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    // 计算距离
    return R * c;
}

struct pos {
    double latitude;
    double longitude;

    pos(): latitude(0), longitude(0) {
    }

    pos(double lon, double lat) {
        longitude = lon;
        latitude = lat;
    }

    double getDistance(const pos &p) const {
        return calculateDistance(p.latitude, p.longitude, this->latitude, this->longitude);
    }
};


int main() {
    // 选择的节点：
    // 计信院
    SetConsoleOutputCP(65001); // 设置控制台输出为 UTF-8
    network<std::string> nw;
    map<string, pos> pos_map;
    pos_map["计算机信息与科学学院"] = pos(106.424379, 29.82264);
    pos_map["23教"] = pos(106.422059, 29.820891);
    pos_map["26教"] = pos(106.422074, 29.822729);
    pos_map["28教"] = pos(106.423153, 29.823441);
    pos_map["29教"] = pos(106.423222, 29.822752);
    pos_map["地理科学学院"] = pos(106.422907, 29.821563);
    pos_map["梅园食堂"] = pos(106.423287, 29.824382);
    pos_map["外国语学院"] = pos(106.421291, 29.821574);
    pos_map["西塔学院"] = pos(106.424224, 29.824438);
    pos_map["物理科学与技术学院"] = pos(106.42531, 29.822908);
    pos_map["数学与统计学院"] = pos(106.426053, 29.823643);
    pos_map["杏园食堂"] = pos(106.426138, 29.825065);
    pos_map["志成大厦"] = pos(106.425539, 29.825293);
    pos_map["橘园文化广场"] = pos(106.424172, 29.825542);
    pos_map["化学化工学院"] = pos(106.421072, 29.822818);
    pos_map["外国语学院"] = pos(106.421307, 29.82146);
    pos_map["中心图书馆"] = pos(106.424612, 29.820514);
    pos_map["弘光垒实验室"] = pos(106.423847, 29.823754);
    pos_map["橘园食堂"] = pos(106.426031, 29.826622);
    pos_map["第二运动场"] = pos(106.427518, 29.825451);
    pos_map["砺剑班训练场"] = pos(106.420632, 29.820361);
    std::list<std::pair<std::string, std::string> > edges;
    edges.push_back(std::make_pair("26教", "28教"));
    edges.push_back(std::make_pair("26教", "29教"));
    edges.push_back(std::make_pair("28教", "29教"));
    edges.push_back(std::make_pair("28教", "梅园食堂"));
    edges.push_back(std::make_pair("29教", "计算机信息与科学学院"));
    edges.push_back(std::make_pair("29教", "地理科学学院"));
    edges.push_back(std::make_pair("29教", "弘光垒实验室"));
    edges.push_back(std::make_pair("29教", "西塔学院"));
    edges.push_back(std::make_pair("计算机信息与科学学院", "物理科学与技术学院"));
    edges.push_back(std::make_pair("数学与统计学院", "物理科学与技术学院"));
    edges.push_back(std::make_pair("地理科学学院", "23教"));
    edges.push_back(std::make_pair("外国语学院", "23教"));
    edges.push_back(std::make_pair("中心图书馆", "29教"));
    edges.push_back(std::make_pair("外国语学院", "化学化工学院"));
    // edges.push_back(std::make_pair("29教", "化学化工学院"));
    edges.push_back(std::make_pair("26教", "化学化工学院"));
    edges.push_back(std::make_pair("外国语学院", "砺剑班训练场"));
    edges.push_back(std::make_pair("化工化学学院", "26教"));
    edges.push_back(std::make_pair("化工化学学院", "梅园食堂"));
    edges.push_back(std::make_pair("梅园食堂", "化工化学学院"));
    edges.push_back(std::make_pair("梅园食堂", "橘园文化广场"));
    edges.push_back(std::make_pair("志成大厦", "西塔学院"));
    edges.push_back(std::make_pair("志成大厦", "橘园文化广场"));
    edges.push_back(std::make_pair("志成大厦", "杏园食堂"));
    edges.push_back(std::make_pair("第二运动场", "杏园食堂"));
    edges.push_back(std::make_pair("橘园食堂", "杏园食堂"));
    edges.push_back(std::make_pair("橘园食堂", "第二运动场"));
    edges.push_back(std::make_pair("中心图书馆", "计算机信息与科学学院"));
    edges.push_back(std::make_pair("中心图书馆", "地理科学学院"));
    edges.push_back(std::make_pair("计算机信息与科学学院", "地理科学学院"));
    edges.push_back(std::make_pair("数学与统计学院", "弘光垒实验室"));
    // 打印所有的边
    for (auto &e: edges) {
        std::cout << e.first << " -> " << e.second << std::endl;
    }
    for (auto &p: pos_map) {
        nw.insert_vertex(p.first);
    }
    for (auto &e: edges) {
        nw.insert_edge(e.first, e.second, pos_map[e.first].getDistance(pos_map[e.second]));
        nw.insert_edge(e.second, e.first, pos_map[e.second].getDistance(pos_map[e.first]));
    }
    const auto path = nw.get_shortest_path("26教", "中心图书馆");
    for (auto &p: path.first) {
        std::cout << p << " -> ";
    }
    std::cout << "distance: " << path.second << std::endl;
    pos pos1(106.424083,29.822488);
    pos pos2(106.424301,29.824509);
    std::cout<<pos1.getDistance(pos2)<<std::endl;
    return 0;
    // const string SENTINEL = "***";
    //
    // const string PROMPT =
    //         "Please enter two vertices and a weight; the sentinel is ";
    //
    // const string SHORTEST_PATH_MESSAGE =
    //         "\n\n\nThe shortest path and its total weight are\n\n";
    //
    // string v1, v2;
    //
    // double weight;
    //
    // network<string> my_network; //vertex type is string; string compare is default for storing
    //
    // cout << PROMPT << SENTINEL << endl;
    // cin >> v1;
    // while (v1 != SENTINEL) {
    //     cin >> v2 >> weight;
    //     my_network.insert_edge(v1, v2, weight);
    //     cout << PROMPT << SENTINEL << endl;
    //     cin >> v1;
    // } // getting edges
    //
    // string start, finish;
    //
    // cout << "\nPlease enter start and finish vertices" << endl;
    // cin >> start >> finish;
    // cout << endl;
    //
    // pair<list<string>, double> result = my_network.get_shortest_path(start, finish);
    // list<string>::iterator vertex_list_itr;
    //
    // if (result.first.empty() == true)
    //     cout << "Path does not exist!" << endl;
    // else {
    //     for (vertex_list_itr = result.first.begin();
    //          vertex_list_itr != result.first.end();
    //          vertex_list_itr++)
    //         cout << *vertex_list_itr << endl;
    //     cout << endl << "End of shortest path from " << start << " to " << finish << endl;
    //     cout << "Path weight = " << result.second << endl;
    // }
    //
    // return 0;
}
