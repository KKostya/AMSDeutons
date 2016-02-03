EIGENTMP=eigen_temp

wget http://bitbucket.org/eigen/eigen/get/3.3-beta1.tar.bz2 -O ${EIGENTMP}.tar.bz2

mkdir ${EIGENTMP}
tar xvvf ${EIGENTMP}.tar.bz2 -C ${EIGENTMP} --strip-components=1
cp -r ./${EIGENTMP}/Eigen .
cp -r ./${EIGENTMP}/unsupported/Eigen .
rm -rf ${EIGENTMP}
rm -rf ${EIGENTMP}.tar.bz2
