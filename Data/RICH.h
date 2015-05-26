#ifndef RICH_H
#define RICH_H

// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>
#include <vector>

// Local includes

double BetaRICH(AMSEventR * ev );

/** @name User accessor methods
 *  These methods provide user level access to the necessary RICH reconstructed quantities.
 * These are preferred to directly accessing the public attributes in the class and in some cases they provided further functionality.
 */
///@{
/// Distance of the track impacto point in the radiator to the border of the radiator tile
double DistanceTileBorder(AMSEventR* ev);

/// Compute the width of the reconstructed ring measured in the expected width.
/// \param usedInsteadNpCol ignore the signal collected in the hits if set to true
double RingWidth(AMSEventR* ev);

//
// Brand new user interface
//
/// Beta of the event
/// \return Beta
float getBeta(AMSEventR* ev);

/// Charge corrections fail flag (-1/0/1 : Not/Done/Failed)
int PmtCorrectionsFailed(AMSEventR* ev);

/// Total number of used hits in the ring
int getUsedHits(AMSEventR* ev);

/// Total number of photoelectrons in the ring.
float getPhotoElectrons(AMSEventR* ev);

/// Number of expected photoelectrons for a Z=1 ring with the reconstruction input parameters of the current event.
float getExpectedPhotoElectrons(AMSEventR* ev);

/// Continuous Z^2 estimate for this ring
float getCharge2Estimate(AMSEventR* ev);

/// Estimation of the error of the reconstructed beta
/// \return Estimate of the error of the reconstructed beta
float getBetaError(AMSEventR* ev);

/// Quality parameter, providing the probability result of applying a Kolmogorov test to the distribution of charge along the ring.
/// This quantity is almost uniformly distributed between 0 and 1 for rings correctly reconstructed, and peaks at 0 for incorrectly reconstructed ones.
/// \return Kolmogorov test probability.
float getProb(AMSEventR* ev);

/// Quality parameter providing the width of the distribution of charge around the ring over the expected one.
/// This quantity should be close to one from above for correctly reconstructed rings, and large otherwise.
/// \param usedInsteadNpCol Is the same parameter used in RingWidth
/// \return Width of the ring
float getWidth(AMSEventR* ev);


/// \return Uncorrected index associated to the track crossing point.
float getRawIndexUsed(AMSEventR* ev);

/// \return Index associated to the track crossing point.
float getIndexUsed(AMSEventR* ev);

/// The track parameters extrapolated to the radiator as used in the reconstruction.
/// \return A pointer to an array of 5 floats, corresponding to x,y,z theta and phi of the track used in the reconstruction
std::vector<float> getTrackEmissionPoint(AMSEventR* ev);

/// Compute the absolute value of the difference of the recontructed beta between the algorithm used in RichRingR class and the one used in RichRingBR
/// \return Difference in the reconstructed beta between the two RICH reconstruction algorithms
float getBetaConsistency(AMSEventR* ev);

/// Number of hits in the ring
int getHits(AMSEventR* ev);

/// Number of pmts in the ring
int getPMTs(AMSEventR* ev);

/// Number of hits which are consistent with reflected photons
int   getReflectedHits(AMSEventR* ev);

/// Simple statistical test to check if the hit by hit charge is consistent with PMT by PMT one
float getPMTChargeConsistency(AMSEventR* ev);

///@}

/** @name Interface to retrieve quality estimates of the uniformity corrections
 * This is only availble if the uniformity corrections are used. Otherwise the
 * functions return -1.
 */
///@{
// Expected resolution for Z=1 particles
float getBetaExpectedResolution(AMSEventR* ev);

// Expected Rms of the distribution of beta for Z=1 beta=1 particles.
// This gives an estimate of how likely is the event to have tails
float getBetaExpectedRms(AMSEventR* ev);
float getChargeExpectedRms(AMSEventR* ev);



#endif //RICH_H
