for dir in /data/pB1045.*.out/
do
    FN=$(basename $dir)
    python ~/to_csv/mc_to_csv.py --in_directory $dir | gzip -c > ${FN}.gz
done
