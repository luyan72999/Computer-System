for file in "test_cases"/*; do
    if [ -f "$file" ]; then
        filename=$(basename -- "$file")
        echo $filename
        
        ./a.out "test_cases/$filename" >> "results/lru_var_10entries_new.txt"
        
        echo ""
    fi
done
