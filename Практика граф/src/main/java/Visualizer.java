
import javax.swing.*;
import java.awt.*;
import java.util.HashMap;

public class Visualizer extends JPanel {

    private final int leftX = 150;
    private final int rightX = 600;
    private final int vertexRadius = 25;
    private final int vertexDiameter = 2 * vertexRadius;
    public int stepIndex = 0;
    public boolean stopped = false;

    private BipartiteGraph graph = new BipartiteGraph();
    private Kuhn algorithm;

    private Vertex activeEdgeV1, activeEdgeV2;
    private HashMap<Vertex, Vertex> currentMatching;

    Visualizer() {

    }

    private void drawVertex(Graphics2D graphics, Vertex v) {
        int leftX, upperY;
        leftX = v.x - vertexRadius;
        upperY = v.y - vertexRadius;

        Color vertexBorderColor = new Color(0, 0, 0);
        Color vertexBodyColor = new Color(185, 221, 252);
        Color textColor = new Color(0, 0, 0);

        graphics.setColor(vertexBodyColor);
        graphics.fillOval(leftX, upperY, vertexDiameter, vertexDiameter);
        graphics.setColor(vertexBorderColor);
        graphics.drawOval(leftX, upperY, vertexDiameter, vertexDiameter);

        FontMetrics fm = graphics.getFontMetrics();
        String vertexName = v.name;

        int strWidth = fm.stringWidth(vertexName);
        int strHeight = fm.getAscent();
        graphics.setColor(textColor);
        graphics.drawString(vertexName, v.x - strWidth / 2, v.y + strHeight / 2);
    }

    public void drawEdge(Graphics2D graphics, Vertex src, Vertex dst) {
        graphics.setColor(getEdgeColor(src, dst));
        graphics.drawLine(src.x, src.y, dst.x, dst.y);
    }

    public void setActiveEdge(Vertex v1, Vertex v2) {
        activeEdgeV1 = v1;
        activeEdgeV2 = v2;
    }

    public void setCurrentMatching(HashMap<Vertex, Vertex> matching) {
        currentMatching = matching;
    }

    public Color getEdgeColor(Vertex v1, Vertex v2) {
        Color unvisitedEdgeColor = new Color(50, 50, 50);
        Color currentEdgeColor = new Color(0, 0, 255);
        Color notMatchingEdgeColor = new Color(187, 0, 0);
        Color matchingEdgeColor = new Color(0, 187, 0);
        Color c = unvisitedEdgeColor;

        if (stepIndex == (algorithm.hintSteps.size() - 1)) {
            c = notMatchingEdgeColor;
        }

        if ((v1 == activeEdgeV1 && v2 == activeEdgeV2) || (v1 == activeEdgeV2 && v2 == activeEdgeV1)) {
            c = currentEdgeColor;
        } else {
            if (currentMatching != null) {
                boolean isInMatching = currentMatching.containsKey(v1) && (currentMatching.get(v1) == v2);
                isInMatching |= currentMatching.containsKey(v2) && (currentMatching.get(v2) == v1);

                if (isInMatching) {
                    c = matchingEdgeColor;
                }
            }
        }

        return c;
    }

    
    @Override
    public void paintComponent(Graphics graphics) {
        Graphics2D graphics2D = (Graphics2D) graphics;
        super.paintComponent(graphics);
        graphics2D.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        graph = getNextGraph();

        if (graph != null) {

            setActiveEdge(graph.activeEdgeV1, graph.activeEdgeV2);
            setCurrentMatching(graph.currentMatching);
            // подсчитываем координаты графа
            int y1 = vertexDiameter;
            int y2 = y1;

            for (Vertex v : graph.getVertices()) {
                if (graph.isVertexInPart1(v)) {
                    // находится в первой доле
                    v.x = leftX;
                    v.y = y1;
                    y1 += 3 * vertexRadius;
                } else {
                    // находится во второй доле
                    v.x = rightX;
                    v.y = y2;
                    y2 += 3 * vertexRadius;
                }
            }

            // рисуем ребра
            for (Vertex v1 : graph.getVertices()) {
                for (Vertex v2 : graph.getNeighbours(v1)) {
                    drawEdge(graphics2D, v1, v2);
                }
            }

            // рисуем сами вершины
            for (Vertex v : graph.getVertices()) {
                drawVertex(graphics2D, v);
            }
        }
    }

    public void setGraph(BipartiteGraph bg) {
        graph = bg;
        revalidate();
        repaint();
    }

    public void start() {
        algorithm = new Kuhn(graph);
    }

    public String getNextHint() {
        stepIndex++;
        if (stepIndex >= algorithm.hintSteps.size()) {
            stepIndex = algorithm.hintSteps.size() - 1;
        }
        return algorithm.hintSteps.get(stepIndex);
    }

    public BipartiteGraph getNextGraph() {
        if (algorithm == null) {
            return null;
        }
        return algorithm.graphSteps.get(stepIndex);
    }

    public int getStepsCount() {
        return algorithm.hintSteps.size();
    }

    public String getPrevHint() {
        stepIndex--;
        if (stepIndex < 0) {
            stepIndex = 0;
        }
        return algorithm.hintSteps.get(stepIndex);
    }

    public String getResult() {
        return algorithm.getMatching();
    }
}
