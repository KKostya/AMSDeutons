function concat {
    dirs=(${dirs})

    for d in ${dirs[@]}; do
        echo $d
        currVars=($(find ${d} -name "*.bin" | xargs -n 1 basename | awk -F'_chunk' '{print $1}' | sort))

        if [[ "${vars[@]}" != "${currVars[@]}" ]]; then
            echo "The list of variables in the dir: "
            echo "${d}"
            echo "is :"
            echo "${currVars[@]}"
            echo "and it does not match the expected list:"
            echo "${vars[@]}"
            exit
        fi
    done

    echo "All folders are valids, starting to concat..."

    mkdir ${outFolder}
    cp ${dirs[0]}/metadata.txt ${outFolder}
    for v in ${vars[@]}; do
        cmd="cat " 
        for d in ${dirs[@]}; do
            cmd+="${d}/${v}_chunk0.bin "
        done
        cmd+=" > ${outFolder}/${v}_chunk0.bin"
        eval $cmd
        if (( "$?" != 0 )); then
            echo "Command: $cmd"
            echo "returned $?"
            echo "Abort !"
            exit
        fi
    done
}

if [ "$#" -lt 1 ]; then
    echo usage: ./concatBinary.sh folder
    exit
fi

folder=$1

subfolders=($(find ${folder} -mindepth 1 -type d))
vars=($(find ${subfolders[0]} -name "*.bin" | xargs -n 1 basename | awk -F'_chunk' '{print $1}' | sort ))

chunkSize=80
j=0
for ((i=0; i < ${#subfolders[@]}; i+=chunkSize)); do
    dirs="${subfolders[@]:i:chunkSize}"
    outFolder="output_$j"
    concat
    ((j++))
done


