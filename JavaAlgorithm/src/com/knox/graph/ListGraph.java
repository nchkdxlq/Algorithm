package com.knox.graph;

import com.knox.tools.Asserts;

import java.util.*;

public class ListGraph<V, W> implements Graph<V, W> {

    private Map<V, Vertex<V, W>> vertices = new HashMap();
    private Set<Edge<V, W>> edges = new HashSet<>();

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

    @Override
    public void bfs(V begin, VertexVisitor<V> visitor) {
        if (visitor == null) return;
        Vertex<V, W> beginVertex = vertices.get(begin);
        if (beginVertex == null) return;

        HashSet<Vertex<V, W>> visitedSet = new HashSet<>();
        Queue<Vertex<V, W>> queue = new LinkedList<>();
        queue.offer(beginVertex);
        visitedSet.add(beginVertex);
        while (!queue.isEmpty()) {
            Vertex<V, W> vertex = queue.poll();
            // 访问
            if (visitor.visit(vertex.value)) return;
            // 把outEdges对应to顶点都加入队列中
            for (Edge<V, W> edge : vertex.outEdges) {
                // 访问过不再访问
                if (visitedSet.contains(edge.to)) continue;
                queue.offer(edge.to);
                visitedSet.add(edge.to);
            }
        }
    }

    @Override
    public void dfs(V begin, VertexVisitor<V> visitor) {
        if (visitor == null) return;
        Vertex<V, W> beginVertex = vertices.get(begin);
        if (beginVertex == null) return;
        // dfs_recursive(beginVertex, visitor, new HashSet<>());
        dfs_iterator(begin, visitor);
    }

    /**
     *  弹出一个顶点vertex
     *  1. 从顶点的outEdges中取出一条边
     *  2. 将选择边的from、to按顺序入栈
     *  3. 访问选择边的to
     *  4. 将to添加到已访问Set中
     *  5. break, 深度优先遍历, 要沿着一条路径往下走
     *
     */
    private void dfs_iterator(V begin, VertexVisitor<V> visitor) {
        Vertex<V, W> beginVertex = vertices.get(begin);
        if (beginVertex == null) return;
        HashSet<Vertex<V, W>> visitedSet = new HashSet<>();
        Stack<Vertex<V, W>> stack = new Stack<>();
        // 先访问起点
        if (visitor.visit(begin)) return;
        visitedSet.add(beginVertex);
        stack.push(beginVertex);

        while (!stack.isEmpty()) {
            Vertex<V, W> vertex = stack.pop();
            for (Edge<V, W> edge : vertex.outEdges) {
                if (visitedSet.contains(edge.to)) continue;
                stack.push(edge.from);
                stack.push(edge.to);
                if (visitor.visit(edge.to.value)) return;
                visitedSet.add(edge.to);
                break;
            }
        }
    }

    private void dfs_recursive(Vertex<V, W> vertex, VertexVisitor<V> visitor, HashSet<Vertex<V, W>> visitedSet) {
        if (visitedSet.contains(vertex)) return;

        visitor.visit(vertex.value);
        visitedSet.add(vertex);
        for (Edge<V, W> edge : vertex.outEdges) {
            dfs_recursive(edge.to, visitor, visitedSet);
        }
    }

    @Override
    public List<V> topologicSort() {
        List<V> list = new ArrayList<>();
        Map<Vertex<V, W>, Integer> vertexInDegreeMap = new HashMap<>();
        Queue<Vertex<V, W>> queue = new LinkedList<>();

        vertices.forEach((V value, Vertex<V, W> vertex) -> {
            if (vertex.inEdges.isEmpty()) {
                queue.offer(vertex);
            } else {
                vertexInDegreeMap.put(vertex, vertex.inEdges.size());
            }
        });

        while (!queue.isEmpty()) {
            Vertex<V, W> vertex = queue.poll();
            list.add(vertex.value);

            for (Edge<V, W> edge : vertex.outEdges) {
                Integer size = vertexInDegreeMap.get(edge.to);
                size--;
                if (size == 0) { // 入度为0, 放入队列
                    queue.offer(edge.to);
                } else {
                    vertexInDegreeMap.put(edge.to, size);
                }
            }
        }

        return list;
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
        // test1();
        // test_undirectGraph();
        test_bfs();
    }

    private static void test_bfs() {
        ListGraph<String, Integer> graph = new ListGraph<>();

        graph.addEdge("V1", "V0", 9);
        graph.addEdge("V1", "V2", 3);
        graph.addEdge("V2", "V0", 2);
        graph.addEdge("V2", "V3", 5);
        graph.addEdge("V3", "V4", 1);
        graph.addEdge("V0", "V4", 6);

        System.out.println("====== V0 begin =======");
        graph.bfs("V0", (String value) -> {
            System.out.println(value);
            return false;
        });

        System.out.println("====== V1 begin =======");
        graph.bfs("V1", null);
    }

    private static void test_undirectGraph() {
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
