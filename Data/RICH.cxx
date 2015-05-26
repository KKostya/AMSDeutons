#include "RICH.h"

double BetaRICH(AMSEventR * ev ) { 
    if(!ev->pRichRing(0)) return  -1;
    return ev->pRichRing(0)->getBeta();
}

/** @name User accessor methods
 *  These methods provide user level access to the necessary RICH reconstructed quantities.
 * These are preferred to directly accessing the public attributes in the class and in some cases they provided further functionality.
 */
///@{

/// Distance of the track impacto point in the radiator to the border of the radiator tile
double DistanceTileBorder(AMSEventR* ev){
    if(!ev->pRichRing(0)) return -1;
    return ev->pRichRing(0)->DistanceTileBorder();
}
/// Compute the width of the reconstructed ring measured in the expected width.
/// \param usedInsteadNpCol ignore the signal collected in the hits if set to true
double RingWidth(AMSEventR* ev){
    if(!ev->pRichRing(0)) return -1;
    return ev->pRichRing(0)->RingWidth();
}

//
// Brand new user interface
//
/// Beta of the event
/// \return Beta
    float getBeta(AMSEventR* ev){
    if(!ev->pRichRing(0)) return 0;
    return ev->pRichRing(0)->getBeta();
}

/// Charge corrections fail flag (-1/0/1 : Not/Done/Failed)
int PmtCorrectionsFailed(AMSEventR* ev){
    if(!ev->pRichRing(0)) return -1;
    return ev->pRichRing(0)->PmtCorrectionsFailed();
}
/// Total number of used hits in the ring
int getUsedHits(AMSEventR* ev){
    if(!ev->pRichRing(0)) return -1;
    return ev->pRichRing(0)->getUsedHits();
}

/// Total number of photoelectrons in the ring.
float getPhotoElectrons(AMSEventR* ev){
    if(!ev->pRichRing(0)) return -1;
    return ev->pRichRing(0)->getPhotoElectrons();
}

float getExpectedPhotoElectrons(AMSEventR* ev){
    if(!ev->pRichRing(0)) return -1;
    return ev->pRichRing(0)->getExpectedPhotoElectrons();
}

/// Continuous Z^2 estimate for this ring
float getCharge2Estimate(AMSEventR* ev){
    if(!ev->pRichRing(0)) return -1;
    return ev->pRichRing(0)->getCharge2Estimate();
}

/// Estimation of the error of the reconstructed beta
/// \return Estimate of the error of the reconstructed beta
    float getBetaError(AMSEventR* ev){
    if(!ev->pRichRing(0)) return -1;
    return ev->pRichRing(0)->getBetaError();
}
/// Quality parameter, providing the probability result of applying a Kolmogorov test to the distribution of charge along the ring.
/// This quantity is almost uniformly distributed between 0 and 1 for rings correctly reconstructed, and peaks at 0 for incorrectly reconstructed ones.
/// \return Kolmogorov test probability.
float getProb(AMSEventR* ev){
    if(!ev->pRichRing(0)) return 0;
    return ev->pRichRing(0)->getProb();
}
/// Quality parameter providing the width of the distribution of charge around the ring over the expected one.
/// This quantity should be close to one from above for correctly reconstructed rings, and large otherwise.
/// \param usedInsteadNpCol Is the same parameter used in RingWidth
/// \return Width of the ring
float getWidth(AMSEventR* ev){
    if(!ev->pRichRing(0)) return -1;
    return ev->pRichRing(0)->getWidth();
}

/// \return Uncorrected index associated to the track crossing point.
    float getRawIndexUsed(AMSEventR* ev){
    if(!ev->pRichRing(0)) return -1;
    return ev->pRichRing(0)->getRawIndexUsed();
}
/// \return Index associated to the track crossing point.
float getIndexUsed(AMSEventR* ev){
    if(!ev->pRichRing(0)) return -1;
    return ev->pRichRing(0)->getIndexUsed();
}
/// The track parameters extrapolated to the radiator as used in the reconstruction.
/// \return A pointer to an array of 5 floats, corresponding to x,y,z theta and phi of the track used in the reconstruction
std::vector<float> getTrackEmissionPoint(AMSEventR* ev){
    if(!ev->pRichRing(0)) return std::vector<float>();
    const float *p = ev->pRichRing(0)->getTrackEmissionPoint();
    return std::vector<float>(p,p+5);
}

/// Compute the absolute value of the difference of the recontructed beta between the algorithm used in RichRingR class and the one used in RichRingBR
/// \return Difference in the reconstructed beta between the two RICH reconstruction algorithms
float getBetaConsistency(AMSEventR* ev){
    if(!ev->pRichRing(0)) return -1;
    return ev->pRichRing(0)->getBetaConsistency();
}
/// Number of hits in the ring
int getHits(AMSEventR* ev)          {
    if(!ev->pRichRing(0)) return -1;
    return ev->pRichRing(0)->getHits();
}
/// Number of pmts in the ring
int   getPMTs(AMSEventR* ev){
    if(!ev->pRichRing(0)) return -1;
    return ev->pRichRing(0)->getPMTs();
}
/// Number of hits which are consistent with reflected photons
int   getReflectedHits(AMSEventR* ev) {
    if(!ev->pRichRing(0)) return -1;
    return ev->pRichRing(0)->getReflectedHits();
}
/// Simple statistical test to check if the hit by hit charge is consistent with PMT by PMT one
float getPMTChargeConsistency(AMSEventR* ev){
    if(!ev->pRichRing(0)) return -1;
    return ev->pRichRing(0)->getPMTChargeConsistency();
}
///@}

/** @name Interface to retrieve quality estimates of the uniformity corrections
 * This is only availble if the uniformity corrections are used. Otherwise the
 * functions return -1.
 */
///@{
// Expected resolution for Z=1 particles
float getBetaExpectedResolution(AMSEventR* ev){
    if(!ev->pRichRing(0)) return -999;
    return ev->pRichRing(0)->getBetaExpectedResolution();
}
// Expected Rms of the distribution of beta for Z=1 beta=1 particles.
// This gives an estimate of how likely is the event to have tails
float getBetaExpectedRms(AMSEventR* ev){
    if(!ev->pRichRing(0)) return -1;
    return ev->pRichRing(0)->getBetaExpectedRms();
}

float getChargeExpectedRms(AMSEventR* ev){
    if(!ev->pRichRing(0)) return -1;
    return ev->pRichRing(0)->getChargeExpectedRms();
}
