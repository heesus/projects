public class Vertex implements Comparable<Vertex> {
    public String name = "";  //имя вершины
    int x = 0, y = 0;  //координаты вершины
    public Vertex parent = null; //родитель вершины (предшественник)
    public boolean visited = false;  //была посещена вершина или нет
    public int color = 0;  //цвет вершины

    public Vertex(String v) {  //создание вершины, где v - имя вершины
        name = v;
    }

    @Override
    public int hashCode() {  //хэш, чтобы было удобнее работать (имя вершины уникально)
        return name.hashCode();
    }

    @Override
    public int compareTo(Vertex other) { //сортировка вершин в HashMap
        return name.compareTo(other.name); /** сравнивает текущую вершиную с другой вершиной
                                              0 - если вершины совпадают
                                              отрицательное - текущая вершина меньше
                                              положительное - текущая вершина больше */
    }

    @Override
    public String toString() { //возвращает имя вершины
        return name;
    }
}