import java.util.*;

public class Main {
  static final int MAX = 1000;
  static int ds[][] = new int[MAX][MAX];

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in).useLocale(Locale.US);
    long begin = System.currentTimeMillis();

    // Read graph and calculate distances. Note that the distance matrix is symmetrical.
    int n = in.nextInt();
    double[] Xs = new double[n];
    double[] Ys = new double[n];
    for (int i = 0; i < n; ++i) {
      Xs[i] = in.nextDouble();
      Ys[i] = in.nextDouble();
    }
    for (int i = 0; i < n; ++i)
      for (int j = i; j < n; ++j)
        ds[i][j] = ds[j][i] = (int) Math.round(Math.sqrt(Math.pow(Xs[i] - Xs[j], 2) + Math.pow(Ys[i] - Ys[j], 2)));

    // Find decent path heuristically.
    int[] path = new int[n];
    int[] shortest_path = new int[n];
    int shortest = Integer.MAX_VALUE;
    List<Integer> starts = new ArrayList(n);
    for (int i = 0; i < n; ++i) starts.add(i);
    Collections.shuffle(starts);
    for (int s : starts) {

      // Construct path with nearest neighbor algorithm.
      nearest_neighbor_path(s, path);

      // Optimize with local search until no improvements occur.
      int l = length(path);
      int t = l + 1;
      while (l < t) {
        t = l;
        opt2(path);
        l = length(path);
      }

      // Keep shortest path.
      if (l < shortest) {
        shortest = l;
        shortest_path = path;
      }

      // Break if out of time.
      if (System.currentTimeMillis() - begin > 1000) break;
    }

    // Print shortest path.
    for (int v : shortest_path) System.out.println(v);
  }

  // Calculate tour length for the given path.
  static int length(int[] path) {
    int l = 0;
    for (int i = 1; i < path.length; ++i) l += ds[path[i - 1]][path[i]];
    l += ds[path[path.length - 1]][path[0]];
    return l;
  }

  // Find decent path with nearest neighbor.
  static void nearest_neighbor_path(int start, int[] path) {
    int n = path.length;
    boolean[] visited = new boolean[n];
    path[0] = 0;//start;
    visited[0] = true;
    for (int i = 1; i < n; ++i) {
      int idx = i; //n + (start + i) % n;
      int min = -1;
      for (int j = 0; j < n; ++j) {
        if (visited[j]) continue;
        if (min == -1) min = j;
        int d1 = ds[path[(idx - 1) % n]][j];
        int d2 = ds[path[(idx - 1) % n]][min];
        if (d1 < d2) min = j;
      }
      visited[min] = true;
      path[idx % n] = min;
    }
  }

  // Optimize path by exchanging pairs of edges with shorter pairs of edges.
  static void opt2(int[] path) {
    int n = path.length;
    for (int i = 0; i <= n; ++i) {
      for (int j = i + 1; j <= n - 1; ++j) {
        int a = path[i % n];
        int b = path[(i + 1) % n];
        int c = path[j % n];
        int d = path[(j + 1) % n];
        if (ds[a][c] + ds[b][d] < ds[a][b] + ds[c][d]) {
          // Reverse path b to c.
          int b_i = i+1;
          int c_i = j;
          for (int k = 0; k < 1 + (c_i - b_i)/2; k++) {
            int t = path[b_i + k];
            path[b_i + k] = path[c_i - k];
            path[c_i - k] = t;
          }
        }
      }
    }
  }
}