import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;
import java.util.TreeSet;

public class BipartiteGraph extends Graph {
    private HashMap<String, Vertex> part1, part2; //доли графа
    public Vertex activeEdgeV1, activeEdgeV2;
    public HashMap<Vertex, Vertex> currentMatching;

    public BipartiteGraph() {  //создание пустого двудольного графа
        part1 = new HashMap<>();
        part2 = new HashMap<>();
    }
    
    

    public BipartiteGraph(Graph g) { //создание подобного графа
        super(g); // создание копии исходного графа
        part1 = new HashMap<>();
        part2 = new HashMap<>();
        currentMatching = new HashMap<>();
        paintGraph(this);  //вершины окрашиваются
        for (Vertex v : getVertices()) {
            if (v.color % 2 == 0) { // четные вершины добавляются в 1 долю
                part1.put(v.name, v);
            } else {
                part2.put(v.name, v); // нечетные добавляются во 2 долю
            }
        }
    }
    
    public BipartiteGraph(BipartiteGraph g) {
        super(g);
        part1 = new HashMap<>();
        part2 = new HashMap<>();
        currentMatching = new HashMap<>();
        part1 = g.part1;
        part2 = g.part2;
        currentMatching = g.currentMatching;
        activeEdgeV1 = g.activeEdgeV1;
        activeEdgeV2 = g.activeEdgeV2;
    }
    
    public Vertex addVertexPart1(String name) { //добавление вершины в 1 долю графа
        Vertex v = new Vertex(name);
        return addVertexPart1(v);
    }

    public Vertex addVertexPart1(Vertex v) { //добавление вершины во 1 долю графа
        Vertex w = vertices.get(v.name);
        if (w == null) { // если вершины нет в списке, добавляется
            vertices.put(v.name, v);
            adjList.put(v, new TreeSet<>());
            part1.put(v.name, v);
            V++;
        }

        return w;
    }

    public Vertex addVertexPart2(String name) { //добавление вершины во 2 долю графа
        Vertex v = new Vertex(name);
        return addVertexPart2(v);
    }

    public Vertex addVertexPart2(Vertex v) { //добавление вершины во 2 долю графа
        Vertex w = vertices.get(v.name);
        if (w == null) { // если вершины нет в списке, добавляется
            vertices.put(v.name, v);
            adjList.put(v, new TreeSet<>());
            part2.put(v.name, v);
            V++;
        }
        return w;
    }

    //добавление вершины в долю, которая противополжна opposedVertex
    public Vertex addVertexOppositePart(String addedVertex, String opposedVertex) {
        Vertex v = new Vertex(addedVertex);
        int part = getVertexPart(opposedVertex);
        if (part == 1)
            return addVertexPart2(v);
        else
        if (part == 2)
            return addVertexPart1(v);
        else
            throw new IllegalStateException( String.format("Неизвестный номер доли {%d} у вершины {%s}", part, opposedVertex) );
    }

    public boolean isVertexInPart1(String name) { //проверка вхождения вершины в 1 долю
        return part1.containsKey(name);
    }

    public boolean isVertexInPart2(String name) { //проверка вхождения вершины во 2 долю
        return part2.containsKey(name);
    }

    public boolean isVertexInPart1(Vertex v) { //проверка вхождения вершины в 1 долю
        return part1.containsValue(v);
    }

    public boolean isVertexInPart2(Vertex v) { //проверка вхождения вершины во 2 долю
        return part2.containsValue(v);
    }

    public int getVertexPart(String name) { //номер доли, которой принадлежит вершина
        if (EntryVertex(name)) {
            if (isVertexInPart1(name)) {
                return 1;
            }
            if (isVertexInPart2(name)) {
                return 2;
            }
            return 0;  //возращает 0, если не принадлежит ни к 1, ни ко 2 доле
        }
        return 0; //возвращает 0, если вершины нет в графе
    }

    public Iterable<Vertex> getPart1Vertices() { //итератор на вершины 1 доли
        return part1.values();
    }

    public Iterable<Vertex> getPart2Vertices() { //итератор на вершины 2 доли
        return part2.values();
    }

    @Override
    public void addEdge(String from, String to) { //добавление ребра в граф
        int fromPart = getVertexPart(from);
        int toPart = getVertexPart(to);
        // добавляются вершины в нужные доли, если необходимо
        if (fromPart > 0) {
            if (toPart > 0) {
                // нельзя соединить вершины из одной доли
                if (fromPart == toPart) {
                    throw new IllegalArgumentException("Невозможно соединить вершины, находящиеся в одной доле");
                }
            } else {
                // добавляется to в долю, противоположную from
                addVertexOppositePart(to, from);
            }
        } else {
            if (toPart > 0) {
                // добавляется from в долю, противоположную to
                addVertexOppositePart(from, to);
            } else {
                // добавляем обе вершины в граф
                addVertexPart1(from);
                addVertexPart2(to);
            }
        }
        super.addEdge(from, to); //соединение вершин ребром
    }

    private void paintGraph(Graph g) { /**раскраска графа
                                          цвет вершины = цвет предыдущей вершины + 1 */
        Vertex v;
        while ((v = g.getUnvisitedVertex()) != null) { //поиск в ширину для непосещенных вершин
            BFS(g, v);
        }
    }

    private void BFS(Graph g, Vertex root) {  //обход графа в ширина, а также раскраска вершин
        Queue<Vertex> queue = new LinkedList<>();
        root.color = 0;
        root.visited = true;
        queue.add(root);
        while (!queue.isEmpty()) {
            Vertex v = queue.remove(); //достается очередная вершина
            int newColor = v.color + 1;
            Iterable<Vertex> neighbours = g.getNeighbours(v);
            for (Vertex w : neighbours) {
                if (w.visited) {
                    // если кратности вершин не совпадают, разбиение на 2 доли невозможно
                    if ((w.color % 2) != (newColor % 2)) {
                        throw new IllegalArgumentException("Для данного графа разбиение на 2 доли невозможно");
                    }
                } else {
                    w.color = newColor; //раскраска вершины
                    w.visited = true;
                    w.parent = v;
                    queue.add(w);
                }
            }
        }
    }

    @Override
    public String toString() { //строковое представление графа
        String s = super.toString() + NEWLINE;
        s += "part1: { ";
        for (Vertex p1 : getPart1Vertices()) {
            s += p1 + ", ";
        }
        s += " }" + NEWLINE;
        s += "part2: { ";
        for (Vertex p2 : getPart2Vertices()) {
            s += p2 + ", ";
        }
        s += " }";
        return s;
    }
}