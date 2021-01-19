package com.knox.graph;

import java.util.List;

public interface Graph<V, W> {

    int edgesSize();

    int vertexSize();

    void addVertex(V v);

    void addEdge(V from, V to, W weight);

    void addEdge(V from, V to);

    void removeVertex(V v);

    void removeEdge(V from, V to);

    // 广度优先搜索
    void bfs(V begin, VertexVisitor<V> visitor);

    // 深度优先搜索
    void dfs(V begin, VertexVisitor<V> visitor);

    List<V> topologicSort();

    static interface VertexVisitor<V> {
        boolean visit(V value);
    }
}
