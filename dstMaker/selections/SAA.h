bool saa(float phi,float theta) 
{
    double const Pi=3.141592;
    phi=(phi-2*Pi)*100;
    theta=theta*100;
    // phi, theta geographic
    bool ssa_good=true;
    if(phi>=-74 && phi<-72 && theta>=-23 && theta<-18) ssa_good=false;
    if(phi>=-72 && phi<-70 && theta>=-27 && theta<-15) ssa_good=false;
    if(phi>=-70 && phi<-68 && theta>=-31 && theta<-13) ssa_good=false;
    if(phi>=-68 && phi<-66 && theta>=-34 && theta<-12) ssa_good=false;
    if(phi>=-66 && phi<-64 && theta>=-36 && theta<-11) ssa_good=false;
    if(phi>=-64 && phi<-62 && theta>=-38 && theta<-10) ssa_good=false;
    if(phi>=-62 && phi<-60 && theta>=-40 && theta<-10) ssa_good=false;
    if(phi>=-60 && phi<-58 && theta>=-40 && theta<-9) ssa_good=false;
    if(phi>=-58 && phi<-56 && theta>=-42 && theta<-8) ssa_good=false;
    if(phi>=-56 && phi<-54 && theta>=-43 && theta<-8) ssa_good=false;
    if(phi>=-54 && phi<-52 && theta>=-43 && theta<-8) ssa_good=false;
    if(phi>=-52 && phi<-50 && theta>=-43 && theta<-8) ssa_good=false;
    if(phi>=-50 && phi<-48 && theta>=-43 && theta<-8) ssa_good=false;
    if(phi>=-48 && phi<-46 && theta>=-44 && theta<-8) ssa_good=false;
    if(phi>=-46 && phi<-44 && theta>=-44 && theta<-8) ssa_good=false;
    if(phi>=-44 && phi<-42 && theta>=-44 && theta<-9) ssa_good=false;
    if(phi>=-42 && phi<-40 && theta>=-43 && theta<-9) ssa_good=false;
    if(phi>=-40 && phi<-38 && theta>=-43 && theta<-11) ssa_good=false;
    if(phi>=-38 && phi<-36 && theta>=-42 && theta<-13) ssa_good=false;
    if(phi>=-36 && phi<-34 && theta>=-42 && theta<-12) ssa_good=false;
    if(phi>=-34 && phi<-32 && theta>=-42 && theta<-14) ssa_good=false;
    if(phi>=-32 && phi<-30 && theta>=-41 && theta<-16) ssa_good=false;
    if(phi>=-30 && phi<-28 && theta>=-40 && theta<-17) ssa_good=false;
    if(phi>=-28 && phi<-26 && theta>=-40 && theta<-18) ssa_good=false;
    if(phi>=-26 && phi<-24 && theta>=-39 && theta<-19) ssa_good=false;
    if(phi>=-24 && phi<-22 && theta>=-38 && theta<-20) ssa_good=false;
    if(phi>=-22 && phi<-20 && theta>=-37 && theta<-21) ssa_good=false;
    if(phi>=-20 && phi<-18 && theta>=-36 && theta<-22) ssa_good=false;
    if(phi>=-18 && phi<-16 && theta>=-35 && theta<-24) ssa_good=false;
    if(phi>=-16 && phi<-14 && theta>=-34 && theta<-25) ssa_good=false;
    if(phi>=-14 && phi<-12 && theta>=-32 && theta<-26) ssa_good=false;
    if(phi>=-12 && phi<-10 && theta>=-31 && theta<-27) ssa_good=false;
    if(phi>=-10 && phi<-8 && theta>=-28 && theta<-27) ssa_good=false;
    return ssa_good;
}

