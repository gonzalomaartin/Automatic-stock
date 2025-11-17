all: main.cpp ./libs/Algorithms.o ./libs/order.o ./libs/container.o ./libs/box.o ./libs/shipment.o ./libs/target.o
	g++ -o ./bin/main main.cpp libs/Algorithms.o libs/order.o libs/container.o libs/box.o libs/shipment.o libs/target.o

all2: main2.cpp ./libs/Algorithms2.o ./libs/order.o ./libs/container2.o ./libs/box2.o ./libs/shipment.o ./libs/target.o
	g++ -o ./bin/main2 main2.cpp libs/Algorithms2.o libs/order.o libs/container2.o libs/box2.o libs/shipment.o libs/target.o
	
libs/Algorithms.o: ./src/bodies/Algorithms.cpp ./src/headers/Algorithms.h ./libs/container.o ./libs/order.o ./libs/shipment.o ./libs/target.o
	g++ -c ./src/bodies/Algorithms.cpp -o ./libs/Algorithms.o 

libs/Algorithms2.o: ./src/bodies/Algorithms2.cpp ./src/headers/Algorithms2.h ./libs/container2.o ./libs/order.o ./libs/shipment.o ./libs/target.o
	g++ -c ./src/bodies/Algorithms2.cpp -o ./libs/Algorithms2.o 

libs/target.o: ./src/bodies/target.cpp ./src/headers/target.h
	g++ -c ./src/bodies/target.cpp -o ./libs/target.o

libs/shipment.o: ./src/bodies/shipment.cpp ./src/headers/shipment.h ./libs/box.o ./libs/container.o 
	g++ -c ./src/bodies/shipment.cpp -o ./libs/shipment.o

libs/order.o: ./src/bodies/order.cpp ./src/headers/order.h ./libs/box.o
	g++ -c ./src/bodies/order.cpp -o ./libs/order.o

libs/container.o: ./src/bodies/container.cpp ./src/headers/container.h ./libs/box.o
	g++ -c ./src/bodies/container.cpp -o ./libs/container.o

libs/container2.o: ./src/bodies/container2.cpp ./src/headers/container2.h ./libs/box2.o
	g++ -c ./src/bodies/container2.cpp -o ./libs/container2.o

libs/box.o: ./src/bodies/box.cpp ./src/headers/box.h
	g++ -c ./src/bodies/box.cpp -o ./libs/box.o

libs/box2.o: ./src/bodies/box2.cpp ./src/headers/box2.h
	g++ -c ./src/bodies/box2.cpp -o ./libs/box2.o

.PHONY: clean

clean:
	rm -f main	