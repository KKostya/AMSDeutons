#include "Tracker.h"

// Bit patterns for fits
int fit[6];
fit[0] = 0x78211;  //  1111000 0010 0001 0001
fit[1] = 0x63211;  //  1100011 0010 0001 0001
fit[2] = 0x0f211;  //  0001111 0010 0001 0001
fit[3] = 0x1c211;  //  0011100 0010 0001 0001
fit[4] = 0x3f211;  //  0111111 0010 0001 0001
fit[5] = 0x7e211;  //  1111110 0010 0001 0001


        // Tracker stuff
        int fitID1 = track->iTrTrackPar(1,1,1);
        int fitID2 = track->iTrTrackPar(1,2,1);
        int fitID3 = track->iTrTrackPar(1,3,1);

double Rup(AMSEvent * ev)
{
        data.Rup      = track->GetRigidity(fitID1);
        data.Rdown    = track->GetRigidity(fitID2);
        data.R        = track->GetRigidity(fitID3);
        data.Chisquare= track->GetChisq(fitID3);

        for(int nFit=0; nFit<6; nFit++)
        {
            data.chiq[nFit] = track->FitT(fit[nFit],-1);
            data.R_[nFit]   = track->GetRigidity(fit[nFit]);
        }

        TrTrackPar parametri = track->gTrTrackPar(fitID3);
        data.layernonusati = 0;
        for (int layer=2;layer<9;layer++) 
        {
            if(!parametri.TestHitLayerJ(layer)) data.layernonusati++;
            data.ResiduiX[layer-2]=-999999;
            data.ResiduiY[layer-2]=-999999;
            if(!track->TestHitLayerJ(layer)) continue;
            AMSPoint Residual_point = track->GetResidualJ(layer,fitID3);
            if(track->TestHitLayerJHasXY(layer))
                data.ResiduiX[layer-2] = Residual_point.x();
            data.ResiduiY[layer-2] = Residual_point.y(); // Theres always an Y hit
        }

        //Edep Tracker
        data.endepostatrack = 0;   
        for(int i=0; i<track->NTrRecHit();i++){
            TrRecHitR *hit=track->pTrRecHit(i);
            data.endepostatrack += hit->Sum();
        }


