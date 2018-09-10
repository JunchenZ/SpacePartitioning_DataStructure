#pragma once

#include "Point.hpp"

#include <random>


/* These generators just have 1 method: generate point.

They take a template parameter for the dimension and some constructor parameters for other stuff

*/

//Uniformly (evenly) distributed random points
template<int Dimension>
struct UniformGenerator{

  UniformGenerator(float min_, float max_)
	:min(min_), max(max_), rd{}, gen(rd()), dis(min_, max_) {}

  Point<Dimension> generatePoint(){

	std::array<float, Dimension> data;
	for(int i = 0; i < Dimension; ++i){
	  data[i] = dis(gen);
	}
	return Point<Dimension>{data};
  }
private:
  float min, max;
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen; //Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<> dis;
  
};

//Normally (Gaussian) distributed random points.  These will be clumped around mean.  Spread is determined by stdDev
template<int Dimension>
struct GaussianGenerator{

  GaussianGenerator(float mean_, float stdDev_)
	:mean(mean_), stdDev(stdDev_), rd{}, gen(rd()), dis(mean_, stdDev_) {}

  Point<Dimension> generatePoint(){

	std::array<float, Dimension> data;
	for(int i = 0; i < Dimension; ++i){
	  data[i] = dis(gen);
	}
	return Point<Dimension>{data};
  }
private:
  float mean, stdDev;
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen; //Standard mersenne_twister_engine seeded with rd()
  std::normal_distribution<> dis;
  
};

/*This function is useful for generating points to store/query, and points to use for KNN/Range queries

The struct just groups the 2 point sets together.
 */

template <int Dimension>
struct TrialData{
  std::vector<Point<Dimension> > training, testing;
};

template<int Dimension, typename Generator>
TrialData<Dimension> getTrialData(int trainingSize, int testingSize, Generator& gen){
  TrialData<Dimension> ret;
  for(int i = 0; i < trainingSize; ++i){
	ret.training.push_back(gen.generatePoint());
  }
  for(int i = 0; i < testingSize; ++i){
	ret.testing.push_back(gen.generatePoint());
  }
  return ret;
}
