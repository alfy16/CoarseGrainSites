
#include <chrono>

#include "kmc_topology_feature.hpp"

using namespace std;

namespace kmccoursegrain {

  void occupyTopology_(KMC_TopologyFeature* feature) {
    ++(feature->occupied_);
    ++(feature->total_visit_freq_);
  }

  void occupyTopology_(KMC_TopologyFeature* feature, int&) {
    ++(feature->occupied_);
    ++(feature->total_visit_freq_);
  }

  void vacateTopology_(KMC_TopologyFeature* feature){
    --(feature->occupied_);
  }

  void vacateTopology_(KMC_TopologyFeature* feature,int&){
    --(feature->occupied_);
  }

  bool isOccupiedTopology_(KMC_TopologyFeature* feature){
    return feature->occupied_>0;
  }

  bool isOccupiedTopology_(KMC_TopologyFeature* feature,int&){
    return feature->occupied_>0;
  }

  KMC_TopologyFeature::KMC_TopologyFeature(){
    auto seed = chrono::system_clock::now().time_since_epoch().count();
    random_engine_ = mt19937(seed);
    random_distribution_ = uniform_real_distribution<double>(0.0, 1.0);
    occupied_ = 0;
    escape_time_constant_ = 0.0;
    total_visit_freq_ = 0;
  
    occupy_ptr_ = &occupyTopology_;
    occupy_siteId_ptr_ = &occupyTopology_;

    vacate_ptr_ = vacateTopology_;
    vacate_siteId_ptr_ = vacateTopology_;

    isOccupied_ptr_ = isOccupiedTopology_;
    isOccupied_siteId_ptr_ = isOccupiedTopology_;
  }

  void KMC_TopologyFeature::setRandomSeed(const unsigned long seed){
    random_engine_ = mt19937(seed);
  }

  double KMC_TopologyFeature::getDwellTime(){
    double number = random_distribution_(random_engine_);
    return (-1.0)*log(number) * escape_time_constant_;
  }

  int KMC_TopologyFeature::pickNewSiteId(){
    throw std::runtime_error("Cannot pick new site virtual method must be "
        "overloaded.");
  }

}
