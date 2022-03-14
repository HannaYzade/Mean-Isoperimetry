g++ -std=c++17 -O2 test_generator.cpp -o test_generator
for (( i=1; i<51; i++ )) do
	./test_generator $i > Inputs/input$i.txt
done
