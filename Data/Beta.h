
// Beta and RICH

double Beta(AMSEventR * ev)
{
    ParticleR *  particle    = ev->pParticle(0);
    if(particle->pBetaH()) data.Beta = particle->pBetaH()->GetBeta();
}
data.Betacorr=0;
if(data.Beta>=1) data.Betacorr = data.Beta/(2*data.Beta-1);
else data.Betacorr = data.Beta;

