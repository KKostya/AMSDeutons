#smearing=(30 20 40 25 35 50)

for s in {50..400..25}; do
    bsub -J run_$s -R "rusage[mem=20000]" -q 8nh job.sh $s
done

