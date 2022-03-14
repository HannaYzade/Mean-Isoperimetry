for (( i=1; i<51; i++ )) do
	echo "diff $i"
	diff Outputs/"DP Outputs"/output$i.txt Outputs/"Brute Force Outputs"/output$i.txt
done