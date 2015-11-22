#pragma once
#include <vector>
#include <random>
#include <algorithm>
#include <functional>
#include <limits>
#include <utility>
#include <numeric>
#include <cmath>
using namespace std;

typedef vector<vector<double>> matrix;

inline matrix stochastic(matrix m)
{
  for (auto& r : m) {
    double sum = 0;
    for (auto& e : r) sum += e;
    for (auto& e : r) e /= sum;
  }
  return m;
}

inline matrix initialize_matrix(int rows, int columns)
{
  static auto generator = bind(uniform_real_distribution<double>(0, 1), mt19937());
  matrix m (rows); 
  for (auto& r : m) {
    r = vector<double> (columns);
    generate(r.begin(), r.end(), generator);
  }
  return stochastic(m);
}

class hmm
{
private:
  pair<matrix, matrix> forward(void) { return forward(O); }
  pair<matrix, matrix> forward(vector<int> observations)
  {
    matrix alpha = initialize_matrix(observations.size(), states);
    matrix scalings = initialize_matrix(1, observations.size());
    for (int t = 0; t < observations.size(); ++t)
    {
      scalings[0][t] = 0;
      for (int i = 0; i < states; ++i)
      {
        alpha[t][i] = 0;
        if (t == 0) alpha[t][i] += Pi[0][i];
        else for (int j = 0; j < states; ++j) alpha[t][i] += alpha[t-1][j]*A[j][i];
        alpha[t][i] *= B[i][observations[t]];
        scalings[0][t] += alpha[t][i];
      }
      scalings[0][t] = 1 / scalings[0][t];
      for (int i = 0; i < states; ++i) alpha[t][i] *= scalings[0][t];
    }
    
    return {alpha, scalings};
  }
  
  matrix backward(const matrix& scalings)
  {
    matrix beta = initialize_matrix(O.size(), states);

    for (int t = O.size()-1; t >= 0; --t)
    {
      for (int i = 0; i < states; ++i)
      {
        if (t == O.size()-1) beta[t][i] = scalings[0][t];
        else {
          beta[t][i] = 0;
          for (int j = 0; j < states; ++j) beta[t][i] += A[i][j]*B[j][O[t+1]]*beta[t+1][j];
          beta[t][i] *= scalings[0][t];
        }
      }
    }

    return beta;
  }
  
  pair<matrix, vector<matrix>> update(const matrix& alpha, const matrix& beta)
  {
    matrix gamma = initialize_matrix(O.size(), states);
    vector<matrix> epsilon (O.size());
    for (auto& e : epsilon) e = initialize_matrix(states, states);
    
    for (int t = 0; t < O.size()-1; ++t) 
    {
      double d = 0;
      for (int i = 0; i < states; ++i) for (int j = 0; j < states; ++j)
      {
        d += alpha[t][i]*A[i][j]*B[j][O[t+1]]*beta[t+1][j];
      }
      
      for (int i = 0; i < states; ++i)
      {
        gamma[t][i] = 0;
        for (int j = 0; j < states; ++j)
        {
          epsilon[t][i][j] = (alpha[t][i]*A[i][j]*B[j][O[t+1]]*beta[t+1][j]) / d;
          gamma[t][i] += epsilon[t][i][j];
        }
      }
    }
    return {gamma, epsilon};
  }

public:  
  int states, symbols;
  matrix A, B, Pi;
  vector<int> O;

  // Construct a HMM with the provided start values.
  hmm(matrix A, matrix B, matrix Pi) : A(A), B(B), Pi(Pi) {
    states = A.size();
    symbols = B[0].size();
  }
  
  // Construct a HMM with random values.
	hmm(int N, int M) : states(N), symbols(M) 
  {
    A = initialize_matrix(N, M);
    B = initialize_matrix(N, M);
    Pi = initialize_matrix(1, N);
  }

  // Combine model with other models.
  void merge(vector<hmm> hmms)
  {
    const auto n = hmms.size() + 1; 
    //TODO Merge observations as well?
    
    // Scale current values.
    for (int i = 0; i < states; ++i) for (int j = 0; j < states; ++j) A[i][j] /= n;
    for (int i = 0; i < states; ++i) for (int j = 0; j < symbols; ++j) B[i][j] /= n;
    for (int i = 0; i < states; ++i) Pi[0][i] /= n;

    // Add new values.
    for (const auto& hmm : hmms) 
    {
      for (int i = 0; i < states; ++i) for (int j = 0; j < states; ++j) A[i][j] += hmm.A[i][j] / n;
      for (int i = 0; i < states; ++i) for (int j = 0; j < symbols; ++j) B[i][j] += hmm.B[i][j] / n;
      for (int i = 0; i < states; ++i) Pi[0][i] += hmm.Pi[0][i] / n;
    }
        
    // Keep model row stochastic.
    stochastic(A);
    stochastic(B);
    stochastic(Pi);
  }
  
  // Guess the most likely upcoming emission.
  pair<int, double> next_emission()
  {    
    // Construct initial state probabilities with Viterbi.
    auto sequence = estimate_sequence_of_states();
    auto state_pdf = matrix(1, vector<double> (states, 0));
    state_pdf[0][sequence.back()] = 1;

    // Most probable emission.
    auto emission_pdf = next_emission_distribution(state_pdf);
    double certainty = 0;
    int emission = 0;
    for (int i = 0; i < emission_pdf[0].size(); ++i)
    {
      if (emission_pdf[0][i] > certainty)
      {
        certainty = emission_pdf[0][i];
        emission = i;
      }
    }
    
    return {emission, certainty};
  }

  // Calulate the probabity for the different emissions.
  matrix next_emission_distribution() { return next_emission_distribution(Pi); }
  matrix next_emission_distribution(matrix state_pdf)
  {
    matrix emission_pdf (1, vector<double> (symbols, 0));
    for (int i = 0; i < symbols; ++i) 
      for (int j = 0; j < states; ++j) 
        for (int k = 0; k < states; ++k)
          emission_pdf[0][i] += state_pdf[0][j] * A[j][k] * B[k][i];
    return stochastic(emission_pdf);
  }

  // Calculate the probability to observe a certain emission sequence with the Forward algorithm.
  double probability_of_emission_sequence() { return probability_of_emission_sequence(O); }
  double probability_of_emission_sequence(vector<int> observations)
  {
    auto scalings = forward(observations).second;
    double product = 1;
    for (auto e : scalings[0]) product *= e;
    return 1/product;
  }
  
  // Calculate the most likely sequence of hidden states with the Viterbi algorithm.
  vector<int> estimate_sequence_of_states()
  {
    matrix V (states, vector<double> (O.size()));
    vector<vector<int>> path (states, vector<int> (O.size()));

    for (int s = 0; s < states; ++s)
    {
      V[s][0] = Pi[0][s] * B[s][O[0]];
      path[s][0] = 0;
    }
      
    for (int t = 1; t < O.size(); ++t) for (int s = 0; s < states; ++s)
    {
      V[s][t] = 0;
      path[s][t] = 0;
      for (int i = 0; i < states; ++i)
      {
        double v = V[i][t - 1] * A[i][s] * B[s][O[t]];
        if (v > V[s][t])
        {
          V[s][t] = v;
          path[s][t] = i;
        }
      }
    }

    vector<int> sequence (O.size());
    double max = 0;
    sequence[O.size() - 1] = 0;
    for (int i = 0; i < states; ++i)
    {
      auto v = V[i][O.size() - 1];
      if (v > max)
      {
        max = v;
        sequence[O.size() - 1] = i;
      }
    }

    for (int i = O.size() - 2; i >= 0; --i) sequence[i] = path[sequence[i+1]][i + 1];
    return sequence;
  }
  
  // Train the model to maximize the probability of observing the given sequence of emissions with the Baum-Welch algorithm.
  void estimate_model(int iterations = 1)
  {
    double sequence_probability = numeric_limits<double>::lowest();
    while (iterations--)
    {
      auto p1 = forward();
      auto alpha = p1.first;
      auto scalings = p1.second;
      auto beta = backward(scalings);
      pair<matrix, vector<matrix>> p2 = update(alpha, beta);
      auto gamma = p2.first;
      auto epsilon = p2.second;
      
      // Update model.
      for (int i = 0; i < states; ++i) 
      {
        Pi[0][i] = gamma[0][i];
        
        for (int j = 0; j < states; ++j)
        {
          double n = 0, d = 0;
          for (int t = 0; t < O.size() - 1; ++t)
          {
            n += epsilon[t][i][j];
            d += gamma[t][i];
          }
          A[i][j] = n/d;
        }
        
        for (int j = 0; j < symbols; ++j)
        {
          double n = 0, d = 0;
          for (int t = 0; t < O.size() - 1; ++t)
          {
            if (O[t] == j) n += gamma[t][i];
            d += gamma[t][i];
          }
          B[i][j] = n/d;
        }
      }

      // Stop training early if converged.
      double sum = 0;
      for (int i = 0; i < O.size(); ++i) sum -= log(scalings[0][i]);
      if (sum <= sequence_probability) return;
      sequence_probability = sum;
    }
  }
};