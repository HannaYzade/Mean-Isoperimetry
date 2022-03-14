#creating outputs of brute force algorithm
g++ -std=c++17 -O2 "Brute Force Algorithm"/brute_force_code.cpp -o "Brute Force Algorithm"/brute_force_code
echo "running brute_force_code.cpp"
for (( i=1; i<51; i++ )) do
	echo "test $i"
	SECONDS=0
	"Brute Force Algorithm"/brute_force_code < Inputs/input$i.txt > Outputs/"Brute Force Outputs"/output$i.txt
	duration=$SECONDS
	echo "it took $(($duration / 60)) m and $(($duration % 60)) s to run test $i"
done

#creating outputs of dp algorithm
g++ -std=c++17 -O2 ../"DP Algorithm"/main.cpp -o ../"DP Algorithm"/main
echo "running main.cpp"
for (( i=1; i<51; i++ )) do
	echo "test $i"
	SECONDS=0
	../"DP Algorithm"/main < Inputs/input$i.txt > Outputs/"DP Outputs"/output$i.txt
	duration=$SECONDS
	echo "it took $(($duration / 60)) m and $(($duration % 60)) s to run test $i"
done
