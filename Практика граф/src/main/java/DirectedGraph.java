/** Класс ориентированного невзвешанного графа вершин
   Граф представлен списком ребер */

import java.util.HashMap;
import java.util.TreeSet;

public class DirectedGraph {
    protected static final String NEWLINE = System.getProperty("line.separator");
    protected HashMap<Vertex, TreeSet<Vertex>> adjList;
    protected HashMap<String, Vertex> vertices;
    protected int V;
    protected int E;

    public DirectedGraph() { //создание пустого графа
        adjList = new HashMap<>();
        vertices = new HashMap<>();
        V = E = 0;
    }

    public DirectedGraph(DirectedGraph g) {  //создание копии графа
        adjList = new HashMap<>(g.adjList);
        vertices = new HashMap<>(g.vertices);
        V = g.V;
        E = g.E;
    }

    public void reset() {  //обнуление состояния вершин графа
        for (Vertex v : getVertices()) {
            v.visited = false;
            v.parent = null;
            v.color = 0;
        }
    }

    public Vertex addVertex(String name) { //добавление новой вершины
        Vertex v = new Vertex(name);
        return addVertex(v);  //возвращает новую вершину, или уже существующую
    }

    public Vertex addVertex(Vertex v) {  //добавление в графа новую вершину
        Vertex w = vertices.get(v.name);
        if (w == null) {  // если вершины нет в списке, тогда она добавляется
            w = v;
            vertices.put(w.name, w);
            adjList.put(w, new TreeSet<>());
            V++;
        }
        return w;
    }

    public Vertex getVertex(String name) { //возвращает вершину по имени
        return vertices.get(name);
    }

    public boolean EntryVertex(String name) { //проверка вхождения вершины в граф
        return vertices.containsKey(name);
    }

    public boolean EntryVertex(Vertex v) { //проверка вхождения вершины в граф
        return adjList.containsKey(v);
    }

    public void addEdge(String from, String to) { //добавление ребра в граф
        if (EntryEdge(from, to)) { // если ребро существует, тогда ребро не создается
            return;
        }
        //если такого ребра нет
        Vertex v = addVertex(from); //добавляются вершины, если они еще не добавлены
        Vertex w = addVertex(to);
        adjList.get(v).add(w); //добавление реба
        E++;
    }

    public boolean EntryEdge(Vertex from, Vertex to) { //проверка на существование ребра в графе
        if (EntryVertex(from) && EntryVertex(to)) {
            return adjList.get(from).contains(to);
        } else {
            return false; // если одной из вершин нет в графе
        }
    }

    public boolean EntryEdge(String from, String to) { // проверка на существование ребра в графе
        Vertex v = getVertex(from);
        Vertex w = getVertex(to);
        return EntryEdge(v, w);
    }

    public Iterable<Vertex> getVertices() { //итератор по всем вершинам графа
        return vertices.values();
    }

    public Iterable<Vertex> getNeighbours(Vertex v) { //список соседей текущей вершины
        if (adjList.containsKey(v)) /** возращается итератор по всем соседям вершины
                                       или пустое множество (если вершины нет) */
            return adjList.get(v);
        else
            return new TreeSet<>();
    }

    public Iterable<Vertex> getNeighbours(String name) { //список соседей вершины с текущим именем
        Vertex v = getVertex(name);
        return getNeighbours(v);
    }

    public Vertex getUnvisitedVertex() { //непосещенная вершина графа
        for (Vertex v : vertices.values()) {
            if (!v.visited) {
                return v;
            }
        }
        return null;
    }

    public int numVertices() { //количество вершин в графе
        return V;
    }

    public int numEdges() { //количество ребер в графе
        return E;
    }

    @Override
    public String toString() { //строкое представление графа в виде списка смежности
        String graph = '{' + NEWLINE;
        for (Vertex v : vertices.values()) {
            graph += "\t" + v + ": { ";
            for (Vertex w : adjList.get(v)) {
                graph += w + ", ";
            }
            graph += " }" + NEWLINE;
        }
        graph += '}';
        return graph;
    }

    public boolean isEmpty() {
        return V == 0;
    }
}