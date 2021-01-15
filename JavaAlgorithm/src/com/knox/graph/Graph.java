package com.knox.graph;

public interface Graph<V, W> {

    int edgesSize();

    int vertexSize();

    void addVertex(V vertex);

    void addEdge(V from, V to, W weight);

    void addEdge(V from, V to);

    void removeVertex(V vertex);

    void removeEdge(V from, V to);
}
