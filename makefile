all: mabe

mabe: objectFiles/main.o objectFiles/Analyze_neurocorrelates.o objectFiles/Archivist_DefaultArchivist.o objectFiles/Brain_AbstractBrain.o objectFiles/Genome_AbstractGenome.o objectFiles/Global.o objectFiles/Group_Group.o objectFiles/Optimizer_AbstractOptimizer.o objectFiles/Organism_Organism.o objectFiles/Utilities_Data.o objectFiles/Utilities_MTree.o objectFiles/Utilities_Parameters.o objectFiles/Utilities_Loader.o objectFiles/Utilities_Filesystem.o objectFiles/Utilities_CSV.o objectFiles/World_AbstractWorld.o objectFiles/World_DualWorld_DualWorld.o objectFiles/Genome_CircularGenome_CircularGenome.o objectFiles/Brain_BiLogBrain_BiLogBrain.o objectFiles/Optimizer_SimpleOptimizer_SimpleOptimizer.o objectFiles/Archivist_LODwAPArchivist_LODwAPArchivist.o objectFiles/Archivist_SSwDArchivist_SSwDArchivist.o
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source objectFiles/main.o objectFiles/Analyze_neurocorrelates.o objectFiles/Archivist_DefaultArchivist.o objectFiles/Brain_AbstractBrain.o objectFiles/Genome_AbstractGenome.o objectFiles/Global.o objectFiles/Group_Group.o objectFiles/Optimizer_AbstractOptimizer.o objectFiles/Organism_Organism.o objectFiles/Utilities_Data.o objectFiles/Utilities_MTree.o objectFiles/Utilities_Parameters.o objectFiles/Utilities_Loader.o objectFiles/Utilities_Filesystem.o objectFiles/Utilities_CSV.o objectFiles/World_AbstractWorld.o objectFiles/World_DualWorld_DualWorld.o objectFiles/Genome_CircularGenome_CircularGenome.o objectFiles/Brain_BiLogBrain_BiLogBrain.o objectFiles/Optimizer_SimpleOptimizer_SimpleOptimizer.o objectFiles/Archivist_LODwAPArchivist_LODwAPArchivist.o objectFiles/Archivist_SSwDArchivist_SSwDArchivist.o -o mabe

objectFiles/main.o: ./main.cpp
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source -c ./main.cpp -o objectFiles/main.o

objectFiles/Analyze_neurocorrelates.o: ./Analyze/neurocorrelates.cpp ./Analyze/neurocorrelates.h
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source -c ./Analyze/neurocorrelates.cpp -o objectFiles/Analyze_neurocorrelates.o

objectFiles/Archivist_DefaultArchivist.o: ./Archivist/DefaultArchivist.cpp ./Archivist/DefaultArchivist.h
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source -c ./Archivist/DefaultArchivist.cpp -o objectFiles/Archivist_DefaultArchivist.o

objectFiles/Brain_AbstractBrain.o: ./Brain/AbstractBrain.cpp ./Brain/AbstractBrain.h
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source -c ./Brain/AbstractBrain.cpp -o objectFiles/Brain_AbstractBrain.o

objectFiles/Genome_AbstractGenome.o: ./Genome/AbstractGenome.cpp ./Genome/AbstractGenome.h
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source -c ./Genome/AbstractGenome.cpp -o objectFiles/Genome_AbstractGenome.o

objectFiles/Global.o: ./Global.cpp ./Global.h
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source -c ./Global.cpp -o objectFiles/Global.o

objectFiles/Group_Group.o: ./Group/Group.cpp ./Group/Group.h
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source -c ./Group/Group.cpp -o objectFiles/Group_Group.o

objectFiles/Optimizer_AbstractOptimizer.o: ./Optimizer/AbstractOptimizer.cpp ./Optimizer/AbstractOptimizer.h
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source -c ./Optimizer/AbstractOptimizer.cpp -o objectFiles/Optimizer_AbstractOptimizer.o

objectFiles/Organism_Organism.o: ./Organism/Organism.cpp ./Organism/Organism.h
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source -c ./Organism/Organism.cpp -o objectFiles/Organism_Organism.o

objectFiles/Utilities_Data.o: ./Utilities/Data.cpp ./Utilities/Data.h
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source -c ./Utilities/Data.cpp -o objectFiles/Utilities_Data.o

objectFiles/Utilities_MTree.o: ./Utilities/MTree.cpp ./Utilities/MTree.h
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source -c ./Utilities/MTree.cpp -o objectFiles/Utilities_MTree.o

objectFiles/Utilities_Parameters.o: ./Utilities/Parameters.cpp ./Utilities/Parameters.h
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source -c ./Utilities/Parameters.cpp -o objectFiles/Utilities_Parameters.o

objectFiles/Utilities_Loader.o: ./Utilities/Loader.cpp ./Utilities/Loader.h
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source -c ./Utilities/Loader.cpp -o objectFiles/Utilities_Loader.o

objectFiles/Utilities_Filesystem.o: ./Utilities/Filesystem.cpp ./Utilities/Filesystem.h
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source -c ./Utilities/Filesystem.cpp -o objectFiles/Utilities_Filesystem.o

objectFiles/Utilities_CSV.o: ./Utilities/CSV.cpp ./Utilities/CSV.h
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source -c ./Utilities/CSV.cpp -o objectFiles/Utilities_CSV.o

objectFiles/World_AbstractWorld.o: ./World/AbstractWorld.cpp ./World/AbstractWorld.h
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source -c ./World/AbstractWorld.cpp -o objectFiles/World_AbstractWorld.o

objectFiles/World_DualWorld_DualWorld.o: ./World/DualWorld/DualWorld.cpp ./World/DualWorld/DualWorld.h
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source -c ./World/DualWorld/DualWorld.cpp -o objectFiles/World_DualWorld_DualWorld.o

objectFiles/Genome_CircularGenome_CircularGenome.o: ./Genome/CircularGenome/CircularGenome.cpp ./Genome/CircularGenome/CircularGenome.h
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source -c ./Genome/CircularGenome/CircularGenome.cpp -o objectFiles/Genome_CircularGenome_CircularGenome.o

objectFiles/Brain_BiLogBrain_BiLogBrain.o: ./Brain/BiLogBrain/BiLogBrain.cpp ./Brain/BiLogBrain/BiLogBrain.h
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source -c ./Brain/BiLogBrain/BiLogBrain.cpp -o objectFiles/Brain_BiLogBrain_BiLogBrain.o

objectFiles/Optimizer_SimpleOptimizer_SimpleOptimizer.o: ./Optimizer/SimpleOptimizer/SimpleOptimizer.cpp ./Optimizer/SimpleOptimizer/SimpleOptimizer.h
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source -c ./Optimizer/SimpleOptimizer/SimpleOptimizer.cpp -o objectFiles/Optimizer_SimpleOptimizer_SimpleOptimizer.o

objectFiles/Archivist_LODwAPArchivist_LODwAPArchivist.o: ./Archivist/LODwAPArchivist/LODwAPArchivist.cpp ./Archivist/LODwAPArchivist/LODwAPArchivist.h
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source -c ./Archivist/LODwAPArchivist/LODwAPArchivist.cpp -o objectFiles/Archivist_LODwAPArchivist_LODwAPArchivist.o

objectFiles/Archivist_SSwDArchivist_SSwDArchivist.o: ./Archivist/SSwDArchivist/SSwDArchivist.cpp ./Archivist/SSwDArchivist/SSwDArchivist.h
	c++ -Wno-c++98-compat -w -Wall -std=c++17 -O3 -lpthread -pthread -I/home/nadine/workspace/Empirical/source -c ./Archivist/SSwDArchivist/SSwDArchivist.cpp -o objectFiles/Archivist_SSwDArchivist_SSwDArchivist.o

clean:
	rm -r objectFiles/* mabe

cleanup:
	rm -r objectFiles/*
