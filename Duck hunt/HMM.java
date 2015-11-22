import java.util.*;
import java.math.*;
public class HMM {
  static final int STATES = 5, SYMBOLS = 9;
  double[][] A = new double[STATES][STATES];
  double[][] B = new double[STATES][SYMBOLS];
  double[] PI = new double[STATES];
  int pieces = 1;
  //TODO Make O part of class.
  
  public HMM() {
    randomize();
  }
  
  public HMM(double[][] A, double[][] B, double[] PI) {
    this.A = A;
    this.B = B;
    this.PI = PI;
  }
  
  public HMM(Bird b, int limit) {
    randomize();
    int T = 0;
    for (int i = 0; i < b.getSeqLength(); ++i) if (!b.wasDead(i)) ++T;
    int[] O = new int[T];
    for (int i = 0; i < T; ++i) O[i] = b.getObservation(i);
    baumWelch(O, limit);
  }

  public HMM(Bird b, int limit, HMM old) {
    A = old.A;
    B = old.B;
    PI = old.PI;
    int T = 0;
    for (int i = 0; i < b.getSeqLength(); ++i) if (!b.wasDead(i)) ++T;
    int[] O = new int[T];
    for (int i = 0; i < T; ++i) O[i] = b.getObservation(i);
    baumWelch(O, limit);
  }
  
  void randomize() 
  {
    Random r = new Random();
    for (int i = 0; i < STATES; ++i) for (int j = 0; j < STATES; ++j) A[i][j] = r.nextDouble();
    for (int i = 0; i < STATES; ++i) for (int j = 0; j < SYMBOLS; ++j) B[i][j] = r.nextDouble();
    for (int i = 0; i < STATES; ++i) PI[i] = r.nextDouble();

    for (int i = 0; i < STATES; ++i) {
      double s = 0;
      for (int j = 0; j < STATES; ++j) s += A[i][j];
      for (int j = 0; j < STATES; ++j) A[i][j] /= s;
    }
    
    for (int i = 0; i < STATES; ++i) {
      double s = 0;
      for (int j = 0; j < SYMBOLS; ++j) s += B[i][j];
      for (int j = 0; j < SYMBOLS; ++j) B[i][j] /= s;
    }
    
    double s = 0;
    for (int i = 0; i < STATES; ++i) s += PI[i];
    for (int i = 0; i < STATES; ++i) PI[i] /= s;
  }
  
  public void combine(List<HMM> hmms) {
    pieces = hmms.size();
    for (int i = 0; i < STATES; ++i) for (int j = 0; j < STATES; ++j) A[i][j] = 0;
    for (int i = 0; i < STATES; ++i) for (int j = 0; j < SYMBOLS; ++j) B[i][j] = 0;
    for (int i = 0; i < STATES; ++i) PI[i] = 0;
    
    /* TODO Count seq length rather than HMMs.
    double scale = pieces / (pieces + hmms.size());
    pieces += hmms.size();
    for (int i = 0; i < STATES; ++i) for (int j = 0; j < STATES; ++j) A[i][j] *= scale;
    for (int i = 0; i < STATES; ++i) for (int j = 0; j < SYMBOLS; ++j) B[i][j] *= scale;
    for (int i = 0; i < STATES; ++i) PI[i] *= scale;
    */
    
    for (HMM hmm : hmms) {
      for (int i = 0; i < STATES; ++i) for (int j = 0; j < STATES; ++j) A[i][j] += hmm.A[i][j] / pieces;
      for (int i = 0; i < STATES; ++i) for (int j = 0; j < SYMBOLS; ++j) B[i][j] += hmm.B[i][j] / pieces;
      for (int i = 0; i < STATES; ++i) PI[i] += hmm.PI[i] / pieces;    
    }
  }
  
  public static HMM merge(List<HMM> hmms) {
    double[][] A = new double[STATES][STATES];
    double[][] B = new double[STATES][SYMBOLS];
    double[] PI = new double[STATES];
    for (int i = 0; i < STATES; ++i) for (int j = 0; j < STATES; ++j) {
      double res = 0;
      for (int k = 0; k < hmms.size(); ++k) res += hmms.get(k).A[i][j];
      A[i][j] = res / hmms.size();
    }
    for (int i = 0; i < STATES; ++i) for (int j = 0; j < SYMBOLS; ++j) {
      double res = 0;
      for (int k = 0; k < hmms.size(); ++k) res += hmms.get(k).B[i][j];
      B[i][j] = res / hmms.size();
    }
    for (int i = 0; i < STATES; ++i) {
      double res = 0;
      for (int k = 0; k < hmms.size(); ++k) res += hmms.get(k).PI[i];
      PI[i] = res / hmms.size();
    }
    return new HMM(A, B, PI);
  }
  
  double eln(double x) {
    return (x == 0) ? Double.NaN : Math.log(x);
  }
  
  double eexp(double x) {
    return (Double.isNaN(x)) ? 0 : Math.exp(x);
  }
  
  double elnsum(double elnx, double gamma) {
    if (Double.isNaN(elnx) || Double.isNaN(gamma)) return Double.isNaN(elnx) ? gamma : elnx;
    else return (elnx > gamma) ? elnx + eln(1 + eexp(gamma - elnx)) : gamma + eln(1 + eexp(elnx - gamma));
  }
  
  double elnproduct(double elnx, double gamma) {
    if (Double.isNaN(elnx) || Double.isNaN(gamma)) return Double.NaN;
    else return elnx + gamma;
  }
 
  // HMM1
  public double[] nextEmissionDistribution(int[] O) {
    int[] v = viterbi(O);
    double[] spdf = new double[STATES];
    spdf[v[v.length - 1]] = 1.0;
   
    double[] epdf = new double[SYMBOLS];
    for (int i = 0; i < SYMBOLS; ++i) 
      for (int j = 0; j < STATES; ++j) 
        for (int k = 0; k < STATES; ++k)
          epdf[i] += spdf[j] * A[j][k] * B[k][i];

    return epdf;
  }
  
  // HMM2
  public double estimateBird(Bird b) {
    int T = 0;
    for (int i = 0; i < b.getSeqLength(); ++i) if (!b.wasDead(i)) ++T;
    int[] O = new int[T];
    for (int i = 0; i < T; ++i) O[i] = b.getObservation(i);
    
    double[][] AL = new double[STATES][STATES];
    double[][] BL = new double[STATES][SYMBOLS];
    double[] PIL = new double[STATES];
    for (int i = 0; i < STATES; ++i) for (int j = 0; j < STATES; ++j) AL[i][j] = eln(A[i][j]);
    for (int i = 0; i < STATES; ++i) for (int j = 0; j < SYMBOLS; ++j) BL[i][j] = eln(B[i][j]);
    for (int i = 0; i < STATES; ++i) PIL[i] = eln(PI[i]);
    
    double[][] alpha = new double[T][STATES];
    forward(AL, BL, PIL, O, alpha);
    double s = 0;
    for (int i = 0; i < STATES; ++i) s += eexp(alpha[T - 1][i]);
    return s;
  }

  double forward(double[][] A, double[][] B, double[] PI, int[] O, double[][] alpha) {
    double product = 0, sum;
    
    sum = 0;
    int T = O.length;
    for (int i = 0; i < STATES; ++i) {
      alpha[0][i] = elnproduct(PI[i], B[i][O[0]]);
      sum += alpha[0][i];
    }
    product += eln(sum);
    
    for (int t = 1; t < T; ++t) {
      sum = 0;
      for (int i = 0; i < STATES; ++i) {
        alpha[t][i] = Double.NaN;
        for (int j = 0; j < STATES; ++j) {
          alpha[t][i] = elnsum(alpha[t][i], elnproduct(alpha[t - 1][j], A[j][i]));
        }
        alpha[t][i] = elnproduct(alpha[t][i], B[i][O[t]]);
        sum += alpha[t][i];
      }
      product += eln(sum);
    }

    return -product;
  }
  
  // HMM3
  public int[] viterbi(int[] O) {
    int K = A.length;
    int T = O.length;
    double[][] T1 = new double[K][T];
    int[][] T2 = new int[K][T];
    for (int i = 0; i < K; ++i) {
      T1[i][0] = PI[i] * B[i][O[0]];
      T2[i][0] = 0;
    }

    for (int i = 1; i < T; ++i) for (int j = 0; j < K; ++j) for (int k = 0; k < K; ++k) {
      double v = T1[k][i - 1] * A[k][j] * B[j][O[i]];
      if (v > T1[j][i]) {
        T1[j][i] = v;
        T2[j][i] = k;
      }
    }

    double max = 0;
    int[] z = new int[T];
    for (int k = 0; k < K; ++k) {
      double v = T1[k][T - 1];
      if (v > max) {
        max = v;
        z[T - 1] = k;
      }
    }
    for (int i = T - 1; i >= 1; --i) z[i - 1] = T2[z[i]][i];
    return z;
  }
  
  // HMM4
  void baumWelch(int[] O, int iterations) {
    double[][] alpha = new double[O.length][STATES];
    double[][] beta = new double[O.length][STATES];
    double[][] gamma = new double[O.length][STATES];
    double[][][] epsilon = new double[O.length][STATES][STATES];
    int T = O.length;
    
    //TODO Convert every to log probability on every iteration?
    for (int i = 0; i < STATES; ++i) for (int j = 0; j < STATES; ++j) A[i][j] = eln(A[i][j]);
    for (int i = 0; i < STATES; ++i) for (int j = 0; j < SYMBOLS; ++j) B[i][j] = eln(B[i][j]);
    for (int i = 0; i < STATES; ++i) PI[i] = eln(PI[i]);
    
    double l1 = -Double.MAX_VALUE;
    while (--iterations != 0) {
      
      // Forward
      double l2 = forward(A, B, PI, O, alpha);
      
      // Backward
      int STATES = A.length;
      for (int i = 0; i < STATES; ++i) beta[T - 1][i] = 0;
      for (int t = T - 2; t >= 0; --t) for (int i = 0; i < STATES; ++i) {
        beta[t][i] = Double.NaN;
        for (int j = 0; j < STATES; ++j) {
          beta[t][i] = elnsum(beta[t][i], elnproduct(A[i][j], elnproduct(B[j][O[t + 1]], beta[t + 1][j])));
        }
      }
      
      // Update
      //TODO Use scalings from forward pass instead.
      for (int t = 0; t < T; ++t) {
        double c = Double.NaN;
        for (int i = 0; i < STATES; ++i) {
          gamma[t][i] = elnproduct(alpha[t][i], beta[t][i]);
          c = elnsum(c, gamma[t][i]);
        }
        for (int i = 0; i < STATES; ++i) gamma[t][i] = elnproduct(gamma[t][i], -c);
      }
      for (int t = 0; t < O.length - 1; ++t) {
        double c = Double.NaN;
        for (int i = 0; i < STATES; ++i) for (int j = 0; j < STATES; ++j) {
          epsilon[t][i][j] = elnproduct(alpha[t][i], elnproduct(A[i][j],elnproduct(B[j][O[t + 1]],beta[t + 1][j])));
          c = elnsum(c, epsilon[t][i][j]);
        }
        for (int i = 0; i < STATES; ++i) for (int j = 0; j < STATES; ++j) epsilon[t][i][j] = elnproduct(epsilon[t][i][j], -c);
      }
      
      // Reestimate model.
      for (int i = 0; i < STATES; ++i) {
        PI[i] = eexp(gamma[0][i]);

        for (int j = 0; j < STATES; ++j) {
          double n = Double.NaN, d = Double.NaN;
          for (int t = 0; t < gamma.length - 1; ++t) {
            n = elnsum(n, epsilon[t][i][j]);
            d = elnsum(d, gamma[t][i]);
          }
          A[i][j] = eexp(elnproduct(n, -d));
        }

        for (int k = 0; k < SYMBOLS; ++k) {
          double n = Double.NaN, d = Double.NaN;
          for (int t = 0; t < O.length; ++t) {
            if (O[t] == k) n = elnsum(n, gamma[t][i]);
            d = elnsum(d, gamma[t][i]);
          }
          B[i][k] = eexp(elnproduct(n, -d));
        }
      }
      
      if (l2 <= l1) return;
      l1 = l2;
    }
  }
}
