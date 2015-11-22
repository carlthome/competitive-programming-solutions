import java.util.*;
public class Player {
  static final int SPECIES = 6;
  static final Action cDontShoot = new Action(-1, -1);
  int[] speciesCounts = new int[SPECIES];
  final HMM[] speciesModels = new HMM[SPECIES];
  List<HMM> birdModels = new ArrayList<HMM>(), shootModels = new ArrayList<HMM>();
  int round = -1, time = 0;
  boolean STORK = false;

  public Player() {
    for (int i = 0; i < SPECIES; ++i) speciesModels[i] = new HMM();
  }

  public Action shoot(GameState pState, Deadline pDue) {
    ++time;
    
    // New round: new birds!
    if (round != pState.getRound()) {
      round = pState.getRound();
      time = 0;
      shootModels.clear();
      for (int i = 0; i < pState.getNumBirds(); ++i) 
        shootModels.add(new HMM());
    }
    
    // Observe birds and train models.
    if (time > 99 - pState.getNumBirds() * 1.5 + 1) {
      int iterations = 120 / pState.getNumBirds();
      double max = 0.5 + iterations / 40.0;
      Action action = cDontShoot;
      for (int i = 0; i < pState.getNumBirds(); ++i) {
        Bird b = pState.getBird(i);

        if (!b.isDead()) {
          shootModels.set(i, new HMM(b, iterations, shootModels.get(i)));
          
          int T = 0;
          for (int j = 0; j < b.getSeqLength() && !b.wasDead(j); ++j) ++T;
          int[] O = new int[T];
          for (int j = 0; j < T; ++j) O[j] = b.getObservation(j);    
          
          double[] eps = shootModels.get(i).nextEmissionDistribution(O);
          for (int j = 0; j < eps.length; ++j) {
            if (eps[j] > max) {
              max = eps[j];
              action = new Action(i, j);
            }
          }
        }
      }
      return action;
    } else return cDontShoot;
  }
  
  public int[] guess(GameState pState, Deadline pDue) {    
    int[] guesses = new int[pState.getNumBirds()];

    if (pState.getRound() == 0) { 
      // Make an arbitrary guess of every bird's species the first round.
      for (int i = 0; i < pState.getNumBirds(); ++i) {
        birdModels.add(new HMM(pState.getBird(i), 500));
        guesses[i] = Constants.SPECIES_PIGEON;
      }
    } else {
      // See which bird observations fit best with each model.
      birdModels = new ArrayList<HMM>();
      for (int i = 0; i < pState.getNumBirds(); ++i) {
        birdModels.add(new HMM(pState.getBird(i), 500));
        
        int species = -1;
        double max = 0;
        for (int j = 0; j < SPECIES; ++j) {
          if (speciesCounts[j] == 0) continue;
          double d = speciesModels[j].estimateBird(pState.getBird(i));
          if (d > max) {
            max = d;
            species = j;
          }
        }
        
        guesses[i] = (species == -1) ? Constants.SPECIES_UNKNOWN : species;
      }
    }

    return guesses;
  }
  
  public void hit(GameState pState, int pBird, Deadline pDue) {
  }

  public void reveal(GameState pState, int[] pSpecies, Deadline pDue) {    
    int size = pSpecies.length;
    List<List<HMM>> answers = new ArrayList<List<HMM>>(SPECIES);
    for (int i = 0; i < SPECIES; ++i) 
      answers.add(new ArrayList<HMM>());
    
    for (int i = 0; i < size; ++i) 
      if (pSpecies[i] != Constants.SPECIES_UNKNOWN) {
        answers.get(pSpecies[i]).add(birdModels.get(i));
        if (pSpecies[i] == Constants.SPECIES_BLACK_STORK) STORK = true;
      }

    birdModels.clear();
    for (int i = 0; i < SPECIES; ++i) {
      if (answers.get(i).isEmpty()) continue;
      int w = speciesCounts[i];
      if (w > 0) {
        answers.get(i).add(speciesModels[i]);
      }

      speciesModels[i] = HMM.merge(answers.get(i));
      speciesCounts[i] += answers.get(i).size() - (w > 0 ? 1 : 0);
    }
  }
}
