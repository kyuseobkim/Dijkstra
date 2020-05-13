#include <algorithm>
#include <vector>

#include "graph.h"
#include "shortest_path.h"

#include "gtest/gtest.h"

using namespace std;

namespace dijkstra {
namespace {

class GraphTest : public ::testing::Test {
     protected:
        void SetUp() override {
            g3.add(0, 1);
        }
        // void TearDown() override { }

        Graph g1 {0, 10};
        Graph g2 {1, 10};
        Graph g3 {0.5, 10};

};

TEST_F(GraphTest, NoEdges) {
    EXPECT_EQ(g1.V(), 10);
    EXPECT_EQ(g1.E(), 0);
}

TEST_F(GraphTest, FullyConnected) {
    EXPECT_EQ(g2.V(), 10);
    EXPECT_EQ(g2.E(), 45);
}

TEST_F(GraphTest, GetEdgeValue) {
    double v = g1.get_edge_value(0, 5);
    EXPECT_EQ(g1.get_edge_value(0, 5), v);
    g1.set_edge_value(0, 5, 10);
    EXPECT_EQ(g1.get_edge_value(0, 5), 10);
}

TEST_F(GraphTest, Neighbors) {
    EXPECT_TRUE(g3.adjacent(0, 1));
    EXPECT_TRUE(g3.adjacent(1, 0));
    vector<int> n = g3.neighbors(0);
    EXPECT_GE(n.size(), 1);
    EXPECT_NE(find(n.begin(), n.end(), 1), n.end());
}

class PathTest : public ::testing::Test {
     protected:
        void SetUp() override {
            g3.add(0, 1);
            g3.set_edge_value(0, 1, 0.1);
        }
        // void TearDown() override { }

        Graph g3 {0, 10};
        ShortestPath sp {g3};
};

TEST_F(PathTest, PathSize) {
    EXPECT_TRUE(g3.adjacent(0, 1));
    EXPECT_TRUE(g3.adjacent(1, 0));
    vector<int> n = g3.neighbors(0);
    EXPECT_GE(n.size(), 1);
    EXPECT_NE(find(n.begin(), n.end(), 1), n.end());
    EXPECT_EQ(g3.get_edge_value(0, 1), 0.1);
    EXPECT_EQ(g3.get_edge_value(1, 0), 0.1);

    EXPECT_EQ(sp.path_size(0, 0), 0);
    EXPECT_EQ(sp.path_size(0, 1), 0.1);

    vector<int> path = sp.path(0, 1);
    ASSERT_EQ(path.size(), 2);
    EXPECT_EQ(path[0], 0);
    EXPECT_EQ(path[1], 1);
}


TEST_F(PathTest, SimplePath) {
    g3.add(0, 2);
    g3.set_edge_value(0, 2, 5);
    g3.add(1, 2);
    g3.set_edge_value(1, 2, 4);

    EXPECT_EQ(sp.path_size(0, 2), 4.1);
    EXPECT_EQ(sp.path_size(1, 2), 4);

    vector<int> path = sp.path(0, 2);
    ASSERT_EQ(path.size(), 3);
    EXPECT_EQ(path[0], 0);
    EXPECT_EQ(path[1], 1);
    EXPECT_EQ(path[2], 2);

    path = sp.path(1, 2);
    ASSERT_EQ(path.size(), 2);
    EXPECT_EQ(path[0], 1);
    EXPECT_EQ(path[1], 2);

    path = sp.path(2, 0);
    ASSERT_EQ(path.size(), 3);
    EXPECT_EQ(path[0], 2);
    EXPECT_EQ(path[1], 1);
    EXPECT_EQ(path[2], 0);

    g3.set_edge_value(0, 2, 4);
    g3.set_edge_value(1, 2, 5);

    EXPECT_EQ(sp.path_size(0, 2), 4);
    EXPECT_EQ(sp.path_size(1, 2), 4.1);

    path = sp.path(1, 2);
    ASSERT_EQ(path.size(), 3);
    EXPECT_EQ(path[0], 1);
    EXPECT_EQ(path[1], 0);
    EXPECT_EQ(path[2], 2);
}

}
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
