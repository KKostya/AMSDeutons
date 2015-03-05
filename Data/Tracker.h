
void Run   (AMSEventR * ev, std::ostream & output){ output <<  ev->fHeader.Run;   }
void Event (AMSEventR * ev, std::ostream & output){ output <<  ev->fHeader.Event; }
void UTime (AMSEventR * ev, std::ostream & output){ output <<  ev->UTime();       }
void ThetaM(AMSEventR * ev, std::ostream & output){ output <<  ev->fHeader.ThetaM;}

