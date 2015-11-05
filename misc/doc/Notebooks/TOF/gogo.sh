smearing=(30 20 40 25 35 50)

for s in ${smearing[@]}; do
    ipython smearing.py $s
done

