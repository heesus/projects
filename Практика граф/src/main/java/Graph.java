import java.util.HashMap;


public class Graph extends DirectedGraph {
    public Graph() { //создание пустого графа
        adjList = new HashMap<>();
        vertices = new HashMap<>();
        V = E = 0;
    }

    public Graph(Graph g) {  //создание копии графа
        adjList = new HashMap<>(g.adjList);
        vertices = new HashMap<>(g.vertices);
        V = g.V;
        E = g.E;
    }

    @Override
    public void addEdge(String from, String to) { //добавление ребра в граф
        super.addEdge(from, to); //если какой-то вершины нет в графе, то она создается
        super.addEdge(to, from);
        E--;  //два ребра считаются как одно
    }
}