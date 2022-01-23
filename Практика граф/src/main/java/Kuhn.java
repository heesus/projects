//Класс реализации алгоритма Куна для поиска наибольшего паросочетания в графе

import java.util.HashMap;
import java.util.ArrayList;

public class Kuhn {
    protected static final String NEWLINE = System.getProperty("line.separator");

    private volatile boolean running = true;
    private volatile boolean finished = false;

    public ArrayList<BipartiteGraph> graphSteps = new ArrayList<>();
    public ArrayList<String> hintSteps = new ArrayList<>();
    public int stepsCounter = 0;
    
    BipartiteGraph graph; // исходный граф
    HashMap<Vertex, Vertex> matching; // текущее паросочетание

    public Kuhn(BipartiteGraph g) {
        graph = g;
        sendHint("Алгоритм запущен", 0);
        matching = new HashMap<>();
        if (graph != null) {
            // для каждой вершины 1-й доли пытаемся найти увеличивающуюся цепь
            for (Vertex v : graph.getPart1Vertices()) {
                if (running) {
                    sendHint(NEWLINE + "Запущен DFS из вершины " + v, 0);
                    graph.reset();
                    if (DFS(v, 0)) {
                        sendHint("Текущее паросочетание", 0);
                        sendHint(getMatching(), 0);
                    }
                } else {
                    break;
                }
            }
        }
        sendActiveEdgeChanged(null, null);
        sendHint(NEWLINE + "Алгоритм завершен", 0);
        stop();
    }

    private boolean DFS(Vertex root, int depth) {
        if (root.visited) {
            sendHint("Вершина " + root + " уже была посещена, не рассматриваем", depth);
            return false;
        }
        sendHint("Рассматриваем вершину " + root, depth);
        root.visited = true; // вершина становится посещенной
        for (Vertex to : graph.getNeighbours(root)) {
            sendHint("Пытаемся найти увеличивающуюся цепь через вершину " + to, depth);
            sendActiveEdgeChanged(root, to);
            sendHint("Текущее ребро: " + root + " " + to, depth);
            if (!matching.containsKey(to) || DFS(matching.get(to), depth + 1)) {
                // если удалось найти увеличивающуюся цепь, добавляем ребро в текущее паросочетание
                sendHint("Удалось найти увеличивающуюся цепь.", depth);
                matching.put(to, root);
                sendMatchingChanged();
                sendHint("Добавляем ребро " + root + " " + to + " в паросочетание", depth);
                return true;
            } else {
                sendHint("НЕ удалось найти увеличивающуюся цепь.", depth);
                sendHint("Ребро " + root + " " + to + " в паросочетание НЕ добавлено", depth);
            }
        }
        return false;
    }
    
    public void addGraphStep(BipartiteGraph biGraph) {
        BipartiteGraph graph = new BipartiteGraph(biGraph);
        graphSteps.add(graph);
    }
    
    public void addHintStep(String hint) {
        if(hintSteps.isEmpty()){
            hintSteps.add(hint);
        } else{
            hintSteps.add(hintSteps.get(hintSteps.size() - 1) + hint);
        }
    }

    public String getMatching() { //текущее паросочетание
        String s = "";
        for (Vertex v1 : graph.getVertices()) {
            if (matching.containsKey(v1)) {
                Vertex src = v1, dst = matching.get(v1);
                if (src.compareTo(dst) > 0) {
                    src = dst;
                    dst = v1;
                }
                s += (src + " " + dst + System.lineSeparator());
            }
        }
        return s;
    }

    public boolean isFinished() { //алгоритм закончил свою работу или нет
        return finished;
    }

    public void stop() { //флаг завершения алгоритма
        running = false;
        finished = true;
    }
    
    private void sendHint(String hint, int depth) {
        for(int i = 0; i < depth; i++) {
            hint = "| " + hint;
        }          
        addHintStep(NEWLINE + hint);
        addGraphStep(graph);
    }
   

    private void sendActiveEdgeChanged(Vertex v1, Vertex v2) {
        graph.activeEdgeV1 = v1;
        graph.activeEdgeV2 = v2;
    }

    private void sendMatchingChanged() {
        HashMap<Vertex, Vertex> m = new HashMap<>(matching);
        graph.currentMatching = m;
    }
}
