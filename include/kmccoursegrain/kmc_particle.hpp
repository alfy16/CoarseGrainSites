#ifndef KMCCOURSEGRAIN_KMC_PARTICLE_HPP
#define KMCCOURSEGRAIN_KMC_PARTICLE_HPP

#include <map>
#include <list>
#include <vector>
#include "kmc_constants.hpp"

namespace kmccoursegrain{

  /**
   * \brief Particle class meant to be inherited 
   *
   * This class is designed to be inhertied by a class external to the library. It
   * provides the necessary interface required by functions internal to the
   * library. A key point of the class is to keep track of the particles movement
   * between sites. In this way the particle may be thought of having a memory. 
   * The size of the memory can also be controlled. In this way it is possible 
   * during runtime for the library to note if the particle becomes stuck moving
   * between two or more sites. The library can then course grain the low energy
   * sites and hopefully improve the performance.  
   **/
  class KMC_Particle{
    public: 
      KMC_Particle();

      /**
       * \brief Sets the size of the particles memory
       *
       * This allows you to change the memory of the particle. The larger the
       * memory the correspondingly larger computer resources. It essentially
       * allows the particle to record the number of unique sites visited. So
       * if a memory of 4 is set than a total of unique sites are recorded at a
       * time. 
       *
       * \param[in] numberSitesToRemember
       **/
      void setMemoryCapacity(unsigned int numberSitesToRemember);

      /**
       * \brief Returns the size of the memory
       **/
      unsigned int getMemoryCapacity() const;

      /** 
       * \brief Record the id of the site the particle currently resides on
       *
       * Default value is assigned for the clusterId if it is not provided
       *
       * \param[in] siteId id of the site the particle is to occupy
       * \param[in] clusterId id of the cluster if there is one that the site 
       * belongs to, by default this is unassigned
       **/
      void occupySite(int siteId, int clusterId = constants::unassignedId);

      /** 
       * \brief Return the number of times the particle has visited the
       * currently occupied site or cluster
       *
       * \return a pair, the string indicates if it is on a cluster or a site,
       * the integer is the frequency.
       **/
      int getVisitationFrequencyOfCurrentlyOccupiedSite();

      /**
       * \brief Grabs the id of the site the particle currently resides on
       *
       * \return is of site
       **/
      int getIdOfSiteCurrentlyOccupying() const;

      /**
       * \brief Returns a list of the particles memory
       *
       * The memory consists of recording the number of unique sites visited
       * most recently and the corresponding number of times the sites have been
       * visited and the clusters the site might be attached too. 
       *
       * \return A vector of vectors is returned the first int is the id of the 
       * site, the second int is the id of the cluster. The third int is the 
       * count of the number of times the particle has visited the site. Element
       * (0) is the most recently visited site followed by sites that were 
       * visited later.
      **/
      std::vector<std::vector<int>> getMemory();

      /**
       * \brief Remove a memory from a particle
       *
       * This is necessary if the memory is out of date
       *
       * \param[in] siteId the id of the site to be removed from memory
       **/
      void removeMemory(const int siteId);

      /**
       * \brief Record the site the particle will move to next
       *
       * \param[in] site id the particle will try to move to if it remains 
       * unoccupied.
       **/
      void setPotentialSite(const int siteId) { potentialSite_ = siteId; }

      /**
       * \brief the ability to reset the frequency by which a particle has been 
       * visited
       *
       * Will throw an error if the site is not in memory.
       *
       * \param[in] siteId id of the site whos visitation frequency is to be 
       * reset
       **/
      void resetVisitationFrequency(const int siteId);

      /**
       * \brief Set the cluster a site belongs too
       *
       * If a site is updated and now belongs to a cluster this information 
       * can be recorded. 
       **/
      void setClusterSiteBelongsTo(const int siteId, const int clusterId);

      /**
       * \brief Return the id of the site the particle will attempt to move to
       **/
      int getPotentialSite() const; 

      /**
       * \brief Get the dwell time 
       **/
      double getDwellTime() const { return dwelltime_; }

      /**
       * \brief Set the dwell time
       **/
      void setDwellTime(const double dwelltime) { dwelltime_ = dwelltime; }
    private:

      struct Memory {
        int siteId;
        int clusterId;
        int visitFrequency;
      };

      /// The next site the particle will try to move to
      int potentialSite_;

      /// The length of time the particle will remain on the current site
      double dwelltime_;

      /** 
       * \brief List that is essentially the particles memory
       *
       * Once a site is attached to a cluster, a single memory is stored per 
       * cluster, thus if two sites are part of the same cluster, the memory
       * will reflect the most recently visited site. 
       **/
      std::list<Memory> memoryQueue_;

      /// Does the particle remember visiting either the cluster of the site
      bool remember_(const int siteId,const int clusterId);
      /// Does the particle remember visiting the site
      bool rememberSite_(const int siteId);
      /// Does the particle remember visiting the cluster
      bool rememberCluster_(const int clusterId);

      /**
       * \brief Make the site id `siteId` the most currently remembered site
       *
       * This function works by moving the Memory of the site to the top of the
       * memoryQueue.
       *
       * \param[in] siteId id of the site most recently visited by the particle
       **/
      void refreshMemoryOfSite_(const int siteId);
      void refreshMemoryOfCluster_(const int clusterId);

      /**
       * \brief Creates a new memory
       *
       * Because the memory is fixed in size, if a new memory is needed then the
       * oldest memory is removed from the list and a new memory is created such
       * that it appears at the top of the list. 
       * 
       * \param[in] siteId of a site that is not yet stored in the memory of the 
       * particle but has just been visited
       **/
      void createNewMemory_(int siteId, int clusterId);

      /// Will move the iterator to the location of the memoryQueue_ where 
      /// siteId is found
      std::list<Memory>::iterator getMemoryIteratorSite_(const int siteId);
      std::list<Memory>::iterator getMemoryIteratorCluster_(const int clusterId);
  };

}
#endif // KMCCOURSEGRAIN_KMC_PARTICLE_HPP
