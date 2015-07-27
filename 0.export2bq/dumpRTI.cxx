// std includes
#include <tuple>
#include <functional>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <root_setup.h>

// source /afs/cern.ch/sw/lcg/contrib/gcc/4.8/x86_64-slc6/setup.sh

std::fstream fs;

typedef std::tuple<std::string, std::function<void(AMSSetupR::RTI &)>> namedFunc;

template<typename T>
namedFunc make_namedFunc(std::string s, T f)
{
    return std::make_tuple(s, std::function<void(AMSSetupR::RTI &)>(f));
}

int main(int argc, char * argv[])
{
    int c;
    std::string outFname;
    unsigned int start = 0, end = 0;
    while((c = getopt(argc, argv, "o:i:f:")) != -1) {
        if(c == 'o') outFname = std::string(optarg);
        if(c == 'i') start = atoi(optarg);
        if(c == 'f') end   = atoi(optarg);
    }
    if(outFname.empty()) return 1;

    fs.open(outFname, std::fstream::out);
    fs << std::fixed;

    AMSSetupR setup;
    AMSSetupR::RTI::UseLatest(6);
    AMSSetupR::RTI rti;

    std::vector<namedFunc> variables{
        make_namedFunc("Run",           [](AMSSetupR::RTI & rti){ fs << rti.run;   }),
        make_namedFunc("BadRunReason",  [](AMSSetupR::RTI & rti){ std::string s; rti.IsBadRun(s); fs << s; }),
        make_namedFunc("FirstEvent",    [](AMSSetupR::RTI & rti){ fs << rti.evno;  }),
        make_namedFunc("LastEvent",     [](AMSSetupR::RTI & rti){ fs << rti.evnol; }),
        make_namedFunc("Lifetime",      [](AMSSetupR::RTI & rti){ fs << rti.lf;    }),
        make_namedFunc("IsInSAA",       [](AMSSetupR::RTI & rti){ fs << rti.IsInSAA();   }),

        make_namedFunc("JMDCtime",      [](AMSSetupR::RTI & rti){ fs << rti.gettime(0,0);}),
        make_namedFunc("UTCtime",       [](AMSSetupR::RTI & rti){ fs << rti.gettime(1,0);}),
        make_namedFunc("JMDCtimeLast",  [](AMSSetupR::RTI & rti){ fs << rti.gettime(0,1);}),
        make_namedFunc("UTCtimeLast",   [](AMSSetupR::RTI & rti){ fs << rti.gettime(1,1);}),

        make_namedFunc("ThetaM",        [](AMSSetupR::RTI & rti){ fs << rti.getthetam(); }),
        make_namedFunc("PhiM",          [](AMSSetupR::RTI & rti){ fs << rti.getphim();   }),
        make_namedFunc("betaSun",       [](AMSSetupR::RTI & rti){ fs << rti.getbetasun();}),

        make_namedFunc("ThetaS",        [](AMSSetupR::RTI & rti){ fs << rti.theta;       }),
        make_namedFunc("PhiS",          [](AMSSetupR::RTI & rti){ fs << rti.phi;         }),
        make_namedFunc("R",             [](AMSSetupR::RTI & rti){ fs << rti.r;           }),
        make_namedFunc("Zenith",        [](AMSSetupR::RTI & rti){ fs << rti.zenith;      }),

        make_namedFunc("issRoll",       [](AMSSetupR::RTI & rti){ float r,p,y; rti.getissatt(r,p,y); fs << r; }),
        make_namedFunc("issPitch ",     [](AMSSetupR::RTI & rti){ float r,p,y; rti.getissatt(r,p,y); fs << p; }),
        make_namedFunc("issYaw",        [](AMSSetupR::RTI & rti){ float r,p,y; rti.getissatt(r,p,y); fs << y; }),
        make_namedFunc("issVelS",       [](AMSSetupR::RTI & rti){ float vs,vp,vt; rti.getissatt(vs,vp,vt); fs << vs; }),
        make_namedFunc("issVelPhi ",    [](AMSSetupR::RTI & rti){ float vs,vp,vt; rti.getissatt(vs,vp,vt); fs << vp; }),
        make_namedFunc("issVelTheta",   [](AMSSetupR::RTI & rti){ float vs,vp,vt; rti.getissatt(vs,vp,vt); fs << vt; }),

        make_namedFunc("Cutoff25neg",   [](AMSSetupR::RTI & rti){ fs << rti.cf[0][0]; }),
        make_namedFunc("Cutoff30neg",   [](AMSSetupR::RTI & rti){ fs << rti.cf[1][0]; }),
        make_namedFunc("Cutoff35neg",   [](AMSSetupR::RTI & rti){ fs << rti.cf[2][0]; }),
        make_namedFunc("Cutoff40neg",   [](AMSSetupR::RTI & rti){ fs << rti.cf[3][0]; }),
        make_namedFunc("Cutoff25pos",   [](AMSSetupR::RTI & rti){ fs << rti.cf[0][1]; }),
        make_namedFunc("Cutoff30pos",   [](AMSSetupR::RTI & rti){ fs << rti.cf[1][1]; }),
        make_namedFunc("Cutoff35pos",   [](AMSSetupR::RTI & rti){ fs << rti.cf[2][1]; }),
        make_namedFunc("Cutoff40pos",   [](AMSSetupR::RTI & rti){ fs << rti.cf[3][1]; }),

        make_namedFunc("IGRF25neg",     [](AMSSetupR::RTI & rti){ fs << rti.cfi[0][0]; }),
        make_namedFunc("IGRF30neg",     [](AMSSetupR::RTI & rti){ fs << rti.cfi[1][0]; }),
        make_namedFunc("IGRF35neg",     [](AMSSetupR::RTI & rti){ fs << rti.cfi[2][0]; }),
        make_namedFunc("IGRF40neg",     [](AMSSetupR::RTI & rti){ fs << rti.cfi[3][0]; }),
        make_namedFunc("IGRF25pos",     [](AMSSetupR::RTI & rti){ fs << rti.cfi[0][1]; }),
        make_namedFunc("IGRF30pos",     [](AMSSetupR::RTI & rti){ fs << rti.cfi[1][1]; }),
        make_namedFunc("IGRF35pos",     [](AMSSetupR::RTI & rti){ fs << rti.cfi[2][1]; }),
        make_namedFunc("IGRF40pos",     [](AMSSetupR::RTI & rti){ fs << rti.cfi[3][1]; }),

        make_namedFunc("GalacticLat",   [](AMSSetupR::RTI & rti){ fs << rti.glat;    }),
        make_namedFunc("GalacticLon",   [](AMSSetupR::RTI & rti){ fs << rti.glong;   }),
        make_namedFunc("nExistEvents",  [](AMSSetupR::RTI & rti){ fs << rti.nev;     }),
        make_namedFunc("nAbsentEvents", [](AMSSetupR::RTI & rti){ fs << rti.nerr;    }),
        make_namedFunc("nPartcles",     [](AMSSetupR::RTI & rti){ fs << rti.npart;   }),
        make_namedFunc("nTriggger",     [](AMSSetupR::RTI & rti){ fs << rti.ntrig;   }),
        make_namedFunc("avgNTRDrh",     [](AMSSetupR::RTI & rti){ fs << rti.mtrdh;   }),
        make_namedFunc("nHWerr",        [](AMSSetupR::RTI & rti){ fs << rti.nhwerr;  }),
    };

    for(auto var: variables) 
        fs << std::get<0>(var) << ","; 
    fs << "\n";
        
    for(int t = start; t < end; t++ )
    {
        setup.getRTI(rti, t);
        for(auto var: variables) 
        { 
            std::get<1>(var)(rti); 
            fs << ","; 
        }
        fs << "\n"; 
    }
}

