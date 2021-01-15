package com.knox.graph;

import com.knox.tools.Asserts;

import java.util.*;

public class ListGraph<V, W> implements Graph<V, W> {

    private Map<V, Vertex<V, W>> vertices = new HashMap();
    private Set<Edge<V, W>> edges = new HashSet();

    @Override
    public int edgesSize() {
        return edges.size();
    }

    @Override
    public int vertexSize() {
        return vertices.size();
    }

    @Override
    public void addVertex(V vertex) {
        // 包含这个顶点, 直接返回
        if (vertices.containsKey(vertex)) return;
        vertices.put(vertex, new Vertex<>(vertex));
    }

    @Override
    public void addEdge(V from, V to, W weight) {
        Vertex<V, W> fromV = createVertexIfNotExists(from);
        Vertex<V, W> toV = createVertexIfNotExists(to);

        Edge<V, W> edge = new Edge(fromV, toV);
        edge.weight = weight;

        // set中不方便取元素, 所以先把set中旧的edge删除, 再添加新的edge, 让set中包含最新的edge
        if (edges.remove(edge)) { // 如果set中包含删除的对象, 会返回true
            fromV.outEdges.remove(edge);
            toV.inEdges.remove(edge);
        }
        edges.add(edge);
        fromV.outEdges.add(edge);
        toV.inEdges.add(edge);
    }

    @Override
    public void addEdge(V from, V to) {
        addEdge(from, to, null);
    }

    @Override
    public void removeVertex(V value) {
        // 在Map中删除key, 会返回对应的value
        Vertex<V, W> vertex = vertices.remove(value);
        // 不存在这个顶点
        if (vertex == null) return;

        Iterator<Edge<V, W>> inEdgesInterator = vertex.inEdges.iterator();
        while (inEdgesInterator.hasNext()) {
            Edge<V, W> edge = inEdgesInterator.next();
            // 总edges中删除
            edges.remove(edge);
            // 当前是inEdges, 找到from.outEdges, 从中删除
            edge.from.outEdges.remove(edge);
            // 从当前迭代器, inEdges中删除
            inEdgesInterator.remove();
        }

        Iterator<Edge<V, W>> outEdgesInterator = vertex.outEdges.iterator();
        while (outEdgesInterator.hasNext()) {
            Edge<V, W> edge = outEdgesInterator.next();
            // 总edges中删除
            edges.remove(edge);
            // 当前是outEdges, 找到to.inEdges, 从中删除
            edge.to.inEdges.remove(edge);
            // 从当前迭代器, outEdges中删除
            outEdgesInterator.remove();
        }
    }

    @Override
    public void removeEdge(V from, V to) {
        Vertex<V, W> fromVertex = vertices.get(from);
        if (fromVertex == null) return;
        Vertex<V, W> toVertex = vertices.get(to);
        if (toVertex == null) return;
        Edge<V, W> edge = new Edge<>(fromVertex, toVertex);

        if (edges.remove(edge)) {
            // 从起始顶点的outEdges删除
            fromVertex.outEdges.remove(edge);
            // 从终止顶点的inEdges删除
            toVertex.inEdges.remove(edge);
        }
    }

    private Vertex<V, W> createVertexIfNotExists(V value) {
        Vertex<V, W> vertex = vertices.get(value);
        if (vertex == null) {
            vertex = new Vertex<>(value);
            vertices.put(value, vertex);
        }
        return vertex;
    }

    private static class Vertex<V, W> {
        V value;
        Set<Edge<V, W>> inEdges = new HashSet<>();
        Set<Edge<V, W>> outEdges = new HashSet<>();

        Vertex(V value) {
            this.value = value;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Vertex<V, W> vertex = (Vertex<V, W>) o;
            return Objects.equals(value, vertex.value);
        }

        @Override
        public int hashCode() {
            return Objects.hash(value);
        }
    }

    private static class Edge<V, W> {
        Vertex<V, W> from;
        Vertex<V, W> to;
        W weight;

        Edge(Vertex<V, W> from, Vertex<V, W> to) {
            this.from = from;
            this.to = to;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Edge<V, W> edge = (Edge<V, W>) o;
            return Objects.equals(from, edge.from) && Objects.equals(to, edge.to);
        }

        @Override
        public int hashCode() {
            return Objects.hash(from, to);
        }
    }

    public static void main(String[] args) {
        test1();
    }

    private static void undirectGraph() {
        ListGraph<String, Integer> graph = new ListGraph<>();
        // 用有向图表示无向图, 两个方向都添加一条边就是无向图
        graph.addEdge("V1", "V0");
        graph.addEdge("V0", "V1");

        graph.addEdge("V0", "V3");
        graph.addEdge("V3", "V0");

        graph.addEdge("V2", "V3");
        graph.addEdge("V3", "V2");

        graph.addEdge("V1", "V2");
        graph.addEdge("V2", "V1");

        graph.addEdge("V0", "V2");
        graph.addEdge("V2", "V0");
    }

    private static void test1() {
        ListGraph<String, Integer> graph = new ListGraph<>();

        graph.addEdge("V1", "V0", 9);
        graph.addEdge("V1", "V2", 3);
        graph.addEdge("V2", "V0", 2);
        graph.addEdge("V2", "V3", 5);
        graph.addEdge("V3", "V4", 1);
        graph.addEdge("V0", "V4", 6);

        Asserts.testEqual(graph.edgesSize(), 6);
        Asserts.testEqual(graph.vertexSize(), 5);

        // test V0
        Vertex<String, Integer> v0 = graph.vertices.get("V0");
        Asserts.testNonNull(v0);
        Asserts.testEqual(v0.outEdges.size(), 1);
        Asserts.testEqual(v0.inEdges.size(), 2);

        // test V1
        Vertex<String, Integer> v1 = graph.vertices.get("V1");
        Asserts.testNonNull(v1);
        Asserts.testEqual(v1.outEdges.size(), 2);
        Asserts.testEqual(v1.inEdges.size(), 0);

        // test V2
        Vertex<String, Integer> v2 = graph.vertices.get("V2");
        Asserts.testNonNull(v2);
        Asserts.testEqual(v2.outEdges.size(), 2);
        Asserts.testEqual(v2.inEdges.size(), 1);

        // test V3
        Vertex<String, Integer> v3 = graph.vertices.get("V3");
        Asserts.testNonNull(v3);
        Asserts.testEqual(v3.outEdges.size(), 1);
        Asserts.testEqual(v3.inEdges.size(), 1);

        // test V4
        Vertex<String, Integer> v4 = graph.vertices.get("V4");
        Asserts.testNonNull(v4);
        Asserts.testEqual(v4.outEdges.size(), 0);
        Asserts.testEqual(v4.inEdges.size(), 2);

        Vertex<String, Integer> vx = graph.vertices.get("vx");
        Asserts.testNull(vx);

        // test remove edge
        graph.removeEdge("V1", "V0");
        Asserts.testEqual(graph.edgesSize(), 5);

        graph.removeEdge("V1", "VX"); // 移除不存在的边
        Asserts.testEqual(graph.edgesSize(), 5);

        // test remove Vertex
        graph.removeVertex("V1");
        Asserts.testEqual(graph.vertexSize(), 4);
        Asserts.testEqual(graph.edgesSize(), 4);

    }
}
