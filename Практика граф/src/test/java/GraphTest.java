import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;


public class GraphTest{
    @Test
    public void runTest1() {
        Graph g = new Graph();
        g.addEdge("A", "B");
        BipartiteGraph bg = new BipartiteGraph(g);
        Kuhn k = new Kuhn(bg,true);
        k.run();
       Assertions.assertEquals("A B\n", k.getMatching());
    }
    @Test
    public void runTest2() {
        Graph g = new Graph();
        g.addEdge("1", "3");
        g.addEdge("1", "4");
        BipartiteGraph bg = new BipartiteGraph(g);
        Kuhn k = new Kuhn(bg,true);
        k.run();
        Assertions.assertEquals("1 3\n", k.getMatching());
    }
    @Test
    public void runTest3() {
        Graph g = new Graph();
        g.addEdge("1", "3");
        g.addEdge("2", "4");
        BipartiteGraph bg = new BipartiteGraph(g);
        Kuhn k = new Kuhn(bg,true);
        k.run();
        Assertions.assertEquals("1 3\n2 4\n", k.getMatching());
    }
    @Test
    public void runTest4() {
        Graph g = new Graph();
        try {
            g.addEdge("1", "3");
            g.addEdge("2", "2");
            BipartiteGraph bg = new BipartiteGraph(g);
        }catch (IllegalArgumentException ex){
            Assertions.assertNotEquals("", ex.getMessage());
        }
    }
    @Test
    public void runTest5() {
        try {
            Graph g = new Graph();
            g.addEdge(" ", " ");
            BipartiteGraph bg = new BipartiteGraph(g);
        }catch (Exception ex){
            Assertions.assertNotEquals("", ex.getMessage());
        }
    }
    @Test
    public void runTest6() {
        try {
            Graph g = new Graph();
            g.addEdge("1", " ");
            BipartiteGraph bg = new BipartiteGraph(g);
        }catch (Exception ex){
            Assertions.assertNotEquals("", ex.getMessage());
        }
    }
}
